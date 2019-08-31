#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

class Game
{

public:
    static void Start();
    static int imageSize; //size for minesweeper squares
    enum GameState { Uninitialized, ShowingTitle, ShowingMenu, Playing, Exiting};
    static GameState _gameState;

private:
    static bool IsExiting();
    static void GameLoop();
    static void ShowTitleScreen();

    static int windowWidth;
    static int windowHeight;

    static sf::RenderWindow _mainWindow;
};

#endif //MINESWEEPER_GAME_H
