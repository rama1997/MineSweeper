#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

class Minesweeper{

public:
    static int gameWidth;
    static int gameHeight;
    static void play(sf::RenderWindow& window);

private:
    static void setUpBlankBoard(std::vector<std::vector<int> > &gg,std::vector<std::vector<int> > &ig,std::vector<std::vector<int> > &v);
    static void setUpGameGrid(std::vector<std::vector<int> > &gameGrid, int clickedMX, int clickedMY);
    static void checkZero(std::vector<std::vector<int> > &gameGrid,std::vector<std::vector<int> > &imageGrid,std::vector<std::vector<int> > &visited, int clickedMX, int clickedMY);
};

#endif //MINESWEEPER_MINESWEEPER_H
