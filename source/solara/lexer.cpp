/**
 * @file lexer.cpp
 */

#include "lexer.h"

#include <iostream>
#include <fstream>

namespace solara {

    static bool is_newline(const char c) {
        return c == '\n';
    }

    static bool is_unicode_char(const char c) {
        return !is_newline(c);
    }

    static bool is_unicode_letter(const char c) {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }

    static bool is_unicode_digit(const char c) {
        return (c >= '0' && c <= '9');
    }

    static bool is_letter(const char c) {
        return is_unicode_letter(c) || (c == '_');
    }

    static bool is_decimal_digit(const char c) {
        return is_unicode_digit(c);
    }

    static bool is_octal_digit(const char c) {
        return (c >= '0' && c <= '7');
    }

    static bool is_hexadecimal_digit(const char c) {
        return is_unicode_digit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
    }

    static bool is_white_space(const char c) {
        return c == ' ' || c == '\t' || c == '\r' || is_newline(c) || c == '\0';
    }

    Lexer::Lexer(CompilerContext* ctx) {
        assert(ctx != nullptr);
        ctx_ = ctx;
    }

    void Lexer::init(const std::filesystem::path& path) {
        pos_ = 0;
        line_ = 0;
        column_ = 0;

        if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
            std::ifstream file(path);
            
            if (!file.is_open()) {
                std::cout << "Error: Could not open source file: " << path << std::endl;
                return;
            }

            source_.assign(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>()
            );
        } else {
            std::cout << "Error: Source file does not exist: " << path << std::endl;
        }
    }

    TokenLexeme Lexer::next_token() {
        TokenLexeme token;
        token = tokenize();
        while (token.type == TokenType::NONE) {
            token = tokenize();
        }
        return token;
    }

    char Lexer::peek(const u32 offset) const {
        const size_t s = source_.size();
        const u64 i = pos_ + offset;
        if (i < s) {
            return source_.at(i);
        }
        return '\0';
    }

    bool Lexer::has_next(const u32 offset) const {
        return (pos_ + offset) < source_.size();
    }

    TokenLexeme Lexer::tokenize() {
        if (!has_next()) {
            return create_end_token();
        }

        char c = peek(0);

        // clear and handle white spaces
        while (is_white_space(c)) {
            pos_++;
            if (c == '\n') {
                newline();
            }
            c = peek(0);
        }

        // generate identifiers or keywords
        if (is_letter(c)) {
            u64 i = 1;
            c = peek(i);
            while (is_letter(c) || is_unicode_digit(c)) {
                i++;
                c = peek(i);
            }
            return create_keyword_token(i);
        }

        // generate number literals
        if (is_unicode_digit(c) || c == '.') {
            enum {
                FlagDecimal         = 1 << 0,
                FlagOctal           = 1 << 1,
                FlagHexadecimal     = 1 << 2,
                FlagFloatingPoint   = 1 << 3
            };

            u08 flags = 0;
            u64 i = 1;

            if (c >= '1' && c <= '9') {
                flags |= FlagDecimal;
            } else if (c == '0') {
                c = peek(i);
                i++;
                if (is_octal_digit(c)) {
                    flags |= FlagOctal;
                } else if (c == 'x' || c == 'X') {
                    c = peek(i);
                    i++;
                    if (is_hexadecimal_digit(c)) {
                        flags |= FlagHexadecimal;
                    } else {
                        // TODO: error
                    }
                } else if (!is_decimal_digit(c)) {
                    // might still be octal "0" or floating point if '.' is found
                    flags |= FlagOctal;
                }
            } else if (c == '.') {
                c = peek(i);
                i++;
                if (is_decimal_digit(c)) {
                    flags |= FlagFloatingPoint;
                } else {
                    // TODO: error
                }
            }

            c = peek(i);

            while (!is_white_space(c)) {
                if (is_decimal_digit(c)) {
                    if (is_octal_digit(c)) {

                    } else {
                        if (flags & FlagOctal) {
                            // TODO: error - incorrect octal scan
                        }
                    }
                } else if (is_hexadecimal_digit(c)) {
                    if (flags & FlagHexadecimal) {
                        
                    } else {
                        // TODO: error - hexadecimal was not being scanned
                    }
                } else if (c == '.') {
                    if (flags & FlagFloatingPoint) {
                        // TODO: error - point has already been scanned
                    } else if (flags & FlagHexadecimal) {
                        // TODO: error - hexadecimal was being scanned
                    } else {
                        flags |= FlagFloatingPoint;
                    }
                } else if (is_white_space(c)) {
                    
                } else {

                }

                i++;
                c = peek(i);
            }
            return create_token(TokenType::LIT_INT, i - 1);
        }

        if (c == '/') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::DIV_ASSIGN, 2);
            } else if (c == '/') {
                pos_ += 2;
                consume_singleline_comment();
                return create_invalid_token();
            } else if (c == '*') {
                pos_ += 2;
                consume_multiline_comment();
                return create_invalid_token();
            } else {
                return create_token(TokenType::DIV, 1);
            }
        }

        if (c == '*') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::STAR_ASSIGN, 2);
            } else {
                return create_token(TokenType::STAR, 1);
            }
        }

        if (c == '+') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::PLUS_ASSIGN, 2);
            } else if (c == '+') {
                return create_token(TokenType::INC, 2);
            } else {
                return create_token(TokenType::PLUS, 1);
            }
        }

        if (c == '-') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::MINUS_ASSIGN, 2);
            } else if (c == '-') {
                return create_token(TokenType::DEC, 2);
            } else {
                return create_token(TokenType::MINUS, 1);
            }
        }

        if (c == '%') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::MOD_ASSIGN, 2);
            } else {
                return create_token(TokenType::MOD, 1);
            }
        }

        if (c == '&') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::NONE, 2);
            } else if (c == '&') {
                return create_token(TokenType::AND, 2);
            } else {
                return create_token(TokenType::NONE, 1);
            }
        }

        if (c == '|') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::NONE, 2);
            } else if (c == '|') {
                return create_token(TokenType::OR, 2);
            } else {
                return create_token(TokenType::NONE, 1);
            }
        }

        if (c == '=') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::EQ, 2);
            } else {
                return create_token(TokenType::ASSIGN, 1);
            }
        }

        if (c == '<') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::LE, 2);
            } else if (c == '<') {
                c = peek(2);
                if (c == '=') {
                    return create_token(TokenType::NONE, 3);
                } else {
                    return create_token(TokenType::NONE, 2);
                }
            } else {
                return create_token(TokenType::LT, 1);
            }
        }

        if (c == '>') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::GE, 2);
            } else if (c == '>') {
                c = peek(2);
                if (c == '=') {
                    return create_token(TokenType::NONE, 3);
                } else {
                    return create_token(TokenType::NONE, 2);
                }
            } else {
                return create_token(TokenType::GT, 1);
            }
        }

        if (c == '!') {
            c = peek(1);
            if (c == '=') {
                return create_token(TokenType::NEQ, 2);
            } else {
                return create_token(TokenType::NOT, 1);
            }
        }

        // punctuation
        if (c == '(') {
            return create_token(TokenType::LPAR, 1);
        }
        if (c == ')') {
            return create_token(TokenType::RPAR, 1);
        }
        if (c == '{') {
            return create_token(TokenType::LBRACE, 1);
        }
        if (c == '}') {
            return create_token(TokenType::RBRACE, 1);
        }
        if (c == '[') {
            return create_token(TokenType::LSQ, 1);
        }
        if (c == ']') {
            return create_token(TokenType::RSQ, 1);
        }
        if (c == ',') {
            return create_token(TokenType::COMMA, 1);
        }
        if (c == '.') {
            return create_token(TokenType::PERIOD, 1);
        }
        if (c == ':') {
            return create_token(TokenType::COLON, 1);
        }
        if (c == ';') {
            return create_token(TokenType::SEMICOLON, 1);
        }

        pos_++;
        column_++;

        return create_invalid_token();
    }

    TokenLexeme Lexer::create_token(const TokenType type, u64 length) {
        TokenLexeme token;
        token.type = type;
        token.span.line = line_;
        token.span.column = column_;

        if (token_has_value(type)) {
            const u64 begin = pos_;
            const std::string_view view = source_;
            const std::string_view token_literal = view.substr(begin, length);
            const u64 tok_lit_id = ctx_->string_table.add(token_literal);
            token.literal_id = tok_lit_id;
        }

        pos_ += length;
        column_ += length;

        return token;
    }

    TokenLexeme Lexer::create_keyword_token(const u64 length) {
        const u64 begin = pos_;
        const std::string_view source_view = source_;
        const std::string_view token_view = source_view.substr(begin, length);

        TokenLexeme out;
        out.type = identify_keyword(token_view);
        if (out.type == TokenType::IDENTIFIER) {
            out.literal_id = ctx_->string_table.add(token_view);
        }

        pos_ += length;
        column_ += length;

        return out;
    }

    TokenLexeme Lexer::create_end_token() {
        TokenLexeme out;
        out.type = TokenType::END;
        return out;
    }

    TokenLexeme Lexer::create_invalid_token() {
        TokenLexeme out;
        out.type = TokenType::NONE;
        return out;
    }

    void Lexer::newline() {
        line_++;
        column_ = 0;
    }

    void Lexer::consume_singleline_comment() {
        u64 i = 0;
        char c = peek(i);
        while (!is_newline(c)) {
            i++;
            c = peek(i);
        }
        pos_ += i;
    }

    void Lexer::consume_multiline_comment() {
        u64 i = 0;
        while (has_next(i)) {
            char c = peek(i);
            i++;
            if (c == '*') {
                c = peek(i);
                i++;
                if (c == '/') {
                    break;
                }
            }
        }
        pos_ += i;
    }

} /* solara */
