/**
 * @file token.h
 */

#pragma once

#include "common.h"
#include "solara.h"

#include <unordered_map>
#include <string>

namespace solara {
    
    enum class TokenType : u16 {
        NONE = 0,

        IDENTIFIER,

        // keywords
        KW_BREAK,
        KW_CONST,
        KW_CONTINUE,
        KW_DEFAULT,
        KW_ELSE,
        KW_FOR,
        KW_IF,
        KW_RETURN,
        KW_STRUCT,
        KW_SWITCH,
        KW_PUB,
        KW_MODULE,

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
        COLON,
        SEMICOLON,

        END,

        MAX
    };

    struct TokenSourceSpan {
        u64 line, column;
    };

    struct TokenLexeme {
        TokenType type;
        u64 literal_id;
        TokenSourceSpan span;

        bool is_valid() const;
    };

    struct TokenMetadata {
        TokenType type_;
        std::string_view name_;
        std::string_view source_name_;
    };

    bool token_has_value(const TokenType type);
    TokenType identify_keyword(const std::string_view string);

    void print_token(CompilerContext* ctx, const TokenLexeme& token);

#if 0
    extern std::unordered_map<std::string, TokenType> keyword_table;
#endif

}