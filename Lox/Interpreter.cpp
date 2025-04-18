#include "Interpreter.h"

Interpreter::Interpreter() {
	globals = std::make_shared<Environment>();
	environment = globals;
    class ClockFunction : public LoxCallable {
    public:
        int arity() override {
            return 0;
        }

        std::shared_ptr<Object> call(std::shared_ptr<Interpreter> interpreter,const std::vector<std::shared_ptr<Object>>& arguments) override {
			return std::make_shared<Number>(static_cast<double>(std::clock()) / CLOCKS_PER_SEC);

        }

        std::string toString() override{
			return "<native fn>";
        }

        bool operator==(const Object& other) const override {
            return false;
        }
    };

	globals->define("clock", std::make_shared<ClockFunction>());
}

void Interpreter::interpret(std::vector<std::shared_ptr<Stmt>> statements) {
    try {
        for (const std::shared_ptr<Stmt>& statement : statements) {
            execute(statement);
        }
    } catch (const RuntimeError& error) {
        Error::runtimeError(error);
    }
}

void Interpreter::execute(const std::shared_ptr<Stmt>& stmt) {
    stmt->accept(*this);
}

void Interpreter::resolve(const std::shared_ptr<Expr> expr, int depth) {
    locals[expr] = depth;
}

std::shared_ptr<Object> Interpreter::lookUpVariable(const Token& name, const std::shared_ptr<Expr>& expr) {
    auto it = locals.find(expr);
    if (it != locals.end()) {
        int distance = it->second;
        return environment->getAt(distance, name.lexeme);
    }
    else {
        return globals->get(std::make_shared<Token>(name));
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
    case TokenType::GREATER_EQUAL:
        checkNumberOperands(expr.op, left, right);
        return std::make_shared<Bool>(std::dynamic_pointer_cast<Number>(left)->value >= std::dynamic_pointer_cast<Number>(right)->value);
    case TokenType::LESS:
        checkNumberOperands(expr.op, left, right);
        return std::make_shared<Bool>(std::dynamic_pointer_cast<Number>(left)->value < std::dynamic_pointer_cast<Number>(right)->value);
    case TokenType::LESS_EQUAL:
        checkNumberOperands(expr.op, left, right);
        return std::make_shared<Bool>(std::dynamic_pointer_cast<Number>(left)->value <= std::dynamic_pointer_cast<Number>(right)->value);
    case TokenType::BANG_EQUAL:
        return std::make_shared<Bool>(!isEqual(left, right));
    case TokenType::EQUAL_EQUAL:
        return std::make_shared<Bool>(isEqual(left, right));
    case TokenType::MINUS:
        checkNumberOperands(expr.op, left, right);
        return std::make_shared<Number>(std::dynamic_pointer_cast<Number>(left)->value - std::dynamic_pointer_cast<Number>(right)->value);
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
    case TokenType::SLASH:
        checkNumberOperands(expr.op, left, right);
        return std::make_shared<Number>(std::dynamic_pointer_cast<Number>(left)->value / std::dynamic_pointer_cast<Number>(right)->value);
    case TokenType::STAR:
        checkNumberOperands(expr.op, left, right);
        return std::make_shared<Number>(std::dynamic_pointer_cast<Number>(left)->value * std::dynamic_pointer_cast<Number>(right)->value);
    }
    return nullptr;
}

std::shared_ptr<Object> Interpreter::visitUnaryExpr(const Unary& expr) {
    auto right = evaluate(expr.right);

    switch (expr.op.type) {
    case TokenType::BANG:
        return std::make_shared<Bool>(!isTruthy(right));
    case TokenType::MINUS:
        checkNumberOperand(expr.op, right);
        return std::make_shared<Number>(-std::dynamic_pointer_cast<Number>(right)->value);
    }

    return nullptr;
}

std::shared_ptr<Object> Interpreter::visitVariableExpr(const Variable& expr) {
    return lookUpVariable(expr.name, std::const_pointer_cast<Expr>(expr.shared_from_this()));
}


std::shared_ptr<Object> Interpreter::visitAssignExpr(const Assign& expr) {
    std::shared_ptr<Object> value = evaluate(expr.value);

    auto it = locals.find(std::const_pointer_cast<Expr>(expr.shared_from_this()));
    ;


    if (it != locals.end()) {
        int distance = it->second;
        environment->assignAt(distance, expr.name, value);
    }
    else {
        globals->assign(std::make_shared<Token>(expr.name), value);
    }
    return value;
}


std::shared_ptr<Object> Interpreter::visitLogicalExpr(const Logical& expr) {
    std::shared_ptr<Object> left = evaluate(expr.left);
    if (expr.op.type == TokenType::OR) {
        if (isTruthy(left)) return left;
    }
    else {
        if (!isTruthy(left)) return left;
    }
    return evaluate(expr.right);
}

std::shared_ptr<Object> Interpreter::visitCallExpr(const Call& expr) {
    std::shared_ptr<Object> callee = evaluate(expr.callee);

    std::vector<std::shared_ptr<Object>> arguments;
    for (const auto& argument : *expr.arguments) {
        arguments.push_back(evaluate(argument));
    }

    
    std::shared_ptr<LoxCallable> function = std::dynamic_pointer_cast<LoxCallable>(callee);


    if (!function) {
        throw RuntimeError(std::make_shared<Token>(expr.paren), "Can only call functions and classes.");
    }

    return function->call(shared_from_this(), arguments);
}

std::shared_ptr<Object> Interpreter::visitGetExpr(const Get& expr) {
    std::shared_ptr<Object> object = evaluate(expr.object);
    if (auto instance = std::dynamic_pointer_cast<LoxInstance>(object)) {
        return instance->get(expr.name);
    }
    throw RuntimeError(std::make_shared<Token>(expr.name), "Only instances have properties.");
}


std::shared_ptr<Object> Interpreter::visitSetExpr(const Set& expr) {
    std::shared_ptr<Object> object = evaluate(expr.object);

    if (!(std::dynamic_pointer_cast<LoxInstance>(object))) {
        throw RuntimeError(std::make_shared<Token>(expr.name), "Only instances have fields.");
    }

	std::shared_ptr<Object> value = evaluate(expr.value);
	std::dynamic_pointer_cast<LoxInstance>(object)->set(expr.name, value);
	return value;
}

std::shared_ptr<Object> Interpreter::visitSuperExpr(const Super& expr) {
	int distance = locals[std::const_pointer_cast<Expr>(expr.shared_from_this())];
	std::shared_ptr<LoxClass> superclass = std::dynamic_pointer_cast<LoxClass>(environment->getAt(distance, "super"));

	std::shared_ptr<LoxInstance> object = std::dynamic_pointer_cast<LoxInstance>(environment->getAt(distance - 1, "this"));

	std::shared_ptr<LoxFunction> method = superclass->findMethod(expr.method.lexeme);

	if (method == nullptr) {
		throw RuntimeError(std::make_shared<Token>(expr.method), "Undefined property '" + expr.method.lexeme + "'.");
	}
	return method->bind(object);
}

std::shared_ptr<Object> Interpreter::visitThisExpr(const This& expr) {
	return lookUpVariable(expr.keyword, std::const_pointer_cast<Expr>(expr.shared_from_this()));
}

void Interpreter::visitExpressionStmt(std::shared_ptr<ExpressionStmt> stmt) {
    evaluate(stmt->expression);
}


void Interpreter::visitPrintStmt(std::shared_ptr<PrintStmt> stmt) {
    std::shared_ptr<Object> value = evaluate(stmt->expression);
    std::cout << stringify(value) << std::endl;
}


void Interpreter::visitVarStmt(std::shared_ptr<VarStmt> stmt) {
    std::shared_ptr<Object> value = nullptr;
    if (stmt->initializer != nullptr) {
        value = evaluate(stmt->initializer);
    }
    environment->define(stmt->name.lexeme, value);
}



void Interpreter::visitIfStmt(std::shared_ptr<IfStmt> stmt) {
    if (isTruthy(evaluate(stmt->condition))) {
		execute(stmt->thenBranch);
	}
    else if (stmt->elseBranch != nullptr) {
        execute(stmt->elseBranch);
    }
    return;
}

void Interpreter::visitWhileStmt(std::shared_ptr<WhileStmt> stmt) {
	while (isTruthy(evaluate(stmt->condition))) {
		execute(stmt->body);
	}
    return;
}

void Interpreter::visitFunctionStmt(std::shared_ptr<FunctionStmt> stmt) {
    std::shared_ptr<LoxFunction> function = std::make_shared<LoxFunction>(std::make_shared<FunctionStmt>(stmt->name, stmt->params, stmt->body), environment, false);
    environment->define(stmt->name.lexeme, function);
}

void Interpreter::visitClassStmt(std::shared_ptr<ClassStmt> stmt) {
	std::shared_ptr<Object> superclass = nullptr;

    if (stmt->superclass != nullptr) {
		superclass = evaluate(stmt->superclass);
        if (std::dynamic_pointer_cast<LoxClass>(superclass) == nullptr) {
			throw RuntimeError(std::make_shared<Token>(stmt->superclass->name), "Superclass must be a class.");
        }
    }

    environment->define(stmt->name.lexeme, nullptr);

    if (stmt->superclass != nullptr) {
		environment = std::make_shared<Environment>(environment);
		environment->define("super", superclass);
    }

	std::shared_ptr<std::map<std::string, std::shared_ptr<LoxFunction>>> methods = std::make_shared<std::map<std::string, std::shared_ptr<LoxFunction>>>();

    for (std::shared_ptr<FunctionStmt> method : *stmt->methods) {
		std::shared_ptr<LoxFunction> function = std::make_shared<LoxFunction>(method, environment, method->name.lexeme == "init");
		methods->insert({ method->name.lexeme, function });
    }

	std::shared_ptr<LoxClass> klass = std::make_shared<LoxClass>(stmt->name.lexeme, std::dynamic_pointer_cast<LoxClass>(superclass), methods);
    
	if (superclass != nullptr) {
		environment = environment->enclosing;
	}

    environment->assign(std::make_shared<Token>(stmt->name), klass);
    return;
}

void Interpreter::visitReturnStmt(std::shared_ptr<ReturnStmt> stmt) {
	std::shared_ptr<Object> value = nullptr;
	if (stmt->value != nullptr) {
		value = evaluate(stmt->value);
	}
	throw Return(value);
}

void Interpreter::visitBlock(std::shared_ptr<Block> stmt) {
    executeBlock(stmt->statements, std::make_shared<Environment>(environment));
}

void Interpreter::executeBlock(const std::shared_ptr<std::vector<std::shared_ptr<Stmt>>>& statements, std::shared_ptr<Environment> environment) {
    std::shared_ptr<Environment> previous = this->environment;

    try {
        this->environment = environment;

        for (const auto& statement : *statements) {
            execute(statement);
        }
    } catch (...) {
        this->environment = previous;
        throw;
    }

    this->environment = previous;
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