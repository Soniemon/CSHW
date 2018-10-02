//Arvind Sundar
//afs170230

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <string>
#include <cmath>

using namespace std;

void mainMenu();
void reserveTickets();
bool intVerify(string);
bool charVerify(string);
int findAudCol(fstream&);
int findAudRow(fstream&);
void displayAud(fstream&, string&, int, int);
string scrubdRows(string, int);
int askSeat(int, int, string, int&, char&);
int amountTickets(string);
bool reserveCheck(fstream&, int, int);
void showReserve(fstream&, int, char, int, int, string);
void saveData(fstream&, string, int);
int findBetter(fstream&, int, int, int, int);
void finalOutput();

//so i can get any chunk of the alpha off this string
string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(){

//Explain the purpose of the program
cout << "This program will allow you to reserve ";
cout << "seats for the Avengers 4 Movie\n\n";

//Run the main menu
mainMenu();
finalOutput();

}

void mainMenu(){
    string holder;
    int iHolder;

    //Prompt the user if the about what they'd like to do
    cout << "Would you like to :\n\n";
    cout << "1. Reserve Tickets\n";
    cout << "2. Exit Program\n\n";
    getline(cin, holder);
    //if holder is in int safely convert string to int
    if (intVerify(holder)) {
        iHolder = stoi(holder);
    }
    //if entry isn't valid keep prompting and looping
    while(!intVerify(holder) || (iHolder != 1 && iHolder != 2)) {
        cout << "Please enter a valid number\n\n";
        getline(cin, holder);
        if (intVerify(holder)) {
            iHolder = stoi(holder);
        }
    }
    //If 1 is pressed proceed with reserving, if 2 end program
    if (iHolder == 1) {
        reserveTickets();
    }
    if (iHolder == 2) {
        return;
    }
    return;
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

    if (input.length() <= 0 || input.length()>3) {
        isInt = false;
    }
    return isInt;
}

bool charVerify(string input) {
    bool isChar = true;
    //check first char of string to see if char
    //if length isn't 1 not a char
    if(input.length()!=1) {
        isChar = false;
    }
    if(!isalpha(input[0])) {
        isChar = false;
    }
    return isChar;
}

void reserveTickets(){
    //string for sanitizing inputs
    string charInput;
    //character var for holding y/n input
    char holder;
    //variables holding size of auditorium
    int audCol, audRow;
    //variable holding the starting seat the person wants
    int userSeat, uRow;
    char uCol;
    //Holds distance from best available
    int bestA;
    //the alphabet chunk will be assigned to here
    string colName;
    //variables holding the amount of each type of ticket the user wants (customer tickets)
    int aCTickets, cCTickets, sCTickets, tCTickets;
    //Hold the string that will be inserted into the file
    string ticketLetters;
    //opening the data file with input and output flags
    fstream audFile;
    audFile.open("A1.txt", ios::in | ios::out | ios::binary);
    //finding the number of columns
    audCol = findAudCol(audFile);
    //finding number of rows
    audRow = findAudRow(audFile);
    //Show the current setup of the auditorium
    displayAud(audFile, colName, audCol, audRow);
    //Ask user which seat they want to be in
    userSeat = askSeat(audRow, audCol, colName, uRow, uCol);
    cout << "\n";
    //Ask user how much of each ticket they want
    aCTickets = amountTickets(" adult ");
    cCTickets = amountTickets(" child ");
    sCTickets = amountTickets(" senior ");
    cout << "\n";
    tCTickets = aCTickets + cCTickets + sCTickets;
    ticketLetters.append(aCTickets,'A');
    ticketLetters.append(cCTickets,'C');
    ticketLetters.append(sCTickets,'S');

    //check if the reservations are open if so ask if they'd
    //like to complete reservation
    if(reserveCheck(audFile, userSeat, tCTickets)) {
        showReserve(audFile, uRow, uCol, audRow, audCol, ticketLetters);
        //Ask if they'd like to reserve the seats
        cout << "\nWould you like to reserve these seats (Y/N)\n\n";
        getline(cin, charInput);
        if (charVerify(charInput)) {
            holder = charInput.c_str()[0];
        }
        while(!charVerify(charInput) || (toupper(holder) != 'Y' && toupper(holder) != 'N')) {
            cout << "\nPlease give a valid character (Y/N)\n\n";
            getline(cin, charInput);
            if (charVerify(charInput)) {
                holder = charInput.c_str()[0];
            }
        }
        if (toupper(holder) == 'Y') {
            saveData(audFile, ticketLetters, userSeat);
            audFile.close();
            cout << "\nYour reservation has been made!\n\n";
            mainMenu();
        }
        if (toupper(holder) == 'N') {
            cout << "\nReservation canceled\n\n";
            mainMenu();
        }
    }

    else {
        //attempt to find better seats
        bestA = findBetter(audFile, tCTickets, audCol, uRow, userSeat);
        if(reserveCheck(audFile, (userSeat + bestA), tCTickets)){
            cout << "\nThe seats you wanted are not available...\n\n";
            cout << "However, these seats are.\n\n";
            //run show reserve with uCol starting from row wanted
            showReserve(audFile, uRow, (uCol + bestA), audRow, audCol, ticketLetters);
            //ask if they'd like reserve these seats
            cout << "\nWould you like to reserve these seats (Y/N)\n\n";
            getline(cin, charInput);
            if (charVerify(charInput)) {
                holder = charInput.c_str()[0];
            }
            while(!charVerify(charInput) || (toupper(holder) != 'Y' && toupper(holder) != 'N')) {
                cout << "\nPlease give a valid character (Y/N)\n\n";
                getline(cin, charInput);
                if (charVerify(charInput)) {
                    holder = charInput.c_str()[0];
                }
            }
            if (toupper(holder) == 'Y') {
                saveData(audFile, ticketLetters, (userSeat + bestA));
                audFile.close();
                cout << "\nYour reservation has been made!\n\n";
                mainMenu();
            }
            if (toupper(holder) == 'N') {
                cout << "\nReservation canceled\n\n";
                mainMenu();
            }
        }
        else {
            cout << "\nThe type of seats you are looking for cannot be accommodated with our current space.\n";
            cout << "Sorry for the inconvenience.\n\n";
            audFile.close();
            mainMenu();
        }
    }
    return;
}

int findAudCol(fstream &audFile) {
    //Read in a line from the file
    string columns;
    audFile.seekg(0L,ios::beg);
    getline(audFile, columns);
    //return the number of characters in the string
    //indicating # of columns
    return columns.length() - 1;
}

int findAudRow(fstream &audFile) {
    //have a string hold lines for input
    string garbageHolder;
    //counts the amount of lines
    int counter = 0;
    //sets the file to the beginning because we're passing by ref
    audFile.seekg(0L,ios::beg);

    //while the eof hasn't been reached read in a line and count it as another row
    while (!audFile.eof()) {
        getline(audFile, garbageHolder);
        counter++;
    }
    //return the number of rows
    return counter;
}

void displayAud(fstream &audFile, string &colName, int audCol, int audRow) {
    //stands for scrubbed display row
    string sdRow;
    //only the amount of letters for the rows will show up
    colName.assign(alphabet.c_str(), audCol);
    cout << "\n  " << colName << endl;
    //sets the file to the beginning because we're passing by ref
    audFile.seekg(0L,ios::beg);
    //Loop and read in all the lines into a string array
    for(int i = 0; i < audRow; i++) {
        getline(audFile, sdRow);
        //Scrub rows so user only sees # and .
        cout << (i +1) << " " << scrubdRows(sdRow, audCol) << endl;
    }
    return;
}

string scrubdRows(string sRow, int audCol) {
    //iterate through every character and if it isn't a period make it a #
    for (int i = 0; i < audCol; i++) {
        if(sRow[i] != '.' && sRow[i] != '\r'){
            sRow[i] = '#';
        }
    }
    return sRow;
}

int askSeat(int audRow, int audCol, string colName, int &uRow, char &uCol){
    //Holds initial input for user's row and column before converted to data types
    string inRow, inCol;
    //Get the position in the file where the user wants their beginning seat to be
    cout << "\nPlease input the row you wish to sit in: " << endl;
    getline(cin, inRow);
    if(intVerify(inRow)) {
        uRow = stoi(inRow);
    }
    while (!intVerify(inRow) || (uRow < 1 || uRow > audRow)) {
        cout << "\nPlease input a valid row number: ";
        getline(cin, inRow);
        if(intVerify(inRow)) {
            uRow = stoi(inRow);
        }
    }
    cout << "\nPlease input the letter of the first seat you wish to sit in: " << endl;
    getline(cin, inCol);
    if(charVerify(inCol)) {
        uCol = inCol.c_str()[0];
    }
    while (!charVerify(inCol) || colName.find(toupper(uCol)) == string::npos) {
        cout << "\nPlease input a valid column letter: ";
        getline(cin, inCol);
        if(charVerify(inCol)) {
            uCol = inCol.c_str()[0];

        }
    }
    //to get the position of the seat in the file i need to
    //multiply (uRow - 1) by (audCol + 2) to fill in the characters
    //in the row behind, then add the position of the char in the alphabet to get the seat
    return (((uRow - 1) * (audCol + 2)) + colName.find(toupper(uCol)));

}

int amountTickets (string ageGroup) {
    //Whenever a number greater than 0 is input return it.
    string inputTickets;
    int numTickets;
    cout << "Please enter the amount of" << ageGroup << "tickets you would like to purchase: ";
    getline(cin, inputTickets);
    if (intVerify(inputTickets)) {
        numTickets = stoi(inputTickets);
        }
    while (!intVerify(inputTickets) || (numTickets < 0))
    {
        cout << "Please enter a valid number" << endl;
        getline(cin, inputTickets);
        if (intVerify(inputTickets)) {
            numTickets = stoi(inputTickets);
            }
        }
    return numTickets;
}

bool reserveCheck(fstream &audFile, int filePos, int seatsInSeq){
    //look at the file and move over for where the sequence of seats is
    //If there is a taken seat return false
    bool isOpen = true;
    char ch;
    audFile.seekg(filePos, ios::beg);

    for (int i = 0; i < seatsInSeq; i++) {
        audFile.get(ch);
        if (ch != '.' || audFile.eof() ){
            isOpen = false;
        }
    }
    return isOpen;
}

void showReserve(fstream &audFile, int uRow, char uCol, int audRow, int audCol, string ticketLetters) {
    //the chunk will be assigned to here
    string colName;
    //stands for scrubbed display row
    string sdRow;
    //only the amount of letters for the rows will show up
    colName.assign(alphabet.c_str(), audCol);
    cout << "  " << colName << endl;
    //sets the file to the beginning because we're passing by ref
    audFile.clear();
    audFile.seekg(0L,ios::beg);
    //Loop and read in all the lines into a string array
    for(int i = 0; i < audRow; i++) {
        getline(audFile, sdRow);
        if (i == (uRow - 1)) {
            //if the iteration lands on the row the user wants
            //Replace the seats they want with the ones they selected
            //starts at letter from col, goes for length of seats and takes from seats
            sdRow = scrubdRows(sdRow, audCol);
            sdRow.replace(alphabet.find(toupper(uCol)), ticketLetters.length(), ticketLetters);
            cout << (i + 1) << " " << sdRow << endl;
        }
        //Scrub rows so user only sees # and .
        else {
        cout << (i +1) << " " << scrubdRows(sdRow, audCol) << endl;
        }
    }
    return;
}

void saveData(fstream &audFile, string insertSeats, int filePos) {
    audFile.seekg(filePos, ios::beg);
    //audFile.seekp(filePos, ios::beg);
    for(unsigned i = 0; i < insertSeats.length(); i++){
        audFile.put(insertSeats.c_str()[i]);
    }
    return;
}

int findBetter(fstream &audFile ,int totalTickets, int numCol, int uRow, int userSeat) {
    int avSeats[26];
    int seatI = 0;
    int swapInt;
    char ch;
    //will hold the distances for comparison
    double a, b;
    //Will hold row the user wants to sit in
    string row;
    //holds whether or not the seats are clear
    bool sClear;
    //holds whether or not a swap has been done
    bool swapped = false;
    //starting position of row
    int rowPos;
    //clear eof from file
    audFile.clear();
    rowPos = ((uRow-1)*(numCol+2));
    //move file pointer to beginning of row
    for(int i = 0; i < (numCol - totalTickets + 1); i++) {
        audFile.seekg(rowPos + i, ios::beg);
        sClear = true;
        for(int j = 0; j < totalTickets; j++) {
            //If the all the seats checked are clear add it to the list of options
            audFile.get(ch);
            if (ch != '.') {
                sClear = false;
                break;
            }
        }
        if (sClear) {
            //the list of options
            avSeats[seatI] = i;
            seatI++;
        }

    }
    for(;seatI < 26; seatI++) {
        //fill the rest of the elements with -1
        avSeats[seatI] = -1;
    }
    //bubble sort array to put best available at index 0
    for(int i = 0; i < 26; i++) {
        swapped = false;
        for(int j = 0; j < 26 - i - 1; j++) {
            // if a seat is more desirable than another swap them
            a = abs((avSeats[j] + ((totalTickets)/ 2)) - ((numCol)/2));
            b = abs((avSeats[j + 1] + ((totalTickets)/ 2)) - ((numCol)/2));
            if(avSeats[j] == -1 && avSeats[j + 1] == -1) {
                break;
            }
            if (a > b) {
                swapped = true;
                swapInt = avSeats[j];
                avSeats[j] = avSeats[j + 1];
                avSeats[j + 1] = swapInt;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return ((avSeats[0] + rowPos) - userSeat);
}

void finalOutput() {
    //holds the char read in from file
    char seatChar;
    int aTickets = 0;
    int cTickets = 0;
    int sTickets = 0;
    int totalTickets = 0;
    int totalSeats = 0;
    double totalSales;
    double adultPrice = 10.00;
    double childPrice = 5.00;
    double seniorPrice = 7.50;
    fstream audFile("A1.txt", ios::in | ios::binary);
    audFile.clear();
    audFile.seekg(0L,ios::beg);
    //read through every character in the file whenever an important thing pops up increment variables
    while (audFile.get(seatChar)){
        if(toupper(seatChar) == 'A'){
            aTickets++;
        }
        if(toupper(seatChar) == 'C'){
            cTickets++;
        }
        if(toupper(seatChar) == 'S'){
            sTickets++;
        }
        if(isprint(seatChar)) {
            totalSeats++;
        }
    }
    //total tickets = all tickets
    totalTickets = aTickets + cTickets + sTickets;
    totalSales = (aTickets * adultPrice) + (cTickets * childPrice) + (sTickets * seniorPrice);
    cout << setw(62) << left << "\nTotal Seats in Auditorium: " << totalSeats << endl;
    cout << setw(62) << left << "Total Tickets Sold: " << totalTickets << endl;
    cout << setw(62) << left << "Adult Tickets Sold: " << aTickets << endl;
    cout << setw(62) << left << "Child Tickets Sold: " << cTickets << endl;
    cout << setw(62) << left << "Senior Tickets Sold: " << sTickets << endl;
    cout << setw(60) << left << "Total Ticket Sales: " << "$" << setprecision(2) << fixed << setprecision(2) << totalSales << endl;
    audFile.close();

}
