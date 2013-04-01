#ifndef _AST_POINTER_H_
#define_AST_POINTER_H_
class AstPointer : public AST
{
	 AstPointer *pointer;
	 AstTypeQualList *list;
	  
public:
	AstPointer(AstPointer *pointer , AstTypeQualList *list  )
	{
		this->pointer = pointer;
		this->list= list ; 
		
	}
	void Visit()
	{
		
	}
	
} ; 


#endif 
