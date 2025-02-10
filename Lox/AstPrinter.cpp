#include "AstPrinter.h"


std::string AstPrinter::print(const std::shared_ptr<Expr>& expr) {
	return expr->accept(*this)->toString();
} 

std::shared_ptr<Object> AstPrinter::visitBinaryExpr(const Binary& expr){
	return parenthesize(expr.op.lexeme, expr.left, expr.right);
}

std::shared_ptr<Object> AstPrinter::visitGroupingExpr(const Grouping& expr)  {
	return parenthesize("group", expr.expression);
}

std::shared_ptr<Object> AstPrinter::visitLiteralExpr(const Literal& expr)  {
    if (expr.value) {
		return expr.value;
    }
	return std::make_shared<String>("unknown");
}

std::shared_ptr<Object> AstPrinter::visitUnaryExpr(const Unary& expr)  {
	return parenthesize(expr.op.lexeme, expr.right);
}

template<typename... Exprs>
std::shared_ptr<Object> AstPrinter::parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr, Exprs... rest) {
    std::string result = "(" + name;
    appendExpr(result, expr);
    (appendExpr(result, rest), ...);
    result += ")";
    return std::make_shared<String>(result);
}

std::shared_ptr<Object> AstPrinter::parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr) {
    std::string result = "(" + name + " " + expr->accept(*this)->toString() + ")";
	return std::make_shared<String>(result);
}
void AstPrinter::appendExpr(std::string& result, const std::shared_ptr<Expr>& expr) {
    result += " " + expr->accept(*this)->toString();
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