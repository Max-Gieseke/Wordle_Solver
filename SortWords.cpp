//Max Gieseke

#include <string>
#include <iostream>
#include <fstream>
#include "SortWords.h"
#include <cmath>
#include <utility>

using namespace std;

//Initializes a sortWords that has no startWord
SortWords::SortWords() {
    this->startWord = "";
    for (int i = 0; i < 243; i++){
        containers[i] = WordDict();
    }
}

//Initializes a sortWords that has a startWord
SortWords::SortWords(string startWord){
    this->startWord = std::move(startWord);
    for (int i = 0; i < 243; i++){
        containers[i] = WordDict();
    }
}

//Copy constructor
SortWords::SortWords(SortWords *pWords) {
    startWord = pWords->startWord;
    for (int i = 0; i < 243; i++){
        containers[i] = pWords->containers[i];
    }
}

//Converts letters to the corresponding integer to be able to sort the word codes
int SortWords::letToInt(char let){
    switch(let){
        case 'g':
            return 1;
        case 'y':
            return 2;
        case 'b':
            return 3;
        default:
            return 0;
    }
}

//Campares the startWord to another word, guess and returns a string showing how the words are alike
//g = letter in same spot, y = both words have the same letter, but different spots, b = the words do not have
//the same letter
string SortWords::compare(string guess){
    char unUsedLets[5] = {'0', '0', '0', '0', '0'};
    string ret = "bbbbb";

    for (int i = 0; i < 5; i++){
        if (startWord[i] == guess[i]){
            ret[i] = 'g';
        }
        else {
            unUsedLets[i] = guess[i];
        }
    }
    for (int i = 0; i < 5; i++){
        if(unUsedLets[i] != '0'){
            for(int j = 0; j < 5; j++){
                if (i != j && unUsedLets[i] == startWord[j]){
                    if (ret[j] != 'g'){
                        ret[j] = 'y';
                        break;
                    }
                }
            }
        }
    }

    return ret;
}

//Converts a string (from compare) to an index for the containers array
int SortWords::keyToIndex(string key) {
    int index = 0;
    for (int i = 0; i < 5; i++){
        index += (letToInt(key[i]) - 1) * pow(3, 4 - i);
    }

    return index;
}

//Takes a word and puts it in containers based on the code from compare
void SortWords::putInContainer(string potAns) {
    int index = keyToIndex(compare(potAns));
    containers[index].addWord(potAns);
}

//Determines how "good" a word is by how many words it would eliminate by it being guessed, lower is better
double SortWords::getValueOfWord() {
    double value = 0;
    double preVal;
    for (int i = 0; i < 243; i++){
        preVal = containers[i].getSize();
        value += (pow(preVal, 2) / NUM_WORDS);
    }

    return value;
}
//gets a container matching the index
WordDict SortWords::getContainer(int index) {
    return containers[index];
}

//Gets the word that eliminates the largest number of remaining words by getting the value of all words and seeing
//which one has the best probability of having the least number of words (lower is better)
string SortWords::bestWord(string * remainingWords, int remSize, string * allWords, int allSize) {
    //For all words, see which one reduces remaining words the most
    SortWords potWord;
    string bestWord;
    double lowestProb = INT32_MAX;
    double currentProb;
    for (int i = 0; i < allSize; i++){
        potWord = new SortWords(*(allWords + i));
        for (int j = 0; j < remSize; j++){
            potWord.putInContainer(*(remainingWords + j));
        }
        currentProb = potWord.getValueOfWord();
        if (currentProb < lowestProb){
            bestWord = potWord.getStartWord();
            lowestProb = currentProb;
        }
    }
    return bestWord;
}
//Puts a list of words in the right container
void SortWords::putListInContainers(string* listOfWords, int size) {
    for (int i = 0; i < size; i++){
        this->putInContainer(*(listOfWords + i));
    }
}

//determines how many turns it takes to solve a given word, singleWord tells the function to display guesses or not
int SortWords::solveTurns(string startWord, const string& answer, string* totalWords, bool singleWord) {
    SortWords* guessWord = new SortWords(std::move(startWord));
    int size = NUM_WORDS;
    string* wordsLeft = new string[size];
    string curWord;
    string code;
    int index;
    int guess = 1;


    for (int i = 0; i < NUM_WORDS; i ++){
        wordsLeft[i] = totalWords[i];
    }

    guessWord->putListInContainers(totalWords, NUM_WORDS);


    while (guess < 7){
        if (singleWord) {
            cout << "Guess " << guess << ": " << guessWord->getStartWord() << endl;
        }
        code = guessWord->compare(answer);
        if (code == "ggggg"){
            break;
        }
        else {
            guess++;
            //Set wordsLeft to remaining words
            index = SortWords::keyToIndex(code);
            size = guessWord->getContainer(index).getSize();
            wordsLeft = guessWord->getContainer(index).getWords();
            curWord = guessWord->bestWord(totalWords, NUM_WORDS, wordsLeft, size);
            //sorts remaining words into containers based on curWord
            guessWord = new SortWords(curWord);
            guessWord->putListInContainers(wordsLeft, size);
        }

    }
    delete [] wordsLeft;
    delete guessWord;

    return guess;
}
