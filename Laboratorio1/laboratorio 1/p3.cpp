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

  Alumno(){};

  Alumno(const string &nombre, const string &apellidos, const string &carrera, float mensualidad) : nombre(nombre),
                                                                                                      apellidos(
                                                                                                              apellidos),
                                                                                                      carrera(carrera),
                                                                                                      mensualidad(
                                                                                                              mensualidad) {};
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
        while(!file.eof() && cont <= pos){
            if(cont < pos){
                string temp = "";
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

void print_vector_alumno(vector<Alumno> alumno_temp){
    for (auto i = alumno_temp.begin(); i != alumno_temp.end() ; i++) {
        cout<<"Nombre: "<<i->nombre<<endl;
        cout<<"Apellidos: "<<i->apellidos<<endl;
        cout<<"Mensualidad: "<<i->mensualidad<<endl;
        cout<<"Carrera: "<<i->carrera<<endl;
        cout<<"-----------------------------------------"<<endl;
    }
}


void test1(VariableRecord* variable){
    vector<Alumno> alumno_temp = variable->load();
    print_vector_alumno(alumno_temp);
    cout<<"Agregando alumnos"<<endl;
    cout<<"|||||||||||||||||||||||||||||||||||||||"<<endl;
    Alumno* alumno_1 = new Alumno("Angel","Tito","CS",1590);
    Alumno* alumno_2 = new Alumno("Ronaldo","Flores","CS",1427);
    Alumno* alumno_3 = new Alumno("Rodo","Vilcarromero","CS",1412);
    Alumno* alumno_4 = new Alumno("Pablo","Lachos","Civil",1320);
    Alumno* alumno_5 = new Alumno("Sebas","Vasquez","Mecatronica",2000);
    Alumno* alumno_6 = new Alumno("Mauricio","Espinoza","Electicidad",1999);
    Alumno* alumno_7 = new Alumno("Nicolas","Nasi","Bioingenieria",1250);
    Alumno* alumno_8 = new Alumno("Pedro","Ramirez","Administracion",1400);
    Alumno* alumno_9 = new Alumno("Peter","Nilson","Civil",1692);
    Alumno* alumno_10 = new Alumno("Roberto","Fernandez","Electrica",1945);
    variable->add(*alumno_1);
    variable->add(*alumno_2);
    variable->add(*alumno_3);
    variable->add(*alumno_4);
    variable->add(*alumno_5);
    variable->add(*alumno_6);
    variable->add(*alumno_7);
    variable->add(*alumno_8);
    variable->add(*alumno_9);
    variable->add(*alumno_10);
    alumno_temp = variable->load();
    print_vector_alumno(alumno_temp);
}

void test2(VariableRecord* variable){
    vector<Alumno> alumno_temp = variable->load();
    print_vector_alumno(alumno_temp);
    cout<<"Dupliquemos los alumnos con ADD"<<endl;
    cout<<"|||||||||||||||||||||||||||||||||||||||"<<endl;
    Alumno alumno_0 = variable->readRecord(0);
    Alumno alumno_1 = variable->readRecord(1);
    Alumno alumno_2 = variable->readRecord(2);
    Alumno alumno_3 = variable->readRecord(3);
    Alumno alumno_4 = variable->readRecord(4);
    Alumno alumno_5 = variable->readRecord(5);
    Alumno alumno_6 = variable->readRecord(6);
    Alumno alumno_7 = variable->readRecord(7);
    Alumno alumno_8 = variable->readRecord(8);
    Alumno alumno_9 = variable->readRecord(9);
    Alumno alumno_10 = variable->readRecord(10);
    variable->add(alumno_0);
    variable->add(alumno_1);
    variable->add(alumno_2);
    variable->add(alumno_3);
    variable->add(alumno_4);
    variable->add(alumno_5);
    variable->add(alumno_6);
    variable->add(alumno_7);
    variable->add(alumno_8);
    variable->add(alumno_9);
    variable->add(alumno_10);
    alumno_temp = variable->load();
    print_vector_alumno(alumno_temp);
}

int main(){
    VariableRecord* temp =  new VariableRecord;
    VariableRecord* temp2 =  new VariableRecord;
    test1(temp);
    test2(temp2);
};