#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <climits>
#include <math.h>
using namespace std;

struct Matricula{
    string codigo;
    int ciclo;
    float mensualidad;
    string observaciones;
};

struct Flexible_lenght_metadata{
    string metadata;

    Flexible_lenght_metadata (){
        ofstream meta("metadata.txt");
        if (meta) {
            meta.close();
            cout << "Archivo creado correctamente." << endl;
        } else {
            cout << "Error al crear el archivo." << endl;
        }
        metadata = "metadata.txt";
    }

    vector<Matricula> load(){
        vector<Matricula> res;
        string text = "datos2.bin";
        ofstream meta(metadata, ios::binary);
        ifstream archivo(text,ios::binary);
        string buffer;
        int posicion=0;
        while (getline(archivo,buffer)) {
            Matricula matricula_temp;
            matricula_temp.codigo = buffer.substr(0, buffer.find("|"));
            buffer.erase(0, buffer.find("|") + 1);
            string ciclo_str = buffer.substr(0, buffer.find("|"));
            matricula_temp.ciclo = stoi(ciclo_str);
            buffer.erase(0, buffer.find("|") + 1);
            string mensualidad_str = buffer.substr(0, buffer.find("|"));
            matricula_temp.mensualidad = stof(mensualidad_str);
            buffer.erase(0, buffer.find("|") + 1);
            matricula_temp.observaciones = buffer;
            int posicion_final = matricula_temp.codigo.size() + matricula_temp.observaciones.size() + ciclo_str.size() + mensualidad_str.size()+3;
            meta << posicion << endl;
            posicion = posicion + posicion_final;
            res.push_back(matricula_temp);
        }
            meta.close();
            archivo.close();
            return res;
    };

    void add(Matricula Record){

    };

    Matricula readRecord(int pos){

    };

};

int main(){
    Flexible_lenght_metadata* test = new Flexible_lenght_metadata();
    vector<Matricula> temp = test->load();
};