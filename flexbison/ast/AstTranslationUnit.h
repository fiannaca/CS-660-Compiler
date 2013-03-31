#ifndef _AST_TRANS_
#define _AST_TRANS_
#include "Ast.h"
#include  "AstExternDec.h"
class AstTrans: public AST 
{
	AstTrans *trans;
	AstExternDec *dec; 
	public:
		AstTrans( AstTrans *trans ,AstExternDec *dec)
		{
			this->trans = trans;
			this->dec= dec; 
		}
		void Visit() 
		{
			
		}
	
};
#endif 
