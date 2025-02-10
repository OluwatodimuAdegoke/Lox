#pragma once

#include "Expr.h"
#include <string>
#include <iostream>
#include <ostream>


class AstPrinter : public Visitor
{
public:
	std::string print(const std::shared_ptr<Expr>& expr);
    
    std::shared_ptr<Object> visitBinaryExpr(const Binary& expr) override;
    std::shared_ptr<Object> visitGroupingExpr(const Grouping& expr) override;
    std::shared_ptr<Object> visitLiteralExpr(const Literal& expr) override;
    std::shared_ptr<Object> visitUnaryExpr(const Unary& expr) override;

    template<typename... Exprs>
    std::shared_ptr<Object> parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr, Exprs... rest);
    
    std::shared_ptr<Object> parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr);
	void appendExpr(std::string& result, const std::shared_ptr<Expr>& expr);

;
};

