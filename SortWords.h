//Class to handle sorting and comparing different words and answers
// Max Gieseke
//

#include "WordDict.h"
#include <string>
#ifndef WORDLE_SORTWORDS_H
#define WORDLE_SORTWORDS_H

class SortWords{
private:
    string startWord;
    WordDict containers[243];
public:
    const static int NUM_WORDS = 12972;
    string getStartWord(){return startWord;}
    SortWords();
    SortWords(string);
    SortWords(SortWords*);
    static int letToInt(char);
    string compare(string);
    static int keyToIndex(string);
    void putInContainer(string);
    double getValueOfWord();
    WordDict getContainer(int);
    string bestWord(string*, int, string*, int);
    void putListInContainers(string*, int);
    static int solveTurns(string, const string&, string*, bool);
};

#endif //WORDLE_SORTWORDS_H
