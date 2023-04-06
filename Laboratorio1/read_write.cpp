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
    Alumno(){}
    Alumno(string code, string nomb, string ape, string carr){
        for (int i = 0; i < 4; ++i) {
            Codigo[i]=code[i];
        }Codigo[4]='\0';
        for (int i = 0; i < 10; ++i) {
            Nombre[i]=nomb[i];
        }Nombre[10]='\0';
        for (int i = 0; i < 19; ++i) {
            Apellidos[i]=ape[i];
        }Apellidos[19]='\0';
        for (int i = 0; i < 14; ++i) {
            Carrera[i]=carr[i];
        }Carrera[14]='\0';
    }
};

ostream & operator << (ostream & stream, Alumno & p){
    stream << "\n";
    stream << p.Codigo<<" ";
    stream << p.Nombre<<" ";
    stream << p.Apellidos<<" ";
    stream << p.Carrera<<" ";
    stream << flush;
    return stream;
}

istream & operator >> (istream & stream, Alumno & p){
    stream.get(p.Codigo, 5);//usar ignore
    stream.ignore();
    stream.get(p.Nombre, 11);
    stream.ignore();
    stream.get(p.Apellidos, 20);
    stream.ignore();
    stream.get(p.Carrera, 15);
    stream.ignore(INT_MAX,'\n');
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
struct FixedRecord {
    string archivo;
    const int size_array=51;
    FixedRecord(string arch = "../datos1.txt") {
        archivo = arch;
    }

    vector<Alumno> load() {
        vector<Alumno> a;
        ifstream file(archivo, ios::in | ios::binary | ios::ate);
        int fileSize = file.tellg();
        int registers = fileSize / size_array;//cant registros
        file.seekg(0, ios::beg);//devolvemos el puntero al inicio
        for (int i = 0; i < registers; i++) {
            Alumno person;
            file>>person;
            a.push_back(person);
        }
        file.close();
        print(a);
        return a;
    }

    void add(Alumno record) {
        ofstream file(archivo,ios::app|ios::binary);
        int sCodigo = strlen(record.Codigo); //5
        int sNombre = strlen(record.Nombre); //11
        int sApellido = strlen(record.Apellidos);//20
        int sCarrera = strlen(record.Carrera);//15
        if (sCodigo < 4) {
            for (int i = sCodigo; i < 4; i++) {
                record.Codigo[i] = ' ';
            }
        }
        if (sNombre < 10) {
            for (int i = sNombre ; i < 10; i++) {
                record.Nombre[i] = ' ';
            }
        }
        if (sApellido < 19) {
            for (int i = sApellido; i < 19; i++) {
                record.Apellidos[i] = ' ';
            }
        }
        if (sCarrera < 14) {
            for (int i = sCarrera; i < 14; i++) {
                record.Carrera[i] = ' ';
            }
        }
        file<<record;
    }

    Alumno readRecord(int pos){
        ifstream file(archivo,ios::ate);
        if(file.is_open()){
            int fileSize = file.tellg();
            Alumno a;
            int sz = fileSize/size_array;
            if(pos<1||pos>sz){
                while(pos<1||pos>sz){
                    cout<<"Ingrese un valor valido entre 1 y "<<sz<<": ";
                    cin>>pos;
                }
            }
            --pos;//3
            file.seekg(pos*size_array+2*pos);
            file>>a;
            return a;
            }else
                cout<<"No se pudo abrir"<<endl;
        }

};

int main()
{
    string archivo="../datos1.txt";
    FixedRecord f;
   // auto a= f.load();


    auto b=f.readRecord(0);
    cout<<b;
    return 0;

}
