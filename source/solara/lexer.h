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
        Lexer(CompilerContext* in_ctx, const std::filesystem::path& path);

        TokenLexeme get_next_token();
        char peek(u64 offset) const;
        bool is_valid() const;

    protected:
        TokenLexeme create_token(const TokenType type, u64 length);
        void newline();

    private:
        CompilerContext* ctx;
        std::string source;
        u64 index = 0;
        u64 column = 0;
        u64 line = 0;
        
    };

} /* solara */
