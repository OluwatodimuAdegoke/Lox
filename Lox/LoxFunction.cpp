#include "LoxFunction.h"


std::shared_ptr<Object> LoxFunction::call(std::shared_ptr<Interpreter> interpreter,const std::vector<std::shared_ptr<Object>>& arguments) {
    std::shared_ptr<Environment> environment = std::make_shared<Environment>(closure);

    for (int i = 0; i < declaration->params->size(); i++) {
        environment->define(declaration->params->at(i).lexeme, arguments[i]);
    }

    try {
        interpreter->executeBlock(declaration->body, environment);
	}
	catch (Return& returnValue) {
		return returnValue.value;
	}
    return nullptr; 
}

int LoxFunction::arity()
{
	return declaration->params->size();
}

std::string LoxFunction::toString() {
    return "<fn " + declaration->name.lexeme + ">";
}

bool LoxFunction::operator==(const Object& other) const {
    if (auto otherFunction = dynamic_cast<const LoxFunction*>(&other)) {
        return declaration == otherFunction->declaration;
    }
    return false;
}