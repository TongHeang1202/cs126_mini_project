#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Hangman {
    private:
        int lives, gamesPlayed;
        string word, hiddenWord, guess, guessedLetters;

        void randomizeWord(){
            int const wordListSize = 3;
            string wordList[] = {"apple", "banana", "car"};
            srand(time(0));
            word = wordList[rand() % wordListSize];
        }

        void getPlayerGuess(){
            while (true){
                cout << "Guess a letter: ";
                getline(cin, guess);
                if (guess.length() > 1) cout << "Only 1 letter allowed!" << endl;
                else if (guess[0] < 'a' || guess[0] > 'z') cout << "Only lowercase letters allowed!" << endl;
                else if (guessedLetters.find(guess[0]) != string::npos) cout << "Already guessed that letter!" << endl;
                else {
                    guessedLetters += guess[0];
                    break;
                }
            }
        }

    public:
        void startGame(){
            gamesPlayed++;
            randomizeWord();

            while(true){
                getPlayerGuess();
                hiddenWord = "";
                for (int i = 0; i < word.length(); i++){
                    hiddenWord = hiddenWord + "_ ";
                }
                cout << guessedLetters;
            }

        }

        
        
};

int main(){
    Hangman hangman;
    hangman.startGame();

    return 0;
}