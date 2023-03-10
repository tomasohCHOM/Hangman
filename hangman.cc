#include <cctype>
#include <iomanip>

#include "hangman.h"

void Hangman::PlayHangman() {
    // Welcome and introduce the rules to the player
    std::cout << "\n=================Hangman=================\n"
              << "Welcome to Hangman! Your goal is to guess the secret word before the man is hanged.\n\n"
              << "You do so by typing letters, revealing the letters of the secret word one by one.\n\n"
              << "For every incorrect guess, one part will be added to the man.\n\n"
              << "If his body is completed before you guess the word, you lose! Good Luck!\n\n";
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
    for (int i = 0; i < incorrect_guesses_.size(); i++) {
        (i == 0) ? (output += incorrect_guesses_[i]) : (output += ", " + incorrect_guesses_[i]);
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