#include "LoxInstance.h"

std::string LoxInstance::toString() {
	return klass->name + " instance";
}

bool LoxInstance::operator==(const Object& other) const {
	if (const LoxInstance* otherInstance = dynamic_cast<const LoxInstance*>(&other)) {
		return klass == otherInstance->klass;
	}
	return false;
}

std::shared_ptr<Object> LoxInstance::get(const Token& name) {
	if (fields.find(name.lexeme) != fields.end()) {
		return fields[name.lexeme];
	}
	std::shared_ptr<LoxFunction> method = klass->findMethod(name.lexeme);
	if (method != nullptr) {
		std::shared_ptr<LoxInstance> instance = std::static_pointer_cast<LoxInstance>(shared_from_this());
		return std::static_pointer_cast<Object>(method->bind(instance));


	}
	throw RuntimeError(std::make_shared<Token>(name), "Undefined property '" + name.lexeme + "'.");
}

void LoxInstance::set(const Token& name, std::shared_ptr<Object> value) {
	fields[name.lexeme] = value;
}