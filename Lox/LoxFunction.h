#pragma once
#include <memory>
#include "Object.h"
#include "LoxCallable.h"
#include "Interpreter.h"

class LoxInstance;


class LoxFunction : public LoxCallable
{
private:
	std::shared_ptr<FunctionStmt> declaration;
	std::shared_ptr<Environment> closure;
	bool isInitializer = false;
public:
	LoxFunction(std::shared_ptr<FunctionStmt> declaration, std::shared_ptr<Environment> closure, bool isInitializer) : declaration(declaration), closure(closure), isInitializer(isInitializer) {}

	std::shared_ptr<Object> call(std::shared_ptr<Interpreter> interpreter,const std::vector<std::shared_ptr<Object>>& arguments) override;
	int arity() override;
	std::string toString() override;
	bool operator==(const Object& other) const override;
	
	std::shared_ptr<LoxFunction> bind(std::shared_ptr<LoxInstance> instance);

};

