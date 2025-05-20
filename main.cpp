#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>
#include <map>

#include "Game.hpp"
#include "Player.hpp"
#include "PlayerFactory.hpp"
#include "Governor.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"

using namespace std;
using namespace coup;

sf::Font loadFont() {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("Missing font file 'arial.ttf'");
    }
    return font;
}

// תרגום סוג שחקן למחרוזת
string roleName(Player* p) {
    if (dynamic_cast<Governor*>(p)) return "Governor";
    if (dynamic_cast<General*>(p)) return "General";
    if (dynamic_cast<Judge*>(p)) return "Judge";
    if (dynamic_cast<Spy*>(p)) return "Spy";
    if (dynamic_cast<Baron*>(p)) return "Baron";
    if (dynamic_cast<Merchant*>(p)) return "Merchant";
    return "Unknown";
}

void drawButton(sf::RenderWindow& window, sf::RectangleShape& button, sf::Text& label) {
    window.draw(button);
    window.draw(label);
}

int main() {
    Game game;
    vector<unique_ptr<Player>> players;
    std::vector<Player*> pendingUndoResponders;
    string currentTurnPlayerName = "";


    sf::RenderWindow window(sf::VideoMode(1000, 700), "Coup Game - SFML GUI");
    sf::Font font = loadFont();

    enum Screen { MENU, NAME_INPUT, GAME, SELECT_TARGET, UNDO_PROMPT, UNDO_SELECT_TARGET ,WINNER_SCREEN } screen = MENU;
    string currentInput, pendingAction;
    Player* lastActor = nullptr;
    Player* undoResponder = nullptr;

    sf::RectangleShape addBtn(sf::Vector2f(200, 50));
    addBtn.setPosition(400, 200);
    addBtn.setFillColor(sf::Color::Green);
    sf::Text addLabel("Add Player", font, 20);
    addLabel.setPosition(440, 215);
    addLabel.setFillColor(sf::Color::Black);

    sf::RectangleShape startBtn(sf::Vector2f(200, 50));
    startBtn.setPosition(400, 300);
    startBtn.setFillColor(sf::Color::Blue);
    sf::Text startLabel("Start Game", font, 20);
    startLabel.setPosition(440, 315);
    startLabel.setFillColor(sf::Color::White);

    sf::Text prompt("Enter name:", font, 20);
    prompt.setPosition(420, 100);
    prompt.setFillColor(sf::Color::White);
    sf::Text inputText("", font, 20);
    inputText.setPosition(420, 150);
    inputText.setFillColor(sf::Color::Cyan);

    sf::RectangleShape inputBox(sf::Vector2f(300, 40));
    inputBox.setPosition(415, 145);
    inputBox.setFillColor(sf::Color(50, 50, 50)); // צבע רקע כהה
    vector<string> actions;
    vector<sf::RectangleShape> actionButtons;
    vector<sf::Text> actionLabels;

    sf::Text turnText("", font, 22);
    turnText.setPosition(400, 30);
    turnText.setFillColor(sf::Color::Black);

    vector<sf::RectangleShape> targetButtons;
    vector<sf::Text> targetLabels;
    vector<Player*> targetRefs;

    sf::RectangleShape yesBtn(sf::Vector2f(100, 40));
    yesBtn.setPosition(300, 300);
    yesBtn.setFillColor(sf::Color::Green);
    sf::Text yesLbl("Yes", font, 20);
    yesLbl.setPosition(330, 310);

    sf::RectangleShape noBtn(sf::Vector2f(100, 40));
    noBtn.setPosition(500, 300);
    noBtn.setFillColor(sf::Color::Red);
    sf::Text noLbl("No", font, 20);
    noLbl.setPosition(540, 310);

    sf::Text undoPromptText("", font, 24);
    undoPromptText.setPosition(350, 200);
    undoPromptText.setFillColor(sf::Color::White);

    sf::Text winnerText("", font, 30);
    winnerText.setPosition(350, 300);
    winnerText.setFillColor(sf::Color::Yellow);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (screen == NAME_INPUT && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !currentInput.empty()) {
                    currentInput.pop_back();
                } else if (event.text.unicode == '\n' || event.text.unicode == '\r') {
                    if (!currentInput.empty()) {
                        Player* p = PlayerFactory::createRandomPlayer(game, currentInput);
                        players.push_back(unique_ptr<Player>(p));
                    }
                    currentInput.clear();
                    screen = MENU;
                } else if (event.text.unicode < 128 && isprint(event.text.unicode)) {
                    currentInput += static_cast<char>(event.text.unicode);
                }
                continue;
            }

            if (screen == MENU && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                if (addBtn.getGlobalBounds().contains(mouse) && players.size() < 6) {
                    screen = NAME_INPUT;
                } else if (startBtn.getGlobalBounds().contains(mouse) && players.size() >= 2) {
                    if (!game.players().empty()) {
                        std::cout << "[DEBUG] Game players in memory after start:" << std::endl;
                        for (Player* p : game.getPlaersList()) { 
                            std::cout << " - " << p->getName() << " | addr: " << p;
                            if (dynamic_cast<Judge*>(p)) std::cout << " [JUDGE]";
                            std::cout << std::endl;
                        }
                        screen = GAME;
                        game.currentPlayer()->startTurn();
                    } else {
                        std::cerr << "No players in the game (game.players() is empty)!" << std::endl;
                    }
                }
            }

            if (screen == UNDO_PROMPT && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (yesBtn.getGlobalBounds().contains(mouse)) {
                    if (auto* g = dynamic_cast<General*>(undoResponder)){
                        try{
                            g->undo(*game.getLastTarget());
                            std::cout << g->getName() << " undo the coup " <<std::endl;

                            game.nextTurn();
                            pendingUndoResponders.clear();
                            screen = GAME;
                            currentTurnPlayerName = ""; 
                        }catch(std::exception& e){
                            
                            game.nextTurn();
                            pendingUndoResponders.clear();
                            screen = GAME;
                        }
                    }
                    else if (auto* gov = dynamic_cast<Governor*>(undoResponder)){
                        try{
                            gov->undo(*game.getLastTarget());
                            std::cout << gov->getName() << " undo the tax " <<std::endl;

                            game.nextTurn();
                            screen = GAME;
                        }catch (std::exception& e) {
                            std::cerr << "Undo error: " << e.what() << std::endl;
                            game.nextTurn();
                            pendingUndoResponders.clear();
                            screen = GAME;
                        }
                    }
                    else if (auto* j = dynamic_cast<Judge*>(undoResponder)){ 
                        try{
                            std::cout << "[DEBUG] Judge clicked yes" << std::endl;
                            
                            
                            j->undo(*game.getLastTarget());
                            std::cout << j->getName() << " undo the bribe " <<std::endl;
                            game.nextTurn();
                            
                            screen = GAME;
                        }catch(std::exception& e){
                            std::cerr << "Undo error: " << e.what() << std::endl;
                            game.nextTurn();
                            pendingUndoResponders.clear();
                            screen = GAME;
                        }
                    }
          
                    pendingUndoResponders.clear();
                    screen = GAME;
                
                }

                else if (noBtn.getGlobalBounds().contains(mouse)) {
                    if (!pendingUndoResponders.empty()) {
                        pendingUndoResponders.erase(pendingUndoResponders.begin());
                    }
                    if (!pendingUndoResponders.empty()) {
                        undoResponder = pendingUndoResponders.front();
                        screen = UNDO_PROMPT;
                    } else {
                        
                        if (game.turn() == lastActor->getName()) {
                            game.nextTurn();
                        }
                        screen = GAME;
                    }
                }
            }

            if (screen == SELECT_TARGET && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                for (size_t i = 0; i < targetButtons.size(); ++i) {
                    if (targetButtons[i].getGlobalBounds().contains(mouse)) {
                        
                        if (targetRefs.empty() || i >= targetRefs.size()) {
                            screen = GAME;
                            break;
                        }
                        
                        
                        Player* current = game.currentPlayer();
                        Player* chosen = targetRefs[i];
                        try {
                            if (pendingAction == "coup") {
                                current->coup(*chosen);
                                std::cout << current->getName() <<" make coup on " << chosen->getName() << "\n";

                                std::vector<Player*> generals;
                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<General*>(p.get())) {
                                        generals.push_back(p.get());
                                    }
                                }
                                if (!generals.empty()) {
                                    pendingUndoResponders = generals;
                                    undoResponder = pendingUndoResponders.front();
                                    lastActor = current;
                                    screen = UNDO_PROMPT;
                                    break;
                                } else {
                                    game.nextTurn(); 
                                }
                            }
                            else if (pendingAction == "tax") {
                                current->tax();
                                std::cout << current->getName() <<" make tax "<< "\n";

                                std::vector<Player*> governor;
                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<Governor*>(p.get())) {
                                        governor.push_back(p.get());
                                    }
                                }
                                if (!governor.empty()) {
                                    pendingUndoResponders = governor;
                                    undoResponder = pendingUndoResponders.front();
                                    lastActor = current;
                                    screen = UNDO_PROMPT;
                                    break;
                                } else {
                                    game.nextTurn();
                                    screen = GAME;
                                }
                            }
                            else if (pendingAction == "bribe") {
                                current->bribe();
                                std::cout << current->getName() <<" make bribe "<< "\n";

                                bool foundJudge = false;
                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<Judge*>(p.get())) {
                                        undoResponder = p.get();
                                        lastActor = current;
                                        screen = UNDO_PROMPT;
                                        foundJudge = true;
                                        break;
                                    }
                                }

                                if (!foundJudge) {
                                    game.nextTurn(); 
                                    screen = GAME;
                                }
                            }
                            else if (pendingAction == "arrest") {

                                if(chosen != game.currentPlayer()->getLastTargetArrest()){
                                    current->arrest(*chosen);
                                    std::cout << current->getName() <<" make arrest on " << chosen->getName() << "\n";
                                    game.nextTurn();
                                    screen = GAME;
                                }
                                else{
                                    std::cerr << "[ERROR] You can't arrest the same player twice in a row" << std::endl;
                                    screen = GAME;
                                    pendingAction = "";
                                }

                            }
                            else if (pendingAction == "sanction") {
                                current->sanction(*chosen);
                                std::cout << current->getName() <<" make sanction on " << chosen->getName() << "\n";
                                game.nextTurn(); // =====---====
                                screen = GAME;
                            }
                            else if (pendingAction == "block arrest") {
                                if (auto* s = dynamic_cast<Spy*>(current)) {
                                    s->blockArrest(*chosen);
                                    std::cout << current->getName() <<" make block arrest on " << chosen->getName() << "\n";
                                    game.nextTurn(); // =====---====
                                    screen = GAME;
                                }


                            }

                        
                            if (screen != UNDO_PROMPT) {
                                screen = GAME;
                            }
                        } catch (std::exception& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                            game.nextTurn(); 
                            screen = GAME;
                        }

                        break;
                    }
                }
            }

            if (screen == GAME && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                for (size_t i = 0; i < actionButtons.size(); ++i) {
                    if (actionButtons[i].getGlobalBounds().contains(mouse)) {
                        string action = actions[i];
                        std::cout << "Clicked on action: " << action << std::endl;
                        Player* current = game.currentPlayer();
                        
                        // if (current->coins() >= 10) {
                        //     pendingAction = "coup";                                // חייב לבצע Coup → הצג בחירת יעד
                    
                        //     targetButtons.clear();
                        //     targetLabels.clear();
                        //     targetRefs.clear();
                        //     for (auto& p : players) {
                        //         if (p.get() != current && p->isInGame()) {
                        //             sf::RectangleShape btn(sf::Vector2f(120, 40));
                        //             btn.setPosition(400, 150 + targetButtons.size() * 50);
                        //             targetButtons.push_back(btn);

                        //             sf::Text lbl(p->getName(), font, 18);
                        //             lbl.setPosition(410, 160 + targetLabels.size() * 50);
                        //             lbl.setFillColor(sf::Color::Black);
                        //             targetLabels.push_back(lbl);

                        //             targetRefs.push_back(p.get());
                        //         }
                        //     }
                        // screen = SELECT_TARGET;
                        // continue;  
                        // }

                        
                        try {
                            if (action == "gather"){
                                current->gather();
                                std::cout << current->getName() << " make gather " <<std::endl;

                                game.nextTurn();
                            }
                            else if (action == "tax") {
                                current->tax();
                                std::cout << current->getName() << " make tax " <<std::endl;

                                bool findPlayer = false;
                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<Governor*>(p.get())) {
                                        findPlayer = true;
                                        undoResponder = p.get();
                                        lastActor = current;
                                        screen = UNDO_PROMPT;
                                        break;
                                    }
                                }
                                if(!findPlayer){
                                    game.nextTurn();
                                }
                            }
                            else if (action == "bribe") {
                                bool findPlayer = false;
                                current->bribe();
                                std::cout << current->getName() << " make bribe " <<std::endl;

                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<Judge*>(p.get())) {
                                        findPlayer = true;
                                        undoResponder = p.get();
                                        lastActor = current;
                                        screen = UNDO_PROMPT;
                                        break;
                                    }
                                }
                                if(!findPlayer){
                                    game.nextTurn();
                                }
                            }
                            else if (action == "invest") {
                                if (auto* b = dynamic_cast<Baron*>(current)){
                                    b->invest();
                                    std::cout << current->getName() << " make invest " <<std::endl;

                                    game.nextTurn();
                                }
                            }
                            else if (action == "undo") {
                                undoResponder = current;
                                lastActor = game.getLastPlayer();
                                screen = UNDO_PROMPT;
                            }
                            else if (action == "arrest" || action == "sanction" || action == "coup" || action == "block arrest") {
                                pendingAction = action;
                                targetButtons.clear();
                                targetLabels.clear();
                                targetRefs.clear();
                                for (auto& p : players) {
                                    if (p.get() != current && p->isInGame()) {
                                        sf::RectangleShape btn(sf::Vector2f(120, 40));
                                        btn.setPosition(400, 150 + targetButtons.size() * 50);
                                        targetButtons.push_back(btn);

                                        sf::Text lbl(p->getName(), font, 18);
                                        lbl.setPosition(410, 160 + targetLabels.size() * 50);
                                        lbl.setFillColor(sf::Color::Black);
                                        targetLabels.push_back(lbl);

                                        targetRefs.push_back(p.get());
                                    }
                                }
                                std::cout << "Targets found: " << targetRefs.size() << std::endl;
                                if (targetRefs.empty()) {
                                    std::cerr << "No valid targets for action: " << action << std::endl;                                    
                                    screen = GAME;
                                } else {
                                    std::cout << "[DEBUG] switching to SELECT_TARGET for " << action << std::endl;
                                    screen = SELECT_TARGET;

                                }
                            }
                            else if (action == "pass") {
                                try {
                                    current->pass();
                                } catch (std::exception& e) {
                                    cerr << "Pass error: " << e.what() << endl;
                                }
                            }
                        } catch (std::exception& e) {
                            cerr << "Action error: " << e.what() << endl;
                        }
                        break;
                    }
                }
            }
        }

        window.clear(sf::Color(200, 200, 200)); 

        if (screen == MENU) {
            drawButton(window, addBtn, addLabel);
            drawButton(window, startBtn, startLabel);
        } else if (screen == NAME_INPUT) {
            inputText.setString(currentInput);
            window.draw(inputBox); 
            window.draw(prompt);
            window.draw(inputText);
        } else if (screen == GAME) {
    
            if (game.players().size() > 1) {
                Player* current = game.currentPlayer();

                if (current->getName() != currentTurnPlayerName ) {
                    currentTurnPlayerName = current->getName();
                    
                    actions.clear();
                    actionButtons.clear();
                    actionLabels.clear();

                    if (current->coins() >= 10) {
                        actions.push_back("coup");
                    }
                    else {
                    
                        if (dynamic_cast<Baron*>(current) || !current->isSanctionBlocked()) {
                            actions.push_back("gather");
                            actions.push_back("tax");
                        }
                        if(current->coins() >= 4){
                            actions.push_back("bribe");
                        }
                        if(current->coins() >= 3){
                            actions.push_back("sanction");
                        }
                        if (current->coins() >= 7) {
                            actions.push_back("coup");
                        }
                        if (!current->isArrestBlocked()) {
                            actions.push_back("arrest");
                        }
                        if (dynamic_cast<Baron*>(current) && current->coins() >= 3){
                            actions.push_back("invest");
                        }
                        if (dynamic_cast<Spy*>(current)) {
                            actions.push_back("block arrest");
                        }

                        if (actions.empty()) {
                            actions.push_back("pass");
                        }

                    }

                    actionButtons.clear();
                    actionLabels.clear();
                    for (size_t i = 0; i < actions.size(); ++i) {
                        sf::RectangleShape btn(sf::Vector2f(150, 40));
                        btn.setPosition(50, 100 + i * 50);
                        btn.setFillColor(sf::Color::Green);
                        actionButtons.push_back(btn);

                        sf::Text label(actions[i], font, 18);
                        label.setPosition(60, 110 + i * 50);
                        label.setFillColor(sf::Color::Black);
                        actionLabels.push_back(label);
                    }
                
                }
                turnText.setString("Turn: " + game.turn());
            }
            else if (game.players().size() == 1){
                turnText.setString("The winner is" + game.winner());
            }
            window.draw(turnText);
            for (size_t i = 0; i < actionButtons.size(); ++i) {
                drawButton(window, actionButtons[i], actionLabels[i]);
            }

            float y = 400;

            Player* current = game.currentPlayer();
            bool isSpy = dynamic_cast<Spy*>(current);
            for (auto& p : players) {
                if (p->isInGame()) {

                    std::string coinInfo;
                    
                    if (p.get() == current) {
                        coinInfo = " (" + std::to_string(p->coins()) + " coins)";
                    }
                    else if (isSpy) {
                        coinInfo = " (" + std::to_string(p->coins()) + " coins)";
                    }
                    else {
                        coinInfo = " (-- coins)";
                    }

                    sf::Text status(p->getName() + " - " + roleName(p.get()) + coinInfo, font, 18);
                    status.setPosition(600, y);
                    status.setFillColor(sf::Color::Black);
                    window.draw(status);
                    y += 30;
                }
            }
            if (game.players().size() == 1) {
                try {
                    std::string winner = game.winner();
                    winnerText.setString("Winner: " + winner);
                    screen = WINNER_SCREEN;
                } catch (...) {
                    
                }
            }
        } else if (screen == SELECT_TARGET || screen == UNDO_SELECT_TARGET) {
            for (size_t i = 0; i < targetButtons.size(); ++i) {
                drawButton(window, targetButtons[i], targetLabels[i]);
            }
        } else if (screen == UNDO_PROMPT) {
            undoPromptText.setString(undoResponder->getName() + " : Undo this action? ( " +game.getLastAction()+ ")");
            window.draw(undoPromptText);
            drawButton(window, yesBtn, yesLbl);
            drawButton(window, noBtn, noLbl);
        }
        else if (screen == WINNER_SCREEN) {
            window.draw(winnerText);
        }

        window.display();
    }

    return 0;
}

