#include "tokenizer.h"
#include<iostream>
#include<regex>
#include<stdio.h>
#include<vector>
#include<map>
#include<string>

Tokenizer::Tokenizer(std::string ln, std::string parserType) {
    // complete the constructor

    Token val;
  
    std::regex reg("[A-Za-z0-9]*|[+]|[-]|[*]|[(]|[)]");
    
    if(parserType == "formula"){
        for(size_t i = 0; i < ln.length(); i++){
            if ((int(ln[i]) > 32 && int(ln[i]) < 40) || (int(ln[i])== 44) || (int(ln[i]) > 45 && int(ln[i])< 48) || (int(ln[i])> 57 &&  int(ln[i]) < 65) || (int(ln[i])> 90 &&  int(ln[i]) < 97) || (int(ln[i])> 122)  ) {
                throw std::invalid_argument("Error: invalid input");
            }
        }
    }

  
    for (std::sregex_iterator it = std::sregex_iterator(ln.begin(), ln.end(), reg); it != std::sregex_iterator(); it++) {
        std::smatch match;
        match = *it;
      
        if (match.str(0).length() > 0 and match.str(0) !=" " ){
            // std::cout<<"position : "<<match.str(0);
            val.content = match.str(0);
            if (val.content.compare("+")==0 || val.content.compare("*")==0){
                val.type = "OPERATOR";
            }
            else if (val.content.compare("(")==0){
                val.type = "LEFTPARAN";
            }
            else if (val.content.compare(")")==0){
                val.type = "RIGHTPARAN";
            }
            else if (val.content.compare("-")==0){
                val.type = "NEGATION";
            }
            
            else{
                val.type = "VARIABLE";
                if (std::isdigit(val.content[0]) || val.content.length() > 10) {
                    throw std::invalid_argument("Error: invalid input");
                }
            }
            stringTokens.push_back(val);
        }
        
    }
  
}
  

bool Tokenizer::advanceToken() {
    // your code starts here
    if (i>= stringTokens.size())
        return false;
  
    else 
        i++;
  
    return false;
}

bool Tokenizer::hasToken() const {
    // your code starts here
    return i < stringTokens.size();
    
    return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() 
{
  
    // your code starts there
    Token resultToken;
    if (hasToken()){
        resultToken=stringTokens.at(i);
        return resultToken;
    }
    return resultToken;
}


