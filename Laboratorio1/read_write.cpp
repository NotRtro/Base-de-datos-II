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
    stream.get(p.Codigo, 5);//usar ignore
    stream.get(p.Nombre, 11);
    stream.get(p.Apellidos, 20);
    stream.get(p.Carrera, 15);
    stream.get();//omite caracteres stream.ignore(INT_MAX,'\n');
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
        cout<<"Codigo: "; readFromConsole(person1.Codigo, 5);
        cout<<"Nombre: "; readFromConsole(person1.Nombre, 11);
        cout<<"Apellidos: "; readFromConsole(person1.Apellidos, 20);
        cout<<"Carrera: "; readFromConsole(person1.Carrera, 15);
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

void print(vector<Alumno>& v){
    for(auto i:v){
        cout<<"Codigo: "<<i.Codigo<<endl;
        cout<<"Nombre: "<<i.Nombre<<endl;
        cout<<"Apellidos: "<<i.Apellidos<<endl;
        cout<<"Carrera: "<<i.Carrera<<endl;
    }
}
struct FixedRecord{
    string archivo;
    int size;
    FixedRecord(string arch="../datos1.txt"){
        archivo=arch;
    }
    vector<Alumno>load(){
        vector<Alumno>a;
        ifstream file(archivo,ios::in|ios::binary|ios::ate);
        const int size=51;
        int fileSize=file.tellg();
        int registers=fileSize/size;//cant registros
        file.seekg(0,ios::beg);//devolvemos el puntero al inicio
        int s;
        for(int i=0; i < registers;i++){
            Alumno person;
            file.seekg(i*size+2*i);
//            cout<<"soy el i: "<<i<<" soy el puntero: "<<file.tellg()<<endl;
            file.get(person.Codigo,5,'\0');
            s=file.tellg();
            file.seekg(s+1);
//            cout<<"soy el puntero: "<<file.tellg()<<endl;
            file.get(person.Nombre,11,'\0');
            s=file.tellg();
            file.seekg(s+1);
            //cout<<"soy el puntero: "<<file.tellg()<<endl;
            file.get(person.Apellidos,20,'\0');
            s=file.tellg();
            file.seekg(s+1);
//            cout<<"soy el puntero: "<<file.tellg()<<endl;
            file.get(person.Carrera,15,'\0');
            file.get();
            a.push_back(person);
        }

        file.close();
        print(a);
        return a;
    }

    void add(Alumno record){

    }

};

int main()
{
    string archivo="../datos1.txt";
//    testWrite(archivo);
//    testRead(archivo);
    ofstream file(archivo,ios::app|ios::binary);
    Alumno a;
    string code,nombre,ape,carr;

    cout<<"Ingresar codigo: ";cin>>code;
    if (code.length()< 4) {
        for (int i = code.length(); i < 4; i++) {
            code += " ";
        }
    }
    for (int i = 0; i < 10; i++) {
        a.Codigo[i] = code[i];
    }
    cout<<"Ingresar nombre: ";cin>>nombre;
    if (nombre.length() < 10) {
        for (int i = nombre.length(); i < 4; i++) {
            nombre += " ";
        }
    }
    for (int i = 0; i < 10; i++) {
        a.Nombre[i] = nombre[i];
    }
    cout<<"Ingresar apellidos: ";cin>>ape;
    if (ape.length() < 19) {
        for (int i = ape.length(); i < 19; i++) {
            ape += " ";
        }
    }
    for (int i = 0; i < 19; i++) {
        a.Apellidos[i] = ape[i];
    }
    cout<<"Ingresar carrera: ";cin>>carr;
    if (carr.length() < 14) {
        for (int i = carr.length(); i < 14; i++) {
            carr += " ";
        }
    }
    for (int i = 0; i < 14; i++) {
        a.Carrera[i] = carr[i];
    }
    cout<<a.Codigo<<" "<<a.Nombre<<" "<<a.Apellidos<<" "<<a.Carrera<<endl;
    return 0;
}
