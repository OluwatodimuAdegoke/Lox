//#pragma once
//
//#include "Expr.h"
//#include <string>
//#include <iostream>
//#include <ostream>
//
///*
//* AstPrinter class that contains the functions to print the abstract syntax tree
//* It inherits from the Visitor class and contains the functions to visit the different expressions
//* 
//* Functions:
//* print: Function to print the expression
//* visitBinaryExpr: Function to visit the binary expression
//* visitGroupingExpr: Function to visit the grouping expression
//* visitLiteralExpr: Function to visit the literal expression
//* visitUnaryExpr: Function to visit the unary expression
//* parenthesize: Function to parenthesize the expression
//* appendExpr: Function to append the expression
//* 
//*/
//class AstPrinter : public VisitorExpr
//{
//public:
//	std::string print(const std::shared_ptr<Expr>& expr);
//    
//    std::shared_ptr<Object> visitBinaryExpr(const Binary& expr) override;
//    std::shared_ptr<Object> visitGroupingExpr(const Grouping& expr) override;
//    std::shared_ptr<Object> visitLiteralExpr(const Literal& expr) override;
//    std::shared_ptr<Object> visitUnaryExpr(const Unary& expr) override;
//	std::shared_ptr<Object> visitVariableExpr(const Variable& expr) override;
//	std::shared_ptr<Object> visitAssignExpr(const Assign& expr) override;
//
//    template<typename... Exprs>
//    std::shared_ptr<Object> parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr, Exprs... rest);
//    
//    std::shared_ptr<Object> parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr);
//	void appendExpr(std::string& result, const std::shared_ptr<Expr>& expr);
//
//;
//};
//
