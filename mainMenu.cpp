#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "mainMenu.h"
#include "game.h"
#include "Minesweeper.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

    //Load menu image from file
    sf::Texture mainMenuImage;
    mainMenuImage.loadFromFile("images/mainmenu.png");
    sf::Sprite sprite(mainMenuImage);

    //Setup clickable regions

    //Play menu item coordinates
    MenuItem playButton;
    playButton.rect.top= 200;
    playButton.rect.height = (Game::windowHeight/2) - playButton.rect.top;
    playButton.rect.left = 0;
    playButton.rect.width = Game::windowWidth;
    playButton.action = Play;

    //Exit menu item coordinates
    MenuItem exitButton;
    exitButton.rect.top = 500;
    exitButton.rect.height = exitButton.rect.top - 250;
    exitButton.rect.left = 0;
    exitButton.rect.width = Game::windowWidth;
    exitButton.action = Exit;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);

    window.draw(sprite);
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
        sf::Rect<int> menuItemRect = (*it).rect;
        if( menuItemRect.top + menuItemRect.height >= y
            && menuItemRect.top <= y
            && menuItemRect.left <= x
            && menuItemRect.left + menuItemRect.width >= x)
        {
            return (*it).action;
        }
    }

    return Nothing;
}
