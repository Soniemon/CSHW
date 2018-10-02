//Arvind Sundar
//Kelvin Ojiako

#include <fstream>
#include <iostream>

using namespace std;

bool fileCheck(ifstream&, string);
int findSize(ifstream&);
int* fillArray(ifstream&, int*);
int lowestNum(int*);
int highestNum(int*);
int sumAll(int*);

int main() {

ifstream inFile;
string filename;
int arySize;

cout <<"Please enter filename\n\n";
cin >> filename;

while(!fileCheck(inFile, filename)) {

    cout << "Please enter valid filename\n\n";
    cin >> filename;

}

arySize = findSize(inFile);
cout << arySize<< endl;


}

bool fileCheck(ifstream& inFile, string filename) {
    inFile.open(filename.c_str());
    if(!inFile.is_open()) {
        return false;
    } else {
        return true;
    }
}

int findSize(ifstream& inFile) {
    cout << "running" <<endl;
    int holder;
    int counter = 0;

    while(!inFile.eof()) {
        if(inFile >> holder){
        counter++;
        }
    }
    cout << counter;
return counter;

}
