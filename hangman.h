#include <iostream>
#include <vector>

#include "dictionary.h"

#ifndef HANGMAN_H
#define HANGMAN_H

class Hangman {
    public:
        Hangman();
        std::string DisplayIncorrectGuesses();
        void PlayHangman();
        void DrawHangman();
        void RevealLetterLocation();

    private:
        Dictionary dictionary_;
        std::string answer_;
        std::string hidden_word_;
        std::string letter_guess_;
        std::vector<std::string> incorrect_guesses_;
        int lives_;
};

#endif // HANGMAN_H