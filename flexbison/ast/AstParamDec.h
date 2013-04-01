#ifdef   _PARAM_DECL_
#define  _PARAM_DECL_
class AstParamDec : public AST
{
	AstDecSpeci *speci;
	AstDeclarator *declarator; 
	AstAbstractDecl *adecl; 
public:
    AstParamDec (AstDecSpeci *speci ,AstDeclarator *declarator , AstAbstractDecl *adecl )
    {
    	this->speci = speci;
    	this->declarator = declarator; 
    	this->adecl = adecl; 
    }
	void Visit()
	{
		
	}
	
}; 



#endif 
