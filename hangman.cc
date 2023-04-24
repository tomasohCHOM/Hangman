#include <cctype>
#include <iomanip>

#include "hangman.h"

Hangman::Hangman() : dictionary_("valid_words.txt"), answer_(dictionary_.GetRandomWord()), lives_(6) {
    // Welcome and introduce the rules to the player.
    std::cout << "\n=================Hangman=================\n"
              << "Welcome to Hangman! Your goal is to guess the secret word before the man is hanged.\n\n"
              << "You do so by typing letters, revealing the letters of the secret word one by one.\n\n"
              << "For every incorrect guess, one part will be added to the man.\n\n"
              << "If his body is completed before you guess the word, you lose! Good Luck!\n\n";
    // A variable that will check if the difficulty was NOT selected, true by default.
    bool isNotSelected = true;

    // While the difficulty wasn't selected, execute the loop body.
    while (isNotSelected) {
        // Prompt the user to select a difficulty.
        std::cout << "Which difficulty are you going to play on?\n"
                << "Press '1': Easy\n"
                << "Press '2': Medium\n"
                << "Press '3': Very Hard\n";
        
        // Accept user input as an integer.
        int difficultyLevel = 0;
        std::cin >> difficultyLevel;

        switch(difficultyLevel) {
            // Easy difficulty.
            case 1:
                std::cout << "You selected to play in Easy difficulty. This should be fun!\n";
                dictionary_ = Dictionary("valid_words.txt");
                isNotSelected = false;
                break;
            // Medium difficulty.
            case 2:
                std::cout << "Medium difficulty? Now we are talking!\n";
                dictionary_ = Dictionary("valid_words.txt");
                isNotSelected = false;
                break;
            // Very hard difficulty.
            case 3:
                std::cout << "Wow, you chose Very Hard? Prepare yourself...\n";
                dictionary_ = Dictionary("valid_words.txt");
                isNotSelected = false;
                break;
            // Neither of the above, ask for user input again.
            default:
                std::cout << "Invalid input. Try again and choose an appropriate difficulty.\n";
                break;
        }
    }
}

void Hangman::PlayHangman() {
    // Make the hidden word by taking the length of the answer and replacing it with "_".
    for (int i = 0; i < answer_.size(); i++) {
        hidden_word_ += "_";
    }
    // Draw the empty hangman as well as the unrevealed word hidden with "_"s.
    DrawHangman();
    std::cout << "The word: " << hidden_word_ << "\n";
    while (lives_ > 0 && answer_ != hidden_word_) {
        // Prompt the user to enter their guess.
        std::cout << "Enter your guess (must be a letter): ";
        std::cin >> letter_guess_;
        // This ensures that the input is a lower case letter.
        if (letter_guess_.size() == 1 && (int)letter_guess_[0] >= 97 && (int)letter_guess_[0] <= 122) {
            // Find whether the letter exists in the answer.
            if (answer_.find(letter_guess_) != -1) {
                RevealLetterLocation();
            } else {
                lives_--;
                incorrect_guesses_.push_back(letter_guess_);
                std::cout << "That's incorrect! A part has been added to the Hangman's body.\n";
            }
        } else {
            std::cout << "Invalid input, must be a lower case letter. Please, try again.\n";
        }
        // Draw the now updated hangman (depending on whether the guess is correct or not).
        DrawHangman();
        std::cout << "List of Incorrect Guesses: " << DisplayIncorrectGuesses() << "\n";
        std::cout << "The word: " << hidden_word_ << "\n\n";
    }
    if (answer_ == hidden_word_) {
        std::cout << "Congrats! You saved the Hangman and won the game.\n";
    } else {
        std::cout << "You lose! The Hangman was hanged. The answer was " << std::quoted(answer_)
                  << ".\nGG Go Next.\n";
    }
}

std::string Hangman::DisplayIncorrectGuesses() {
    std::string output = "[";
    for (std::vector<std::string>::const_iterator itr = incorrect_guesses_.cbegin(); itr != incorrect_guesses_.cend(); ++itr) {
        (itr == incorrect_guesses_.cbegin()) ? (output += *itr) : (output += ", " + *itr);
    }
    output += "]";
    return output;
}

void Hangman::RevealLetterLocation() {
    for (int i = 0; i < answer_.size(); i++) {
        if (answer_[i] == letter_guess_[0]) {
            hidden_word_[i] = letter_guess_[0];
        }
    }
}

void Hangman::DrawHangman() {
    if (lives_ == 6) {
        std::cout << ".____.\n"
              << "|    |\n"
              << "|    \n"
              << "|   \n"
              << "|   \n"
              << "|\nI\n\n";
    } else if (lives_ == 5) {
        std::cout << ".____.\n"
              << "|    |\n"
              << "|    O\n"
              << "|   \n"
              << "|   \n"
              << "|\nI\n\n";
    }
    else if (lives_ == 4) {
        std::cout << ".____.\n"
              << "|    |\n"
              << "|    O\n"
              << "|    |\n"
              << "|   \n"
              << "|\nI\n\n";
    }
    else if (lives_ == 3) {
        std::cout << ".____.\n"
              << "|    |\n"
              << "|    O\n"
              << "|   /|\n"
              << "|   \n"
              << "|\nI\n\n";
    }
    else if (lives_ == 2) {
        std::cout << ".____.\n"
              << "|    |\n"
              << "|    O\n"
              << "|   /|\\\n"
              << "|   \n"
              << "|\nI\n\n";
    }
    else if (lives_ == 1) {
        std::cout << ".____.\n"
              << "|    |\n"
              << "|    O\n"
              << "|   /|\\\n"
              << "|   / \n"
              << "|\nI\n\n";
    } else {
        std::cout << ".____.\n"
              << "|    |\n"
              << "|    O\n"
              << "|   /|\\\n"
              << "|   / \\\n"
              << "|\nI\n\n";
    }
}