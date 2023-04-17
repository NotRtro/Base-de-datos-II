//
// Created by rvilc on 5/04/2023.
//
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;
struct Alumno
{
    char codigo[5];
    char nombre[11];
    char apellidos[20];
    char carrera[15];
    int ciclo;
    float mensualidad;
    int nexdel = -2; // Indica que el registro no ha sido eliminado
    Alumno(){}
    Alumno(string code, string nomb, string ape, string carr, int cic, float mensu): ciclo(cic), mensualidad(mensu){
        for (int i = 0; i < 4; ++i) {
            codigo[i]=code[i];
        }codigo[4]='\0';
        for (int i = 0; i < 10; ++i) {
            nombre[i]=nomb[i];
        }nombre[10]='\0';
        for (int i = 0; i < 19; ++i) {
            apellidos[i]=ape[i];
        }apellidos[19]='\0';
        for (int i = 0; i < 14; ++i) {
            carrera[i]=carr[i];
        }carrera[14]='\0';
    }

    friend ostream& operator<<(ostream& stream, Alumno const& p)
    {
        stream << "\n";
        stream << p.codigo<<" ";
        stream << p.nombre<<" ";
        stream << p.apellidos<<" ";
        stream << p.carrera<<" ";
        stream << p.ciclo<<" ";
        stream << p.mensualidad<<" ";
        stream << flush;
        return stream;
    }
    friend istream & operator >> (istream & stream, Alumno & p){
        stream.get(p.codigo, 5);//usar ignore
        stream.ignore();
        stream.get(p.nombre, 11);
        stream.ignore();
        stream.get(p.apellidos, 20);
        stream.ignore();
        stream.get(p.carrera, 15);
        stream.ignore(INT_MAX,'\n');
        return stream;
    }
};
class FixedRecord{
private:
    string archivo;

    // para acceso rapido
    int get_header(){
        ifstream file(archivo, ios::binary);
        int h;
        file.read((char*)&h,sizeof(int));
        file.close();
        return h;
    }
    void set_header(int n){
        fstream file(archivo, ios::binary | ios::out | ios::in);
        file.seekp(0, ios_base::beg);
        file.write((char*)&n,sizeof(int));
        file.close();
    }
    void readFromConsole(char container[], int size)
    {
        string temp;
        getline(cin,temp);
        for (int i = 0; i < size; i++)
            container[i] = (i < temp.size()) ? temp[i] : ' ';
        cin.clear();
    }
public:
    FixedRecord(string name){
        this->archivo = name;
        int header = -1;

        ofstream(archivo, std::ofstream::app | std::fstream::binary);
        fstream file(archivo, ios::binary | ios::in | ios::out);
        file.seekg(0, ios::end);
        if(file.tellg()==0){
            file.write((char*)&header,sizeof(int));
            file.close();
        }
    }
    vector<Alumno> load(){
        ifstream file(archivo, ios::binary);
        if (!file.is_open()) out_of_range("No se logro abrir el archivo");
        vector<Alumno> result;
        Alumno alumno;

        file.seekg(sizeof(int));
        while (!file.eof()){
            alumno = Alumno();
            file.read((char *)&alumno, sizeof(Alumno));

            if (alumno.nexdel == -2)
                result.push_back(alumno);
        }
        result.pop_back();
        file.close();
        return result;
    }
    void add(Alumno &record){
        fstream arch(archivo, ios::binary | ios::in | ios::out);
        if (!arch.is_open()) out_of_range("No se logro abrir el archivo");
        if (!arch.is_open())
            cerr << "No se pudo abrir el archivo\n";
        cout << "Codigo: ";
        readFromConsole(record.codigo, 5);
        cout << "Nombre: ";
        readFromConsole(record.nombre, 11);
        cout << "Apellidos: ";
        readFromConsole(record.apellidos, 20);
        cout << "Carrera: ";
        readFromConsole(record.carrera, 15);
        cout << "Ciclo: ";
        cin >> record.ciclo;
        cout << "Mensualidad: ";
        cin >> record.mensualidad;
        int header = this->get_header();
        if(header == -1){
            arch.seekp(0,ios::end);
            arch.write((char *)&record, sizeof(record));
            arch.close();
        }
        else{
            //Empieza el algoritmo
            Alumno temporal=this->readRecord(this->get_header()); //Optenemos el elemento
            //que apunta la cabecera
            int temp_nextdel=temporal.nexdel; //Aqui guardamos el nextdel del primer
            //eliminado
            //Luego colocar el nuevo elemento en donde apunta la cabecera. AQUUIIIIIIIIIII
            arch.seekp (0, arch.beg);
            arch.seekp(sizeof(int),ios_base::cur); // Tamanio del header
            //
            arch.seekp(this->get_header() * (sizeof(Alumno)),ios_base::cur);
            arch.write((char *)&record, sizeof(record));
            //
            this->set_header(temp_nextdel);
            arch.close();
        }
    }
    Alumno readRecord(int pos){
        ifstream arch(archivo, ios::binary);
        if (!arch.is_open()) out_of_range("No se logro abrir el archivo");
        Alumno aux;
        arch.seekg(pos * (sizeof(Alumno))+sizeof(int), ios_base::beg);
        arch.read((char*)&aux,sizeof(Alumno));
        arch.close();
        return aux;
    }
    bool eliminar(int pos){
        int header=this->get_header();
        this->set_header(pos);
        fstream file(archivo, ios::binary | ios::out | ios::in);
        file.seekp(0,ios_base::beg);
        file.seekp(sizeof(int));
        file.seekp(pos*sizeof(Alumno),ios_base::cur);
        file.seekp(sizeof(Alumno)-sizeof(int),ios_base::cur);
        file.write((char*)&header,sizeof(int));
        file.close();

        return true;
    }

};

void completarListaAlumnos(vector<Alumno>&alum){
    Alumno a1("0010","Ronaldo","Flores Soto","Computacion",7,1600);
    Alumno a2("0020","Dylan","Soto de Flores","Computacion",7,1900);
    Alumno a3("0030","Rodo","Vilcarromero","Mecatronica",7,1800);
    Alumno a4("0040","Angel","Titel","Computacion",7,1500);
    Alumno a5("0050","Chamo","De Venezuela","Extorsionar",7,1400);
    Alumno a6("0060","Jeff","El loco Latex","Extorsion Pro.",7,1500);
    Alumno a7("0070","Jalado","En Ada pero feliz","Troste",7,2000);
    Alumno a8("0080","uvuvwevwevwe onyetenyevwe ugwemuhwem osas","xd","Africa",7,2200);
    Alumno a9("0090","Aprobar","BaseDatos2","EsMiMeta",7,2100);
    Alumno a10("10","SinIdeas","AYUDAAAAAAAAA",":(((((",7,2300);
    Alumno a11("1","Por la tarea","Me quede en casa :(","no se que poner",7,3100);
    Alumno a12("2","SinPiedad","Sin Dolor","Karate Kid",7,1900);
    Alumno a13("4","ADA","JuancitoTuTerror","uwu",7,2000);
    Alumno a14("05","Juancito","Gutierrez","Teo computacion",7,1600);
    Alumno a15("100","Valentin","Quezada","Computacion",7,1600);
    Alumno a16("20000000","Enzo","Camizan","Computacion",7,1600);
    Alumno a17("300","Arturo","Dinastia solin","Industrial",7,1600);
    Alumno a18("040","Ramiro","Montanhez","Civil",7,1600);
    Alumno a19("50159715","Sergio","Quizpe","Ecuacion Diferencial",7,1600);
    Alumno a20("600000","Baloo","flores soto","ser perrito uu",7,1600);
    alum.push_back(a1);alum.push_back(a2);alum.push_back(a3);alum.push_back(a4);alum.push_back(a5);alum.push_back(a6);
    alum.push_back(a7);alum.push_back(a8);alum.push_back(a9);alum.push_back(a10);alum.push_back(a11);alum.push_back(a12);
    alum.push_back(a13);alum.push_back(a14);alum.push_back(a15);alum.push_back(a16);alum.push_back(a17);alum.push_back(a18);
    alum.push_back(a19);alum.push_back(a20);
}


int main()
{
    FixedRecord p1("datos1_2.txt");
    //vector<Alumno> temp;
    //completarListaAlumnos(temp);
   // for (auto i: temp) {
       //
       // p1.add(i);
    //}
    Alumno a;
    p1.add(a);
    return 0;
}