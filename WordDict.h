//An array-list with an associated string value
//Max Gieseke
#include <string>

#ifndef WORDDICT_H
#define WORDICT_H

using namespace std;

class WordDict{

private:
    string key;
    string* words;
    int size;
    int maxArray;
public:
    WordDict();
    void addWord(string);
    string* getWords(){return words;} //Returns words, pointer to the words with the same key
    int getSize(){return size;} //returns the number of words
};

#endif