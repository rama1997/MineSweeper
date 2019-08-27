#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <queue>
#include <utility>
#include <vector>
#include <cmath>
#include "game.h"

bool firstClick = true;
int gameWidth = 20;
int gameHeight = 20;
//IF CHANGE GAME PARAMETER:
//change visited array inital declaration
int imageSize = 32; //image is 32 by 32 pixel image

void setUpBlankBoard(std::vector<std::vector<int>> &gg,std::vector<std::vector<int>> &ig,std::vector<std::vector<int>> &v){
    for(int i = 0; i <= gameWidth+1; i++){
        for(int j = 0; j<= gameHeight+1; j++){
            v[i][j] = false;    //mark all grid coord not visited
            if(i == 0 || j == 0 || i == gameWidth+1 || j == gameHeight+1){
                v[i][j] = true; //mark edge case of map visited so game stops searching at edge
            }
        }
    }
    for (int i=1; i<=gameWidth; i++) { //create random board at the start of the game
        for (int j=1; j<=gameHeight; j++){
            ig[i][j]=10; //set all squares on visual grid to be unopened
            gg[i][j] = 0; //set game as blank
        }
    }
}

void setUpGameGrid(std::vector<std::vector<int>> &gameGrid, int clickedMX, int clickedMY){
    for (int i = 1; i <= gameWidth; i++) { //create random board at the first click
        for (int j = 1; j <= gameHeight; j++) {
            if (rand() % 5 == 0) {
                gameGrid[i][j] = 9; //randomly determine which squares are bombs on game grid
            } else {
                gameGrid[i][j] = 0;
            }
        }
    }
    gameGrid[clickedMX][clickedMY] = 0; //set first click position and area around it to never have a bomb
    gameGrid[clickedMX + 1][clickedMY] = 0;
    gameGrid[clickedMX - 1][clickedMY] = 0;
    gameGrid[clickedMX][clickedMY + 1] = 0;
    gameGrid[clickedMX][clickedMY - 1] = 0;
    gameGrid[clickedMX + 1][clickedMY + 1] = 0;
    gameGrid[clickedMX - 1][clickedMY + 1] = 0;
    gameGrid[clickedMX + 1][clickedMY - 1] = 0;
    gameGrid[clickedMX - 1][clickedMY - 1] = 0;

    for (int i = 1; i <=
                    gameWidth; i++) {   //for each square, look at space around them to figure out how many bombs are around them
        for (int j = 1; j <= gameHeight; j++) {
            int n = 0;
            if (gameGrid[i][j] == 9) {
                continue;
            }
            if (gameGrid[i + 1][j] == 9) {
                n++;
            }
            if (gameGrid[i - 1][j] == 9) {
                n++;
            }
            if (gameGrid[i][j + 1] == 9) {
                n++;
            }
            if (gameGrid[i][j - 1] == 9) {
                n++;
            }
            if (gameGrid[i + 1][j + 1] == 9) {
                n++;
            }
            if (gameGrid[i - 1][j - 1] == 9) {
                n++;
            }
            if (gameGrid[i - 1][j + 1] == 9) {
                n++;
            }
            if (gameGrid[i + 1][j - 1] == 9) {
                n++;
            }
            gameGrid[i][j] = n;
        }
    }
}

void checkZero(std::vector<std::vector<int>> &gameGrid,std::vector<std::vector<int>> &imageGrid,std::vector<std::vector<int>> &visited, int clickedMX, int clickedMY){
    //if user clicks on 0, scan around to open up more spaces. If other spaces are zero, repeat on that space. If other spaces are bombs, don't do anything. Else, reveal.
    imageGrid[clickedMX][clickedMY] = 0;
    visited[clickedMX][clickedMY] = true;
    std::queue<std::pair<int, int>> myQ; //queue of all spaces to check
    myQ.push(std::make_pair(clickedMX, clickedMY));
    while (!myQ.empty()) {
        int x = myQ.front().first;
        int y = myQ.front().second;
        imageGrid[x][y] = gameGrid[x][y];
        myQ.pop();
        if (gameGrid[x - 1][y] != 9) {
            imageGrid[x - 1][y] = gameGrid[x - 1][y];
            if (gameGrid[x - 1][y] == 0 && visited[x - 1][y] == false) {
                myQ.push(std::make_pair(x - 1, y));
                visited[x - 1][y] = true;
            }
        }
        if (gameGrid[x + 1][y] != 9) {
            imageGrid[x + 1][y] = gameGrid[x + 1][y];
            if (gameGrid[x + 1][y] == 0 && visited[x + 1][y] == false) {
                myQ.push(std::make_pair(x + 1, y));
                visited[x + 1][y] = true;
            }
        }
        if (gameGrid[x][y + 1] != 9) {
            imageGrid[x][y + 1] = gameGrid[x][y + 1];
            if (gameGrid[x][y + 1] == 0 && visited[x][y + 1] == false) {
                myQ.push(std::make_pair(x, y + 1));
                visited[x][y + 1] = true;
            }
        }
        if (gameGrid[x][y - 1] != 9) {
            imageGrid[x][y - 1] = gameGrid[x][y - 1];
            if (gameGrid[x][y - 1] == 0 && visited[x][y - 1] == false) {
                myQ.push(std::make_pair(x, y - 1));
                visited[x][y - 1] = true;
            }
        }
        if (gameGrid[x + 1][y + 1] != 9) {
            imageGrid[x + 1][y + 1] = gameGrid[x + 1][y + 1];
            if (gameGrid[x + 1][y + 1] == 0 && visited[x + 1][y + 1] == false) {
                myQ.push(std::make_pair(x + 1, y + 1));
                visited[x + 1][y + 1] = true;
            }
        }
        if (gameGrid[x - 1][y - 1] != 9) {
            imageGrid[x - 1][y - 1] = gameGrid[x - 1][y - 1];
            if (gameGrid[x - 1][y - 1] == 0 && visited[x - 1][y - 1] == false) {
                myQ.push(std::make_pair(x - 1, y - 1));
                visited[x - 1][y - 1] = true;
            }
        }
        if (gameGrid[x + 1][y - 1] != 9) {
            imageGrid[x + 1][y - 1] = gameGrid[x + 1][y - 1];
            if (gameGrid[x + 1][y - 1] == 0 && visited[x + 1][y - 1] == false) {
                myQ.push(std::make_pair(x + 1, y - 1));
                visited[x + 1][y - 1] = true;
            }
        }
        if (gameGrid[x - 1][y + 1] != 9) {
            imageGrid[x - 1][y + 1] = gameGrid[x - 1][y + 1];
            if (gameGrid[x - 1][y + 1] == 0 && visited[x - 1][y + 1] == false) {
                myQ.push(std::make_pair(x - 1, y + 1));
                visited[x - 1][y + 1] = true;
            }
        }
    }

}

int main()
{
    Game::Start();

    srand(time(0)); //RNG
    sf::RenderWindow window(sf::VideoMode(Game::windowWidth, Game::windowHeight), "Minesweeper!", sf::Style::Default);

    sf::Font font;      //font and text stuff
    font.loadFromFile("fonts/OpenSans-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Red);
    text.setPosition(35, 700);

    sf::Text timer;     //timer text box
    timer.setFont(font);
    timer.setString("");
    timer.setCharacterSize(32);
    timer.setFillColor(sf::Color::White);
    timer.setPosition(35, 900);

    sf::Clock clock;

    sf::RectangleShape playAgainButton(sf::Vector2f(200.f, 50.f));      //play button stuff
    playAgainButton.setFillColor(sf::Color::Black);
    sf::FloatRect playButtonBounds(playAgainButton.getLocalBounds());
    playAgainButton.setPosition(350 - (playButtonBounds.width/2), 800); //buttonbound.width = 200, divide by 2 is 100. Want center of box to be centered horizontally which should be at 350. 350 - 100 = 250 so box should start at 250 width.
    sf::Vector2f playButtonPosition = playAgainButton.getPosition();

    sf::Text playAgainText;     //play button text
    playAgainText.setFont(font);
    playAgainText.setString("");
    playAgainText.setCharacterSize(32);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setPosition(350 - (playButtonBounds.width/2), 800);
    playAgainText.setString("Click to restart");

    sf::Texture texture;            //image sprite stuff
    texture.loadFromFile("images/tiles.jpg");
    sf::Sprite sprite(texture);

    std::vector<std::vector<int>> gameGrid(gameWidth+2); //game
    std::vector<std::vector<int>> imageGrid(gameWidth+2); //visual
    std::vector<std::vector<int>> visited(gameWidth+2); //used when user clicks on 0
    for (int i = 0; i < gameWidth+2; i++) {
        gameGrid[i].resize(gameHeight+2);
        imageGrid[i].resize(gameHeight+2);
        visited[i].resize(gameHeight+2);
    }

    setUpBlankBoard(gameGrid,imageGrid,visited);    //set up blank board at the start of program

    while (window.isOpen())
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int mouseX = mousePosition.x/imageSize;
        int mouseY = mousePosition.y/imageSize;
        int clickedMX;
        int clickedMY;
        bool gameLost = false;
        bool gameWon = false;
        bool showTime = false;

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed){
                if (event.key.code == sf::Mouse::Left){  // on left mouse click, change visual grid to match game grid, "uncover" the square
                    if(mouseX <= gameWidth && mouseY <= gameHeight) { //map does not uncover unless user clicks within map screen
                        imageGrid[mouseX][mouseY] = gameGrid[mouseX][mouseY];
                        clickedMX = mouseX;     // new variables for clicked mouse pos
                        clickedMY = mouseY;
                        if (firstClick == true) { //board is built AFTER first click so that first click is never a bomb and always 0
                            clock.restart();
                            showTime = true;
                            setUpGameGrid(gameGrid, clickedMX, clickedMY);
                            firstClick = false;
                        }
                        if (gameGrid[clickedMX][clickedMY] == 0 && visited[clickedMX][clickedMY] == false) {
                            //if user clicks on 0, scan around to open up more spaces. If other spaces are zero, repeat on that space. If other spaces are bombs, don't do anything. Else, reveal.
                            checkZero(gameGrid, imageGrid, visited, clickedMX, clickedMY);
                        }
                        gameWon = true;
                        showTime = true;
                        for (int i=1; i<=gameWidth; i++) {  //check if game is won
                            for (int j = 1; j <= gameHeight; j++) {
                                if(gameGrid[i][j] != 9 && imageGrid[i][j] != gameGrid[i][j]){
                                    gameWon = false;
                                    showTime = false;
                                }
                            }
                        }
                    }
                    else if(mouseX*imageSize >= playButtonPosition.x && mouseY*imageSize >= playButtonPosition.y && mouseX*imageSize <= playButtonPosition.x + playButtonBounds.width && mouseY*imageSize <= playButtonPosition.y + playButtonBounds.height){
                        setUpBlankBoard(gameGrid,imageGrid,visited);
                        text.setString("");
                        gameLost = false;
                        gameWon = false;
                        firstClick = true;
                        showTime = false;
                        clock.restart();
                    }
                }
                else if (event.key.code == sf::Mouse::Right){ //on right mouse click, insert flag
                    if(imageGrid[mouseX][mouseY] == 10){
                        imageGrid[mouseX][mouseY] = 11;
                    }
                    else if(imageGrid[mouseX][mouseY] == 11){
                        imageGrid[mouseX][mouseY] = 10;
                    }
                }
                if(imageGrid[mouseX][mouseY] == 9){ //if user clicks on a bomb, game ends
                    gameLost = true;
                }
            }
        }

        window.clear();     //clear window after each click
        for (int i=1; i<=gameWidth; i++) {
            for (int j = 1; j <= gameHeight; j++) {
                if (gameLost == true) {    //if game lost, uncover whole map
                    imageGrid[i][j] = gameGrid[i][j];
                    text.setString("Game Over You Lose");
                    gameWon = false;
                    showTime = false;
                }
                sprite.setTextureRect(sf::IntRect(imageGrid[i][j] * imageSize, 0, imageSize, imageSize));
                sprite.setPosition(i * imageSize, j * imageSize);
                window.draw(sprite);
            }
        }
        if(gameWon == true){
            text.setString("Congratz You Win");
            gameLost = false;
            showTime = false;
        }
        if(showTime == true){
            // TODO: add/fix timer
            sf::Time elapsed1 = clock.getElapsedTime();
            timer.setString(std::to_string((int)round(elapsed1.asSeconds())));
        }
        window.draw(timer);
        window.draw(text);
        window.draw(playAgainButton);
        window.draw(playAgainText);
        window.display();
    }
    return 0;
}


