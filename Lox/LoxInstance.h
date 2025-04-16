#pragma once

#include <vector>
#include <map>
#include <memory>
#include "Error.h"
#include "Stmt.h" 
#include "LoxClass.h" 
#include "LoxFunction.h"

class LoxClass;

class LoxInstance : public Object, public std::enable_shared_from_this<LoxInstance>
{
	std::shared_ptr<LoxClass> klass;
	std::map<std::string, std::shared_ptr<Object>> fields;
public:
	LoxInstance(std::shared_ptr<LoxClass> klass) : klass(klass) {};

	std::string toString() override;
	bool operator==(const Object& other) const override;

	std::shared_ptr<Object> get(const Token& name);
	void set(const Token& name, std::shared_ptr<Object> value);
};

