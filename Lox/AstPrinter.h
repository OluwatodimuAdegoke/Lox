#pragma once
#include "Expr.h"
#include <string>
#include <iostream>
#include <ostream>


class AstPrinter : public Visitor
{
public:
	std::string print(const std::shared_ptr<Expr>& expr);
    
    std::string visitBinaryExpr(const Binary& expr) override;
    std::string visitGroupingExpr(const Grouping& expr) override;
    std::string visitLiteralExpr(const Literal& expr) override;
    std::string visitUnaryExpr(const Unary& expr) override;

    template<typename... Exprs>
    std::string parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr, Exprs... rest);
    std::string parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr);
	void appendExpr(std::string& result, const std::shared_ptr<Expr>& expr);

;
};

