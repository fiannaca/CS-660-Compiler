#ifndef _AST_LABEL_
#define _AST_LABEL_
#include "AstStatement.h"
#include <string>
using namespace std; 
class AstLabel: AstStatement 
{
	string labelName;
	AstStatement *statement;
	public:
		AstLabel(AstStatement *stmt)
		{
			this->statement = stmt ; 
		}
		void Visit() 
		{
			
		}
	
};
#endif 
