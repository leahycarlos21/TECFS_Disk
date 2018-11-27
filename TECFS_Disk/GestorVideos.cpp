//
// Created by leahycarlos21 on 21/11/18.
//

#include "GestorVideos.h"
#include <iostream>
#include "Singleton.h"
#include "GestorDB.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cstring>

using namespace std;


int GestorVideos::fileSize(const string nombreFile) {
    ifstream in(nombreFile, ifstream::ate | ifstream::binary);
    int sizeFile = in.tellg();
    return sizeFile;
}

///Verificacion si el directorio esta vacio
bool GestorVideos::folderVacio(string nombreDir) {
    DIR *dir;
    struct dirent *elemento;
    bool vacio;
    int num = 0;
    if (dir = opendir(nombreDir.c_str())) {
        while (elemento = readdir(dir)) {
            if (++num > 2)
                break;
        }
    }
    closedir(dir);
    if (num <= 2)
        vacio = true;
    else
        vacio = false;

    return vacio;
}

///Encontrar un bloque disponible
string GestorVideos::freeBloque(string path) {
    string rutis;
    bool free = false;
    int num = 1;
    while (!free) {
        rutis = path + std::to_string(num);
        if (folderVacio(rutis) == true)
            free = true;
        else
            num++;
    }
    return rutis;
}

///Realizar division del archivo
LinkedList<vector<byte>> GestorVideos::splitFile(vector<byte> vector) {
    float partNumfloat = (float) vector.size() / (float) 10000000;
    int numPartes = partNumfloat;
    if (partNumfloat > numPartes)
        numPartes += 1;
    int partSize = 10000000;
    int inicio = 0, end = partSize;
    LinkedList<std::vector<byte>> partes = LinkedList<std::vector<byte>>();

    for (int i = 0; i < numPartes; ++i) {
        if (i == (numPartes - 1))
            end = vector.size();

        std::vector<byte> sub(&vector[inicio], &vector[end]);
        partes.insertAtEnd(sub);

        inicio = end;
        end += partSize;
    }
    return partes;
}

///Almacenar la parte del video
void GestorVideos::saveParte(string parteVideo, string nombreFile) {
    string path = Singleton::getDirectorio() + "/Bloque";
    vector<byte> vector(parteVideo.begin(), parteVideo.end());

    LinkedList<std::vector<byte>> parts = splitFile(vector);
    Singleton::getInstancia()->data += nombreFile + ";";
    for (int i = 0; i < parts.getSize(); i++) {
        std::vector<byte> vector = parts.getElement(i)->getData();
        string part(vector.begin(), vector.end());
        string bloque = freeBloque(path);
        Singleton::getInstancia()->data += bloque + ";";
        ofstream file;
        file.open(bloque + "/" + nombreFile + ".bin", ios::out | ios::binary);
        file.write((const char *) &vector[0], vector.size());
        file.close();
    }
    Singleton::getInstancia()->data += "*";
    cout << nombreFile << "Guardado" << endl;
}

///Obtener parte de un video
string GestorVideos::getParte(string nombreFile) {
    LinkedList<string> elementos = splitString(Singleton::data, "*");
    string videoData;

    for (int i = 0; i < elementos.getSize(); ++i) {
        LinkedList<string> data = splitString(elementos.getElement(i)->getData(), ";");
        if (strcmp(data.getElement(0)->getData().c_str(), nombreFile.c_str()) == 0) {
            videoData = elementos.getElement(i)->getData();
            i = elementos.getSize();
        }
    }

    string parte = "";
    LinkedList<std::string> data = splitString(videoData, ";");
    for (int j = 1; j < data.getSize(); ++j) {
        string path = data.getElement(j)->getData();
        ifstream file1(path + "/" + nombreFile + ".bin", ios::binary);
        vector<byte> vector((istreambuf_iterator<char>(file1)), std::istreambuf_iterator<char>());

        if (!file1.is_open()) {
            cout << "No se ha podido guarda el archivo " << nombreFile << ".bin" << std::endl;
        }

        file1.close();

        parte += string(vector.begin(), vector.end());
    }

    return parte;
}

///Separar un string en elementos
LinkedList<string> GestorVideos::splitString(std::string string, char *splitCaracter) {
    LinkedList<std::string> list = LinkedList<std::string>();
    char *messageChar = strdup(string.c_str());
    char *element = strtok(messageChar, splitCaracter);
    while (element != NULL) {
        std::string str(element);
        list.insertAtEnd(str);
        element = strtok(NULL, splitCaracter); ///Separar el resto del char al haber una coma
    }

    return list;
}