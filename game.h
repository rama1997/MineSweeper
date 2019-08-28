#include <SFML/Graphics.hpp>

#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

class Game
{

public:
    static void Start();
    //TODO: make windowWidth/ windowHeight private
    static int windowWidth;
    static int windowHeight;
    static int imageSize; //size for minesweeper squares

private:
    static bool IsExiting();
    static void GameLoop();
    static void ShowTitleScreen();

    enum GameState { Uninitialized, ShowingTitle, ShowingMenu, Playing, Exiting};

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
};

#endif //MINESWEEPER_GAME_H
