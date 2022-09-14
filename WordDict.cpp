//Max Gieseke

#include "WordDict.h"

#include <string>

using namespace std;


//Creates new WordDict with starting array size of 20
WordDict::WordDict() {
    this->words = new string[20];
    this->size = 0;
    this->maxArray = 19;
}

//WordDict::~WordDict() {
//    delete [] words;
//}


//Adds new word to word (the array)
void WordDict::addWord(string word) {
    if (size == maxArray){
        string* temp = new string[size * 2];
        maxArray = size * 2;
        //copy array
        for (int i = 0; i < size; i ++){
            temp[i] = words[i];
        }
        temp[size++] = word;
        delete[] words;
        words = temp;

    }
    else {
        words[size++] = word;
    }
}
