#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;
//reinterpret_cast<tipo>
// convierte un puntero de un tipo de dato a otro puntero de otro tipo de dato que pidamos en los < >
struct Record {
    char nombre[30];//c h a m o \0
    char carrera[20];
    int ciclo;

    void setData() {
        cout << "Alumno:";
        cin >> nombre;//chamo
        cout << "Carrera: ";
        cin >> carrera;
        cout << "Ciclo: ";
        cin >> ciclo;
    }

    void showData() {
        cout << "\nNombre: " << nombre;
        cout << "\nCarrera: " << carrera;
        cout << "\nCiclo : " << ciclo;
        cout << "\n";
    }

    string getKey() {
        string temp;
        for (auto l: nombre) {
            if (l != '\000') {
                temp += l;
            }else{
                break;
            }
        }
        return temp;
    }
};
ostream& operator<<(ostream&os,Record&alumno){
    os<<"\n";
    os<<"Nombre: "<<alumno.nombre<<endl;
    os<<"Apellido: "<<alumno.carrera<<endl;
    os<<"Cilo: "<<alumno.ciclo<<endl;
    return os;
}
class RandomFile {
private:
    string fileName;
    string indexName;
    //map: mantiene ordenado las entradas
    map<string, long> index;

public:
    RandomFile(string _fileName) {
        this->fileName = _fileName;
        this->indexName = _fileName + "_ind";
        readIndex();
    }

    ~RandomFile() {
        writeIndex();
    }

    /*
    * leer el indice desde disco - CLEAR
    */
    void readIndex() {
        ifstream file(fileName, ios::binary);
        if (!file.is_open()) throw "NO SE PUDO ABRIR, AYUDAAAA!!!!";
        else{
            while(!file.eof()){
                char s[30];
                long pos;
                file.read(s, 30);
                file.read(reinterpret_cast<char*>(&pos),sizeof(pos));
                index.insert({s,pos});
            }
        }
        file.close();
    }

    /*
    * Regresa el indice al disco - CLEAR
    */
    void writeIndex() {
        ofstream file(fileName, ios::binary);
        file.seekp(0,ios_base::beg);
        for (auto const &val: index) {
            file.write(val.first.data(),val.second);
            for(int i=0; i<30-val.first.length();i++){
                file<<'\0';
            }
            file.write(reinterpret_cast<const char*>(&val.second),sizeof(long));
        }
        file.close();
    }

    /*
    * Escribe el registro al final del archivo de datos. Se actualiza el indice. - clear
    */
    void write_record(Record record) {
        ofstream dataFile;
        dataFile.open(this->fileName, ios::app | ios::binary);
        long posFisica = dataFile.tellp();
        dataFile.write((char *) &record, sizeof(Record));
        this->index[record.getKey()] = posFisica;
        dataFile.close();
    }


    /*
    * Busca un registro que coincida con la key - clear
    */
    Record search(string key) {
        auto encontrar = index.find(key);
        if (encontrar == index.end()) {
            throw "La llave que coloco no existe";
        }else{
            Record result;
            fstream file(fileName, ios::in | ios::out | ios::binary);
            file.seekg(encontrar->second,ios::beg);
            file.read(result.nombre, 30);
            file.read(result.carrera, 20);
            file.read(reinterpret_cast<char*>(&result.carrera), sizeof(result.carrera));
            return result;
        }
    }

    /*
   * Muestra todos los registros de acuerdo como fueron insertados en el archivo de datos - CLEAR
   */
    void scanAll() {
        ifstream file(this->fileName,ios::binary);
        file.seekg(0,ios_base::beg);
        if(!file.is_open()){throw "NO SE ABRIO, AYUDAAAA!!!";}
        else{
            Record alum{};
            file.read(alum.nombre,30);
            file.read(alum.carrera,30);
            file.read(reinterpret_cast<char*>(&alum.ciclo),sizeof(alum.ciclo));
            cout<<alum;
        }
        file.clear();
        file.close();
    }

    /*
   * Muestra todos los registros de acuerdo a como estan ordenados en el indice - CLEAR
   */
    void scanAllByIndex() {
        ifstream file(this->fileName,ios::binary);
        if(!file.is_open()) throw "NO SE ABRIO, AYUDAAAA!!!";
        else{
            for(const auto&i:index){
                Record re;
                file.seekg(i.second,ios::beg);
                file.read(re.nombre,30);
                file.read(re.nombre,30);
                file.read(reinterpret_cast<char*>(&re.ciclo),sizeof(re.ciclo));
                cout<<re;
            }
        }
        file.close();
    }

};


