#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Hangman {
    private:
        int lives, gamesPlayed, gamesWon;
        string word, hiddenWord, guess, guessedLetters;
        bool isWin;

        void randomizeWord(){
            int const wordListSize = 3;
            string wordList[] = {"apple", "banana", "car"};
            srand(time(0));
            word = wordList[rand() % wordListSize];
        }

        void displayScreen(){
            cout << "Lives: " << lives << endl;
            hiddenWord = "";
            for (int i = 0; i < word.length(); i++){
                if (guessedLetters.find(word[i]) != string::npos) hiddenWord = hiddenWord + word[i] + " ";
                else hiddenWord += "_ ";
            }
            cout << hiddenWord << endl;
        }

        void getPlayerGuess(){
            while (true){
                cout << "Guess a letter: ";
                getline(cin, guess);
                // Check if guess is allowed
                if (guess.length() > 1) cout << "Only 1 letter allowed!" << endl;
                else if (guess[0] < 'a' || guess[0] > 'z') cout << "Only lowercase letters allowed!" << endl;
                else if (guessedLetters.find(guess[0]) != string::npos) cout << "Already guessed that letter!" << endl;
                else {
                    guessedLetters += guess[0];
                    break;
                }
            }
        }

        void checkPlayerGuess(){
            if (word.find(guess[0]) != string::npos){
                cout << "Correct Guess!" << endl;

                isWin = true;
                for (int i = 0; i < word.length(); i++){
                    if (guessedLetters.find(word[i]) == string::npos) isWin = false;
                }
            }
            else {
                isWin = false;
                cout << "Wrong Guess!" << endl;
                lives--;
            }
        }

        bool checkGameEnd(){
            if (lives == 0){
                cout << "-----------------------------" << endl;
                cout << "YOU LOST!" << endl;
                cout << "The word is: " << word << endl;
                return true;
            }
            else if (isWin){
                cout << "-----------------------------" << endl;
                cout << "YOU WON!" << endl;
                cout << "The word is: " << word << endl;
                gamesWon++;
                return true;
            }
            return false;
        }

        

    public:
        Hangman(){
            gamesPlayed = 0;
            gamesWon = 0;
        }

        void startGame(){
            lives = 7;
            gamesPlayed++;
            randomizeWord();

            while(true){
                cout << "-----------------------------" << endl;
                displayScreen();
                getPlayerGuess();
                checkPlayerGuess();
                if (checkGameEnd()) break;
            }
        }
};

int main(){
    Hangman hangman;
    hangman.startGame();

    return 0;
}