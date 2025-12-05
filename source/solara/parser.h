/**
 * @file parser.h
 */

#pragma once

#include "common.h"
#include "solara.h"
#include "token.h"
#include "lexer.h"

namespace solara {

    class Parser {
    public:
        Parser(CompilerContext* ctx);

        void init(const std::filesystem::path& path);

    protected:
        TokenLexeme match(const TokenType token);
        void consume();

        void parse();
        void parse_module(const bool pub);
        void parse_program();
        void parse_function(const bool pub);
        void parse_function_params();
        void parse_function_body();
        void parse_statement();
        void parse_expression(const u08 rbp);

    private:
        CompilerContext* ctx_;
        Lexer lexer_;
        TokenLexeme token_;
    };

} /* solara */