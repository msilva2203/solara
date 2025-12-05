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
        OP_PLUS,
        OP_MINUS,
        OP_STAR,
        OP_DIV,
        OP_MOD,
        OP_PLUS_ASSIGN,
        OP_MINUS_ASSIGN,
        OP_STAR_ASSIGN,
        OP_DIV_ASSIGN,
        OP_MOD_ASSIGN,
        OP_AND,
        OP_OR,
        OP_INC,
        OP_DEC,
        OP_EQ,
        OP_LT,
        OP_GT,
        OP_ASSIGN,
        OP_NOT,
        OP_NEQ,
        OP_LE,
        OP_GE,

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

    bool token_is_keyword(const TokenType type);
    bool token_is_literal(const TokenType type);
    bool token_is_operator(const TokenType type);
    bool token_has_value(const TokenType type);
    TokenType identify_keyword(const std::string_view string);

    void print_token(CompilerContext* ctx, const TokenLexeme& token);

#if 0
    extern std::unordered_map<std::string, TokenType> keyword_table;
#endif

}