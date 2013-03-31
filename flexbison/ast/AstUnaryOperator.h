#ifndef _AST_UNARY_
#define _AST_UNARY_
class AstUnary: public AstExpression
{ 
   	 string operatorType; 
   	 AstExpression *exp; 
public:
	 AstUnary(AstExpression *ex,const string &op)
	 {
	 	 this->exp= ex ; 
		 this->operatorType = op; 
	 }
	 void Visit()
	 {
	 	
	 }
	
};

#endif 
