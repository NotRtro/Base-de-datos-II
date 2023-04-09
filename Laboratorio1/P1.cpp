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
    stream << p.Codigo<<" ";
    stream << p.Nombre<<" ";
    stream << p.Apellidos<<" ";
    stream << p.Carrera<<" ";
    stream << "\n";
  //  stream << flush;
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
        //print(a);
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
            file.seekg(pos*size_array+ pos);
            file>>a;
            return a;
            }else
                cout<<"No se pudo abrir"<<endl;
        }

};
void completarListaAlumnos(vector<Alumno>&alum){
    Alumno a1("0010","Ronaldo","Flores Soto","Computacion");
    Alumno a2("0020","Dylan","Soto de Flores","Computacion");
    Alumno a3("0030","Rodo","Vilcarromero","Mecatronica");
    Alumno a4("0040","Angel","Titel","Computacion");
    Alumno a5("0050","Chamo","De Venezuela","Extorsionar");
    Alumno a6("0060","Jeff","El loco Latex","Extorsion Pro.");
    Alumno a7("0070","Jalado","En Ada pero feliz","Troste");
    Alumno a8("0080","uvuvwevwevwe onyetenyevwe ugwemuhwem osas","xd","Africa");
    Alumno a9("0090","Aprobar","BaseDatos2","EsMiMeta");
    Alumno a10("10","SinIdeas","AYUDAAAAAAAAA",":(((((");
    Alumno a11("1","Por la tarea","Me quede en casa :(","no se que poner");
    Alumno a12("2","SinPiedad","Sin Dolor","Karate Kid");
    Alumno a13("4","ADA","JuancitoTuTerror","uwu");
    Alumno a14("05","Juancito","Gutierrez","Teo computacion");
    Alumno a15("100","Valentin","Quezada","Computacion");
    Alumno a16("20000000","Enzo","Camizan","Computacion");
    Alumno a17("300","Arturo","Dinastia solin","Industrial");
    Alumno a18("040","Ramiro","Montanhez","Civil");
    Alumno a19("50159715","Sergio","Quizpe","Ecuacion Diferencial");
    Alumno a20("600000","Baloo","flores soto","ser perrito uu");
    alum.push_back(a1);alum.push_back(a2);alum.push_back(a3);alum.push_back(a4);alum.push_back(a5);alum.push_back(a6);
    alum.push_back(a7);alum.push_back(a8);alum.push_back(a9);alum.push_back(a10);alum.push_back(a11);alum.push_back(a12);
    alum.push_back(a13);alum.push_back(a14);alum.push_back(a15);alum.push_back(a16);alum.push_back(a17);alum.push_back(a18);
    alum.push_back(a19);alum.push_back(a20);
}

int main()
{
    string archivo="../Test1.txt";
    FixedRecord f(archivo);
    vector<Alumno>lista;
    completarListaAlumnos(lista);

    for(auto& i:lista){
        f.add(i);
    }
    auto copyList=f.load();
    print(copyList);
    auto a1=f.readRecord(0);
    cout<<a1<<endl;
    auto a2=f.readRecord(7);
    cout<<a2<<endl;
    auto a3=f.readRecord(5);
    cout<<a3<<endl;
    auto a4=f.readRecord(3);
    cout<<a4<<endl;
    return 0;
}