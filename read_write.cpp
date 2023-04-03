#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <climits>

using namespace std;

struct Alumno//Record
{
    char Codigo [5];
    char Nombre [11];
    char Apellidos [20];
    char Carrera [15];
};

ostream & operator << (ostream & stream, Alumno & p){
    stream << p.Codigo;
    stream << p.Nombre;
    stream << p.Apellidos;
    stream << p.Carrera;
    stream << "\n";
    stream << flush;
    return stream;
}

istream & operator >> (istream & stream, Alumno & p){
    stream.get(p.Codigo, 5);
    stream.get(p.Nombre, 11);
    stream.get(p.Apellidos, 20);
    stream.get(p.Carrera, 15);
    stream.get();
    return stream;
}

void readFromConsole(char buffer[], int size){
    string temp;
    cin >> temp;
    for(int i=0; i<size; i++)
        buffer[i] = (i < temp.size())? temp[i] : ' ';
    buffer[size-1] = '\0';
    cin.clear();
}

void testWrite(string filename){
    ofstream outFile;
    //escribir
    outFile.open(filename, ios::app);
    if(outFile.is_open()){
        //leer desde consola datos para person1
        Alumno person1;
        cout<<"Nombre:"; readFromConsole(person1.Nombre, 12);
        cout<<"Apellidos:"; readFromConsole(person1.Apellidos, 12);
        outFile << person1;
        outFile.close();

    }
    else
        cerr<<"No se pudo abrir el archivo\n";
}

void testRead(string filename)
{
    ifstream inFile;
    //leer
    inFile.open(filename);
    Alumno person2;
    if(inFile.is_open()){
        while(!inFile.eof()){
            inFile >> person2;
            cout << "Nombre:" << person2.Nombre << endl;
            cout << "Apellidos:"<< person2.Apellidos << endl;
        }
        inFile.close();
    }
    else
        cerr<<"No se pudo abrir el archivos\n";
}

struct FixedRecord{
    string archivo;
    int size;
    FixedRecord(string arch="../datos1.txt"){
        archivo=arch;
    }
    vector<Alumno>load(){
        vector<Alumno>a;
    }

};

void print(vector<Alumno>& v){
    for(auto i:v){
        cout<<"Codigo: "<<i.Codigo<<endl;
        cout<<"Nombre: "<<i.Nombre<<endl;
        cout<<"Apellidos: "<<i.Apellidos<<endl;
        cout<<"Carrera: "<<i.Carrera<<endl;
    }
}
int main()
{
    //testWrite("test.txt");
    //testRead("test.txt");
    string arc="../datos1.txt";
    vector<Alumno>a;
    ifstream file(arc,ios::in|ios::binary|ios::ate);
    const int size=51;
    int fileSize=file.tellg();
    int registers=fileSize/size;
    file.seekg(0,ios::beg);//devolvemos el puntero al inicio
    for(int i=0; i < registers;i++){
        Alumno person;
        file.seekg(i*size+2*i);
        cout<<"soy el i: "<<i<<" soy el puntero: "<<file.tellg()<<endl;
        file.get(person.Codigo,5,'\0');
        cout<<"soy el puntero: "<<file.tellg()<<endl;
        file.get(person.Nombre,11,'\0');
        cout<<"soy el puntero: "<<file.tellg()<<endl;
        file.get(person.Apellidos,20,'\0');
        cout<<"soy el puntero: "<<file.tellg()<<endl;
        file.get(person.Carrera,15,'\0');
        file.get();
        a.push_back(person);
    }
    print(a);
    return 0;
}