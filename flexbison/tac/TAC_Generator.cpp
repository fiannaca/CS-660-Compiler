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

void TAC_Generator::toTAC(TwoOpInstructions t, void* op1, void* op2, string c)
{
    if(c.size() > 0)
        WriteComment(c);
    
    stringstream ss;

    ss.setf(flags);
    ss.fill(' ');

    switch(t)
    {
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
                //TODO - associate string op1 with label op2
                string* ptr1 = (string*)op1;
                string* ptr2 = (string*)op2;

                ss << setw(width) << "STRING" 
                   << setw(width) << *ptr1 
                   << setw(width) << *ptr2;    
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

        case COMMENT:
            {
                string* ptr = (string*)op;

                ss << commentStart << *ptr << commentEnd;
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
    //fout << endl;
}
        
void TAC_Generator::Emit(string codeToEmit)
{
    buffer.push_back(codeToEmit);
    //fout << codeToEmit << endl;
    //fout.flush();    
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
                            
    ss << setw(8) << lCount;
                                    
    lCount++;
                                            
    return ss.str();
}

string TAC_Generator::GetIVarName()
{
    stringstream ss;
            
    ss << "I";
                    
    ss.fill('0');
                            
    ss << setw(8) << iCount;
                                    
    iCount++;
                                            
    return ss.str();
}

string TAC_Generator::GetFVarName()
{
    stringstream ss;
            
    ss << "F";
                    
    ss.fill('0');
                            
    ss << setw(8) << fCount;
                                    
    fCount++;
                                            
    return ss.str();
}
















