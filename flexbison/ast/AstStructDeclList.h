#ifndef _AST_STRUCTDELLIST_H_
#define _AST_STRUCTDELLIST_H_
#include "AstStatement.h"
using namespace std; 
class AstStructDeclList : public AstStatement 
{
	AstStructDecl *sdecl; 
	AstStructDeclList *stdlist;
public:
	AstStructDeclList( AstStructDecl *sdecl , AstStructDeclList *stdlist)
	{
		this->sdecl= sdecl ;
		this->stdlist = stdlist; 
	}
	void Visit()
	{
		
	} 
	
};


#endif 
