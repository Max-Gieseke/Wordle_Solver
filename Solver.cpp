//Solves a game of wordle based on a given starting word
// Max Gieseke


#include <iostream>
#include <string>
#include <fstream>
#include "SortWords.h"

using namespace std;

int main(){

    ifstream infile;
    string words[SortWords::NUM_WORDS];
    int size = SortWords::NUM_WORDS;
    string first = "raise"; //Change to use different starting word
    string answer;
    int spot = 0;
    SortWords startingWord;
    int guesses;

    infile.open("wordleGuesses.txt");
    if (!infile){exit(17);}

    while(!infile.eof()){
        getline(infile, words[spot++], '\n');
    }

    cout << "Answer: \n"; //What word it should solve for
    cin >> answer;

    guesses = SortWords::solveTurns(first, answer, words, true);

    cout << "Solved in " << guesses << " guesses";
}