#include <iostream>
#include <SFML/Graphics.hpp>

#include "SceneManager.h"
#include "SteeringManager.h"
#include "scenes/ArriveScene.h"
#include "scenes/FleeScene.h"
#include "scenes/SeekScene.h"

int main()
{
    // window settings
    sf::RenderWindow window(sf::VideoMode(800, 600), "Steering Behaviors");
    window.setFramerateLimit(60);
    sf::Clock clock;

    // Scene Management
    SceneManager sceneManager;
    sceneManager.addScene(SceneName::SEEK, std::make_unique<SeekScene>(window));
    sceneManager.addScene(SceneName::FLEE, std::make_unique<FleeScene>(window));
    sceneManager.addScene(SceneName::ARRIVE, std::make_unique<ArriveScene>(window));

    sceneManager.switchTo(SceneName::SEEK);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sceneManager.handleInput(event);

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Num1:
                    sceneManager.switchTo(SceneName::SEEK);
                    break;
                case sf::Keyboard::Num2:
                    sceneManager.switchTo(SceneName::FLEE);
                    break;
                case sf::Keyboard::Num3:
                    sceneManager.switchTo(SceneName::ARRIVE);
                    break;
                default:
                    std::cout << "Key 1 for seek" << std::endl;
                    std::cout << "Key 2 for flee" << std::endl;
                    std::cout << "Key 3 for arrive" << std::endl;
                    break;
                }
            }
        }

        sf::Time deltaTime = clock.restart();
        sceneManager.update(deltaTime);

        window.clear();
        sceneManager.render(window);
        window.display();
    }

    return 0;
}
