#ifdef   _AST_ABSDECL_H_
#define  _AST_ABSDECL_H_
class AstAbstractDecl : public AST
{
	AstPointer *pointer;
	AstDirectAbsDecl *dec; 
public:
	AstAbstractDecl( AstPointer *pointer , AstDirectAbsDecl *dec)
	{
		this->pointer = pointer;
		this->dec = dec; 
	} 
	void Visit()
	{
		
	}
	
};

#endif 
