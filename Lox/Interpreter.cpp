#include "Interpreter.h"

void Interpreter::interpret(const std::shared_ptr<Expr>& expr) {
	try {
		std::shared_ptr<Object> value = evaluate(expr);
		std::cout << stringify(value) << std::endl;
	}
	catch (const RuntimeError& error) {
		Error::runtimeError(error);
	}
}

std::string Interpreter::stringify(const std::shared_ptr<Object>& object) {
	if (object == nullptr) return "nil";
	return object->toString();
}

std::shared_ptr<Object> Interpreter::visitLiteralExpr(const Literal& expr) {
	return expr.value;
}

std::shared_ptr<Object> Interpreter::visitGroupingExpr(const Grouping& expr) {
	return evaluate(expr.expression);
}


std::shared_ptr<Object> Interpreter::visitBinaryExpr(const Binary& expr) {
	std::shared_ptr<Object> left = evaluate(expr.left);
	std::shared_ptr<Object> right = evaluate(expr.right);

	switch (expr.op.type) {
	case TokenType::GREATER:
		checkNumberOperands(expr.op, left, right);
		return std::make_shared<Bool>(std::dynamic_pointer_cast<Number>(left)->value > std::dynamic_pointer_cast<Number>(right)->value);
		break;

	case TokenType::GREATER_EQUAL:
		checkNumberOperands(expr.op, left, right);
		return std::make_shared<Bool>(std::dynamic_pointer_cast<Number>(left)->value >= std::dynamic_pointer_cast<Number>(right)->value);
		break;

	case TokenType::LESS:
		checkNumberOperands(expr.op, left, right);
		return std::make_shared<Bool>(std::dynamic_pointer_cast<Number>(left)->value < std::dynamic_pointer_cast<Number>(right)->value);
		break;

	case TokenType::LESS_EQUAL:
		checkNumberOperands(expr.op, left, right);
		return std::make_shared<Bool>(std::dynamic_pointer_cast<Number>(left)->value <= std::dynamic_pointer_cast<Number>(right)->value);
		break;

	case TokenType::BANG_EQUAL:
		return std::make_shared<Bool>(!isEqual(left, right));
	case TokenType::EQUAL_EQUAL:
		return std::make_shared<Bool>(isEqual(left, right));

	case TokenType::MINUS:
		checkNumberOperands(expr.op, left, right);
		return std::make_shared<Number>(std::dynamic_pointer_cast<Number>(left)->value - std::dynamic_pointer_cast<Number>(right)->value);
		break;

	case TokenType::PLUS:

		if (auto leftNumber = std::dynamic_pointer_cast<Number>(left)) {
			if (auto rightNumber = std::dynamic_pointer_cast<Number>(right)) {
				return std::make_shared<Number>(leftNumber->value + rightNumber->value);
			}
		}
		if (auto leftString = std::dynamic_pointer_cast<String>(left)) {
			if (auto rightString = std::dynamic_pointer_cast<String>(right)) {
				return std::make_shared<String>(leftString->value + rightString->value);
			}
		}
		throw RuntimeError(std::make_shared<Token>(expr.op), "Operands must be two numbers or two strings.");
		break;

	case TokenType::SLASH:
		checkNumberOperands(expr.op, left, right);
		return std::make_shared<Number>(std::dynamic_pointer_cast<Number>(left)->value / std::dynamic_pointer_cast<Number>(right)->value);
		break;

	case TokenType::STAR:
		checkNumberOperands(expr.op, left, right);
		return std::make_shared<Number>(std::dynamic_pointer_cast<Number>(left)->value * std::dynamic_pointer_cast<Number>(right)->value);
		break;

	}
	return nullptr;
}

std::shared_ptr<Object> Interpreter::visitUnaryExpr(const Unary& expr) {
    auto right = evaluate(expr.right);

    switch (expr.op.type) {

    case TokenType::BANG:
        return std::make_shared<Bool>(!isTruthy(right));

    case TokenType::MINUS:
		checkNumberOperand(expr.op,right);
		return std::make_shared<Number>(-std::dynamic_pointer_cast<Number>(right)->value);

    }

    return nullptr;
}

std::shared_ptr<Object> Interpreter::evaluate(const std::shared_ptr<Expr>& expr) {
    return expr->accept(*this);
}

bool Interpreter::isTruthy(const std::shared_ptr<Object>& object) {
    if (object == nullptr) return false;
    if (auto boolean = std::dynamic_pointer_cast<Bool>(object)) return boolean->value;
	return true;
}

bool Interpreter::isEqual(const std::shared_ptr<Object>& left, const std::shared_ptr<Object>& right) {
	if (left == nullptr && right == nullptr) return true;
	if (left == nullptr) return false;
	return *left == *right;
}

void Interpreter::checkNumberOperand(const Token& op, const std::shared_ptr<Object>& operand) {
	if (auto number = std::dynamic_pointer_cast<Number>(operand)) return;
	throw RuntimeError(std::make_shared<Token>(op), "Operand must be a number.");
}

void Interpreter::checkNumberOperands(const Token& op, const std::shared_ptr<Object>& left, const std::shared_ptr<Object>& right) {
	if (auto leftNumber = std::dynamic_pointer_cast<Number>(left)) {
		if (auto rightNumber = std::dynamic_pointer_cast<Number>(right)) return;
	}
	throw RuntimeError(std::make_shared<Token>(op), "Operands must be numbers.");
}
