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

    private:
        CompilerContext* ctx_;
        Lexer lexer_;
        TokenLexeme token_;
    };

} /* solara */