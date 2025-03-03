#pragma once
#include "Object.h"

class Expression;
class Print;


class VisitorStmt {
public:

	virtual std::shared_ptr<Object> visitExpressionStmt(const Expression& stmt) = 0;
	virtual std::shared_ptr<Object> visitPrintStmt(const Print& stmt) = 0;
    virtual ~VisitorStmt() = default;
};