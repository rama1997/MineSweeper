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

private:
    static bool IsExiting();
    static void GameLoop();
    static void ShowTitleScreen();
    static void ShowMainMenu();

    enum GameState { Uninitialized, ShowingTitle, Paused,
        ShowingMenu, Playing, Exiting };

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
};

#endif //MINESWEEPER_GAME_H
