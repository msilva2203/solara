/**
 * @file token.cpp
 */

#include "token.h"
#include "stringtable.h"

#include <iostream>
#include <array>
//#include <format>

namespace solara {

    /**
     * The metadata table for token types.
     * Elements are required to be inserted in the same order as the TokenType enum class elements.
     */
    constexpr std::array<TokenMetadata, static_cast<i32>(TokenType::MAX)> token_metadata_table = {{
        { TokenType::NONE, "NONE", "" },
        { TokenType::IDENTIFIER, "IDENTIFIER", "" },
        { TokenType::KW_BREAK, "BREAK", "break" },
        { TokenType::KW_CONST, "CONST", "const" },
        { TokenType::KW_CONTINUE, "CONTINUE", "continue" },
        { TokenType::KW_DEFAULT, "DEFAULT", "default" },
        { TokenType::KW_ELSE, "ELSE", "else" },
        { TokenType::KW_FOR, "FOR", "for" },
        { TokenType::KW_IF, "IF", "if" },
        { TokenType::KW_RETURN, "RETURN", "return" },
        { TokenType::KW_STRUCT, "STRUCT", "struct" },
        { TokenType::KW_SWITCH, "SWITCH", "switch" },
        { TokenType::KW_PUB, "PUB", "pub" },
        { TokenType::KW_MODULE, "MODULE", "module" },
        { TokenType::LIT_INT, "LIT_INT", "" },
        { TokenType::LIT_FLOAT, "LIT_FLOAT", "" },
        { TokenType::LIT_STRING, "LIT_STRING", "" },
        { TokenType::PLUS, "PLUS", "+" },
        { TokenType::MINUS, "MINUS", "-" },
        { TokenType::STAR, "STAR", "*" },
        { TokenType::DIV, "DIV", "/" },
        { TokenType::MOD, "MOD", "%" },
        { TokenType::PLUS_ASSIGN, "PLUS_ASSIGN", "+=" },
        { TokenType::MINUS_ASSIGN, "MINUS_ASSIGN", "-=" },
        { TokenType::STAR_ASSIGN, "STAR_ASSIGN", "*=" },
        { TokenType::DIV_ASSIGN, "DIV_ASSIGN", "/=" },
        { TokenType::MOD_ASSIGN, "MOD_ASSIGN", "%=" },
        { TokenType::AND, "AND", "&&" },
        { TokenType::OR, "OR", "||" },
        { TokenType::INC, "INC", "++" },
        { TokenType::DEC, "DEC", "--" },
        { TokenType::EQ, "EQ", "==" },
        { TokenType::LT, "LT", "<" },
        { TokenType::GT, "GT", ">" },
        { TokenType::ASSIGN, "ASSIGN", "=" },
        { TokenType::NOT, "NOT", "!" },
        { TokenType::NEQ, "NEQ", "!=" },
        { TokenType::LE, "LE", "<=" },
        { TokenType::GE, "GE", ">=" },
        { TokenType::LPAR, "LPAR", "(" },
        { TokenType::RPAR, "RPAR", ")" },
        { TokenType::LSQ, "LSQ", "[" },
        { TokenType::RSQ, "RSQ", "]" },
        { TokenType::LBRACE, "LBRACE", "{" },
        { TokenType::RBRACE, "RBRACE", "}" },
        { TokenType::COMMA, "COMMA", "," },
        { TokenType::PERIOD, "PERIOD", "." },
        { TokenType::COLON, "COLON", ":" },
        { TokenType::SEMICOLON, "SEMICOLON", ";" },
        { TokenType::END, "EOF", "" },
    }};

    /**
     * Obtains the metadata for the specified token type
     * @param type The type of the token
     * @returns The metadata of the token type
     */
    constexpr const TokenMetadata& get_token_metadata(const TokenType type) {
        assert(static_cast<i32>(type) < token_metadata_table.size());
        return token_metadata_table[static_cast<i32>(type)];
    }

    bool TokenLexeme::is_valid() const {
        return type != TokenType::NONE;
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

    TokenType identify_keyword(const std::string_view string) {
        if (string == "break") return TokenType::KW_BREAK;
        if (string == "const") return TokenType::KW_CONST;
        if (string == "continue") return TokenType::KW_CONTINUE;
        if (string == "default") return TokenType::KW_DEFAULT;
        if (string == "else") return TokenType::KW_ELSE;
        if (string == "for") return TokenType::KW_FOR;
        if (string == "if") return TokenType::KW_IF;
        if (string == "module") return TokenType::KW_MODULE;
        if (string == "pub") return TokenType::KW_PUB;
        if (string == "return") return TokenType::KW_RETURN;
        if (string == "struct") return TokenType::KW_STRUCT;
        if (string == "switch") return TokenType::KW_SWITCH;
        return TokenType::IDENTIFIER;
    }

    static void print_value_token(CompilerContext* ctx, const TokenLexeme& token) {
        TokenMetadata meta = get_token_metadata(token.type);
        std::cout << meta.name_ << "(" << ctx->string_table.get_string(token.literal_id) << ")" << std::endl;
    }

    static void print_nonvalue_token(CompilerContext* ctx, const TokenLexeme& token) {
        TokenMetadata meta = get_token_metadata(token.type);
        std::cout << meta.name_ << std::endl;
    }

    void print_token(CompilerContext* ctx, const TokenLexeme& token) {
        assert(ctx != nullptr);
        if (!token.is_valid()) {
            return;
        }
        if (token_has_value(token.type)) {
            print_value_token(ctx, token);
        } else {
            print_nonvalue_token(ctx, token);
        }
    }

#if 0
    std::unordered_map<std::string, TokenType> keyword_table = {
        { "break"    , TokenType::KW_BREAK },
        { "const"    , TokenType::KW_CONST },
        { "continue" , TokenType::KW_CONTINUE },
        { "default"  , TokenType::KW_DEFAULT },
        { "else"     , TokenType::KW_ELSE },
        { "for"      , TokenType::KW_FOR },
        { "if"       , TokenType::KW_IF },
        { "module"   , TokenType::KW_MODULE },
        { "pub"      , TokenType::KW_PUB },
        { "return"   , TokenType::KW_RETURN },
        { "struct"   , TokenType::KW_STRUCT },
        { "switch"   , TokenType::KW_SWITCH }
    };
#endif

}