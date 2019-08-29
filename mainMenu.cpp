#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <queue>
#include <utility>
#include <vector>
#include <cmath>
#include "game.h"
#include "Minesweeper.h"
#include "mainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

    //Load menu image from file
    sf::Texture mainMenuImage;
    mainMenuImage.loadFromFile("images/mainmenu.png");
    sf::Sprite sprite(mainMenuImage);

    //Setup clickable regions

    //Play menu item coordinates
    MenuItem playButton;
    playButton.action = Play;
    sf::RectangleShape test(sf::Vector2f(1000, 300));
    test.setFillColor(sf::Color::Transparent);
//    test.setOutlineColor(sf::Color::Red);
    test.setOutlineThickness(5);
    test.setPosition(0,190);
    playButton.rect = test;

    //Exit menu item coordinates
    MenuItem exitButton;
    exitButton.action = Exit;
    sf::RectangleShape test2(sf::Vector2f(1000, 230));
    test2.setFillColor(sf::Color::Transparent);
//    test2.setOutlineColor(sf::Color::Blue);
    test2.setOutlineThickness(5);
    test2.setPosition(0,500);
    exitButton.rect = test2;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);

    window.draw(sprite);
    window.draw(test);
    window.draw(test2);
    window.display();

    return GetMenuResponse(window);
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            return HandleClick(event.mouseButton.x,event.mouseButton.y);
        }
        if(event.type == sf::Event::Closed)
        {
            return Exit;
        }
    }
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;

    for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::RectangleShape menuItemRect = (*it).rect;
        sf::FloatRect MIRB(menuItemRect.getLocalBounds());
        sf::Vector2f MIRP = menuItemRect.getPosition();
        if( x > MIRP.x && x< MIRP.x + MIRB.width && y > MIRP.y && y< MIRP.y + MIRB.height)
        {
            return (*it).action;
        }
    }

    return Nothing;
}
