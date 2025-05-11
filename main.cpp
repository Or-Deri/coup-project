#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>

#include "Game.hpp"
#include "Player.hpp"
#include "PlayerFactory.cpp"
#include "Governor.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Spy.hpp"

using namespace std;
using namespace coup;

int main() {
    Game game;
    vector<unique_ptr<Player>> players;

    for (int i = 1; i <= 4; ++i) {
        string name = "Player" + to_string(i);
        Player* p = PlayerFactory::createRandomPlayer(game, name);
        players.push_back(unique_ptr<Player>(p));
    }

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Coup Game - GUI");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Missing font file 'arial.ttf'\n";
        return 1;
    }

    sf::Text title("Coup Game", font, 30);
    title.setPosition(400, 10);
    title.setFillColor(sf::Color::White);

    sf::Text playerTurnText("", font, 24);
    playerTurnText.setPosition(100, 60);
    playerTurnText.setFillColor(sf::Color::Cyan);

    vector<pair<string, sf::RectangleShape>> actions = {
        {"gather", sf::RectangleShape(sf::Vector2f(160, 40))},
        {"tax", sf::RectangleShape(sf::Vector2f(160, 40))},
        {"bribe", sf::RectangleShape(sf::Vector2f(160, 40))},
        {"invest", sf::RectangleShape(sf::Vector2f(160, 40))},
        {"coup", sf::RectangleShape(sf::Vector2f(160, 40))},
        {"undo", sf::RectangleShape(sf::Vector2f(160, 40))},
        {"spy_view", sf::RectangleShape(sf::Vector2f(160, 40))},
        {"spy_block", sf::RectangleShape(sf::Vector2f(160, 40))}
    };

    vector<sf::Text> actionLabels;

    for (size_t i = 0; i < actions.size(); ++i) {
        actions[i].second.setPosition(100, 120 + i * 50);
        actions[i].second.setFillColor(sf::Color::Green);

        sf::Text label(actions[i].first, font, 18);
        label.setPosition(110, 125 + i * 50);
        label.setFillColor(sf::Color::Black);
        actionLabels.push_back(label);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                Player* current = game.currentPlayer();

                try {
                    for (size_t i = 0; i < actions.size(); ++i) {
                        if (actions[i].second.getGlobalBounds().contains(mouse)) {
                            const string& act = actions[i].first;

                            if (act == "gather") current->gather();
                            else if (act == "tax") current->tax();
                            else if (act == "bribe") current->bribe();
                            else if (act == "invest") {
                                if (auto* b = dynamic_cast<Baron*>(current)) b->invest();
                            }
                            else if (act == "coup") {
                                for (auto& p : players) {
                                    if (p.get() != current && p->isInGame()) {
                                        current->coup(*p);
                                        break;
                                    }
                                }
                            }
                            else if (act == "undo") {
                                if (auto* g = dynamic_cast<General*>(current)) {
                                    Player* target = game.getLastPlayer();
                                    if (target) {
                                        g->setUndo(true);
                                        g->undo(*target);
                                    }
                                }
                                if (auto* gov = dynamic_cast<Governor*>(current)) {
                                    Player* target = game.getLastPlayer();
                                    if (target) {
                                        gov->setUndo(true);
                                        gov->undo(*target);
                                    }
                                }
                                if (auto* j = dynamic_cast<Judge*>(current)) {
                                    Player* target = game.getLastPlayer();
                                    if (target) {
                                        j->setUndo(true);
                                        j->undo(*target);
                                    }
                                }
                            }
                            else if (act == "spy_view") {
                                if (auto* spy = dynamic_cast<Spy*>(current)) {
                                    for (auto& p : players) {
                                        if (p.get() != current && p->isInGame()) {
                                            cout << "[Spy] " << p->getName() << " has " << spy->seeCoins(*p) << " coins.\n";
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (act == "spy_block") {
                                if (auto* spy = dynamic_cast<Spy*>(current)) {
                                    for (auto& p : players) {
                                        if (p.get() != current && p->isInGame()) {
                                            spy->blockArrest(*p);
                                            cout << "[Spy] Blocked arrest on " << p->getName() << endl;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }
        }

        playerTurnText.setString("Current Turn: " + game.turn());

        window.clear();
        window.draw(title);
        window.draw(playerTurnText);
        for (const auto& btn : actions) window.draw(btn.second);
        for (const auto& lbl : actionLabels) window.draw(lbl);
        window.display();
    }

    return 0;
}
