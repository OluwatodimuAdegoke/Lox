#pragma once

#include <memory>
#include "Interpreter.h"
#include "Object.h"

class Interpreter;

class LoxCallable : public Object
{
public:
	virtual ~LoxCallable() = default;
	virtual std::shared_ptr<Object> call(std::shared_ptr<Interpreter> interpreter, const std::vector<std::shared_ptr<Object>>& arguments) = 0;
	virtual int arity() = 0;

	virtual std::string toString() = 0;
	virtual bool operator==(const Object& other) const = 0;

};