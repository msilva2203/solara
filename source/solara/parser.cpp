/**
 * @file parser.cpp
 */

#include "parser.h"

#include <iostream>

namespace solara {

    Parser::Parser(CompilerContext* ctx) 
        : lexer_(ctx) 
    {
        assert(ctx != nullptr);
        ctx_ = ctx;
    }

    void Parser::init(const std::filesystem::path& path) {
        lexer_.init(path);
        parse();
    }

    TokenLexeme Parser::match(const TokenType token) {
        TokenLexeme out;
        out.type = TokenType::NONE;
        if (token_.type == token) {
            out = token_;
            consume();
        } else {
            // TODO: error
        }
        return out;
    }

    void Parser::consume() {
        token_ = lexer_.next_token();
        print_token(ctx_, token_);
        if (token_.type == TokenType::END) {
            // TODO: finish
        }
    }

    void Parser::parse() {
        consume();
        bool pub_module = false;
        if (token_.type == TokenType::KW_PUB) {
            pub_module = true;
            consume();
        }
        parse_module(pub_module);
    }

    void Parser::parse_module(const bool pub) {
        match(TokenType::KW_MODULE);
        auto name = match(TokenType::IDENTIFIER);
        match(TokenType::SEMICOLON);

        if (name.type == TokenType::IDENTIFIER) {
            std::cout << ctx_->string_table_.get_string(name.literal_id) << std::endl;
        }
    }

} /* solara */