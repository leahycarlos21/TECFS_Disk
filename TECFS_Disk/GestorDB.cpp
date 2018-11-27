
#include "GestorDB.h"
#include "Singleton.h"

///Crea el fichero con la parte especifica de la DB
void GestorDB::crearFile(string contenido) {
    string nombreFile = Singleton::getDirectorio()+"/metadata.bin";
    ofstream file(nombreFile,ios::out|ios::binary);
    file.write(contenido.c_str(),contenido.size());
    file.close();
}

///Obtener parte de la DB almacenada en el disco
string GestorDB::getData() {
    string nombreFile = Singleton::getDirectorio()+"/metadata.bin";
    ifstream file(nombreFile, ios::binary);
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return data;
}