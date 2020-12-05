/*
Copyright (c) 2020, Patrik Nyström
All rights reserved.
This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

// Clear terminal screen
void clearScreen() {
#if defined _WIN32 // If using Windows use cls
    system("cls");
#elif defined __linux__ // If using Linux use clear
    system("clear");
#endif
}

// Class for hangman game
class Hangman {
    private:
        std::string word; // The correct word
        std::string incompleteWord; // The incomplete word
        std::vector<std::string> wordlist; // List of words

        int lives; // Lives left
    public:
        // Constructor
        Hangman() {
            // Construct the wordlist
            constructWordlist();

            // Initialize game
            initializeGame();
        }

        // A function that constructs the wordlist
        void constructWordlist() {
            // Read words from a file
            std::ifstream file("wordlist.txt");

            // If file opened succesfully do this
            if (file.is_open()) {
                std::string line;

                // Read file line by line
                while(std::getline(file, line)) {
                    wordlist.push_back(line); // Add the word to the wordlist
                }
                file.close(); // Close the file
            } else { // Otherwise on error exit the game
                std::cout << "Couldn't open file!\n";
                exit(1);
            }
        }

        // A function that initializes the game
        void initializeGame() {
            // Seed the random number generator
            srand((unsigned)time(NULL));

            // Generate random number between 0 and 25
            int amountOfWords = wordlist.size() - 1;
            int randomNum = (rand() % amountOfWords);
            word = wordlist.at(randomNum); // Use a random word from the wordlist as the correct word

            incompleteWord.clear(); // If re-initializing the game, clear the incomplete word

            // Add '_' characters to the incomplete word (resembles hidden word)
            for (size_t i = 0; i < word.length(); i++) {
                incompleteWord += "_";
            }

            lives = 6; // Player has 6 lives
        }

        // A function that shows the amount of lives left
        void showLives() {
            std::cout << "Lives: " << std::to_string(lives) << "\n";
        }

        // A function that shows the incomplete word
        void showWord() {
            std::cout << incompleteWord << "\n\n";
        }

        // Show the correct hanging man
        void showMan() {
            switch (lives) {
                case 6: // 6 lives left
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 5: // 5 lives left
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << " O    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 4: // 4 lives left
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << " O    |\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 3: // 3 lives left
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "\\O    |\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 2: // 2 lives left
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "\\O/   |\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 1: // 1 lives left
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "\\O/   |\n";
                    std::cout << " |    |\n";
                    std::cout << "/     |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 0: // No lives left
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "\\O/   |\n";
                    std::cout << " |    |\n";
                    std::cout << "/ \\   |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
            }
        }

        // A function that gets input from the player
        std::string getInput() {
            std::string input;
            std::getline(std::cin, input);

            return input;
        }

        // A function that validates the input the player gave
        void validateAnswer(std::string answer) {
            // If the character is found in the correct word, then modify the incomplete word.
            // (correct answer)
            if (word.find(answer[0]) != std::string::npos) {
                for (size_t i = 0; i < word.length(); i++) {
                    // Set the correct character to the correct position in the incomplete word
                    if (word[i] == answer[0]) {
                        incompleteWord[i] = answer[0];
                    }
                }
            } else {
                // If the character wasn't found in the correct word, then the player loses a life
                // (incorrect answer)
                lives--;
            }
        }

        // The main game loop
        void run() {
            clearScreen(); // Clear terminal screen
            std::cout << "A very simple hangman game.\n";

            // Game runs in a infinite while loop
            while (true) {
                showLives(); // Show lives left
                showWord(); // Show the incomplete word to the player
                showMan(); // Show the hanging man

                // Ask input from the player and validate it
                std::cout << "Give a character: ";
                std::string input = getInput();
                validateAnswer(input);
                std::cout << "\n";

                // If the player has no lives left, then the player loses the game
                if (lives == 0) {
                    showLives();
                    showWord();
                    showMan();

                    std::cout << "You lost!\n";
                    std::cout << "The correct word was: " << word << "\n";
                    break;
                // If the player completes the incomplete word, then the player wins
                } else if (incompleteWord == word) {
                    showLives();
                    showWord();
                    showMan();

                    std::cout << "You won!\n";
                    break;
                }
            }

            // Ask if the player wants to play again
            std::cout << "\n\nDo you want to play again? (yes/no)\n";
            std::string input = getInput();

            if (input == "yes") {
                initializeGame(); // Re-initialize the game
                run(); // Run the game
            } else if (input == "no") {
                ;; // Do nothing
            } else {
                ;; // Do nothing
            }
        }
};

int main() {
    // Create the game and run it
    Hangman hangman = Hangman();
    hangman.run();
    return 0;
}