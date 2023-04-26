#include <iostream>
#include <vector>

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary {
    public:
        Dictionary(const std::string &valid_words_filename);
        const std::string &GetRandomWord() const;
    private:
        std::vector<std::string> valid_words_;
};

#endif // DICTIONARY_H