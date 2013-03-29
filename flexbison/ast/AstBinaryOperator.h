#ifndef _AST_BINARY_
#define _AST_BINARY_
#include <string>
#include "AstExpression.h"
using namespace std;
class AstBinary: public AstExpression
{ 
   	 string operatorType;
	 AstExpression *expr1 ;
	 AstExpression *expr2;  
public:
	 AstBinary(AstExpression  *exp1 ,const string &op , AstExpression *exp2)
	 {
	 	 this->expr1 = exp1 ; 
		 this->operatorType = op;
		 this->expr2 = exp2 ;  
	 }
	 void Visit()
	 {
	 	
	 }
	
};

#endif 
