//Arvind Sundar
//afs170230

#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

bool fileCheck(fstream&);
int fileRow(fstream&);
int fileCol(fstream&);
void fillArray(int**, fstream&, int, int);
bool intVerify(string);
//void runGenerations(int**, int**, int);
//void rewriteFile(int**, fstream&);


int main() {

    //filestream for bacteria input and output
    fstream simFile;
    //stores the rows and cols in the file for array creation
    int row, col;
    //stores how many generations of the sim will be run
    int gens;
    //if file is bad give output error and close program
    if(!fileCheck(simFile)) {
        cout << "FILE ERROR\nMAKE SURE A VALID FILE IS BEING USED\n";
        return 1;
    }
    //find the amount of rows and cols for the array creation
    row = fileRow(simFile);
    col = fileCol(simFile);
    //create dynamically allocated arrays for the bacteria
    //create an pointer to an array of pointers
    int** bacAry = new int*[row];
    //for each pointer in that array create another array of integers
    for(int i = 0; i < row; i++) {
        *bacAry = new int[col];
        bacAry++;
    }
    //reset pos of pointer
    bacAry-=row;
    int** lifeAry = new int*[row];
    for(int i = 0; i < row; i++) {
        *lifeAry = new int[col];
        lifeAry++;
    }
    lifeAry-=row;
    //fill the array
    fillArray(bacAry, simFile, row, col);

    return 0;
}

bool fileCheck(fstream& simFile){
    //Open simbac.txt in bot input and output mode
    simFile.open("simbac.txt", ios::in);
    //If file is able to be opened return true
    if(simFile.is_open()){
        return true;
    }
    //else false
    return false;
}

int fileRow(fstream& simFile) {
    //counting through amount of rows in the file
    //this var just temporarily holds each row
    string holder;
    //counts how many rows there are
    int counter = 0;
    //loop through file taking in rows til end of file and inc rows
    while(!simFile.eof()){
        getline(simFile, holder);
        counter++;
    }
    //set file pointer back to start
    simFile.seekg(0L, ios::beg);
    simFile.clear();
    return counter;
}

int fileCol(fstream& simFile) {
    //counting through the amount of characters in a row
    //this string holds all the chars in a row
    string holder;
    //put a line into holder
    getline(simFile, holder);
    //set file pointer back to start
    simFile.seekg(0L, ios::beg);
    return holder.length();
}

void fillArray(int** ary, fstream& simFile, int rows, int cols) {
    //holds characters from the file
    char ch;
    //loop through the file putting data into the array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            simFile.get(ch);
            if(ch == '*'){
                **ary = 1;
            } else {
                **ary = 0;
            }
            ++*ary;
        }
        simFile.ignore();
        *ary-=cols;
        ++ary;
    }
    /*ary -= rows;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << **ary;
            ++*ary;
        }
        cout << endl;
        *ary-=cols;
        ++ary;
    }*/
}
