#include "RandomFile.h"

using namespace std;

void writeFile(RandomFile& file) {

    Record record;
    for (int i = 0; i < 1; i++) {
        record.setData();
        file.write_record(record);
    }
    auto nuevo=file.search(record.getKey());
    cout << nuevo;

}

void readFile(RandomFile& file) {
    cout << "--------- show all data -----------\n";
    file.scanAll();
    cout << "--------- show all sorted data -----------\n";
    file.scanAllByIndex();
}

int main() {
    RandomFile f("../data.dat");
//    writeFile(f);
//    readFile(f);

    return 0;
}