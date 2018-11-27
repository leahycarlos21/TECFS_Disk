//
// Created by leahycarlos21 on 21/11/18.
//

#include <fstream>
#include "Singleton.h"


///Inicializacion de las variables
string Singleton::data = "";
Singleton *Singleton::instancia = nullptr;
sf::TcpSocket *Singleton::tcpServer = nullptr;
string Singleton::directorio = "unkown";

Singleton::Singleton() {}

void Singleton::parsear(std::string xml, sf::IpAddress *ip, int *port, string *path) {
    string line;
    cout << xml << endl;
    ifstream in("../" + xml);

    bool inicioIP = false;
    bool inicioPort = false;
    bool inicioPath = false;

    while (getline(in, line)) {
        string aux;

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ' && aux.size() == 0) {

            } else {
                aux += line[i];
            }
        }
        ///Data IP
        if (aux == "<Ip>") {
            inicioIP = true;
            continue;
        } else if (aux == "</Ip>") {
            inicioIP = false;
        }
        if (inicioIP) {
            ///Se asigna la ip del XML al *ip
            *ip = aux;
        }
        ///Data PORT
        if (aux == "<Port>") {
            inicioPort = true;
            continue;
        } else if (aux == "</Port>") {
            inicioPort = false;
        }
        if (inicioPort) {
            *port = atoi(aux.c_str());
        }
        ///Data PATH
        if (aux == "<Path>") {
            inicioPath = true;
            continue;
        } else if (aux == "</Path>") {
            inicioPath = false;
        }
        if (inicioPath) {
            *path = aux;
        }
    }
}

Singleton *Singleton::getInstancia() {
    if (instancia == nullptr) {
        instancia = new Singleton();
        tcpServer = new sf::TcpSocket();
        string xmlData = "Data.xml";
        int PORT;
        sf::IpAddress IP;

        cout << "IPaddress: " << IP.toString() << endl;
        string PATH;
        parsear(xmlData, &IP, &PORT, &PATH);
        cout << "IPaddress2: " << IP.toString() << endl;

        directorio = PATH;
        tcpServer->connect(IP, PORT);
        sf::Packet data;
        data << "Disk";
        tcpServer->send(data);
        cout << "Enviado" << endl;
    }
    return instancia;
}

string Singleton::getDirectorio() {
    return directorio;
}

sf::TcpSocket *Singleton::getTcpServer() {
    if (instancia == nullptr)
        getInstancia();
    return tcpServer;
}

///Almacenamiento de los datos del disco
void Singleton::crearDirectorioDisk(int numDisk) {
    if (instancia == nullptr)
        getInstancia();
    Singleton::directorio += to_string(numDisk);
    ///Crear la carpeta con el sistema de archivos
    mkdir(directorio.c_str(), 0777);
}

void Singleton::crearBloquesDisk(string path) {
    string bloque = path + "/Bloque";
    for (int i = 1; i <= 30; i++) {
        string number = to_string(i);
        path = bloque;
        path = path + number;
        cout << "el path es" << path << endl;
        if (mkdir(path.c_str(), 0777) == -1)
            mkdir(path.c_str(), 0777);
    }
}