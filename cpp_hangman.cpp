#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Hangman {
    private:
        string getRandomWord(){
            string word;
            int const wordListSize = 3;
            string wordList[] = {"apple", "banana", "car"};
            srand(time(0));
            word = wordList[rand() % wordListSize];
            return word;
        }

    public:
        void startGame(){
            cout << getRandomWord();
        }
        
};

int main(){
    Hangman hangman;
    hangman.startGame();

    return 0;
}