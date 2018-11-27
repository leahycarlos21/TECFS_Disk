//
// Created by leahycarlos21 on 21/11/18.
//

#ifndef TECFS_DISK_GESTORVIDEOS_H
#define TECFS_DISK_GESTORVIDEOS_H


#include <iostream>

#include <iostream>
#include <vector>
#include <fstream>
#include <dirent.h>

#include "Singleton.h"
#include "DataStructures/LinkedList.h"

typedef unsigned char byte;


using namespace std;

class GestorVideos {
public:
    static int fileSize(const string nombreFile);

    static bool folderVacio(string nombreDir);

    static string freeBloque(string path);

    static LinkedList<vector<byte>> splitFile(vector<byte> vector);

    static void saveParte(string parteVideo,string nombreFile);

    static std::string getParte(string nombreFile);

    static LinkedList<std::string> splitString(std::string string, char *splitCaracter);
};


#endif //TECFS_DISK_GESTORVIDEOS_H
