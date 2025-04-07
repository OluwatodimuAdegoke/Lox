#pragma once
#include <memory>
#include "Object.h"
#include "LoxCallable.h"


class LoxFunction : public LoxCallable
{
private:
	std::shared_ptr<FunctionStmt> declaration;
	std::shared_ptr<Environment> closure;
public:
	LoxFunction(std::shared_ptr<FunctionStmt> declaration, std::shared_ptr<Environment> closure) : declaration(declaration), closure(closure) {}

	std::shared_ptr<Object> call(std::shared_ptr<Interpreter> interpreter, const std::vector<std::shared_ptr<Object>>& arguments) override;
	int arity() override;
	std::string toString() override;
	bool operator==(const Object& other) const override;
};
