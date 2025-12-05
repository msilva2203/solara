/**
 * @file ast.cpp
 */

#include "ast.h"

#include <iostream>

namespace solara {

    static void print_null_node(std::ostream& out, const u32 depth) {
        for (u32 i = 0; i < depth; i++) {
            out << "..";
        }
        out << "NULL" << std::endl;
    }

    void SyntaxNode::dump() {
        dump(std::cout);
    }

    void SyntaxNode::dump(std::ostream& out) {
        print(out, 0);
    }

    void SyntaxNode::print(std::ostream& out, const u32 depth) {
        for (u32 i = 0; i < depth; i++) {
            out << "..";
        }
        out << get_name();
        print_spec(out, depth);
        out << std::endl;
        print_children(out, depth + 1);
    }

    void SyntaxNode::print_spec(std::ostream& out, const u32 depth) {
        out << "<>";
    }

    void SyntaxNode::print_children(std::ostream& out, const u32 depth) {
        // stub
    }

    void ModuleDeclNode::print_children(std::ostream& out, const u32 depth) {
        // stub
    }

    void CompoundStmtNode::print_children(std::ostream& out, const u32 depth) {
        // stub
    }

    void BinaryExprNode::print_children(std::ostream& out, const u32 depth) {
        if (left_) {
            left_->print(out, depth);
        } else {
            print_null_node(out, depth);
        }
        if (right_) {
            right_->print(out, depth);
        } else {
            print_null_node(out, depth);
        }
    }

    void UnaryExprNode::print_children(std::ostream& out, const u32 depth) {
        if (expr_) {
            expr_->print(out, depth);
        } else {
            print_null_node(out, depth);
        }
    }

    void LiteralExprNode::print_children(std::ostream& out, const u32 depth) {
        // stub
    }

} /* solara */