#include "Resolver.h"


void Resolver::resolve(std::shared_ptr<std::vector<std::shared_ptr<Stmt>>> statements) {
	for (auto& statement : *statements) {
		resolve(statement);
	}
}

void Resolver::resolve(std::shared_ptr<Stmt> stmt) {
	stmt->accept(*this);
}

void Resolver::resolve(std::shared_ptr<Expr> expr) {
	expr->accept(*this);
}

void Resolver::beginScope() {
	scopes->push_back(std::map<std::string, bool>());
}

void Resolver::endScope() {
	scopes->pop_back();
}

void Resolver::declare(const Token& name) {
	if (scopes->empty()) {
		return;
	}
	std::map<std::string, bool> scope = scopes->back();
	if (scope.find(name.lexeme) != scope.end()) {
		Error::error(name, "Variable with this name already declared in this scope.");
		return;
	}
	scope[name.lexeme] = false;
}


void Resolver::define(const Token& name) {
	if (scopes->empty()) {
		return;
	}
	auto& scope = scopes->back();
	scope[name.lexeme] = true;
}


void Resolver::resolveLocal(std::shared_ptr<const Expr> expr, const Token& name) {
	for (size_t i = scopes->size(); i-- > 0;) {
		if (scopes->at(i).find(name.lexeme) != scopes->at(i).end()) {
			interpreter->resolve(std::const_pointer_cast<Expr>(expr), static_cast<int>(scopes->size() - 1 - i));
			return;
		}
	}
}


void Resolver::resolveFunction(const FunctionStmt& stmt, FunctionType type) {
	
	FunctionType enclosingFunction = currentFunction;
	currentFunction = type;

	beginScope();
	for (auto& param : *stmt.params) {
		declare(param);
		define(param);
	}
	resolve(stmt.body);
	endScope();

	currentFunction = enclosingFunction;
}

void Resolver::visitBlock(const Block& stmt) {
	beginScope();
	resolve(stmt.statements);
	endScope();
	return;
}

void Resolver::visitVarStmt(const VarStmt& stmt) {
	declare(stmt.name);
	if (stmt.initializer != nullptr) {
		resolve(stmt.initializer);
	}
	define(stmt.name);
	return;
}


std::shared_ptr<Object> Resolver::visitVariableExpr(const Variable& expr) {
	if (!scopes->empty()) {
		auto& scope = scopes->back();
		if (scope.find(expr.name.lexeme) != scope.end() && scope[expr.name.lexeme] == false) {
			Error::error(expr.name, "Cannot read local variable in its own initializer.");
		}
	}
	resolveLocal(expr.shared_from_this(), expr.name);
	return nullptr;
}

std::shared_ptr<Object> Resolver::visitAssignExpr(const Assign& expr) {
	resolve(expr.value);
	resolveLocal(expr.shared_from_this(), expr.name);
	return nullptr;
}

void Resolver::visitFunctionStmt(const FunctionStmt& stmt) {
	declare(stmt.name);
	define(stmt.name);

	resolveFunction(stmt, FunctionType::FUNCTION);
	return;
}

void Resolver::visitExpressionStmt(const ExpressionStmt& stmt) {
	resolve(stmt.expression);
	return;
}

void Resolver::visitIfStmt(const IfStmt& stmt) {
	resolve(stmt.condition);
	resolve(stmt.thenBranch);
	if (stmt.elseBranch != nullptr) {
		resolve(stmt.elseBranch);
	}
	return;
}

void Resolver::visitPrintStmt(const PrintStmt& stmt) {
	resolve(stmt.expression);
	return;
}

void Resolver::visitReturnStmt(const ReturnStmt& stmt) {

	if (currentFunction == FunctionType::NONE) {
		Error::error(stmt.keyword, "Cannot return from top-level code.");
	}
	if (stmt.value != nullptr) {
		resolve(stmt.value);
	}
	return;
}

void Resolver::visitWhileStmt(const WhileStmt& stmt) {
	resolve(stmt.condition);
	resolve(stmt.body);
	return;
}

std::shared_ptr<Object> Resolver::visitBinaryExpr(const Binary& expr) {
	resolve(expr.left);
	resolve(expr.right);
	return nullptr;
}

std::shared_ptr<Object> Resolver::visitCallExpr(const Call& expr) {
	resolve(expr.callee);
	for (auto& argument : *expr.arguments) {
		resolve(argument);
	}
	return nullptr;
}

std::shared_ptr<Object> Resolver::visitGroupingExpr(const Grouping& expr) {
	resolve(expr.expression);
	return nullptr;
}

std::shared_ptr<Object> Resolver::visitLiteralExpr(const Literal& expr) {
	return nullptr;
}

std::shared_ptr<Object> Resolver::visitLogicalExpr(const Logical& expr) {
	resolve(expr.left);
	resolve(expr.right);
	return nullptr;
}

std::shared_ptr<Object> Resolver::visitUnaryExpr(const Unary& expr) {
	resolve(expr.right);
	return nullptr;
}