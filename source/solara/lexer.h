/**
 * @file lexer.h
 */

#pragma once

#include "common.h"

#include <string>

namespace lexer {

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
        INT,
        FLOAT,
        STRING,

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

    struct TokenLexeme {
        TokenType type;

        void print();
    };

    class Lexer {
    public:
        Lexer(const std::string& in_source);

        TokenLexeme get_next_token();
        char peek(u64 offset) const;
        bool is_valid() const;

    protected:
        TokenLexeme create_token(const TokenType type, u64 length);
        void newline();

    private:
        std::string source;
        u64 index = 0;
        u64 column = 0;
        u64 line = 0;
        
    };

} /* lexer */
