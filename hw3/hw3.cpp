#include<iostream>
#include<string>

using namespace std;

int oddSum(int[], int, int i = 1);
void reverseString(string, int i = 0);
void mainMenu();
void goAgain();

int main(){

    mainMenu();
    return 0;


}

void mainMenu(){
    int holder;
    int result;
    int arySize;
    string word;
    /*  Ask the user what function they would like to see
        Verify their input to see if it's valid
        Depending on their answer run the function they wanted */
    cout << "Choose which function you want use \n";
    cout << "1. Add Odd Indices \n";
    cout << "2. Reverse String \n\n";

    cin >> holder;
    cin.ignore();
    do{
        if (holder == 1) {
            cout << "How many elements do you want your array to have? \n";
            cin >> arySize;
            int ary[arySize];
            for(int i = 0; i < arySize; i++) {
                cout << "\nEnter integer for index " << i << ":" << endl;
                cin >> ary[i];
            }
            /*  Run adding function
            Will return integer sum to main
            cout Sum */
            result = oddSum(ary, arySize);
           // result = oddSum(ary, arySize));
            cout << "The total is : " << result << endl;
            goAgain();
        }
        if (holder == 2) {
            //  Run string reversing function
            cout << "Please input the string you wish to reverse.\n\n";
            getline(cin, word);
            reverseString(word);
            cout << "\n\n";
            goAgain();
        }
        if(holder!=1 && holder!= 2){
            cout << "Please enter valid number \n\n";
            cin >> holder;
            //cin.ignore();
        }
    }
    while(holder!=1 && holder!= 2);
}

int oddSum(int ary[], int arySize, int i) {
    /*  When the most substring of the array is
        greater than or equal to (sizeof(array)/sizeof(array[0])) - 1 */
        if (i >= arySize)
            return 0;

    /*  If the most recently read character of the program
        Isn't the last odd number run the function again with i += 2 */
        return (ary[i] + oddSum(ary,arySize, (i+2)));
}

void reverseString(string word, int i){
    /*  When the most recent character of the string is
        read as \0 return from function */
        if (word.c_str()[i] == '\0') {
            return;
        }
    /*  If the most recently read character of the program
        Isn't \0 run the function again with i incremented */
        reverseString(word, i+1);
    //  cout the most recently read character
        cout << word.at(i);
}

void goAgain(){
    int holder;
    cout << "Would you like to: " << endl;
    cout << "1. Reset Program" << endl;
    cout << "2. Exit Program" << endl;
    cin >> holder;
    cin.ignore();
    do{
        if (holder == 1) {
            mainMenu();
        }
        if(holder!=1 && holder!= 2){
            cout << "Please enter valid number" << endl;
            cin >> holder;
            cin.ignore();
        }
    }
    while(holder!=1 && holder!= 2);
}
