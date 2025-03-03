//#include "AstPrinter.h"
//
//std::shared_ptr<Object> AstPrinter::visitAssignExpr(const Assign& expr) {
//	return parenthesize("assign", expr.name, expr.value);
//}
//
//std::shared_ptr<Object> AstPrinter::visitVariableExpr(const Variable& expr) {
//	return std::make_shared<String>(expr.name.lexeme);
//}
//
//std::string AstPrinter::print(const std::shared_ptr<Expr>& expr) {
//	return expr->accept(*this)->toString();
//} 
//
//std::shared_ptr<Object> AstPrinter::visitBinaryExpr(const Binary& expr){
//	return parenthesize(expr.op.lexeme, expr.left, expr.right);
//}
//
//std::shared_ptr<Object> AstPrinter::visitGroupingExpr(const Grouping& expr)  {
//	return parenthesize("group", expr.expression);
//}
//
//std::shared_ptr<Object> AstPrinter::visitLiteralExpr(const Literal& expr)  {
//    if (expr.value) {
//		return expr.value;
//    }
//	return std::make_shared<String>("unknown");
//}
//
//std::shared_ptr<Object> AstPrinter::visitUnaryExpr(const Unary& expr)  {
//	return parenthesize(expr.op.lexeme, expr.right);
//}
//
//template<typename... Exprs>
//std::shared_ptr<Object> AstPrinter::parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr, Exprs... rest) {
//    std::string result = "(" + name;
//    appendExpr(result, expr);
//    (appendExpr(result, rest), ...);
//    result += ")";
//    return std::make_shared<String>(result);
//}
//
//std::shared_ptr<Object> AstPrinter::parenthesize(const std::string& name, const std::shared_ptr<Expr>& expr) {
//    std::string result = "(" + name + " " + expr->accept(*this)->toString() + ")";
//	return std::make_shared<String>(result);
//}
//void AstPrinter::appendExpr(std::string& result, const std::shared_ptr<Expr>& expr) {
//    result += " " + expr->accept(*this)->toString();
//}
