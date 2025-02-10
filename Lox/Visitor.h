#pragma once
#include <memory>
#include "Object.h"

class Binary;
class Grouping;
class Literal;
class Unary;


class Visitor {
public:
    virtual std::shared_ptr<Object> visitBinaryExpr(const Binary& expr) = 0;
    virtual std::shared_ptr<Object> visitGroupingExpr(const Grouping& expr) = 0;
    virtual std::shared_ptr<Object> visitLiteralExpr(const Literal& expr) = 0;
    virtual std::shared_ptr<Object> visitUnaryExpr(const Unary& expr) = 0;
    virtual ~Visitor() = default;
};