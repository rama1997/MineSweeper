#include <SFML/Graphics.hpp>
#include "game.h"
#include "mainMenu.h"

int Game::windowWidth = 700;
int Game::windowHeight = 1000;
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;

void Game::Start()
{
    if(_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(windowWidth,windowHeight,32),"Minesweeper!",sf::Style::Close);

    _gameState = Game::ShowingTitle;

    while(!IsExiting())
    {
        GameLoop();
    }

    _mainWindow.close();
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

void Game::GameLoop()
{
    sf::Event event;
    while(_mainWindow.pollEvent(event))
    {

        switch(_gameState)
        {
            case Game::ShowingTitle:
            {
                ShowTitleScreen();
                if(event.type == sf::Event::Closed || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed )
                {
                    _gameState = Game::ShowingMenu;
                }
                break;
            }
            case Game::ShowingMenu:
            {
                ShowMainMenu();
                if(event.type == sf::Event::Closed || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed )
                {
                    _gameState = Game::Playing;
                }
                break;
            }
            case Game::Playing:
            {
                _mainWindow.clear(sf::Color(255,0,0));
                _mainWindow.display();
                if(event.type == sf::Event::Closed || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed )
                {
                    _gameState = Game::Exiting;
                }
                break;
            }
        }
    }
}

void Game::ShowTitleScreen() {
    sf::Texture titleImage;
    titleImage.loadFromFile("images/title.jpg");
    sf::Sprite titleScreen(titleImage);
    _mainWindow.draw(titleScreen);
    _mainWindow.display();
}

void Game::ShowMainMenu() {
    MainMenu mainMenu;
    mainMenu.Show(_mainWindow);
}