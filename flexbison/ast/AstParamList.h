#ifndef _AST_PARAMTYPELLIST_H_
#define _AST_PARAMTYPELLIST_H_
#include "AstStatement.h"
using namespace std; 
class AstParamList : public AstStatement 
{
	
    AstParamDec *dec;
	AstParamList *plist;
public:
	AstParamList( AstParamDec *dec , AstParamList *plist)
	{
		this->dec = dec; 
		this->plist = plist ; 
	}
	void Visit()
	{
		
	} 
	
};


#endif 
