//Arvind Sundar
//afs170230


#include <fstream>
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool vowelChecker(char);
void vowelExtractor(string);

int main(){
    string filename;
    //enter filename variable
    cout << "Please type in the name of the file you want to use!" << endl;
    cin >> filename;

    vowelExtractor(filename);
}

void vowelExtractor(string filename){
    fstream txtFile;
    string newFile;
    //concatenate vowels_ to the beginning to make a new filename
    string vFilename = "vowels_" + filename;
    bool eof = false;
    //character that will be tested (test subject)
    char tSub;
    //open the file with the string the user input and have it in input mode
    txtFile.open(filename.c_str(), ios::in);

    while(!txtFile.good()){
        txtFile.clear();
        cout<<"Please you a valid filename"<<endl;
        cin>>filename;
        vFilename = "vowels_" + filename;
        txtFile.open(filename.c_str(), ios::in);
    }
    //while the end of file has not been reached
    while(!eof) {
        //receive a character from the file
        txtFile.get(tSub);
        //if the character was an eof break from loop
        if (txtFile.eof()) {
            eof = true;
            continue;
        }
        //check if the character is one of the allowed characters, if so add it to the new file string
        if (vowelChecker(tSub)) {
            newFile += tSub;
        }
    }

    //close the input file and then open up the vowels output file
    txtFile.close();
    txtFile.open(vFilename.c_str(), ios::out);
    //write new data to the output file
    txtFile << newFile;
}

bool vowelChecker(char letter) {
    // if a, e, i, o, u, or \n are found return true
    if (tolower(letter) == 'a' || tolower(letter) == 'e' || tolower(letter) == 'i' || tolower(letter) == 'o' || tolower(letter) == 'u' || tolower(letter) == '\n') {
        return true;
    }
    else{
        return false;
    }
}
