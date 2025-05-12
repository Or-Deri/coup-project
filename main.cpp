// main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>
#include <map>

#include "Game.hpp"
#include "Player.hpp"
#include "PlayerFactory.cpp"
#include "Governor.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"

using namespace std;
using namespace coup;

// פונקציית עזר לטעינת פונטים
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

// פונקציית עזר לציור כפתורים
void drawButton(sf::RenderWindow& window, sf::RectangleShape& button, sf::Text& label) {
    window.draw(button);
    window.draw(label);
}

int main() {
    Game game;
    vector<unique_ptr<Player>> players;

    sf::RenderWindow window(sf::VideoMode(1000, 700), "Coup Game - SFML GUI");
    sf::Font font = loadFont();

    enum Screen { MENU, NAME_INPUT, GAME, SELECT_TARGET, UNDO_PROMPT, UNDO_SELECT_TARGET } screen = MENU;
    string currentInput, pendingAction;
    Player* selectedTarget = nullptr;
    Player* lastActor = nullptr;
    Player* undoResponder = nullptr;

    // כפתורים למסך הראשי
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

    vector<string> actions = {"gather", "tax", "bribe", "invest", "coup", "arrest", "sanction", "undo"};
    vector<sf::RectangleShape> actionButtons;
    vector<sf::Text> actionLabels;

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

    sf::Text turnText("", font, 22);
    turnText.setPosition(400, 30);
    turnText.setFillColor(sf::Color::White);

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
                    screen = GAME;
                    game.currentPlayer()->startTurn();
                }
            }

            if (screen == UNDO_PROMPT && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                if (yesBtn.getGlobalBounds().contains(mouse)) {
                    if (auto* g = dynamic_cast<General*>(undoResponder)) g->undo(*lastActor);
                    else if (auto* gov = dynamic_cast<Governor*>(undoResponder)) gov->undo(*lastActor);
                    else if (auto* j = dynamic_cast<Judge*>(undoResponder)) j->undo(*lastActor);
                    else if (auto* s = dynamic_cast<Spy*>(undoResponder)) s->blockArrest(*lastActor);
                    screen = GAME;
                } else if (noBtn.getGlobalBounds().contains(mouse)) {
                    screen = GAME;
                }
            }

            if (screen == SELECT_TARGET && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                for (size_t i = 0; i < targetButtons.size(); ++i) {
                    if (targetButtons[i].getGlobalBounds().contains(mouse)) {
                        Player* current = game.currentPlayer();
                        Player* chosen = targetRefs[i];
                        try {
                            if (pendingAction == "coup") current->coup(*chosen);
                            else if (pendingAction == "arrest") {
                                current->arrest(*chosen);
                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<Spy*>(p.get())) {
                                        undoResponder = p.get();
                                        lastActor = chosen;
                                        screen = UNDO_PROMPT;
                                        break;
                                    }
                                }
                            }
                            else if (pendingAction == "sanction") current->sanction(*chosen);
                        } catch (...) {}
                        screen = GAME;
                        break;
                    }
                }
            }

            if (screen == GAME && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                for (size_t i = 0; i < actionButtons.size(); ++i) {
                    if (actionButtons[i].getGlobalBounds().contains(mouse)) {
                        string action = actions[i];
                        Player* current = game.currentPlayer();
                        if (current->coins() >= 10) {
                            pendingAction = "coup";                                // חייב לבצע Coup → הצג בחירת יעד
                    
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
                        screen = SELECT_TARGET;
                        continue;  // לא מאפשר לבצע שום פעולה אחרת
                        }

                        
                        try {
                            if (action == "gather") current->gather();
                            else if (action == "tax") {
                                current->tax();
                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<Governor*>(p.get())) {
                                        undoResponder = p.get();
                                        lastActor = current;
                                        screen = UNDO_PROMPT;
                                        break;
                                    }
                                }
                            }
                            else if (action == "bribe") {
                                current->bribe();
                                for (auto& p : players) {
                                    if (p.get() != current && dynamic_cast<Judge*>(p.get())) {
                                        undoResponder = p.get();
                                        lastActor = current;
                                        screen = UNDO_PROMPT;
                                        break;
                                    }
                                }
                            }
                            else if (action == "invest") {
                                if (auto* b = dynamic_cast<Baron*>(current)) b->invest();
                            }
                            else if (action == "undo") {
                                undoResponder = current;
                                lastActor = game.getLastPlayer();
                                screen = UNDO_PROMPT;
                            }
                            else if (action == "arrest" || action == "sanction" || action == "coup") {
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
                                screen = SELECT_TARGET;
                            }
                        } catch (std::exception& e) {
                            cerr << "Action error: " << e.what() << endl;
                        }
                        break;
                    }
                }
            }
        }

        window.clear();

        if (screen == MENU) {
            drawButton(window, addBtn, addLabel);
            drawButton(window, startBtn, startLabel);
        } else if (screen == NAME_INPUT) {
            inputText.setString(currentInput);
            window.draw(prompt);
            window.draw(inputText);
        } else if (screen == GAME) {
            turnText.setString("Turn: " + game.turn());
            window.draw(turnText);
            for (size_t i = 0; i < actionButtons.size(); ++i) {
                drawButton(window, actionButtons[i], actionLabels[i]);
            }
            float y = 400;
            for (auto& p : players) {
                if (p->isInGame()) {
                    sf::Text status(p->getName() + " - " + roleName(p.get()) + " (" + to_string(p->coins()) + " coins)", font, 18);
                    status.setPosition(600, y);
                    status.setFillColor(sf::Color::White);
                    window.draw(status);
                    y += 30;
                }
            }
        } else if (screen == SELECT_TARGET || screen == UNDO_SELECT_TARGET) {
            for (size_t i = 0; i < targetButtons.size(); ++i) {
                drawButton(window, targetButtons[i], targetLabels[i]);
            }
        } else if (screen == UNDO_PROMPT) {
            undoPromptText.setString(undoResponder->getName() + ": Undo this action?");
            window.draw(undoPromptText);
            drawButton(window, yesBtn, yesLbl);
            drawButton(window, noBtn, noLbl);
        }

        window.display();
    }

    return 0;
}

