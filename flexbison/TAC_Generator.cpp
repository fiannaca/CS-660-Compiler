#include "TAC_Generator.h"

int TAC_Generator::lCount = 0;
int TAC_Generator::iCount = 0;
int TAC_Generator::fCount = 0;

TAC_Generator::TAC_Generator(const string &fileName)
    : width(12)
{
    //Default to MIPS comment style
    commentStart = "#";
    commentEnd = "" ;

    fout.open(fileName.c_str());
    fout.clear(); 
}

TAC_Generator::TAC_Generator()
    : width(12)
{
    //Default to MIPS comment style
    commentStart = "#";
    commentEnd = "" ;
}

TAC_Generator::~TAC_Generator()
{
    fout.close();
}

void TAC_Generator::toTAC(ThreeOpInstructions t, void* op1, void* op2, void* op3 )
{
    stringstream ss;

    ss.setf(flags);
    ss.fill(' ');

    switch(t)
    {
        case ADD:
            {
                //TODO - add
            }
            break;

        case SUB:
            {
                //TODO - subtract
            }
            break;

        case MULT:
            {
                //TODO - multiply
            }
            break;

        case DIV:
            {
                //TODO - divide
            }
            break;

        case EQ:
            {
                //TODO - equal
            }
            break;

        case GT:
            {
                //TODO - greater than
            }
            break;

        case LT:
            {
                //TODO - less than
            }
            break;

        case GE:
            {
                //TODO - greater or equal
            }
            break;

        case LE:
            {
                //TODO - less or equal
            }
            break;

        case NE:
            {
                //TODO - not equal
            }
            break;

        case ASSIGN:
            {
                //TODO - assignment
            }
            break;

        case BREQ:
            {
                //TODO - branch equal
            }
            break;

        case BRGT:
            {
                //TODO - branch greater than
            }
            break;

        case BRLT:
            {
                //TODO - branch less than
            }
            break;

        case BRGE:
            {
                //TODO - branch greater than or equal
            }
            break;

        case BRLE:
            {
                //TODO - branch less than or equal
            }
            break;

        case BRNE:
            {
                //TODO - branch not equal
            }
            break;

        case PROCENTRY:
            {
                //TODO - begins the definition of a function
            }
            break;

        case BOUND:
            {
                //TODO - implements runtime bounds checking
            }
            break;
    }

    Emit(ss.str());
}

void TAC_Generator::toTAC(TwoOpInstructions t, void* op1, void* op2 )
{
    stringstream ss;

    ss.setf(flags);
    ss.fill(' ');

    switch(t)
    {
        case NEG:
            {
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "NEG" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;
            }
            break;

        case NOT:
            {
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "NOT" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;
            }
            break;

        case ADDR:
            {
                //TODO - op2 gets the address of op1
            }
            break;

        case GLOBAL:
            {
                //TODO - declare op1 a global of size op2
            }
            break;

        case STRING:
            {
                //TODO - associate string op1 with label op2
            }
            break;

    }

    Emit(ss.str());
}

void TAC_Generator::toTAC(OneOpInstructions t, void* op)
{
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

        case COMMENT:
            {
                string* ptr = (string*)op;

                ss << commentStart << *ptr << commentEnd;
            }
            break;

    }

    Emit(ss.str());
}

void TAC_Generator::toTAC(NoOpInstructions t)
{
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

void TAC_Generator::WriteComment(string &comment)
{
    string commentString = commentStart + comment + commentEnd;
    fout << commentString << endl ;
    fout.flush(); 
}

void TAC_Generator::Emit(string codeToEmit)
{
    fout << codeToEmit << endl;
    fout.flush();    
}

void TAC_Generator::SetFile(const string &filename)
{
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

string TAC_Generator::GetLabelName()
{
    stringstream ss;
            
    ss << "L";
                    
    ss.fill('0');
                            
    ss << setw(8) << lCount;
                                    
    lCount++;
                                            
    return ss.str();
}

string TAC_Generator::GetIVarName()
{
    stringstream ss;
            
    ss << "I";
                    
    ss.fill('0');
                            
    ss << setw(8) << lCount;
                                    
    iCount++;
                                            
    return ss.str();
}

string TAC_Generator::GetFVarName()
{
    stringstream ss;
            
    ss << "F";
                    
    ss.fill('0');
                            
    ss << setw(8) << lCount;
                                    
    fCount++;
                                            
    return ss.str();
}
















