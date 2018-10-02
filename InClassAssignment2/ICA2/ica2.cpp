//Arvind Sundar
//Kelvin Ojiako

#include <fstream>
#include <iostream>

using namespace std;

bool fileCheck(ifstream&, string);
int findSize(ifstream&);
void fillArray(ifstream&, int*, int);
int lowestNum(int*, int);
int highestNum(int*, int);
double sumAll(int*, int);

int main() {

    ifstream inFile;
    string filename;
    int arySize;
    int lowest;
    int highest;
    double sum;
    double avg;

     cout <<"Please enter filename\n\n";
    cin >> filename;

    while(!fileCheck(inFile, filename)) {

        cout << "Please enter valid filename\n\n";
        cin >> filename;

    }

    arySize = findSize(inFile);

    int* ary = new int[arySize];

    fillArray(inFile ,ary, arySize);

    lowest = lowestNum(ary, arySize);
    highest = highestNum(ary, arySize);
    sum = sumAll(ary, arySize);
    avg = (sum/arySize);
    cout <<"Lowest:" << lowest << endl << "Highest: " << highest << endl <<"Sum: "<< sum << endl <<"Avg: "<< avg << endl;

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
    int holder;
    int counter = 0;

    while(!inFile.eof()){
        inFile >> holder;
        counter++;
    }
    inFile.clear();
    return counter;

}

void fillArray(ifstream& inFile, int *ptr, int arySize){
    inFile.seekg(0l, ios::beg);
    for (int i = 0; i < arySize; i++) {
        inFile >> *ptr;
        ptr++;
    }
    //return ptr -= arySize;
}

int lowestNum(int *ptr, int arySize) {
int held;
held = *ptr;
ptr++;

    for(int i = 0; i < arySize -1; i++) {
        if (held > *ptr) {
            held = *ptr;
        }
        ptr++;
    }
return held;
}

int highestNum(int *ptr, int arySize) {
int held;
held = *ptr;
ptr++;

    for(int i = 0; i < arySize -1; i++) {
        if (held < *ptr) {
            held = *ptr;
        }
        ptr++;
    }
return held;
}

double sumAll(int *ptr, int arySize) {
double sum = 0;

    for(int i = 0; i < arySize; i++){
        sum += *ptr;
        ptr++;
    }
return sum;
}


