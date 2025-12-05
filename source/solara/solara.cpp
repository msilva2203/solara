/**
 * @file solara.cpp
 * 
 * @author Marco Silva
 * @date 2025-11-18
 */

#include "solara.h"
#include "lexer.h"
#include "stringtable.h"
#include "parser.h"
#include "ast.h"

#include <iostream>

namespace solara {

    void parse_settings(i32 argc, char* argv[], CompilerSettings& out_settings) {
        enum class ParseState {
            None = 0,
            InputFile,
            OutputFile
        };

        ParseState parse_state = ParseState::InputFile;

        for (i32 i = 1; i < argc; i++) {
            const std::string arg = argv[i];

            if (arg.empty()) {
                continue;
            }

            if (arg.at(0) == '-') {
                if (arg.compare("-s") == 0) {
                    parse_state = ParseState::InputFile;
                } else if (arg.compare("-o") == 0) {
                    parse_state = ParseState::OutputFile;
                } else {
                    parse_state = ParseState::None;
                }
            }

            switch (parse_state) {
                case ParseState::InputFile:
                    out_settings.input_file_ = arg;
                    break;
                case ParseState::OutputFile:
                    out_settings.output_file_ = arg;
                    break;
                default:
                    break;
            }
        }
    }

    void init(const CompilerSettings& settings) {
        CompilerContext ctx(settings);

        ctx.logger_.log(
            INFO,
            "Solara Context has been initialized."
        );

        auto expr1 = make_syntax_node<LiteralExprNode>();
        auto expr2 = make_syntax_node<LiteralExprNode>();
        auto bin1 = make_syntax_node<BinaryExprNode>(BinaryOperation::SUB, expr1, expr2);
        auto expr3 = make_syntax_node<LiteralExprNode>();
        auto ast = make_syntax_node<BinaryExprNode>(BinaryOperation::ADD, bin1, expr3);
        ast->dump();

        delete expr1;
        delete expr2;
        delete bin1;
        delete expr3;
        delete ast;

#if 0
        Lexer lexer(&ctx);
        lexer.init(settings.input_file_);
        while (lexer.has_next()) {
            auto tok = lexer.next_token();
            print_token(&ctx, tok);
        }

        Parser parser(&ctx);
        parser.init(settings.input_file_);
#endif
    }

} /* solara */
