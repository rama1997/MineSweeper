#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef MINESWEEPER_SOCKET_H
#define MINESWEEPER_SOCKET_H

class Socket
{
public:
    static sf::IpAddress ip;
    static sf::TcpSocket socket;
    static char connectionType;
    static char buffer[2000];
    static std::size_t received;
    static sf::Packet packet;
    static bool connected;
    static bool firstClick;

    static void start();
};

#endif //MINESWEEPER_SOCKET_H
