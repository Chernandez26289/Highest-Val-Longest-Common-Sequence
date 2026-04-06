#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "LCS.h"
#include <unordered_map>

int main(){
    string inputFileName;
    cout << "Input file name (../inputs/<file_name>.txt): ";
    cin >> inputFileName;
    cout << "Trying to open: " << inputFileName << endl;
    ifstream inputFile(inputFileName);
    if(!inputFile.is_open()){
        cout << "Failed to open input file: "<< inputFileName << endl;
        return 1;
    }
    int k;
    if(!(inputFile >> k)){
        cout << "K must be an integer." << endl;
        return 1;
    }
    if(k < 1){
        cout << "No values for characters given." << endl;
        return 1;
    }
    unordered_map<char, int> charValues;
    for(int i = 0; i < k; i++){
        char character;
        int characterValue;
        if(!(inputFile >> character >> characterValue)){
            cout<<"There is an invalid pair input in the file provided." << endl;
            return 1;
        }
        charValues[character] = characterValue;
    }
    string A, B;
    if(!(inputFile >> A)){
        cout << "Missing string A." << endl;
        return 1;
    }
    if(!(inputFile >> B)){
        cout << "Missing string B." << endl;
        return 1;
    }
    int isExtra;
    if(inputFile>>isExtra){
        cout << "Extra line of input in file." << endl;
        return 1;
    }
    inputFile.close();
    cout << "K = " << k << endl;
    cout << "Character values:" << endl;
    for(auto &pair : charValues){
        cout << pair.first << " -> " << pair.second << endl;
    }
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.