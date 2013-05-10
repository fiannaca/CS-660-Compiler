
#include "TAC_Generator.h"

int TAC_Generator::lCount = 0;
int TAC_Generator::iCount = 0;
int TAC_Generator::fCount = 0;

TAC_Generator::TAC_Generator(const string &fileName)
    : width(12)
    , blankBeforeComment(false)
{
    //Default to MIPS comment style
    commentStart = "#";
    commentEnd = "" ;
    
    CurrentLabel = "";

    fout.open(fileName.c_str());
    fout.clear();
}

TAC_Generator::TAC_Generator()
    : width(12)
    , blankBeforeComment(false)
{
    //Default to MIPS comment style
    commentStart = "#";
    commentEnd = "" ;
    
    CurrentLabel = "";

    fout.open("TAC.out");
    fout.clear();
}

TAC_Generator::~TAC_Generator()
{
    for(auto it = buffer.begin(); it != buffer.end(); ++it)
        fout << *it << endl;
    
    fout.close();
}

void TAC_Generator::toTAC(ThreeOpInstructions t, void* op1, void* op2, void* op3, string c )
{
    if(c.size() > 0)
        WriteComment(c);
    
    stringstream ss;

    ss.setf(flags);
    ss.fill(' ');

    switch(t)
    {
        case ADD:
            {
                //TODO - adds op1 and op2 and places the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "ADD"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break;

        case SUB:
            {
                //TODO - subtracts op1 and op2 and places the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "SUB"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break;

        case MULT:
            {
                //TODO - multiplys op1 and op2 and places the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "MULT"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break;

        case DIV:
            {
                //TODO - divides op1 and op2 and places the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "DIV"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break;
        case SHIFTL:
            {
                //TODO - shifts op1 by op2 left  and places the result in op3 
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "SHIFTL"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break;
        case SHIFTR:
            {
                //TODO - shifts op1 by op2 right and places the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "SHIFTR"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break;
        case AND:
            {
                //TODO - bitwise ands op1 and op2 and places the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "AND"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break; 
        case LAND:
            {
                //TODO - logical ands the op1 and op2 and places the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "LAND"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break; 
        case XOR:
            {
                //TODO - bitwise xor op1 and op2 and place the result in op3 
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "XOR"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break; 
        case OR:
            {
                //TODO - bitwise or op1 and op2 and place the result in op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "OR"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break; 
        case LOR:
            {
                //TODO - logical or op1 and op2 and place the result in op3 
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "LOR"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;
            }
            break;              
        case EQ:
            {
                //TODO - if op1 and op2 are equal, then op3 is 1, else op3 is 0
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "EQ"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;                
            }
            break;

        case GT:
            {
                //TODO - if op1 is greater than op2, then op3 is 1, else op3 is 0
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "GT"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;   
            }
            break;

        case LT:
            {
                //TODO - if op1 is less than op2, then op3 is 1, else op3 is 0
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "LT"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;  
            }
            break;

        case GE:
            {
                //TODO - if op1 is greater than or equal to op2, then op3 is 1, else op3 is 0
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "GE"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;  
            }
            break;
        case REM:
            {
                //TODO -
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "REM"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3;  
            }
            break;
        case LE:
            {
                //TODO - if op1 is less than or equal to op2, then op3 is 1, else op3 is 0
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "LE"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case NE:
            {
                //TODO - if op1 is not equal to op2, then op3 is 1, else op3 is 0
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "NE"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case BREQ:
            {
                //TODO - if op1 is equal to op2, then branch to op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "BREQ"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case BRGT:
            {
                //TODO - if op1 is greater than op2, then branch to op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "BREQ"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case BRLT:
            {
                //TODO - if op1 is less than op2, then branch to op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "BRLT"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case BRGE:
            {
                //TODO - if op1 is greater than or equal to op2, then branch to op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "BRGE"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case BRLE:
            {
                //TODO - if op1 is less than or equal to op2, then branch to op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "BRLE"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case BRNE:
            {
                //TODO - if op1 is not equal to op2, then branch to op3
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                string* ptr3 = (string*)op3;
                
                ss << setw(width) << "BRNE"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
            }
            break;

        case BOUND:
            {
                //TODO - implements runtime bounds checking
            }
            break;
	case ALLOC:
	    {
		string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;
                int* ptr3 = (int*)op3;
		ss << setw(width) << "ALLOC"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2
                   << setw(width) << *ptr3; 
		
	    }
    }

    Emit(ss.str());
}

void TAC_Generator::toTAC(TwoOpInstructions t, void* op1, void* op2, string c)
{
    if(c.size() > 0)
        WriteComment(c);
    
    stringstream ss;

    ss.setf(flags);
    ss.fill(' ');

    switch(t)
    {



        case MOV:
            {
                //TODO
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "MOV" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;
            }
            break;


        case NEG:
            {
                //op2 gets negative op1
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "NEG" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;
            }
            break;

        case NOT:
            {
                //op2 gets 1 if op1 is 0, op2 gets 0 otherwise
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "NOT" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;
            }
            break;

        case ASSIGN:
            {
                //TODO - assignment
                string* ptr1 = (string*)op1; //The register to write to memory
                string* ptr2 = (string *)op2; //The offset in memory to write the value to
                
                ss << setw(width) << "ASSIGN"
                   << setw(width) << *ptr1
                   << setw(width) << *ptr2;
            }
            break;

        case ADDR:
            {
                //TODO - op2 gets the address of op1
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "ADDR" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;                
            }
            break;

        case GLOBAL:
            {
                //TODO - declare op1 a global of size op2
                string* ptr1 = (string*)op1;
                int val2 = (long)op2;

                ss << setw(width) << "GLOBAL" 
                   << setw(width) << *ptr1 
                   << setw(width) << val2;
            }
            break;

        case STRING:
            {
                //TODO - associate string op2 with label op1
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "STRING" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;    
            }
            break;
            
        case IMMEDIATE_I:
            {
                //Load the value into the register
                string* ptr1 = (string*)op1;
                int val = (long)op2;
                
                ss << setw(width) << "IMMEDIATE_I"
                   << setw(width) << *ptr1
                   << setw(width) << val;
            }
            break;
            
        case IMMEDIATE_F:
            {
                //Load the value into the register
                string* ptr1 = (string*)op1;
                double val = *(double*)op2;
                
                ss << setw(width) << "IMMEDIATE_F"
                   << setw(width) << *ptr1
                   << setw(width) << val;
            }
            break;
    }

    Emit(ss.str());
}

void TAC_Generator::toTAC(OneOpInstructions t, void* op, string c)
{
    if(c.size() > 0)
        WriteComment(c);
    
    stringstream ss;

    ss.setf(flags);
    ss.fill(' ');

    switch(t)
    {
        case LABEL:
            {
                string* ptr = (string*)op;

                ss << setw(width) << "LABEL" 
                   << setw(width) << *ptr;
            }
            break;

        case BR:
            {
                string* ptr = (string*)op;

                ss << setw(width) << "BR"  
                   << setw(width) << *ptr;
            }
            break;

        case ARGS:
            {
                int val = (long)op;

                ss << setw(width) << "ARGS"  
                   << setw(width) << val;
            }
            break;

        case REFOUT:
            {
                string* ptr = (string*)op;

                ss << setw(width) << "REFOUT"  
                   << setw(width) << *ptr;
            }
            break;

        case VALOUT:
            {
                string* ptr = (string*)op;

                ss << setw(width) << "VALOUT"  
                   << setw(width) << *ptr;
            }
            break;

        case CALL:
            {
                string* ptr = (string*)op;

                ss << setw(width) << "CALL"  
                   << setw(width) << *ptr;
            }
            break;

        case PROCENTRY:
            {
                //TODO - begins the definition of a function
                string* ptr = (string*)op;

                ss << setw(width) << "PROCENTRY"  
                   << setw(width) << *ptr;
            }
            break;
            
        case COMMENT:
            {
                string* ptr = (string*)op;

                ss << commentStart << *ptr << commentEnd;
            }
            
        case BEGINFRAME:
            {   
                int val = (long)op;
                ss << setw(width) << "BEGINFRAME"
                   << setw(width) << val;
            }
            break;

    }

    Emit(ss.str());
}

void TAC_Generator::toTAC(NoOpInstructions t, string c)
{
    if(c.size() > 0)
        WriteComment(c);
    
    stringstream ss;

    ss.setf(flags);
    ss.fill(' ');

    switch(t)
    {
        case HALT:
            ss << setw(width) << "HALT";
            break;

        case ENDPROC:
            ss << setw(width) << "ENDPROC";
            break;

        case RETURN:
            ss << setw(width) << "RETURN";
            break;
            
        case ENDFRAME:
            ss << setw(width) << "ENDFRAME";
            break;
    }

    Emit(ss.str());
}

void TAC_Generator::SetCommentStart(string commentStart)
{
    this->commentStart = commentStart;
}

void TAC_Generator::SetCommentEnd(string commentEnd)
{
    this->commentEnd = commentEnd; 
}

void TAC_Generator::WriteComment(string comment)
{
    if(blankBeforeComment)
        Blank();
        
    string commentString = commentStart + comment + commentEnd;
    
    Emit(commentString);
}

void TAC_Generator::Blank()
{
    buffer.push_back("");
}

void TAC_Generator::Emit(string codeToEmit)
{
    buffer.push_back(codeToEmit);   
}

void TAC_Generator::SetFile(const string &filename)
{
    if(fout.is_open())
        fout.close();
        
    fout.open(filename.c_str());
    fout.clear(); 
}

void TAC_Generator::SetColumnWidth(int w)
{
    width = w;
}

void TAC_Generator::SetFormatFlags(ios_base::fmtflags ff)
{
    flags = ff;
}

void TAC_Generator::SetBlankBeforeComments(bool flag)
{
    blankBeforeComment = flag;
}
        
string TAC_Generator::GetLabelName()
{
    stringstream ss;
            
    ss << "L";
                    
    ss.fill('0');
                            
    ss << setw(4) << lCount;
                                    
    lCount++;
                                            
    return ss.str();
}

string TAC_Generator::GetIVarName()
{
    stringstream ss;
            
    ss << "I";
                    
    ss.fill('0');
                            
    ss << setw(4) << iCount;
                                    
    iCount++;
                                            
    return ss.str();
}

string TAC_Generator::GetFVarName()
{
    stringstream ss;
            
    ss << "F";
                    
    ss.fill('0');
                            
    ss << setw(4) << fCount;
                                    
    fCount++;
                                            
    return ss.str();
}

void TAC_Generator::Fetch(string varName , SymTab *symbolTable , string targetTemp)
{
    /**
         TODO Add code to fetch the symbole for the symbol table 
          
         // Assume all variables are GLOBAL for the time being 
    */
     if ( symbolTable->IsGlobal(varName))        
        toTAC(MOV  , (void *) &varName ,(void*) &targetTemp); 



} 

void GenGlobals (  SymTab &symTab ,  TAC_Generator &tacGen)
{
     list<SymbolInfo> globalItems; 
     string symName;
     long symSize;
     globalItems =  symTab.GetGlobals();	
	 list<SymbolInfo>::iterator items = globalItems.begin();
	 while ( items != globalItems.end())
	 {
	   
	       
	       symName = items->symbol_name;
	       symSize = items->symbolType->GetSize();
	       cout<< " \n Name = " << symName << " Size = " << symSize;
	       tacGen.toTAC(TAC_Generator::GLOBAL,(void *)&symName ,(void *)symSize );
	       items++;
	 }
	
}














