#include "LoxClass.h"

LoxClass::LoxClass(std::string name,std::shared_ptr<LoxClass> superclass, std::shared_ptr<std::map<std::string, std::shared_ptr<LoxFunction>>> methods)
{
	this->name = name;
	this->superclass = superclass;
	this->methods = methods;
}

std::string LoxClass::toString() {
	return name;
}

std::shared_ptr<Object> LoxClass::call(std::shared_ptr<Interpreter> interpreter, const std::vector<std::shared_ptr<Object>>& arguments) {
	std::shared_ptr<LoxInstance> instance = std::make_shared<LoxInstance>(shared_from_this());
	
	std::shared_ptr<LoxFunction> initializer = findMethod("init");
	if (initializer != nullptr) {
		initializer->bind(instance)->call(interpreter, arguments);
	}
	return instance;
}

int LoxClass::arity() {
	std::shared_ptr<LoxFunction> initializer = findMethod("init");
	if (initializer == nullptr) {
		return 0;
	}
	return initializer->arity();
}

bool LoxClass::operator== (const Object& other) const {
	if (const LoxClass* otherClass = dynamic_cast<const LoxClass*>(&other)) {
		return name == otherClass->name;
	}
	return false;
}

std::shared_ptr<LoxFunction> LoxClass::findMethod(std::string name) {
	if (methods->find(name) != methods->end()) {
		return methods->at(name);
	}
	if(superclass != nullptr) {
		return superclass->findMethod(name);
	}
	return nullptr;
}