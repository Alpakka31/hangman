/*
Copyright (c) 2020, Patrik Nyström
All rights reserved.
This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
*/

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

// Clear terminal screen
void clearScreen() {
#if defined _WIN32
    system("cls");
#elif defined __linux__
    system("clear");
#endif
}

// Class for hangman game
class Hangman {
    private:
        std::string word; // The correct word
        std::string incompleteWord; // The incomplete word
        std::vector<std::string> wordlist; // List of words

        int lives;
    public:
        Hangman() {
            constructWordlist();
            initializeGame();
        }

        // A function that constructs the wordlist
        void constructWordlist() {
            std::ifstream file("wordlist.txt");

            if (file.is_open()) {
                std::string line;

                while(std::getline(file, line)) {
                    wordlist.push_back(line);
                }
                file.close();
            } else {
                std::cout << "Couldn't open file!\n";
                exit(1);
            }
        }

        // A function that initializes the game
        void initializeGame() {
            std::random_device dev;
            std::mt19937 rng(dev());

            int amountOfWords = wordlist.size() - 1;
            std::uniform_int_distribution<std::mt19937::result_type> dist(0, amountOfWords);
            word = wordlist.at(dist(rng));

            incompleteWord.clear();

            // Add '_' characters to the incomplete word (resembles hidden word)
            for (size_t i = 0; i < word.length(); i++) {
                incompleteWord += "_";
            }

            lives = 6;
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
                case 6:
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 5:
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << " O    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 4:
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << " O    |\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 3:
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "\\O    |\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 2:
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "\\O/   |\n";
                    std::cout << " |    |\n";
                    std::cout << "      |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 1:
                    std::cout << " ------\n";
                    std::cout << " |    |\n";
                    std::cout << "\\O/   |\n";
                    std::cout << " |    |\n";
                    std::cout << "/     |\n";
                    std::cout << "      |\n";
                    std::cout << "--------\n";
                    break;
                case 0:
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
            // correct answer
            if (word.find(answer[0]) != std::string::npos) {
                for (size_t i = 0; i < word.length(); i++) {
                    if (word[i] == answer[0]) {
                        incompleteWord[i] = answer[0];
                    }
                }
            } else {
                // incorrect answer
                lives--;
            }
        }

        // The main game loop
        void run() {
            clearScreen();
            std::cout << "A very simple hangman game.\n";

            while (true) {
                showLives();
                showWord();
                showMan();

                std::cout << "Give a character: ";
                std::string input = getInput();
                validateAnswer(input);
                std::cout << "\n";

                if (lives == 0) {
                    showLives();
                    showWord();
                    showMan();

                    std::cout << "You lost!\n";
                    std::cout << "The correct word was: " << word << "\n";
                    break;
                } else if (incompleteWord == word) {
                    showLives();
                    showWord();
                    showMan();

                    std::cout << "You won!\n";
                    break;
                }
            }

            std::cout << "\n\nDo you want to play again? (yes/no)\n";
            std::string input = getInput();

            if (input == "yes") {
                initializeGame();
                run();
            } else if (input == "no") {
                ;;
            } else {
                ;;
            }
        }
};

int main() {
    // Create the game and run it
    Hangman hangman = Hangman();
    hangman.run();
    return 0;
}