#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Hangman {
    private:
        int lives, gamesPlayed, gamesWon;
        string word, hiddenWord, guess, guessedLetters;
        bool gameLoop, isWin;

        // Function to get words from text file and then give a random word
        void randomizeWord(){
            int const wordListSize = 700;
            string wordList[700];
            ifstream inputFile("word_list.txt");
            for (int i = 0; i < wordListSize; i++){
                inputFile >> wordList[i];
            }
            srand(time(0));
            word = wordList[rand() % wordListSize];
        }

        // Function to display lives and hidden word
        void displayScreen(){
            cout << "Lives: " << lives << endl;
            hiddenWord = "";
            for (int i = 0; i < word.length(); i++){
                if (guessedLetters.find(word[i]) != string::npos) hiddenWord = hiddenWord + word[i] + " ";
                else hiddenWord += "_ ";
            }
            cout << hiddenWord << endl;
        }

        // Function to get a valid guess from the player
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

        // Function to check if player guess correctly or not
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

        // Function to check if the game reach the end and check if player win or lose
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
        
        // Function to ask player if they want to play again
        bool playAgain(){
            char choice;
            while (true){
                cout << "Would you like to play again? (Y / N): ";
                cin >> choice;
                cin.ignore();
                if (choice == 'y' || choice =='Y') return true;
                else if (choice == 'n' || choice =='N') return false;
                else cout << "Invalid Option" << endl;
            }
        }
        

    public:
        // Constructor
        Hangman(){
            gamesPlayed = 0;
            gamesWon = 0;
        }

        // Main Game Function
        void startGame(){
            gamesPlayed++;
            gameLoop = true;
            lives = 10;
            guessedLetters = "";
            randomizeWord();

            while(gameLoop){
                cout << "-----------------------------" << endl;
                displayScreen();
                getPlayerGuess();
                checkPlayerGuess();
                if (checkGameEnd()) break;
            }
            
            if (playAgain()) startGame();
            else {
                cout << "Games Played: " << gamesPlayed << endl;
                cout << "Games Won: " << gamesWon << endl;
                cout << "Games Lost: " << gamesPlayed - gamesWon << endl;
                gameLoop = false;
            }
        }
};

int main(){
    Hangman hangman;
    hangman.startGame();

    return 0;
}