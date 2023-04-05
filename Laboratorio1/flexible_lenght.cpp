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

struct VariableRecord{
    string archivo;

    VariableRecord(string archiv="datos2.txt"){
        archivo=archiv;
    };

    vector<Alumno> load(){
        vector <Alumno> res;
        ifstream file(archivo.c_str(),ios::in|ios::binary|ios::ate);
        file.seekg(0,ios::beg);
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
        ofstream file(archivo.c_str(),ios::app);
        file<<"\n"<<record.nombre<<"|"<<record.apellidos<<"|"<<record.carrera<<"|"<<record.mensualidad;
        file.close();
    };

    Alumno readRecord(int pos){
        Alumno alumno_temp;
        ifstream file(archivo.c_str(),ios::in|ios::binary|ios::ate);
        file.seekg(0,ios::beg);
        int cont = 0;
        string temp = "a";
        while(cont <= pos){
            if(cont < pos){
                getline(file,temp,'\n');
                cont++;
                if(temp == ""){
                    cout<<"La posicion que puso no esta dentro del archivo"<<endl;
                    return alumno_temp;
                };
            }
            else if(cont == pos){
                string s_mensualidad="";
                getline(file,alumno_temp.nombre,'|');
                getline(file,alumno_temp.apellidos,'|');
                getline(file,alumno_temp.carrera,'|');
                getline(file,s_mensualidad,'\n');
                alumno_temp.mensualidad = stof(s_mensualidad);
                cont++;
            }
        }
        return alumno_temp;
    };
};

int main(){
    VariableRecord* temp =  new VariableRecord;
    vector<Alumno> prueba = temp->load();
    Alumno* alumno_prueba = new Alumno;
    *alumno_prueba = temp->readRecord(2);
    /*string nombre, apellidos, carrera, mensualidad;
    cout<<"Ingrese el nombre: "<<endl;
    cin>>nombre;
    cout<<"Ingrese el apellidos: "<<endl;
    cin>>apellidos;
    cout<<"Ingrese el carrera: "<<endl;
    cin>>carrera;
    cout<<"Ingrese el mensualidad: "<<endl;
    cin>>mensualidad;
    alumno_prueba->nombre = nombre;
    alumno_prueba->apellidos = apellidos;
    alumno_prueba->carrera = carrera;
    alumno_prueba->mensualidad = stof(mensualidad);*/
    temp->add(*alumno_prueba);
};