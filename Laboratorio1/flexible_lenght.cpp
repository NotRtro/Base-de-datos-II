#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <climits>
using namespace std;

struct Alumno{
  string nombre;
  string apellidos;
  string carrera;
  float mensualidad;
};

void print_vector(vector<Alumno> temp){
    for (int i = 0; i < temp.size(); ++i) {
        cout<<i<<endl;
    }
}

struct VariableRecord{
    string archivo;

    VariableRecord(string archiv="datos2.txt"){
        archivo=archiv;
    };

    vector<Alumno> load(){
        vector <Alumno> res;
        ifstream file(archivo.c_str(),ios::in|ios::binary|ios::ate);
        file.seekg(0,ios::beg);
        string temp_string;
        while(!file.eof()){
            Alumno alumno_temp;
            string s_mensualidad = "";
            getline(file,alumno_temp.nombre,'|');
            if (alumno_temp.nombre == ""){
                break;
            }
            getline(file,alumno_temp.apellidos,'|');
            getline(file,alumno_temp.carrera,'|');
            getline(file,s_mensualidad,'\n');
            if(s_mensualidad != ""){
                alumno_temp.mensualidad = stof(s_mensualidad);
            }
            res.push_back(alumno_temp);
        };
        file.close();
        return res;

    };

    void add(Alumno record){

    };

    Alumno readRecord(int pos){

    };
};

int main(){
    VariableRecord* temp =  new VariableRecord;
    vector<Alumno> prueba = temp->load();
};