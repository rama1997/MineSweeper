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

int Game::windowWidth = 700;
int Game::windowHeight = 1000;
int Game::imageSize = 32; //image for minesweeper content is 32 by 32 pixel image
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;

void Game::Start()
{
    if(_gameState != Uninitialized)
        return;

    _mainWindow.create(sf::VideoMode(windowWidth,windowHeight,32),"Minesweeper!",sf::Style::Close); //create game window on game start

    _gameState = Game::ShowingTitle;   //first state is to show title

    sf::Music music;
    music.openFromFile("audio/weCanGetHigh.ogg");
    music.setLoop(true);
    music.play();

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
            case Game::ShowingTitle: //show title screen, upon click will move to main menu screen
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
                if(event.type == sf::Event::Closed)
                {
                    _gameState = Game::Exiting;
                }
                MainMenu mainMenu;
                MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
                switch(result)
                {
                    case MainMenu::Exit: {
                        _gameState = Game::Exiting;
                        break;
                    }
                    case MainMenu::Play: {
                        _gameState = Game::Playing;
                        break;
                    }
                    case MainMenu::Nothing:{
                        break;
                    }
                }
                break;
            }
            case Game::Playing:
            {
                if(event.type == sf::Event::Closed)
                {
                    _gameState = Game::Exiting;
                }
                Minesweeper game;
                game.play(_mainWindow);
                if(_gameState == Game::Playing){    //if window was closed before gamestate changed, go to exit
                    _gameState = Game::Exiting;
                }
                break;
            }
            case Game::Exiting:
            {
                break;
            }
            case Game::Uninitialized:
            {
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
