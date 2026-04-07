#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
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
        if(charValues.find(character) != charValues.end()){
            cout << "You put two of the same character in the file: " << character << "." << endl;
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
    int n = A.length();
    int m = B.length();
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> values(n+1, vector<int>(m+1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(A[i - 1] != B[j - 1]){
                values[i][j] = max(values[i - 1][j], values[i][j - 1]);
            }else{
                int matchValue = charValues[A[i - 1]];
                values[i][j] = max({
                    values[i - 1][j],
                    values[i][j - 1],
                    values[i - 1][j - 1] + matchValue});
            }
        }
    }
    string subsequence = "";
    while(n > 0 && m > 0){
        if(A[n - 1] == B[m - 1] && values[n][m] == values[n - 1][m - 1] + charValues[A[n - 1]]){
            subsequence += A[n - 1];
            n--;
            m--;
        }else if(values[n - 1][m] >= values[n][m - 1]){
            n--;
        }else{
            m--;
        }
    }
    reverse(subsequence.begin(), subsequence.end());
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << values[A.length()][B.length()] << endl;
    cout << subsequence << endl;
    cout << "Time took to run file " << inputFileName << ": " << duration.count() << " microseconds!" << endl;
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.