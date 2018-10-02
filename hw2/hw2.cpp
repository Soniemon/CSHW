#include <fstream>
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

void openFiles(string);
void vowelExtractor(string);
bool vowelChecker(char);

int main(){

    string filename;

    cout << "Please type in the name of the file you want to use!" << endl;
    cin >> filename;

    vowelExtractor(filename);
}


void vowelExtractor(string filename){
    fstream txtFile;
    string fileLine;
    string vFilename = "vowels_" + filename;
    int pos = 0;

//    txtFile.open(filename.c_str(), ios::in);
    while (!txtFile.eof()){
        txtFile.open(filename.c_str(), ios::in | ios::binary);
        txtFile.seekg(pos, ios::beg);
        getline(txtFile, fileLine);
        cout << fileLine << endl;
        pos = txtFile.tellg();
        txtFile.close();
        txtFile.open(vFilename.c_str(), ios::out | ios::app);
        for(int i = 0; i < fileLine.length(); i++) {
            if(vowelChecker(fileLine[i])) {
                txtFile << fileLine[i];
            }
        }
        txtFile.close();
    }
}

bool vowelChecker(char letter) {
    if (tolower(letter) == 'a' || tolower(letter) == 'e' || tolower(letter) == 'i' || tolower(letter) == 'o' || tolower(letter) == 'u' || tolower(letter) == '\n') {
        return true;
    }
    else{
        return false;
    }
}
