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
#include "socket.h"

sf::IpAddress Socket::ip = sf::IpAddress::getLocalAddress();
char Socket::connectionType = ' ';
sf::TcpSocket Socket::socket;
char Socket::buffer[2000];
std::size_t Socket::received;
sf::Packet Socket::packet;
bool Socket::connected;
bool Socket::firstClick = true;

void Socket::start(){
    std::string text = "Connected to: ";
    std::cout << "Enter (s) for server, Enter (c) for client" << std::endl;
    std::cin >> connectionType;

    if(connectionType == 's'){  //server
        sf::TcpListener listener;   //server listener
        listener.listen(4000);
        connected = true;
        listener.accept(socket);
        text += "Server";
    }
    else if(connectionType == 'c'){ //client
        if(socket.connect(ip, 4000, sf::seconds(10)) == sf::Socket::Done){
            connected = true;
            text += "Client";
        }
    }

    socket.send(text.c_str(), text.length()+1);  //send message
    socket.receive(Socket::buffer, sizeof(buffer), received); //receive message
    std::cout << buffer << std::endl;   //print message

    socket.setBlocking(false);
}

