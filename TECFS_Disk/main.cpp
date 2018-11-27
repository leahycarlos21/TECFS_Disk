#include <iostream>
#include "Singleton.h"
#include "GestorDB.h"
#include "GestorVideos.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cstring>

using namespace std;

int main() {
    int numDisk;
    cout << "Ingresa el numero de disco?" << endl;
    cin >> numDisk;

    Singleton::crearDirectorioDisk(numDisk);
    cout << "Se han creado el disco ingresado" << endl;
    sf::TcpSocket *tcpServer = Singleton::getTcpServer();
    Singleton::crearBloquesDisk(Singleton::getDirectorio());

    while (true) {
        sf::Packet packetRecibido;
        if (tcpServer->receive(packetRecibido) == sf::Socket::Done) {
            string solicitud;
            packetRecibido >> solicitud;
            char *action = (char *) solicitud.c_str();
            ///com
            if (strcmp(action, "exit") == 0) {
                break;
            }

            if (strcmp(action, "database") == 0) {
                string action2;
                packetRecibido >> action2;
                string content;
                packetRecibido >> content;

                ///Creacion de la tabla
                if (strcmp(action2.c_str(), "save") == 0) {
                    GestorDB::crearFile(content);
                    ///Solicitud datos en los discos
                } else if (strcmp(action2.c_str(), "get") == 0) {
                    string data = GestorDB::getData();
                    sf::Packet packetis;
                    packetis << data;
                    tcpServer->send(packetis);
                }
                ///Solicitud del guardado parte video
            } else if (strcmp(action, "savePart") == 0) {
                string nombreFile;
                string parteVideo;
                packetRecibido >> nombreFile;
                packetRecibido >> parteVideo;
                GestorVideos::saveParte(parteVideo, nombreFile);

                ///Solicitud de envio de parte de video
            } else if (strcmp(action, "getPart") == 0) {
                string nombreFile;
                packetRecibido >> nombreFile;

                string parteVideo = GestorVideos::getParte(nombreFile);
                sf::Packet packetRespuesta;
                packetRespuesta << parteVideo;
                tcpServer->send(packetRespuesta);

                ///Verificacion de conexion
            } else if (strcmp(action, "verifyingConnection...") == 0) {
                sf::Packet packetRespuesta;
                packetRespuesta << "Connected";
                tcpServer->send(packetRespuesta);
            }
        }
    }

    return 0;
}