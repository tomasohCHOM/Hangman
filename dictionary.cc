#include "dictionary.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

Dictionary::Dictionary(const std::string &valid_words_filename) {
    std::ifstream words_file(valid_words_filename);
    std::string word;
    while (words_file >> word) {
        valid_words_.push_back(word);
    }
    srand(time(nullptr));
}

const std::string& Dictionary::GetRandomWord() const {
    return valid_words_.at(rand() % valid_words_.size());
}