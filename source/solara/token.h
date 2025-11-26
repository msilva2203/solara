/**
 * @file token.h
 */

#pragma once

#include "common.h"

namespace solara {
    
    enum class TokenType {
        NONE = 0,

        IDENTIFIER,

        // keywords
        BREAK,
        CONST,
        CONTINUE,
        DEFAULT,
        ELSE,
        FOR,
        IF,
        RETURN,
        STRUCT,
        SWITCH,

        // literals
        LIT_INT,
        LIT_FLOAT,
        LIT_STRING,

        // operators
        PLUS,
        MINUS,
        STAR,
        DIV,
        MOD,
        PLUS_ASSIGN,
        MINUS_ASSIGN,
        STAR_ASSIGN,
        DIV_ASSIGN,
        MOD_ASSIGN,
        AND,
        OR,
        INC,
        DEC,
        EQ,
        LT,
        GT,
        ASSIGN,
        NOT,
        NEQ,
        LE,
        GE,

        // punctuation
        LPAR,
        RPAR,
        LSQ,
        RSQ,
        LBRACE,
        RBRACE,
        COMMA,
        PERIOD,
        SEMICOLON
    };

    struct TokenSourceSpan {
        u64 line, column;
    };

    struct TokenLexeme {
        TokenType type;
        u64 literal_id;
        TokenSourceSpan span;

        void print();
    };

    bool token_has_value(const TokenType type);

}