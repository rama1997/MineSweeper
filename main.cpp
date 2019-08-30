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

int main()
{
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;   //client side
    char connectionType, mode;
    char buffer[2000];
    std::size_t received;
    std::string text = "Connected to: ";
    std::cout << "Enter (s) for server, Enter (c) for client" << std::endl;
    std::cin >> connectionType;

    if(connectionType == 's'){
        sf::TcpListener listener;   //server listener
        if (listener.listen(4000) != sf::Socket::Done)
        {
            std::cout << "listener error " << std::endl;
        }
        if (listener.accept(socket) != sf::Socket::Done)
        {
            std::cout << "accept error " << std::endl;
        }
        text += "Server";
    }
    else if(connectionType == 'c'){
        sf::Socket::Status status = socket.connect(ip, 4000, sf::seconds(10));
        if (status != sf::Socket::Done)
        {
            std::cout << "client error " << std::endl;
        }
        text += "Client";
    }

    if(socket.send(text.c_str(), text.length()+1) != sf::Socket::Done)
    {
        std::cout << "send error " << std::endl;
    }

    if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
    {
        std::cout << "receive error " << std::endl;
    }

    std::cout << buffer << std::endl;

    Game::Start();
    return 0;
}


