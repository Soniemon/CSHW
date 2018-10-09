//Arvind Sundar
//afs170230

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool fileCheck(fstream&);
int fileRow(fstream&);
int fileCol(fstream&);
void fillArray(int**, fstream&, int, int);
bool intVerify(string);
void runGenerations(int**, int**, int, int, int);
void popMod(int**, int**, int, int);
void nextGen(int**, int**, int, int);
void rewriteFile(int**, fstream&, int, int);


int main() {

    //filestream for bacteria input and output
    fstream simFile;
    //stores the rows and cols in the file for array creation
    int row, col;
    //stores how many generations of the sim will be run
    int gens;
    //holds the input for generations
    string holder;
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
    //close the file
    simFile.close();

    cout << "Please input how many generations you want to run (Between 1 - 10)\n";

    //verify integer input
    getline(cin, holder);

    if (intVerify(holder)) {
        gens = stoi(holder);
    }

    while(!intVerify(holder) || (gens < 1 && gens > 10)) {
        cout << "Please enter a valid number\n\n";
        getline(cin, holder);
        if (intVerify(holder)) {
            gens = stoi(holder);
        }
    }

    //run the game
    runGenerations(bacAry, lifeAry, gens, row, col);

    //rewrite the file
    rewriteFile(bacAry, simFile, row, col);

    //free the allocated space
    delete [] bacAry;
    delete [] lifeAry;
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
    return;
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

bool intVerify(string input) {
    bool isInt = true;
    //loop through entire string to see if its an int
    //using unsigned as not to compare signed int to unsigned
    for (unsigned i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) {
            isInt = false;
            break;
        }
    }
    if (input.length() <= 0 || input.length()>2) {
        isInt = false;
    }
    return isInt;
}

void runGenerations(int** ary, int** mod, int gens, int rows, int cols) {
    //loop generation process the amount of times user input.
    for(int i = 0; i < gens; i++) {
        cout<<"hi"<<endl;
        //populate the modification array
        popMod(ary, mod, rows, cols);
        //advance generation by 1
        nextGen(ary, mod, rows, cols);
    }
}

void popMod(int** ary, int** mod, int rows, int cols) {
    //holds the position of the beginning of the 2d array
    int** anchor = ary;
    //holds the beginning value for each row when parsing cols
    int *aboveAnchor, *belowAnchor;
    //holds pointers for the surrounding area
    int **above, **around, **below;
    //holds how many surrounding entities are alive
    int surLife;
    //loop through the surrounding area of the pointer
    //make the main pointer loop through each row
    for(int i = 0; i < rows; i++) {
        //setting column anchor only if it is in array
        if(i != 0 ) {
            aboveAnchor = *(ary-1);
        } else {
            aboveAnchor = nullptr;
        }
        if((ary-anchor) < (rows-1)){
            belowAnchor = *(ary+1);
        } else {
            belowAnchor = nullptr;
        }
        //main pointer loops thru each column
        for(int j = 0; j < cols; j++){
            surLife=0;
            //set above pointer to up diagonal left of main
            if (aboveAnchor != nullptr) {
                above = ary-1;
                if (j!=0) {
                    *above += (j-1);
                } else {
                    *above += j;
                }
            }
            //set around to left of main pointer
            around = ary;
            if (j!=0) {
                *around += (j-1);
            } else {
                *around += j;
            }
            //set below pointer to down diagonal left of main
            if (belowAnchor != nullptr){
                below = ary+1;
                if (j!=0) {
                    *below += (j-1);
                } else {
                    *below += j;
                }
            }
            //move above pointer 3 times
            for(int k = 0; k < 3; k++){
                if((aboveAnchor == nullptr) || ((j>=(cols-1)) && (k == 2))){
                    break;
                }
                if((j==0)&&(k==0)){
                    continue;
                }
                if(**above==1){
                    surLife++;
                }
                ++*above;
            }
            //move same line pointer around target
            for(int k = 0; k < 3; k++){
                if((j>=(cols-1)) && (k == 2)){
                    break;
                }
                if(((j==0)&&(k==0)) || (k==1)){
                    continue;
                }
                    if(**around==1){
                        surLife++;
                    }
                ++*around;
            }

            //move below pointer 3 times
            for(int k = 0; k < 3; k++){
                if((belowAnchor == nullptr) || ((j>=(cols-1)) && (k == 2))){
                    break;
                }
                if((j==0)&&(k==0)){
                    continue;
                }
                if(**below==1){
                    surLife++;
                }
                ++*below;
            }

            if (surLife < 2 || surLife > 3) {
                **mod = 0;
                cout << "0 ";
            }
            if (surLife == 3) {
                **mod = 1;
                cout<<"1 ";
            }
            if (surLife == 2) {
                **mod = **ary;
                cout<<**ary<<" ";
            }

            ++*ary;
            ++*mod;
        }
        cout <<endl;
        *ary-=cols;
        *mod-=cols;
        ++ary;
        ++mod;
    }
}

void nextGen(int** ary, int** mod, int rows, int cols) {
    //based on the changes made to the modified array change main array
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            **ary = **mod;
            ++*ary;
            ++*mod;
        }
        *ary-=cols;
        *mod-=cols;
        ++ary;
        ++mod;
    }
}

void rewriteFile(int** ary, fstream& simFile, int rows, int cols) {
    //open the file with out and truncate tags
    simFile.open("simbac2.txt", ios::out | ios::trunc);

    //parse through entire array
    //if 0 ' ' if 1 '*'
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(**ary){
                cout << '*';
            } else {
                cout << ' ';
            }
            ++*ary;
        }
        cout << endl;
        *ary-=cols;
        ++ary;
    }
    ary-=rows;
    //write to file
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(**ary){
                simFile.put('*');
            } else {
                simFile.put(' ');
            }
            ++*ary;
        }
        simFile.put('\n');
        *ary-=cols;
        ++ary;
    }
}
