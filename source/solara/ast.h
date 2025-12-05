/**
 * @file ast.h
 */

#pragma once

#include "common.h"
#include "solara.h"

namespace solara {

    enum class SyntaxNodeType : u08 {
        None = 0,
        ModuleDecl,
        CompoundStmt,
        BinaryExpr,
        UnaryExpr,
        LiteralExpr
    };

    enum SyntaxNodeCategory {
        Declaration = BIT(0),
        Statement   = BIT(1),
        Expression  = BIT(2),
        Type        = BIT(3)
    };

    // Forward declaration of the main syntax node.
    class SyntaxNode;
    using SyntaxNodeHandle = SyntaxNode*;

    /**
     * Base class of a node from the Abstract Syntax Tree.
     * Provides overridable functions that allow the creation of easily integrated node child classes.
     */
    class SyntaxNode {
    public:
        virtual ~SyntaxNode() = default;

        virtual SyntaxNodeType get_type() const = 0;
        virtual const char* get_name() const = 0;
        virtual u16 get_category_flags() const = 0;

        void dump();
        void dump(std::ostream& out);
        void print(std::ostream& out, const u32 depth);

    protected:
        SyntaxNode() {}

        virtual void print_spec(std::ostream& out, const u32 depth);
        virtual void print_children(std::ostream& out, const u32 depth);
    };

#define GENERATE_NODE_BODY(type, category) \
    public: \
        static SyntaxNodeType get_static_type() { return SyntaxNodeType::type; } \
        virtual SyntaxNodeType get_type() const override { return get_static_type(); } \
        virtual const char* get_name() const override { return #type; } \
        virtual u16 get_category_flags() const override { return category; } \
    private: \

    class ModuleDeclNode : public SyntaxNode {
        GENERATE_NODE_BODY(ModuleDecl, Declaration)
    public:
        ModuleDeclNode() {}

    protected:
        virtual void print_children(std::ostream& out, const u32 depth) override;
    };

    class CompoundStmtNode : public SyntaxNode {
        GENERATE_NODE_BODY(CompoundStmt, Statement)
    public:
        CompoundStmtNode() {}

    protected:
        virtual void print_children(std::ostream& out, const u32 depth) override;
    };

    enum class BinaryOperation : u08 {
        ADD,
        SUB,
        MUL,
        DIV
    };

    class BinaryExprNode : public SyntaxNode {
        GENERATE_NODE_BODY(BinaryExpr, Expression)
    public:
        BinaryExprNode(BinaryOperation op, SyntaxNodeHandle left, SyntaxNodeHandle right)
            : op_(op)
            , left_(left)
            , right_(right)
        {}

        BinaryOperation op_;
        SyntaxNodeHandle left_;
        SyntaxNodeHandle right_;

    protected:
        virtual void print_children(std::ostream& out, const u32 depth) override;
    };

    enum class UnaryOperation : u08 {
        INC,
        DEC
    };

    class UnaryExprNode : public SyntaxNode {
        GENERATE_NODE_BODY(UnaryExpr, Expression)
    public:
        UnaryExprNode(UnaryOperation op, SyntaxNodeHandle expr)
            : op_(op)
            , expr_(expr)
        {}

        UnaryOperation op_;
        SyntaxNodeHandle expr_;

    protected:
        virtual void print_children(std::ostream& out, const u32 depth) override;
    };

    class LiteralExprNode : public SyntaxNode {
        GENERATE_NODE_BODY(LiteralExpr, Expression)
    public:
        LiteralExprNode() {}

    protected:
        virtual void print_children(std::ostream& out, const u32 depth) override;
    };

    /**
     * Makes a new heap-allocated Syntax Node with the specified kind and arguments.
     * @param args The template arguments forwarded to the constructor.
     * @returns The handle to the new heap-allocated Syntax Node.
     */
    template<typename T, typename... Args>
    T* make_syntax_node(Args&&... args) {
        return new T{std::forward<Args>(args)...};
    }

} /* solara */