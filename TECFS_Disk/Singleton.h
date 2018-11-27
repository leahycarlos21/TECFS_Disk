//
// Created by leahycarlos21 on 21/11/18.
//

#ifndef TECFS_DISK_SINGLETON_H
#define TECFS_DISK_SINGLETON_H

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
//#include "DataBaseHandler.h"
#include <sys/stat.h>
#include <iostream>
using namespace std;

class Singleton {

private:
    ///Constructor
    Singleton();
    static Singleton *instancia;

    static sf::TcpSocket *tcpServer;

    static std::string directorio;

    static void parsear(std::string xml, sf::IpAddress *ip, int *port, std::string *path);


public:
    static std::string data;

    static Singleton *getInstancia();

    static sf::TcpSocket *getTcpServer();

    static std::string getDirectorio();

    static void crearDirectorioDisk(int numDisk);

    static void crearBloquesDisk(std::string path);



};



#endif //TECFS_DISK_SINGLETON_H
