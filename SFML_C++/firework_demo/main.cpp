#include <SFML/Graphics.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <list>
#include <vector>
#include "includes/firework.hpp"
#include "includes/star.hpp"

namespace fs = std::filesystem;

namespace game_globals {
sf::RenderWindow rWindow;
sf::Clock cClock;
bool music_playing = false;
sf::Music music;
std::list<Firework*> fws;
std::vector<sf::Image*>* images;
std::list<Star*>* starList;
}  // namespace game_globals

/**
 * @brief Processes the events in the input-update-draw cycle. Very close to the "input" stage
 */
void process_events() {
    while (const std::optional event = game_globals::rWindow.pollEvent()) {
        // Window closing event
        if (event->is<sf::Event::Closed>()) {
            game_globals::rWindow.close();
        }
        // Left click (fire a rocket)
        if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonReleased>()) {
            game_globals::fws.push_back(
                new Firework(sf::Vector2f((int)(game_globals::rWindow.getSize().x / 2), (int)(game_globals::rWindow.getSize().y)),
                             sf::Vector2f(mouseButton->position.x, mouseButton->position.y), game_globals::images));
        }
        // M keyboard button (mute music)
        if (const auto* keyreleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyreleased->code == sf::Keyboard::Key::M) {
                if (game_globals::music_playing) {
                    game_globals::music.stop();
                    game_globals::music_playing = false;
                } else {
                    game_globals::music_playing = true;
                    game_globals::music.play();
                }
            }
        }
    }
}

/**
 * @brief Does some variable initialization. Consider this boilerplate.
 */
void initialize_game() {
    // Initialize the window
    game_globals::rWindow = sf::RenderWindow(sf::VideoMode({1280, 960}), "Fireworks!");
    // Initialize the dynamic starfield background
    game_globals::starList = new std::list<Star*>();
    for (int i = 0; i < 1000; ++i) {
        game_globals::starList->push_back(new Star(sf::Vector2f((rand() / (float)RAND_MAX) * game_globals::rWindow.getSize().x,
                                                                (rand() / (float)RAND_MAX) * game_globals::rWindow.getSize().y),
                                                   (rand() / (float)RAND_MAX) * 1.0f + 1.0));
    }
    // Initialize the game music
    if (!game_globals::music.openFromFile("./resources/music/track.ogg")) {
        std::cout << "Error while loading song" << std::endl;
        game_globals::music_playing = false;
    } else {
        game_globals::music_playing = true;
    }
    if (game_globals::music_playing) {
        game_globals::music.play();
    }
    // Getting patterns from the images
    game_globals::images = new std::vector<sf::Image*>();
    std::string path = "./resources/patterns/";
    for (auto p : fs::directory_iterator(path)) {
        sf::Image* tmp = new sf::Image();
        if (tmp->loadFromFile(p.path())) {
            game_globals::images->push_back(tmp);
        }
    }
    game_globals::rWindow.setFramerateLimit(60);
}

/**
 * @brief Update the game state.
 *
 * @param tElapsedTime How much time has passed since last frame
 */
void update_state(sf::Time tElapsedTime) {
    for (auto fw : game_globals::fws) {
        fw->update(tElapsedTime);
    }
    for (auto s : *game_globals::starList) {
        s->update(tElapsedTime);
    }
}

/**
 * @brief Draw stage of the "input-update-draw" pipeline.
 */
void draw() {
    game_globals::rWindow.clear(sf::Color::Black);
    for (auto fw : game_globals::fws) {
        game_globals::rWindow.draw(*fw);
    }
    for (auto s : *game_globals::starList) {
        game_globals::rWindow.draw(*s);
    }
    // game_globals::rWindow.draw(part);
    game_globals::rWindow.display();

    // Clean up extinguished fireworks
    if (game_globals::fws.size() > 0) {
        auto it = std::remove_if(game_globals::fws.begin(), game_globals::fws.end(),
                                 [](const Firework* fw) -> bool { return fw->isExtinguished(); });
        if (it != game_globals::fws.end()) {
            game_globals::fws.erase(it);
        }
    }
}

int main() {
    initialize_game();
    // While the game is running...
    while (game_globals::rWindow.isOpen()) {
        sf::Time tElapsedTime = game_globals::cClock.restart();
        // Process Inputs
        process_events();
        // Update the internal state
        update_state(tElapsedTime);
        // Draw to screen
        draw();
    }
    return 0;
}
