//
// Created by leahycarlos21 on 21/11/18.
//

#ifndef TECFS_DISK_GESTORDB_H
#define TECFS_DISK_GESTORDB_H
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/Packet.hpp>
#include <fstream>
#include <iostream>
using namespace std;
class GestorDB {
public:
    static void crearFile(string contenido);
    static string getData();

};


#endif //TECFS_DISK_GESTORDB_H
