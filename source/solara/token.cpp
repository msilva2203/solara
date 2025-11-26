/**
 * @file token.cpp
 */

#include "token.h"

#include <iostream>

namespace solara {
    
    void TokenLexeme::print() {
        switch (type) {
            case TokenType::PLUS: {
                std::cout << "PLUS" << std::endl;
                break;
            }
            case TokenType::MINUS: {
                std::cout << "MINUS" << std::endl;
                break;
            }
            case TokenType::DEC: {
                std::cout << "DEC" << std::endl;
                break;
            }
            case TokenType::INC: {
                std::cout << "INC" << std::endl;
                break;
            }
            case TokenType::LBRACE: {
                std::cout << "LBRACE" << std::endl;
                break;
            }
            case TokenType::RBRACE: {
                std::cout << "RBRACE" << std::endl;
                break;
            }
            default: {
                std::cout << "OTHER" << std::endl;
                break;
            }
        }
    }

    bool token_has_value(const TokenType type) {
        switch (type) {
            case TokenType::IDENTIFIER:
            case TokenType::LIT_INT:
            case TokenType::LIT_FLOAT:
            case TokenType::LIT_STRING:
                return true;
            default:
                return false;
        }
    }

}