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

    Lexer::Lexer(CompilerContext* in_ctx, const std::filesystem::path& path) {
        ctx = in_ctx;
        index = 0;
        column = 0;
        line = 0;

        if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path)) {
            std::ifstream file(path);
            
            if (!file.is_open()) {
                std::cout << "Error: Could not open source file: " << path << std::endl;
                return;
            }

            source.assign(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>()
            );
        } else {
            std::cout << "Error: Source file does not exist: " << path << std::endl;
        }
    }

    TokenLexeme Lexer::get_next_token() {
        enum class ParseState {
            None = 0,
            SingleLineComment,
            MultiLineComment,
            StringLiteral
        };

        ParseState parse_state = ParseState::None;

        TokenLexeme token;
        token.type = TokenType::NONE;

        char c = peek(0);

        // clear and handle white spaces
        while (is_white_space(c)) {
            index++;
            if (c == '\0') {
                return token;
            } else if (c == '\n') {
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
            return create_token(TokenType::IDENTIFIER, i);
        }

        // generate number literals
        if (is_unicode_digit(c) || c == '.') {
            enum {
                FlagDecimal = 1 << 0,
                FlagOctal = 1 << 1,
                FlagHexadecimal = 1 << 2,
                FlagFloatingPoint = 1 << 3
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
                // TODO: single line comment
                u64 i = 2;
                c = peek(i);
                while (!is_newline(c)) {
                    if (c == '\0') {
                        index += i;
                        return token;
                    }
                    i++;
                    c = peek(i);
                }
                index += i;
                return get_next_token();
            } else if (c == '*') {
                // TODO: multi line comment
                
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
        if (c == ';') {
            return create_token(TokenType::SEMICOLON, 1);
        }

        index++;
        column++;

        return token;
    }

    char Lexer::peek(u64 offset) const {
        const size_t s = source.size();
        const u64 i = index + offset;
        if (i < s) {
            return source.at(i);
        }
        return '\0';
    }

    bool Lexer::is_valid() const {
        return peek(0) != '\0';
    }

    TokenLexeme Lexer::create_token(const TokenType type, u64 length) {
        TokenLexeme token;
        token.type = type;
        token.span.line = line;
        token.span.column = column;

        if (token_has_value(type)) {
            const u64 begin = index;
            const std::string_view view = source;
            const std::string_view token_literal = view.substr(begin, length);
            const u64 tok_lit_id = ctx->string_table.add(token_literal);
            token.literal_id = tok_lit_id;
        }

        index += length;
        column += length;

        return token;
    }

    void Lexer::newline() {
        line++;
        column = 0;
    }

} /* solara */
