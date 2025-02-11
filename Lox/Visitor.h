#pragma once
#include <memory>
#include "Object.h"

class Binary;
class Grouping;
class Literal;
class Unary;


/*
* Visitor abstract class that contains the functions to visit the different expressions
* 
* Functions:
* visitBinaryExpr: Function to visit the binary expression
* visitGroupingExpr: Function to visit the grouping expression
* visitLiteralExpr: Function to visit the literal expression
* visitUnaryExpr: Function to visit the unary expression
*/

class Visitor {
public:
    virtual std::shared_ptr<Object> visitBinaryExpr(const Binary& expr) = 0;
    virtual std::shared_ptr<Object> visitGroupingExpr(const Grouping& expr) = 0;
    virtual std::shared_ptr<Object> visitLiteralExpr(const Literal& expr) = 0;
    virtual std::shared_ptr<Object> visitUnaryExpr(const Unary& expr) = 0;
    virtual ~Visitor() = default;
};