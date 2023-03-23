#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include<vector>
#include<iostream>

struct Token
{
    std::string content;
    std::string type;
    
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
    private:
        std::vector<Token> stringTokens;
        size_t i = 0;
        
  // your code starts here
    public:
        Tokenizer(std::string ln, std::string type);
        bool advanceToken(); // advance to the next token; return false if no more token exist
        bool hasToken() const; // check whether there is a current token
        Token getToken(); // returns the token being processed

};

#endif
