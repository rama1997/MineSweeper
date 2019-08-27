#include <SFML/Graphics.hpp>
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
    playButton.rect.top= 145;
    playButton.rect.height = 380 - playButton.rect.top;
    playButton.rect.left = 0;
    playButton.rect.width = 1023 - playButton.rect.left;
    playButton.action = Play;

    //Exit menu item coordinates
    MenuItem exitButton;
    exitButton.rect.left = 0;
    exitButton.rect.width = 1023 - exitButton.rect.left;
    exitButton.rect.top = 383;
    exitButton.rect.height = 560 - exitButton.rect.top;
    exitButton.action = Exit;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);

    window.draw(sprite);
    window.display();

    //return GetMenuResponse(window);
}

//MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
//{
//    std::list<MenuItem>::iterator it;
//
//    for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
//    {
//        sf::Rect<int> menuItemRect = (*it).rect;
//        if( menuItemRect.Bottom > y
//            && menuItemRect.Top < y
//            && menuItemRect.Left < x
//            && menuItemRect.Right > x)
//        {
//            return (*it).action;
//        }
//    }
//
//    return Nothing;
//}
//
//MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
//{
//    sf::Event menuEvent;
//
//    while(42 != 43)
//    {
//
//        while(window.GetEvent(menuEvent))
//        {
//            if(menuEvent.Type == sf::Event::MouseButtonPressed)
//            {
//                return HandleClick(menuEvent.MouseButton.X,menuEvent.MouseButton.Y);
//            }
//            if(menuEvent.Type == sf::Event::Closed)
//            {
//                return Exit;
//            }
//        }
//    }
//}