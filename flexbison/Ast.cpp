#include "Ast.h"
#include <stdarg.h>


TAC_Generator AST::tacGen("TAC.out");
Visualizer AST::vis;
list<string> AST::tempStack;
string AST::currentTemp="";
string AST::returnLabel="";
string AST::lastID="";
string AST::currentFunction="";
SymTab* AST::symbolTable=NULL;
string AST::currentIdName="";
int AST::currentConstantValue =0;
int AST::currentIndexVal = 0 ;
string AST::currentID = ""; 

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstPrimaryExpr  /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstPrimaryExpr::AstPrimaryExpr(AstID* id)
{
    this->id = id;
    this->constant = NULL;
    this->str = NULL;
    this->expr = NULL;
    this->type = ID;
    this->etype = id->type;
    AST::currentIdName=id->str; 

    this->setLabel("PrimaryExpression");
}

AstPrimaryExpr::AstPrimaryExpr(AstConstant* c)
{
    this->id = NULL;
    this->constant = c;
    this->str = NULL;
    this->expr = NULL;
    this->type = CONST;
    this->etype = c->etype;

    this->setLabel("PrimaryExpression");
}

AstPrimaryExpr::AstPrimaryExpr(AstString* s)
{
    this->id = NULL;
    this->constant = NULL;
    this->str = s;
    this->expr = NULL;
    this->type = STRING;
    this->etype = s->type;

    this->setLabel("PrimaryExpression");
}

AstPrimaryExpr::AstPrimaryExpr(AstExpression* e)
{
    this->id = NULL;
    this->constant = NULL;
    this->str = NULL;
    this->expr = e;
    this->type = EXPR;
    this->etype = e->type;

    this->setLabel("PrimaryExpression");
}

void AstPrimaryExpr::Visit()
{            
    SymTab dummy;
    string currentLabel; 
    string lbl;
    int ival;
    switch(type)
    {
        case ID:
            id->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), id->getUID());

            //Output 3AC
               
    
             currentLabel =TAC_Generator::GetIVarName();
             AST::tempStack.push_back(this->id->str); 
             AST::tacGen.Fetch(this->id->str,AST::symbolTable ,currentLabel);   
             AST::lastID = this->id->str;

                       


            break;

        case CONST:
            constant->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), constant->getUID());

            //Output 3AC
            lbl = tacGen.GetIVarName();
            ival = constant->GetIVal(); 
            tacGen.toTAC(TAC_Generator::IMMEDIATE_I, (void*)&lbl, (void*)ival);
            AST::tempStack.push_back(lbl);
            break;

        case STRING:
            str->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), str->getUID());

            //Output 3AC
            break;

        case EXPR:
            expr->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), expr->getUID());

            //Output 3AC
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstArgExprList  /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstArgExprList::AstArgExprList(AstArgExprList *list, AstAssignExpr *expr)
{
    this->list = list;
    this->expr = expr;
    this->isLastItem = false;
    this->isVisited = false;
    this->setLabel("ArgumentExpressionList");            
}

AstArgExprList::AstArgExprList(AstAssignExpr *expr)
{
    this->list = NULL;
    this->expr = expr;
    this->isLastItem = true;
    this->isVisited = false;
    this->setLabel("ArgumentExpressionList");
}

void AstArgExprList::Visit()
{
    //Visit children nodes
    AstArgExprList *base = this;
    int count = 0 ; 
    string tempVar;
    while(base != NULL && !(base->IsVisited()))
    {
		base->SetVisited(true);
		++count;
		base = base->GetList();
	}
    if(!isLastItem)
    {
        list->Visit();
    }
    

    expr->Visit();
    while(count--)
    {
		tempVar = AST::tempStack.back();
		AST::tempStack.pop_back();
		AST::tacGen.toTAC(TAC_Generator::FPAR,(void *)&tempVar);
		
	} 

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());
    AST::vis.addEdge(this->getUID(), expr->getUID());
    
    if(!this->isLastItem)
    {
        AST::vis.addEdge(this->getUID(), list->getUID());
    }

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstPostfixExpr  /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstPostfixExpr::AstPostfixExpr(AstPrimaryExpr* p)
{
    this->priexpr = p;
    this->ptfExpr = NULL;
    this->brakExpr = NULL;
    this->argExprList = NULL;
    this->id = NULL;
    this->op = NONE;
    this->visited = false; 
    this->t = PRIMARY;
    this->type = p->etype;
    this->currentOffset = 1; 
    isAddr = false;
    this->arrayType = NULL;
    this->setLabel("AstPostfixExpr - Primary");
}

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr* p, AstExpression* e)
{
    this->priexpr = NULL;
    this->ptfExpr = p;
    this->brakExpr = e;
    this->argExprList = NULL;
    this->id = NULL;
    this->op = NONE;
    this->visited  = false;
    this->t = BRACKETS;
    this->currentOffset = 1;     
    isAddr = false; 
   // this->type = ((ArrayType*)p->type)->GetBase();
    this->arrayType = NULL; 
    this->setLabel("AstPostfixExpr - Brackets");
}

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr* p)
{
    this->priexpr = NULL;
    this->ptfExpr = p;
    this->brakExpr = NULL;
    this->argExprList = NULL;
    this->id = NULL;
    this->op = NONE;
    this->visited = false;
    this->t = EMPTY_PARENS;
    this->currentOffset = 1;     
    isAddr = false; 
    this->type = p->type;

    this->arrayType = NULL;
    this->setLabel("AstPostfixExpr - Empty Parens");
}

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *p, AstArgExprList *a)
{
    this->priexpr = NULL;
    this->ptfExpr = p;
    this->brakExpr = NULL;
    this->argExprList = a;
    this->id = NULL;
    this->op = NONE;
    this->visited = false;
    this->t = PARENS;
    this->currentOffset = 1 ; 
    this->type = p->type;
    isAddr = false; 
    this->arrayType = NULL;
    this->setLabel("AstPostfixExpr - Parens");
}

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *p, Operator o, AstID *i)
{
    this->priexpr = NULL;
    this->ptfExpr = p;
    this->brakExpr = NULL;
    this->argExprList = NULL;
    this->id = i;
    this->op = o;
    this->visited = false; 
    if(o == DOT_OP)
        this->t = DOT;
    else
        this->t = PTR;

    this->type = i->type;
    this->currentOffset = 1;   
    this->arrayType = NULL;   
    isAddr = false;   
    this->setLabel("AstPostfixExpr - Dot or Ptr");
}

AstPostfixExpr::AstPostfixExpr(AstPostfixExpr *p, Operator o)
{
    this->priexpr = NULL;
    this->ptfExpr = p;
    this->brakExpr = NULL;
    this->argExprList = NULL;
    this->id = NULL;
    this->op = o;
    this->visited = false; 
    if(o == INC_OP)
        this->t = INC;
    else
        this->t = DEC;
    this->currentOffset = 1; 
    this->type = p->type;
    this->arrayType = NULL;  
    isAddr = false; 
    this->setLabel("AstPostfixExpr - Inc or Dec");
}

//Traversal
void AstPostfixExpr::Visit()
{
   
    string tempVar;
    string lastUsedTemp ,currentLabel;
    string one = "1";
    int arrayBrackets=0;
    SymbolInfo info;
    SymbolInfo *arrayinfo= NULL;
    list<SymbolInfo> localItems;
    localItems =  AST::symbolTable->GetLocals(AST::currentFunction);	
    list<SymbolInfo>::iterator items = localItems.begin();
    string arrayName; 
    string arrayAddr;
    int arrayTypeSize;   
    string immediateValue;
    string result; 
    string effectiveAddress;
    int currentOffset; 
    Type *outerType=NULL; 
    int currentCapacity = 1;     
    AstPostfixExpr *base= this; 
    bool isLeaf;
    
    switch(t)
    {
        case PRIMARY:
            //Visit children nodes
            priexpr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), priexpr->getUID());

            //Output 3AC
            
            break;

        case BRACKETS:
            //Visit children nodes
            
            if ( ! Visited() )
            {
                      info.symbol_name = AST::currentIdName;
                      arrayinfo = AST::symbolTable->fetch_symbol(info); 
                      arrayName = GetArrayName();       
                      while( items != localItems.end())
                      {
                          cout<<endl<<items->symbol_name;
                          if ( items->symbol_name ==  arrayName )
                          {
                             arrayinfo = &(*items); 
                          }            
                          items++;
                      } 
                      if(arrayinfo == NULL  )
                      {
                            std::cout<< "Array not found !";
                      }              
                      else 
                      {             
                           arrayTypeSize = GetInnerType(arrayinfo->symbolType)->GetSize();
                           cout<< "\n Array Type Size :=   "<<arrayTypeSize; 
                           arrayAddr=TAC_Generator::GetIVarName();
                           AST::tacGen.toTAC(TAC_Generator::ADDR, (void *)&arrayName,(void *)&arrayAddr); 
                           outerType = arrayinfo->symbolType;           
                           currentCapacity = arrayTypeSize;
                           while(outerType->GetName() == "ARRAY" && base->isBracket())
                           {
                                base->SetOffset(currentCapacity);
                                currentCapacity *= ((ArrayType*)outerType)->GetDimension();
                                outerType = ((ArrayType*)outerType)->GetBase();
                                base = base->GetPostfix();       

                           }  
                           this->arrayType = ( (ArrayType*)(arrayinfo->symbolType))->GetBase(); 
                           AST::tempStack.push_back(arrayAddr);                                     
                      }
                      
                      
                      visited = true;   
            }
            if(IsAddrExp())
               ptfExpr->SetAddress(true);  
            ptfExpr->SetVisited(true);   
            if ( this->arrayType != NULL ) 
            {
               if ( this->arrayType->GetName() == "ARRAY")
               {
                    ptfExpr->SetArrayType(((ArrayType*)this->arrayType)->GetBase());
               }
            }          
            ptfExpr->Visit();                
            brakExpr->Visit();
              
            isLeaf = false;
            if ( this->arrayType == NULL )
            {
                isLeaf = true;
                 
            }
            else if ( this->arrayType->GetName() != "ARRAY") 
            {
                isLeaf = true;
            }   
            
            
            tempVar=TAC_Generator::GetIVarName();  
            result= TAC_Generator::GetIVarName();  
            effectiveAddress =  TAC_Generator::GetIVarName();  
            immediateValue = AST::tempStack.back();
            AST::tempStack.pop_back();    
          
            currentOffset = this->GetOffset(); 
            AST::tacGen.toTAC(TAC_Generator::IMMEDIATE_I, (void *)&tempVar,(void *)currentOffset); 
            AST::tacGen.toTAC(TAC_Generator::MULT, (void *)&immediateValue,(void *)&tempVar,(void *)&result);     
            currentLabel = AST::tempStack.back();
            AST::tempStack.pop_back();
            if  (isLeaf) 
            {
               currentLabel = AST::tempStack.back();
               AST::tempStack.pop_back();
            }
            AST::tacGen.toTAC(TAC_Generator::ADD , (void *)&currentLabel , (void *)&result ,(void *)&effectiveAddress);            
          
            
            if( !IsAddrExp() && isLeaf )
            { 
              result = TAC_Generator::GetIVarName(); 
              AST::tacGen.toTAC(TAC_Generator::VALAT,(void *)&effectiveAddress, (void *)&result);
              AST::tempStack.push_back(result);   
            }
            else 
            {   
                    AST::tempStack.push_back(effectiveAddress);      
            } 
            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
            AST::vis.addEdge(this->getUID(), brakExpr->getUID());

            //Output 3AC
            
            break;

        case EMPTY_PARENS:
            //Visit children nodes
             ptfExpr->Visit();
             currentLabel =  ptfExpr->GetPrimary()->GetID()->GetName(); 
             AST::tacGen.toTAC(TAC_Generator::CALL,(void *)&currentLabel);
          //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ptfExpr->getUID());

            //Output 3AC
            
            break;

        case PARENS:
            //Visit children nodes
            ptfExpr->Visit();
            argExprList->Visit();
            currentLabel =  ptfExpr->GetPrimary()->GetID()->GetName(); 
            AST::tacGen.toTAC(TAC_Generator::CALL,(void *)&currentLabel);
            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
            AST::vis.addEdge(this->getUID(), argExprList->getUID());

            //Output 3AC
            
            break;

        case DOT:
            //Visit children nodes
            ptfExpr->Visit();
            id->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
            AST::vis.addEdge(this->getUID(), id->getUID());

            //Output 3AC
            
            break;

        case PTR:
            //Visit children nodes
            ptfExpr->Visit();
            id->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ptfExpr->getUID());
            AST::vis.addEdge(this->getUID(), id->getUID());

            //Output 3AC
            
            break;

        case INC:
            //Visit children nodes
            ptfExpr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ptfExpr->getUID());

            //Output 3AC
            currentLabel = TAC_Generator::GetIVarName();
            lastUsedTemp = AST::tempStack.back();
            tempVar =    TAC_Generator::GetIVarName();
            AST::tacGen.toTAC(TAC_Generator::IMMEDIATE_I, (void *)&currentLabel,(void *)1);        
            AST::tacGen.toTAC(TAC_Generator::ADD , (void *) &currentLabel , (void *)&lastUsedTemp , (void *)&tempVar);   
            AST::tacGen.toTAC(TAC_Generator::MOV ,(void *)&tempVar,(void*) &lastUsedTemp ); 
            break;

        case DEC:
            //Visit children nodes
            ptfExpr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ptfExpr->getUID());

            //Output 3AC
            currentLabel =TAC_Generator::GetIVarName();
            lastUsedTemp = AST::tempStack.back(); 
            AST::tacGen.toTAC(TAC_Generator::SUB ,(void *)&lastUsedTemp , (void *) &one , (void *) &currentLabel);
            AST::tacGen.toTAC(TAC_Generator::MOV ,(void*) &lastUsedTemp ,(void *) &currentLabel);  
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstUnaryExpr  ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstUnaryExpr::AstUnaryExpr(AstPostfixExpr *e)
{
    this->expr = e;
    this->isINC = false;
    this->isDEC = false;
    this->op = NULL;
    this->cast = NULL;
    this->uniexpr = NULL;
    this->tname = NULL;
    this->t = POSTFIX;
    this->type = e->type;
    lhs = false;
    this->setLabel("UnaryExpression - Postfix");
}

AstUnaryExpr::AstUnaryExpr(AstUnaryExpr* e, bool inc)
{
    this->expr = NULL;
    this->isINC = inc;
    this->isDEC = !inc;
    this->op = NULL;
    this->cast = NULL;
    this->uniexpr = e;
    this->tname = NULL;
    this->type = e->type;
    lhs = false;
    if(inc)
        this->t = INC;
    else
        this->t = DEC;

    this->setLabel("UnaryExpression - Inc or Dec");
}

AstUnaryExpr::AstUnaryExpr(AstUnaryOp* o, AstCastExpr* c)
{
    this->expr = NULL;
    this->isINC = false;
    this->isDEC = false;
    this->op = o;
    this->cast = c;
    this->uniexpr = NULL;
    this->tname = NULL;
    this->type = c->type;
    lhs = false;
    this->t = CAST;

    this->setLabel("UnaryExpression - Cast");
}

AstUnaryExpr::AstUnaryExpr(AstUnaryExpr* e)
{
    this->expr = NULL;
    this->isINC = false;
    this->isDEC = false;
    this->op = NULL;
    this->cast = NULL;
    this->uniexpr = e;
    this->tname = NULL;
    this->type = e->type;

    this->t = SIZEOF;
    lhs = false;
    this->setLabel("UnaryExpression - Sizeof");
}

AstUnaryExpr::AstUnaryExpr(AstTypeName* t)
{
    this->expr = NULL;
    this->isINC = false;
    this->isDEC = false;
    this->op = NULL;
    this->cast = NULL;
    this->uniexpr = NULL;
    this->tname = t;
    this->type = new PODType("INT", INT_SIZE);

    this->t = SIZEOF_TYPE;
    lhs  = false; 
    this->setLabel("UnaryExpression - Sizeof Type");
}

//Traversal
void AstUnaryExpr::Visit()
{
    string lastUsedTemp;
    string currentLabel;
    long one=1;
    string immediateValue;
    bool isPrimary; 
    bool isArray = false;
    switch(t)
    {
        case POSTFIX:
            //Visit children nodes
            expr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), expr->getUID());

            //Output 3AC
            
            break;

        case INC:
            //Visit children nodes
            uniexpr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), uniexpr->getUID());

            //Output 3AC
            currentLabel =TAC_Generator::GetIVarName();
            lastUsedTemp = AST::tempStack.back(); 
            immediateValue = TAC_Generator::GetIVarName();
            AST::tempStack.pop_back();
            
            AST::tacGen.toTAC(TAC_Generator::IMMEDIATE_I, (void *)&immediateValue,(void *)one); 
            AST::tacGen.toTAC(TAC_Generator::ADD , (void *) &immediateValue , (void *)&lastUsedTemp , (void *)&currentLabel);   
            AST::tacGen.toTAC(TAC_Generator::MOV ,(void *) &currentLabel , (void*) &lastID ); 
            AST::tempStack.push_back( currentLabel);
            break;

        case DEC:
            //Visit children nodes
            uniexpr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), uniexpr->getUID());

            //Output 3AC
            currentLabel =TAC_Generator::GetIVarName();
            lastUsedTemp = AST::tempStack.back(); 
            AST::tempStack.pop_back();
            AST::tacGen.toTAC(TAC_Generator::SUB ,  (void *)&lastUsedTemp , (void *) one , (void *)&currentLabel);   
            AST::tacGen.toTAC(TAC_Generator::MOV ,(void *) &currentLabel ,(void*) &lastID ); 
            AST::tempStack.push_back( currentLabel);
            break;

        case CAST:
            //Visit children nodes
            if(op)
               op->Visit();
            if ( cast->GetUnary()->isPostfix())
            {
				if(cast->GetUnary()->GetPostfix()->isBracket())
				{
					cast->GetUnary()->GetPostfix()->SetAddress(true);
					isArray = true;
					
				}
			}
            cast->Visit();
            
            if ( op)
            {
               if(op->isNeg())
               {
                  lastUsedTemp = AST::tempStack.back();
                  currentLabel =TAC_Generator::GetIVarName();
                  AST::tempStack.pop_back();
                  AST::tacGen.toTAC(TAC_Generator::NEG,(void *)&lastUsedTemp,(void *)&currentLabel);
                  AST::tempStack.push_back(currentLabel);
                  
               } 
               if(op->isTilde())
               {
                  lastUsedTemp = AST::tempStack.back();
                  currentLabel =TAC_Generator::GetIVarName();
                  AST::tempStack.pop_back();
                  AST::tacGen.toTAC(TAC_Generator::TILDE,(void *)&lastUsedTemp,(void *)&currentLabel);
                  AST::tempStack.push_back(currentLabel);   
               }       
               if(op->isAddressOff())
               {
                 if(!isArray)
                 {
                   lastUsedTemp = AST::tempStack.back();
                   currentLabel =TAC_Generator::GetIVarName();
                   AST::tempStack.pop_back();
                   AST::tacGen.toTAC(TAC_Generator::ADDR,(void *)&(AST::currentIdName),(void *)&currentLabel);
                   AST::tempStack.push_back(currentLabel);
                 }
               }       
               if(op->isBang())
               {
                  lastUsedTemp = AST::tempStack.back();
                  currentLabel =TAC_Generator::GetIVarName();
                  AST::tempStack.pop_back();
                  AST::tacGen.toTAC(TAC_Generator::NOT,(void *)&lastUsedTemp,(void *)&currentLabel);
                  AST::tempStack.push_back(currentLabel);

               }       
               if(op->isStar())
               {
				   lastUsedTemp = AST::tempStack.back();
                   currentLabel = TAC_Generator::GetIVarName();
				  
				   if (!lhs)
				   {
				     
				     AST::tacGen.toTAC(TAC_Generator::VALAT,(void *)&lastUsedTemp,(void *)&currentLabel);
				     AST::tempStack.pop_back(); 
				     AST::tempStack.push_back(currentLabel); 
				   }
				   else
				   {
					   
					   //AST::tacGen.toTAC(TAC_Generator::MOV,(void *)&lastUsedTemp,(void *)&currentLabel);
				   } 
				   
				    
			   }
                    
            } 
            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), op->getUID());
            AST::vis.addEdge(this->getUID(), cast->getUID());

            //Output 3AC
            
            break;

        case SIZEOF:
            //Visit children nodes
            uniexpr->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), uniexpr->getUID());

            //Output 3AC
            
            break;

        case SIZEOF_TYPE:
            //Visit children nodes
            tname->Visit();

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), tname->getUID());

            //Output 3AC
            
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstCastExpr  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstCastExpr::AstCastExpr(AstUnaryExpr* u)
{
    this->uniexpr = u;
    this->cast = NULL;
    this->tname = NULL;
    this->type = u->type;

    this->setLabel("CastExpression");
}

AstCastExpr::AstCastExpr(AstTypeName* t, AstCastExpr* c)
{
    this->uniexpr = NULL;
    this->cast = c;
    this->tname = t;

    // TODO Figure out how to do this type checking thing later...
    
    this->setLabel("CastExpression");
}

//Traversal
void AstCastExpr::Visit()
{
    if(uniexpr)
    {
        //Visit children nodes
        uniexpr->Visit();

        //Output visualization
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), uniexpr->getUID());

        //Output 3AC
    }
    else
    {
        //Visit children nodes
        tname->Visit();
        cast->Visit();

        //Output visualization
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), tname->getUID());
        AST::vis.addEdge(this->getUID(), cast->getUID());

        //Output 3AC
    }
}


///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstTypeName  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//TODO complete later
//Constructor
/*
AstTypeName::AstTypeName()
{
    this->setLabel("TypeName");
}
*/
//Traversal
void AstTypeName::Visit()
{
    //Visit children nodes

    //Output visualization
    //AST::vis.addNode(this->getUID(), this->getLabel());
    //AST::vis.addEdge(this->getUID(), child->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstString  //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstString::AstString(string str, Type* t)
{
    this->val = str;
    this->type = t;
    
    this->setLabel("StringLiteral");
}

void AstString::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());

    //Add an extra node to the visualization to see the actual data
    int tmp = Visualizer::GetNextUID();
    AST::vis.addNode(tmp, "Value: " + val);
    AST::vis.addEdge(this->getUID(), tmp);
    
    string lbl = tacGen.GetLabelName();
    
    //TODO this may not be the right way to handle a string
    tacGen.toTAC(TAC_Generator::STRING, (void*)&lbl, (void*)&val);
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstConstant  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
    
AstConstant::AstConstant(int val)
{
    this->type = INT;
    this->ival = val;
    this->etype = new PODType("INT", INT_SIZE);
    AST::currentConstantValue = val;  
    this->setLabel("IntegerConstant");
}

AstConstant::AstConstant(string val)
{
    this->type = CHAR;
    this->str = val;
    this->etype = new PODType("CHAR", CHAR_SIZE);

    this->setLabel("CharacterConstant");
}

AstConstant::AstConstant(double val)
{
    this->type = FLOAT;
    this->dval = val;
    this->etype = new PODType("FLOAT", FLOAT_SIZE);

    this->setLabel("FloatConstant");
}

AstConstant::AstConstant(int val, string name, Type* t)
{
    this->type = ENUM;
    this->ival = val;
    this->str = name;
    this->etype = t;

    this->setLabel("EnumerationConstant");
}

void AstConstant::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());

    //Add an extra node to the visualization to see the actual data
    stringstream ss;
    int tmp = Visualizer::GetNextUID();
    /*
    switch(this->type)
    {
        case INT:
            {
                ss << "Value: " << ival;
                string lbl = tacGen.GetIVarName();
                tacGen.toTAC(TAC_Generator::IMMEDIATE_I, (void*)&lbl, (void*)ival);
                AST::tempStack.push_back(lbl);
            }
            break;
    
        case CHAR:
            {
                ss << "Value: " << str;
                
                // TODO we still need to deal with characters
            }
            break;

        case FLOAT:
            {
                ss << "Value: " << dval;
                string lbl = tacGen.GetFVarName();
                tacGen.toTAC(TAC_Generator::IMMEDIATE_F, (void*)&lbl, (void*)&dval);
            }
            break;

        case ENUM:
            {
                ss << "Name: " << str << ", Value: " << ival;
                string lbl = tacGen.GetIVarName();
                tacGen.toTAC(TAC_Generator::IMMEDIATE_I, (void*)&lbl, (void*)ival);
            }
            break;
    }
    */
    AST::vis.addNode(tmp, ss.str());
    AST::vis.addEdge(this->getUID(), tmp);
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstUnaryOp  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstUnaryOp::AstUnaryOp(Operator o)
{
    this->op = o;

    this->setLabel("UnaryOperator");
}

//Traversal
void AstUnaryOp::Visit()
{
    //Visit children nodes

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstID  //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstID::AstID(string s, Type* t)
{
    this->str = s;
    this->type = t;
    AST::currentID = s; 
    this->setLabel("Identifier");
}

void AstID::Visit()
{
   
   
   AST::vis.addNode(this->getUID(), this->getLabel() + ": " + str);
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstMultExpr  ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstMultExpr::AstMultExpr(AstCastExpr* c)
{
    this->cast = c;
    this->mult = NULL;
    this->op = NONE;
    this->type = c->type;

    this->setLabel("MultiplicativeExpression");
}

AstMultExpr::AstMultExpr(AstMultExpr* m, Operator o, AstCastExpr* c)
{
    this->cast = c;
    this->mult = m;
    this->op = o;
   /* 
    needsCast = !m->type->CheckType(c->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = m->type;
    }
*/

    this->setLabel("MultiplicativeExpression");
}

//Traversal
void AstMultExpr::Visit()
{
    string op1 , op2 , currentLabel; 
    string tempResult;
    //Visit children nodes
    if(mult)
        mult->Visit();

    cast->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(mult)
    {
        stringstream ss;
        int tmp = Visualizer::GetNextUID();
        char c = (op == STAR) ? '*' : ((op == DIV) ? '/' : '%');
        ss << c;

        AST::vis.addNode(tmp, ss.str());

        AST::vis.addEdge(this->getUID(), mult->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        
        
        tempResult = TAC_Generator::GetIVarName(); 
        currentLabel =TAC_Generator::GetIVarName();
        
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        switch(c)
        {
            case '*': 
              AST::tacGen.toTAC(TAC_Generator::MULT , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;
            case '/':
              AST::tacGen.toTAC(TAC_Generator::DIV , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;
            case '%':
              AST::tacGen.toTAC(TAC_Generator::REM , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
              
              break;
		}
        AST::tempStack.push_back( currentLabel);
    }

    AST::vis.addEdge(this->getUID(), cast->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstAddExpr  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstAddExpr::AstAddExpr(AstMultExpr* m)
{
    this->mult = m;
    this->add = NULL;
    this->op = NONE;
    this->type = m->type;

    this->setLabel("AdditiveExpression");
}

AstAddExpr::AstAddExpr(AstAddExpr* a, Operator o, AstMultExpr* m)
{
    this->mult = m;
    this->add = a;
    this->op = o;
   
/* 
    needsCast = !a->type->CheckType(m->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = a->type;
    }
 */   
    this->setLabel("AdditiveExpression");
}

//Traversal
void AstAddExpr::Visit()
{
	
	string op1 , op2 , currentLabel; 
	
    //Visit children nodes
    if(add)
        add->Visit();

    mult->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(add)
    {
        stringstream ss;
        int tmp = Visualizer::GetNextUID();
        char c = (op == PLUS) ? '+' : '-';
        ss << c;
        AST::vis.addNode(tmp, ss.str());

        AST::vis.addEdge(this->getUID(), add->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        
        
        currentLabel =TAC_Generator::GetIVarName();
        
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        
        
        switch(c)
        {
            case '+': 
              AST::tacGen.toTAC(TAC_Generator::ADD , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;
            case '-':
              AST::tacGen.toTAC(TAC_Generator::SUB , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;
            
		}
        AST::tempStack.push_back( currentLabel);
        
        
    }

    AST::vis.addEdge(this->getUID(), mult->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstShiftExpr  ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstShiftExpr::AstShiftExpr(AstAddExpr* a)
{
    this->add = a;
    this->shift = NULL;
    this->op = NONE;
    this->type = a->type;

    this->setLabel("ShiftExpression");
}

AstShiftExpr::AstShiftExpr(AstShiftExpr* s, Operator o, AstAddExpr* a)
{
    this->add = a;
    this->shift = s;
    this->op = o;
  /*  
    needsCast = !s->type->CheckType(a->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = s->type;
    }
*/
    this->setLabel("ShiftExpression");
}

void AstShiftExpr::Visit()
{
	
	string op1 , op2 , currentLabel; 
    //Visit children nodes
    if(shift)
        shift->Visit();

    add->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(shift)
    {
        int tmp = Visualizer::GetNextUID();
        string s = (op == LEFT_OP) ? "<<" : ">>";
        char c = (op == LEFT_OP) ? '<' : '>';
        AST::vis.addNode(tmp, s);

        AST::vis.addEdge(this->getUID(), shift->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        currentLabel =TAC_Generator::GetIVarName();
        
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        
        
        switch(c)
        {
            case '<': 
              AST::tacGen.toTAC(TAC_Generator::SHIFTL , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;
            case '>':
              AST::tacGen.toTAC(TAC_Generator::SHIFTR , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;
            
		}
        AST::tempStack.push_back( currentLabel);
        
        
    }

    AST::vis.addEdge(this->getUID(), add->getUID());

    //Output 3AC
}


///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstRelExpr  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstRelExpr::AstRelExpr(AstShiftExpr* s)
{
    this->shift = s;
    this->rel = NULL;
    this->op = NONE;
    this->type = s->type;

    this->setLabel("RelationalExpression");
}

AstRelExpr::AstRelExpr(AstRelExpr* r, Operator o, AstShiftExpr* s)
{
    this->shift = s;
    this->rel = r;
    this->op = o;
    
  /*
    needsCast = !r->type->CheckType(s->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = r->type;
    }
*/
    this->setLabel("RelationalExpression");
}

//Traversal
void AstRelExpr::Visit()
{
    string op1 , op2 , currentLabel; 
    //Visit children nodes
    if(rel)
        rel->Visit();

    shift->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(rel)
    {
        int tmp = Visualizer::GetNextUID();
        string s = (op == LT_OP) ? "<" : ((op == GT_OP) ? ">" : ((op == LE_OP) ? "<=" : ">="));
        char c= (op == LT_OP) ? '<' : ((op == GT_OP) ? '>' : ((op == LE_OP) ? '!' : '~'));
        AST::vis.addNode(tmp, s);

        AST::vis.addEdge(this->getUID(), rel->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        currentLabel =TAC_Generator::GetIVarName();
        
        switch(c)
        {
            case '<': 
              AST::tacGen.toTAC(TAC_Generator::LT , (void *) &op2 , (void *)&op1 , (void *)&currentLabel);   
              break;
            case '>':
              AST::tacGen.toTAC(TAC_Generator::GT , (void *) &op2 , (void *)&op1 , (void *)&currentLabel);   
              break;
            case '!':   /* <= */
              AST::tacGen.toTAC(TAC_Generator::LE , (void *) &op2 , (void *)&op1 , (void *)&currentLabel);   
              break;    
            case '~': /* >=*/
              AST::tacGen.toTAC(TAC_Generator::GE , (void *) &op2 , (void *)&op1 , (void *)&currentLabel);   
              break;
             
            
		}
        AST::tempStack.push_back( currentLabel);
        
    }

    AST::vis.addEdge(this->getUID(), shift->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstEqExpr  //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstEqExpr::AstEqExpr(AstRelExpr* r)
{
    this->rel = r;
    this->eq = NULL;
    this->op = NONE;
    this->type = r->type;

    this->setLabel("EqualityExpression");
}

AstEqExpr::AstEqExpr(AstEqExpr* e, Operator o, AstRelExpr* r)
{
    this->rel = r;
    this->eq = e;
    this->op = o;
    
    needsCast = !e->type->CheckType(r->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = e->type;
    }

    this->setLabel("EqualityExpression");
}

//Traversal
void AstEqExpr::Visit()
{
    //Visit children nodes
    string op1 , op2 , currentLabel; 
    if(eq)
        eq->Visit();
          
    rel->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(eq)
    {
        int tmp = Visualizer::GetNextUID();
        string s = (op == EQ_OP) ? "==" : "!=";
        char c = (op == EQ_OP) ? '=' : '!';
        AST::vis.addNode(tmp, s);
        if (eq)
           AST::vis.addEdge(this->getUID(), eq->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        currentLabel =TAC_Generator::GetIVarName();
        
        switch(c)
        {
            case '=': 
              AST::tacGen.toTAC(TAC_Generator::EQ , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;
           
            case '!':   /* != */
              AST::tacGen.toTAC(TAC_Generator::NE , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);   
              break;    
           
           
             
            
		}
        AST::tempStack.push_back( currentLabel);
    }

    AST::vis.addEdge(this->getUID(), rel->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstAndExpr  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstAndExpr::AstAndExpr(AstEqExpr* e)
{
    this->eq = e;
    this->a = NULL;
    this->type = e->type;

    this->setLabel("EqualityExpression");
}
AstAndExpr::AstAndExpr(AstAndExpr* a, AstEqExpr* e)
{
    this->eq = e;
    this->a = a;
    
    needsCast = !a->type->CheckType(e->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = a->type;
    }

    this->setLabel("EqualityExpression");
}

void AstAndExpr::Visit()
{
    
    string op1 , op2 , currentLabel; 
    //Visit children nodes
    if(a)
        a->Visit();

    eq->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(a)
    {
        int tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, "&");

        AST::vis.addEdge(this->getUID(), a->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        currentLabel =TAC_Generator::GetIVarName();
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        AST::tacGen.toTAC(TAC_Generator::AND , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);
        AST::tempStack.push_back( currentLabel);
    }

    AST::vis.addEdge(this->getUID(), eq->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstXORExpr  /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstXORExpr::AstXORExpr(AstAndExpr* a)
{
    this->a = a;
    this->x = NULL;
    this->type = a->type;

    this->setLabel("ExclusiveOrExpression");
}

AstXORExpr::AstXORExpr(AstXORExpr* x, AstAndExpr* a)
{
    this->a = a;
    this->x = x;
    
    needsCast = !x->type->CheckType(a->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = x->type;
    }

    this->setLabel("ExclusiveOrExpression");
}

void AstXORExpr::Visit()
{
    string op1 , op2 , currentLabel; 
    //Visit children nodes
    if(x)
        x->Visit();

    a->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(x)
    {
        int tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, "^");

        AST::vis.addEdge(this->getUID(), x->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        
        currentLabel =TAC_Generator::GetIVarName();
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        AST::tacGen.toTAC(TAC_Generator::XOR , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);
        AST::tempStack.push_back( currentLabel);
    
    }

    AST::vis.addEdge(this->getUID(), a->getUID());

    //Output 3AC
}


///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstORExpr   /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstORExpr::AstORExpr(AstXORExpr* x)
{
    this->x = x;
    this->o = NULL;
    this->type = x->type;
    
    this->setLabel("InclusiveOrExpression");
}

AstORExpr::AstORExpr(AstORExpr* o, AstXORExpr* x)
{
    this->x = x;
    this->o = o;
    
    needsCast = !o->type->CheckType(x->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = o->type;
    }
    
    this->setLabel("InclusiveOrExpression");
}

void AstORExpr::Visit()
{
    string op1 , op2 , currentLabel; 
    //Visit children nodes
    if(o)
        o->Visit();

    x->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(o)
    {
        int tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, "|");

        AST::vis.addEdge(this->getUID(), o->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        
        currentLabel =TAC_Generator::GetIVarName();
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        AST::tacGen.toTAC(TAC_Generator::XOR , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);
        AST::tempStack.push_back( currentLabel);
    }

    AST::vis.addEdge(this->getUID(), x->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstLogicAndExpr   ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstLogicAndExpr::AstLogicAndExpr(AstORExpr* o)
{
    this->o = o;
    this->a = NULL;
    this->type = o->type;

    this->setLabel("LogicalAndExpression");
}

AstLogicAndExpr::AstLogicAndExpr(AstLogicAndExpr* a, AstORExpr* o)
{
    this->o = o;
    this->a = a;
  /*  
    needsCast = !a->type->CheckType(o->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = a->type;
    }
*/
    this->setLabel("LogicalAndExpression");
}

void AstLogicAndExpr::Visit()
{
    
    string op1 , op2 , currentLabel; 
    //Visit children nodes
    if(a)
        a->Visit();

    o->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(a)
    {
        int tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, "&&");

        AST::vis.addEdge(this->getUID(), a->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        currentLabel =TAC_Generator::GetIVarName();
        AST::tacGen.toTAC(TAC_Generator::LAND , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);
        AST::tempStack.push_back( currentLabel);
    }

    AST::vis.addEdge(this->getUID(), o->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstLogicOrExpr   ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstLogicOrExpr::AstLogicOrExpr(AstLogicAndExpr* a)
{
    this->a = a;
    this->o = NULL;
    this->type = a->type;

    this->setLabel("LogicalOrExpression");
}

AstLogicOrExpr::AstLogicOrExpr(AstLogicOrExpr* o, AstLogicAndExpr* a)
{
    this->a = a;
    this->o = o;
    
    needsCast = !o->type->CheckType(a->type, isConv, convType);
    if(needsCast)
    {
        this->type = Type::GetResultingType(convType,true);
    }
    else
    {
        this->type = o->type;
    }

    this->setLabel("LogicalOrExpression");
}

void AstLogicOrExpr::Visit()
{
    string op1 , op2 , currentLabel; 
    //Visit children nodes
    if(o)
        o->Visit();

    a->Visit();

    //Output visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(o)
    {
        int tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, "||");

        AST::vis.addEdge(this->getUID(), o->getUID());
        AST::vis.addEdge(this->getUID(), tmp);
        
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        currentLabel =TAC_Generator::GetIVarName();
        AST::tacGen.toTAC(TAC_Generator::LOR , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);
        AST::tempStack.push_back( currentLabel);
    }

    AST::vis.addEdge(this->getUID(), a->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstConditionalExpr   ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstConditionalExpr::AstConditionalExpr(AstLogicOrExpr* o)
{
    this->o = o;
    this->e = NULL;
    this->ce = NULL;
    this->type = o->type;

    this->setLabel("ConditionalExpression");
}

AstConditionalExpr::AstConditionalExpr(AstLogicOrExpr* o, AstExpression* e, AstConditionalExpr* ce)
{
    this->o = o;
    this->e = e;
    this->ce = ce;
    
    needsCast = !e->type->CheckType(ce->type, isConv, convType);
    this->type = e->type;

    this->setLabel("ConditionalExpression");
}

void AstConditionalExpr::Visit()
{
    o->Visit();

    if(e)
    {
        e->Visit();
        ce->Visit();
    }

    AST::vis.addNode(this->getUID(), this->getLabel());
    AST::vis.addEdge(this->getUID(), o->getUID());

    if(e)
    {
        int tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, "?");
        AST::vis.addEdge(this->getUID(), tmp);

        AST::vis.addEdge(this->getUID(), e->getUID());

        tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, ":");
        AST::vis.addEdge(this->getUID(), tmp);

        AST::vis.addEdge(this->getUID(), ce->getUID());
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstConstantExpr   ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstConstantExpr::AstConstantExpr(AstConditionalExpr *e)
{
    this->expr = e;
    this->type = e->type;

    this->setLabel("ConstantExpression");
}

void AstConstantExpr::Visit()
{
    expr->Visit();

    AST::vis.addNode(this->getUID(), this->getLabel());
    AST::vis.addEdge(this->getUID(), expr->getUID());
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstAssignOp   ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstAssignOp::AstAssignOp(Operator o)
{
    this->op = o;
    this->setLabel("AssignmentOperator");
}

void AstAssignOp::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());
    
    switch(op)
    {
        case EQ:
            AST::vis.addDummyNode(this->getUID(), "=");
            break;
            
        case MUL_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "*=");
            break;
            
        case DIV_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "/=");
            break;
            
        case MOD_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "%=");
            break;
            
        case ADD_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "+=");
            break;
            
        case SUB_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "-=");
            break;
            
        case LEFT_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "<<=");
            break;
            
        case RIGHT_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), ">>=");
            break;
            
        case AND_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "&=");
            break;
            
        case XOR_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "^=");
            break;
            
        case OR_ASSIGN:
            AST::vis.addDummyNode(this->getUID(), "|=");
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstAssignExpr   /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstAssignExpr::AstAssignExpr(AstConditionalExpr* c)
{
    this->cond = c;
    this->uni = NULL;
    this->op = NULL;
    this->expr = NULL;

    this->setLabel("AssignmentExpression");
}

AstAssignExpr::AstAssignExpr(AstUnaryExpr* u, AstAssignOp* a, AstAssignExpr* e)
{
    this->cond = NULL;
    this->uni = u;
    this->op = a;
    this->expr = e;

    this->setLabel("AssignmentExpression");
}

void AstAssignExpr::Visit()
{
    
    string op1,op2,currentLabel,tempResult;
    bool lhsAddr=false;  
    if(cond)
    {
        cond->Visit();

        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), cond->getUID());

        //Output 3AC
    }
    else
    {
        
        if( uni->isPostfix())
        {
                   if(uni->GetPostfix()->isBracket())
                   {   
                          uni->GetPostfix()->SetAddress(true);
                          lhsAddr = true;  
                   }                        
        }   
        if ( uni->isPtrAss())
        {
           uni->lhs=true;
           lhsAddr = true;
        }  
        uni->Visit();
        op->Visit();
        expr->Visit();
        
        

        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), uni->getUID());
        AST::vis.addEdge(this->getUID(), op->getUID());
        AST::vis.addEdge(this->getUID(), expr->getUID());
        
        
        op1 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        op2 = AST::tempStack.back(); 
        AST::tempStack.pop_back();
        currentLabel =TAC_Generator::GetIVarName(); 
                 //Output 3AC
        switch(op->op)
        {
        case AstAssignOp::EQ:
            AST::tacGen.toTAC(lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV
, (void *) &op1 , (void *)&op2 );  
            AST::tempStack.push_back(op1);
            break;
            
        case AstAssignOp::MUL_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::MULT , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC(lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);  
            AST::tempStack.push_back(op1);
                       
            break;
            
        case AstAssignOp::DIV_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::DIV , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC(lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);    
            AST::tempStack.push_back(op1);
            
            break;
            
        case AstAssignOp::MOD_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::REM , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC(lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);    
            AST::tempStack.push_back(op1);
            break;
            
        case AstAssignOp::ADD_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::ADD , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC(lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);  
            AST::tempStack.push_back(op1);
            break;
            
        case AstAssignOp::SUB_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::SUB , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC(lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);   
            AST::tempStack.push_back(op1);
            break;
            
        case AstAssignOp::LEFT_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::SHIFTL , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC( lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);   
            AST::tempStack.push_back(op1);
            break;
            
        case AstAssignOp::RIGHT_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::SHIFTR , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC( lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);    
            AST::tempStack.push_back(op1);
            break;
            
        case AstAssignOp::AND_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::AND , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC(lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);   
            AST::tempStack.push_back(op1);
            break;
            
        case AstAssignOp::XOR_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::XOR , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC( lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);    
            AST::tempStack.push_back(op1);
            break;
            
            
        case AstAssignOp::OR_ASSIGN:
            AST::tacGen.toTAC(TAC_Generator::OR , (void *) &op1 , (void *)&op2 , (void *)&currentLabel);  
            AST::tacGen.toTAC( lhsAddr?TAC_Generator::ASSIGN:TAC_Generator::MOV,
 (void *) &op1 ,  (void *)&currentLabel);    
            AST::tempStack.push_back(op1);
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstExpression   /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstExpression::AstExpression(AstAssignExpr* a)
{
    this->ass = a;
    this->expr = NULL;
    this->setLabel("Expression");
}

AstExpression::AstExpression(AstExpression* e, AstAssignExpr* a)
{
    this->ass = a;
    this->expr = e;
    this->setLabel("Expression");
}

void AstExpression::Visit()
{
    
    AST::currentIndexVal  = 0 ; 
    if(expr)
        expr->Visit();

    ass->Visit();

    AST::vis.addNode(this->getUID(), this->getLabel());
    
    if(expr)
        AST::vis.addEdge(this->getUID(), expr->getUID());

    AST::vis.addEdge(this->getUID(), ass->getUID());
    
    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstReturn   /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
    
AstReturn::AstReturn(AstExpression *r)
{
    this->expr = r; 

    this->setLabel("ReturnStatement");
}

AstReturn::AstReturn()
{
    this->expr = NULL;

    this->setLabel("ReturnStatement");
}

void AstReturn::Visit()
{
    if(expr)
        expr->Visit();

    AST::vis.addNode(this->getUID(), this->getLabel());

    if(expr)
        AST::vis.addEdge(this->getUID(), expr->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstContinue   ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstContinue::AstContinue()
{
    this->setLabel("continue");
}

void AstContinue::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());
}	

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstBreak   //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstBreak::AstBreak()
{
    this->setLabel("break");
}

void AstBreak::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstGoto   ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstGoto::AstGoto()
{
    this->setLabel("goto");
}

void AstGoto::Visit()
{
    AST::vis.addNode(this->getUID(), this->getLabel());
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstJump   ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstJump::AstJump(AstGoto* g, AstID* i)
{
    this->go = g;
    this->id = i;
    this->cont = NULL;
    this->br = NULL;
    this->ret = NULL;
    this->expr = NULL;
    this->t = GOTO;

    this->setLabel("JumpStatement");
}

AstJump::AstJump(AstContinue* c)
{
    this->go = NULL;
    this->id = NULL;
    this->cont = c;
    this->br = NULL;
    this->ret = NULL;
    this->expr = NULL;
    this->t = CONTINUE;

    this->setLabel("JumpStatement");
}

AstJump::AstJump(AstBreak* b)
{
    this->go = NULL;
    this->id = NULL;
    this->cont = NULL;
    this->br = b;
    this->ret = NULL;
    this->expr = NULL;
    this->t = BREAK;

    this->setLabel("JumpStatement");
}

AstJump::AstJump(AstReturn* r)
{
    this->go = NULL;
    this->id = NULL;
    this->cont = NULL;
    this->br = NULL;
    this->ret = r;
    this->expr = NULL;
    this->t = EMPTY_RETURN;

    this->setLabel("JumpStatement");
}

AstJump::AstJump(AstReturn* r, AstExpression* e)
{
    this->go = NULL;
    this->id = NULL;
    this->cont = NULL;
    this->br = NULL;
    this->ret = r;
    this->expr = e;
    this->t = RETURN;

    this->setLabel("JumpStatement");
}

void AstJump::Visit()
{
    string evaluatedExpr;
    switch(t)
    {
        case GOTO:
            //Visit Children
            go->Visit();
            id->Visit();

            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), go->getUID());
            AST::vis.addEdge(this->getUID(), id->getUID());

            //Output 3AC
            break;

        case CONTINUE:
            //Visit Children
            cont->Visit();

            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), cont->getUID());

            //Output 3AC
            break;

        case BREAK:
            //Visit Children
            br->Visit();

            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), br->getUID());

            //Output 3AC
            break;

        case EMPTY_RETURN:
            //Visit Children
            ret->Visit();

            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ret->getUID());

            //Output 3AC
            break;

        case RETURN:
            //Visit Children
            ret->Visit();
            if(expr)
            {
             expr->Visit();
            } 
            evaluatedExpr = AST::tempStack.back();
            AST::tacGen.toTAC(TAC_Generator::RETURN,(void *)&evaluatedExpr); 
            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ret->getUID());
            AST::vis.addEdge(this->getUID(), expr->getUID());

            //Output 3AC
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstDoWhile   ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstDoWhile::AstDoWhile( AstStatement *s, AstExpression *t )
{
    this->statement = s;
    this->test = t; 

    this->setLabel("IterationStatement - DoWhile");
}

void AstDoWhile::Visit()
{
    
    string currentLabel ;
    string zero = "0"; 
    string loopLabel = AST::tacGen.GetLabelName();
    string exitLabel = AST::tacGen.GetLabelName();
    //Visit Children
    AST::tacGen.toTAC(TAC_Generator::LABEL,(void *)&loopLabel);
    statement->Visit();
    test->Visit();
    currentLabel = AST::tempStack.back();
    AST::tacGen.toTAC(TAC_Generator::BREQ,(void *)&currentLabel , (void *)&zero , (void *)&exitLabel);
    AST::tacGen.toTAC(TAC_Generator::BR,(void *)&loopLabel);
    AST::tacGen.toTAC(TAC_Generator::LABEL,(void *)&exitLabel); 
     
    //Visualization
    AST::vis.addNode(this->getUID(), this->getLabel());
    AST::vis.addEdge(this->getUID(), statement->getUID());
    AST::vis.addEdge(this->getUID(), test->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstWhile   //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstWhile::AstWhile( AstExpression *test, AstStatement *statement )
{
    this->statement = statement;
    this->test = test;

    this->setLabel("IterationStatement - While");
}

void AstWhile::Visit()
{
    
    string currentLabel ;
    string zero = "0"; 
    string loopLabel = AST::tacGen.GetLabelName();
    string exitLabel = AST::tacGen.GetLabelName();
    //Visit Children
    AST::tacGen.toTAC(TAC_Generator::LABEL,(void *)&loopLabel);
    test->Visit();
    currentLabel = AST::tempStack.back();
    AST::tacGen.toTAC(TAC_Generator::BREQ,(void *)&currentLabel , (void *)&zero , (void *)&exitLabel);
    statement->Visit();
    AST::tacGen.toTAC(TAC_Generator::BR,(void *)&loopLabel);
    AST::tacGen.toTAC(TAC_Generator::LABEL,(void *)&exitLabel); 
    
     
    //Visualization
    AST::vis.addNode(this->getUID(), this->getLabel());
    AST::vis.addEdge(this->getUID(), test->getUID());
    AST::vis.addEdge(this->getUID(), statement->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstFor   ////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstFor::AstFor(AstExpression *init , AstExpression *test , AstExpression *increment , AstStatement *statement)
{
    this->init = init ;
    this->test = test;
    this->increment = increment;
    this->statement = statement; 

    this->setLabel("ForStatement");
}

void AstFor::Visit()
{
    string currentLabel ;
    string zero = "0"; 
    string loopLabel = AST::tacGen.GetLabelName();
    string exitLabel = AST::tacGen.GetLabelName();
    //Visit the children
    if(init)
        init->Visit();
    AST::tacGen.toTAC(TAC_Generator::LABEL,(void *)&loopLabel);
    if(test)
        test->Visit();
    currentLabel = AST::tempStack.back();
    AST::tacGen.toTAC(TAC_Generator::BREQ,(void *)&currentLabel , (void *)&zero , (void *)&exitLabel);
    statement->Visit(); 
    if(increment)
        increment->Visit();
    AST::tacGen.toTAC(TAC_Generator::BR,(void *)&loopLabel);
    AST::tacGen.toTAC(TAC_Generator::LABEL,(void *)&exitLabel); 
    //Visualization
    AST::vis.addNode(this->getUID(), this->getLabel());

    if(init)
        AST::vis.addEdge(this->getUID(), init->getUID());

    if(test)
        AST::vis.addEdge(this->getUID(), test->getUID());

    if(increment)
        AST::vis.addEdge(this->getUID(), increment->getUID());

    AST::vis.addEdge(this->getUID(), statement->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstIteration   //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstIteration::AstIteration(AstDoWhile* d)
{
    this->dwl = d;
    this->wl = NULL;
    this->fr = NULL;
    this->t = DOWHILE;

    this->setLabel("IterationStatement");
}

AstIteration::AstIteration(AstWhile* w)
{
    this->dwl = NULL;
    this->wl = w;
    this->fr = NULL;
    this->t = WHILE;

    this->setLabel("IterationStatement");
}

AstIteration::AstIteration(AstFor* f)
{
    this->dwl = NULL;
    this->wl = NULL;
    this->fr = f;
    this->t = FOR;

    this->setLabel("IterationStatement");
}

void AstIteration::Visit()
{
    switch(t)
    {
        case DOWHILE:
            //Visit Children
            dwl->Visit();

            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), dwl->getUID());

            //Output 3AC
            break;

        case WHILE:
            //Visit Children
            wl->Visit();

            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), wl->getUID());

            //Output 3AC
            break;

        case FOR:
            //Visit Children
            fr->Visit();

            //Visualization
            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), fr->getUID());

            //Output 3AC
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstSwitch   /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstSwitch::AstSwitch(AstExpression* e, AstStatement* s)
{
    this->expr = e;
    this->stmt = s;
    this->setLabel("Switch");
}

void AstSwitch::Visit()
{
    expr->Visit();
    stmt->Visit();

    AST::vis.addNode(this->getUID(), this->getLabel());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstIfElse   /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
 
AstIfElse::AstIfElse( AstExpression *test , AstStatement *statement , AstStatement *elseStatement )
{
    this->test = test;
    this->statement = statement;
    this->elseStatement = elseStatement;

    this->setLabel("IfStatement");
}

void AstIfElse::Visit()
{
    
    string skipLabel  = TAC_Generator::GetLabelName();
    string skipElseLabel  = TAC_Generator::GetLabelName();
    string zero = "0" ; 
    string currentLabel;
    
    
       
    
    
    test->Visit();
    
    currentLabel = AST::tempStack.back();
    AST::tacGen.toTAC(TAC_Generator::BREQ,(void *)&currentLabel,(void *)&zero,(void *)&skipLabel);
    
    
    statement->Visit();
      
    if(elseStatement)
    {
       AST::tacGen.toTAC(TAC_Generator::BR,(void *)&skipElseLabel);                 
    }         
    AST::tacGen.toTAC(TAC_Generator::LABEL , (void *)&skipLabel ); 
    if(elseStatement)
    {
        elseStatement->Visit();
        AST::tacGen.toTAC(TAC_Generator::LABEL , (void *)&skipElseLabel ); 

    }
    AST::vis.addNode(this->getUID(), this->getLabel());
    AST::vis.addEdge(this->getUID(), test->getUID());
    AST::vis.addEdge(this->getUID(), statement->getUID());

    if(elseStatement)
        AST::vis.addEdge(this->getUID(), elseStatement->getUID());

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstSelection   //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstSelection::AstSelection(AstSwitch* s)
{
    this->swtch = s;
    this->ifelse = NULL;
    this->t = SWITCH;

    this->setLabel("SelectionStatement");
}

AstSelection::AstSelection(AstIfElse* ie)
{
    this->swtch = NULL;
    this->ifelse = ie;
    this->t = IFELSE;

    this->setLabel("SelectionStatement");
}

void AstSelection::Visit()
{
    switch(t)
    {
        case SWITCH:
            swtch->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), swtch->getUID());

            //Output 3AC
            break;

        case IFELSE:
            ifelse->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), ifelse->getUID());

            //Output 3AC
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstStatementList   //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstStatementList::AstStatementList(AstStatement *s)
{
    this->stmt = s;
    this->list = NULL;

    this->setLabel("StatementList");
}

AstStatementList::AstStatementList(AstStatementList* l, AstStatement *s)
{
    this->stmt = s;
    this->list = l;

    this->setLabel("StatementList");
}

void AstStatementList::Visit()
{
    if(list)
        list->Visit();

    stmt->Visit();

    AST::vis.addNode(this->getUID(), this->getLabel());
    
    if(list)
        AST::vis.addEdge(this->getUID(), list->getUID());

    AST::vis.addEdge(this->getUID(), stmt->getUID());
    
    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstCompoundStmt   ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstCompoundStmt::AstCompoundStmt(AstDeclarationList* d, AstStatementList* s)
{
    this->declList = d;
    this->stmtList = s;
    this->setLabel("CompoundStatement");
}

void AstCompoundStmt::Visit()
{
    
    
    if(declList)
        declList->Visit();

    if(stmtList)
        stmtList->Visit();

    AST::vis.addNode(this->getUID(), this->getLabel());

    if(declList)
        AST::vis.addEdge(this->getUID(), declList->getUID());

    if(stmtList)
        AST::vis.addEdge(this->getUID(), stmtList->getUID());

    

    //Output 3AC
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstExprStmt   ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstExprStmt::AstExprStmt(AstExpression* e)
{
    this->expr = e;

    this->setLabel("ExpressionStatement");
}

void AstExprStmt::Visit()
{
    if(expr)
    {
        expr->Visit();
 
        AST::vis.addNode(this->getUID(), this->getLabel());
        AST::vis.addEdge(this->getUID(), expr->getUID());

        //Output 3AC
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstLabeledStmt   ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstLabeledStmt::AstLabeledStmt(AstID* i, AstStatement* s)
{
    this->id = i;
    this->stmt = s;
    this->constExpr = NULL;
    this->t = NO_CASE;

    this->setLabel("LabeledStatement");
}

AstLabeledStmt::AstLabeledStmt(AstConstantExpr* c, AstStatement* s)
{
    this->id = NULL;
    this->stmt = s;
    this->constExpr = c;
    this->t = CASE;

    this->setLabel("LabeledStatement");
}

AstLabeledStmt::AstLabeledStmt(AstStatement* s)
{
    this->id = NULL;
    this->stmt = s;
    this->constExpr = NULL;
    this->t = DEFAULT;

    this->setLabel("LabeledStatement");
}

void AstLabeledStmt::Visit()
{
    switch(t)
    {
        case NO_CASE:
            id->Visit();
            stmt->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), id->getUID());
            AST::vis.addEdge(this->getUID(), stmt->getUID());

            //Output 3AC
            break;

        case CASE:
            constExpr->Visit();
            stmt->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), constExpr->getUID());
            AST::vis.addEdge(this->getUID(), stmt->getUID());

            //Output 3AC
            break;

        case DEFAULT:
            stmt->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), stmt->getUID());

            //Output 3AC
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BEGIN: AstStatement   ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

AstStatement::AstStatement(AstLabeledStmt* l)
{
    this->lbl = l;
    this->cmp = NULL;
    this->expr = NULL;
    this->slct = NULL;
    this->iter = NULL;
    this->jump = NULL;
    this->t = LABELED;

    this->setLabel("Statement");
}

AstStatement::AstStatement(AstCompoundStmt* c)
{
    this->lbl = NULL;
    this->cmp = c;
    this->expr = NULL;
    this->slct = NULL;
    this->iter = NULL;
    this->jump = NULL;
    this->t = COMPOUND;

    this->setLabel("Statement");
}

AstStatement::AstStatement(AstExprStmt* e)
{
    this->lbl = NULL;
    this->cmp = NULL;
    this->expr = e;
    this->slct = NULL;
    this->iter = NULL;
    this->jump = NULL;
    this->t = EXPR;

    this->setLabel("Statement");
}

AstStatement::AstStatement(AstSelection* s)
{
    this->lbl = NULL;
    this->cmp = NULL;
    this->expr = NULL;
    this->slct = s;
    this->iter = NULL;
    this->jump = NULL;
    this->t = SELECT;

    this->setLabel("Statement");
}

AstStatement::AstStatement(AstIteration* i)
{
    this->lbl = NULL;
    this->cmp = NULL;
    this->expr = NULL;
    this->slct = NULL;
    this->iter = i;
    this->jump = NULL;
    this->t = ITER;

    this->setLabel("Statement");
}

AstStatement::AstStatement(AstJump* j)
{
    this->lbl = NULL;
    this->cmp = NULL;
    this->expr = NULL;
    this->slct = NULL;
    this->iter = NULL;
    this->jump = j;
    this->t = JUMP;

    this->setLabel("Statement");
}

void AstStatement::Visit()
{
    switch(t)
    {
        case LABELED:
            lbl->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), lbl->getUID());

            //Output 3AC
            break;

        case COMPOUND:
            cmp->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), cmp->getUID());

            //Output 3AC
            break;

        case EXPR:
            expr->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), expr->getUID());

            //Output 3AC
            break;

        case SELECT:
            slct->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), slct->getUID());

            //Output 3AC
            break;

        case ITER:
            iter->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), iter->getUID());

            //Output 3AC
            break;

        case JUMP:
            jump->Visit();

            AST::vis.addNode(this->getUID(), this->getLabel());
            AST::vis.addEdge(this->getUID(), jump->getUID());

            //Output 3AC
            break;
    }
}
void VisVist(int total , ... )
{
   va_list  args_list;
   AST *currentAst; 
   AST *parentAst;  
   int count = 0;
   va_start(args_list,total);
   parentAst = va_arg(args_list,AST*); 
   AST::vis.addNode(parentAst->getUID(),parentAst->getLabel());

   for( count = 0 ; count < total ; count++)
   {
      currentAst = va_arg(args_list,AST*);
      if ( currentAst != NULL )
      {
          currentAst->Visit();  
          AST::vis.addEdge(parentAst->getUID(), currentAst->getUID());

      } 
   }
   va_end(args_list);

} 
void VisAddIntNode ( AST *parentAst , int number )
{

    
    int tempUID =  Visualizer::GetNextUID();
    AST::vis.addNode(tempUID,std::to_string(number)); 
    AST::vis.addEdge(parentAst->getUID(), tempUID);

}

void VisAddStringNode(  AST *parentAst , string &node)
{

    int tempUID =  Visualizer::GetNextUID();
    AST::vis.addNode(tempUID,node); 
    AST::vis.addEdge(parentAst->getUID(),tempUID);


}

void VisVistFmt(char *fmt , ... )
{
   

   va_list  args_list;
   AST *currentAst; 
   AST *parentAst;  
   int count = 0;
   char *fmt_ptr = fmt; 
   int number;
   int tempUID;
   char *c_string; 
   std::string curString;
   va_start(args_list,fmt);
   parentAst = va_arg(args_list,AST*); 
   AST::vis.addNode(parentAst->getUID(),parentAst->getLabel());
   while( fmt_ptr !=NULL)
   {
       switch(*fmt_ptr)
       {
             case 'i':
                     
                     number = va_arg(args_list,int);
                     tempUID =  Visualizer::GetNextUID();
                     AST::vis.addNode(tempUID,std::to_string(number)); 
                     AST::vis.addEdge(parentAst->getUID(), tempUID);
             
                     break;
            case 'a':            
                     currentAst = va_arg(args_list,AST*);
                     if ( currentAst != NULL )
                     {
                        currentAst->Visit();  
                        AST::vis.addEdge(parentAst->getUID(), currentAst->getUID());
                     }
                     break; 
            case 's':
                    c_string = va_arg(args_list,char *);
                    tempUID =  Visualizer::GetNextUID();
                    AST::vis.addNode(tempUID,c_string); 
                    AST::vis.addEdge(parentAst->getUID(),tempUID);

                    break;    

       } 

       fmt_ptr++;
      
   }
   va_end(args_list);

} 











