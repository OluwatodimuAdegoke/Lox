#pragma once
#include <memory>
#include <vector>
#include "Object.h"
#include "LoxCallable.h"
#include "LoxInstance.h"
class LoxFunction;

class LoxClass : public LoxCallable, public std::enable_shared_from_this<LoxClass>
{
public:
	std::string name;
	std::shared_ptr<std::map<std::string, std::shared_ptr<LoxFunction>>> methods;
	std::shared_ptr<LoxClass> superclass;

	LoxClass(std::string name,std::shared_ptr<LoxClass> superclass,  std::shared_ptr<std::map<std::string, std::shared_ptr<LoxFunction>>> methods);

	std::string toString() override;
	std::shared_ptr<Object> call(std::shared_ptr<Interpreter> interpreter, const std::vector<std::shared_ptr<Object>>& arguments) override;
	int arity() override;

	bool operator== (const Object& other)const override;

	std::shared_ptr<LoxFunction> findMethod(std::string name);
};

