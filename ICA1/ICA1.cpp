//Arvind Sundar
//Tan Tran

#include <iostream>

using namespace std;

bool findInt(int[], int, int, int i = 0);
void intBin(int);

int main() {
    int number;
    int numAry[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int arySize;


    cout << "Please input the size of the array\n";
    cin >> arySize;
    cout << "Please input the integer you want to find and turn into binary\n";
    cin >> number;

    if (findInt(numAry, number, arySize)) {
        intBin(number);
    }
    else {
        cout << "Your number wasn't found in the array\n";
    }
}

bool findInt(int numAry[], int num, int SIZE, int i) {
    bool boolin;
    if(i < SIZE) {
        if(numAry[i] == num){
            boolin = true;
        }
        else {
            boolin = (findInt(numAry, num, SIZE, ++i));
        }
    }
    if(i>=SIZE){
        boolin = false;
    }
    return boolin;
}

void intBin (int num) {

    if ((num / 2) < 1) {
        cout << num % 2;
        return;
    }
    intBin(num/2);
    cout << num%2;
    return;
}
