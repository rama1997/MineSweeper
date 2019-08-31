#include <SFML/Graphics.hpp>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#ifndef MINESWEEPER_MAINMENU_H
#define MINESWEEPER_MAINMENU_H

class MainMenu
{

public:
    enum MenuResult { Nothing, Exit, Play };

    struct MenuItem
    {
    public:
        sf::RectangleShape rect;
        MenuResult action;
    };

    MenuResult Show(sf::RenderWindow& window);

private:
    MenuResult GetMenuResponse(sf::RenderWindow& window);
    MenuResult HandleClick(int x, int y);
    std::list<MenuItem> _menuItems;
};

#endif //MINESWEEPER_MAINMENU_H
