/**
 * @file lexer.h
 */

#pragma once

#include "common.h"

namespace lexer {

    enum class TokenType {
        None = 0,
        
        Identifier
    };

    struct Token {
        TokenType type;
    };

    class Lexer {

    

    };

} /* lexer */
