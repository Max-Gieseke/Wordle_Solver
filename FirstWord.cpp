//Finds best first word
//Max Gieseke

#include <iostream>
#include <fstream>
#include <string>
#include "SortWords.h"

using namespace std;


int main(){

    ifstream infile;
    string words[SortWords::NUM_WORDS];
    int size = SortWords::NUM_WORDS;
    int spot = 0;
    SortWords startingWord;
    string bestWord;

    infile.open("wordleGuesses.txt");
    if (!infile){exit(17);}

    while(!infile.eof()){
        getline(infile, words[spot++], '\n');
    }

    bestWord = startingWord.bestWord(words, size, words, size);

    cout << "Best word is " << bestWord;

}

