#include "AstPrinter.h"


std::string AstPrinter::print(const std::shared_ptr<Expr>& expr) {
	return expr->accept(*this);
} 

std::string AstPrinter::visitBinaryExpr(const Binary& expr){
	return parenthesize(expr.operators.lexeme, expr.left, expr.right);
}

std::string AstPrinter::visitGroupingExpr(const Grouping& expr)  {
	return parenthesize("group", expr.expression);
}

std::string AstPrinter::visitLiteralExpr(const Literal& expr)  {
    if (expr.value) {
		return expr.value->toString();
    }
	return "unknown";
}

std::string AstPrinter::visitUnaryExpr(const Unary& expr)  {
	return parenthesize(expr.operators.lexeme, expr.right);
}

template<typename... Exprs>
std::string AstPrinter::parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr, Exprs... rest) {
    std::string result = "(" + name;
    appendExpr(result, expr);
    (appendExpr(result, rest), ...);
    result += ")";
    return result;
}

std::string AstPrinter::parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr) {
    return "(" + name + " " + expr->accept(*this) + ")";
}
void AstPrinter::appendExpr(std::string& result, const std::shared_ptr<Expr>& expr) {
    result += " " + expr->accept(*this);
}


//int main(int argc, char* argv[])
//{
//
//    auto expr = std::make_shared<Binary>(
//		std::make_shared<Literal>(std::make_shared<std::variant<std::nullptr_t, double, std::string>>(1.0)),
//		Token(TokenType::PLUS, "+", "", 1),
//		std::make_shared<Unary>(Token(TokenType::MINUS, "-", "", 1), std::make_shared<Literal>(std::make_shared<std::variant<std::nullptr_t, double, std::string>>(2.0)))
//	);
//
//    auto expression = std::make_shared<Binary>(
//        std::make_shared<Unary>(
//            Token( TokenType::MINUS, "-", "", 1 ),
//            std::make_shared<Literal>(std::make_shared<std::variant<std::nullptr_t, double, std::string>>(2.0))
//        ),
//        Token( TokenType::STAR, "*", "", 1 ),
//        std::make_shared<Grouping>(
//            std::make_shared<Literal>(std::make_shared<std::variant<std::nullptr_t, double, std::string>>(2.0))
//        )
//    );
//
//
//	AstPrinter printer;
//	std::cout << printer.print(expr) << std::endl;
//	return 0;
//}