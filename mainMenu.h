#include <SFML/Graphics.hpp>
#include <list>

#ifndef MINESWEEPER_MAINMENU_H
#define MINESWEEPER_MAINMENU_H

class MainMenu
{

public:
    enum MenuResult { Nothing, Exit, Play };

    struct MenuItem
    {
    public:
        sf::Rect<int> rect;
        MenuResult action;
    };

    MenuResult Show(sf::RenderWindow& window);

private:
    MenuResult GetMenuResponse(sf::RenderWindow& window);
    MenuResult HandleClick(int x, int y);
    std::list<MenuItem> _menuItems;
};

#endif //MINESWEEPER_MAINMENU_H
