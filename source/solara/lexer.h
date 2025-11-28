/**
 * @file lexer.h
 */

#pragma once

#include "common.h"
#include "token.h"
#include "solara.h"

#include <string>
#include <filesystem>

namespace solara {

    class Lexer {
    public:
        Lexer(CompilerContext* ctx);

        void init(const std::filesystem::path& path);
        TokenLexeme next_token();
        char peek(const u32 offset = 0) const;
        bool has_next(const u32 offset = 0) const;

    protected:
        TokenLexeme tokenize();
        TokenLexeme create_token(const TokenType type, u64 length);
        TokenLexeme create_keyword_token(const u64 length);
        TokenLexeme create_end_token();
        TokenLexeme create_invalid_token();
        void newline();
        void consume_singleline_comment();
        void consume_multiline_comment();

    private:
        CompilerContext* ctx_;
        std::string source_;
        u64 pos_ = 0;
        u64 column_ = 0;
        u64 line_ = 0;
        
    };

} /* solara */
