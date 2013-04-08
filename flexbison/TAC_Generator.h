#ifndef TAC_GENERATOR_H_
#define TAC_GENERATOR_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class TAC_Generator
{
    public:
        enum ThreeOpInstructions
        {
            ADD,
            SUB,
            MULT,
            DIV,
            EQ,
            GT,
            LT,
            GE,
            LE,
            NE,
            ASSIGN,
            BREQ,
            BRGT,
            BRLT,
            BRGE,
            BRLE,
            BRNE,
            PROCENTRY,
            BOUND
        };

        enum TwoOpInstructions
        {
            NEG,
            NOT,
            ADDR,
            GLOBAL,
            STRING
        };

        enum OneOpInstructions
        {
            LABEL,
            BR,
            ARGS,
            REFOUT,
            VALOUT,
            CALL,
            COMMENT
        };

        enum NoOpInstructions
        {
            HALT,
            ENDPROC,
            RETURN,
        };

        //Constructor opens the 3AC file and the destructor closes it
        TAC_Generator(const string &fileName);
        TAC_Generator();
        ~TAC_Generator();

        //The toTAC overloads take in a flag to indicate the type of three 
        // address code statement, and a series of parameters required by
        // the particular statement, and generate a formatted 3AC statement
        void toTAC(ThreeOpInstructions t, void*, void*, void* );
        void toTAC(TwoOpInstructions t, void*, void* );
        void toTAC(OneOpInstructions t, void* );
        void toTAC(NoOpInstructions t);

        //These functions handle output of comments into the 3AC file
        void SetCommentStart(string commentStart);
        void SetCommentEnd(string commentEnd);
        void WriteComment(string &comment);

        //These functions handle the pretty printing of the 3AC
        void SetFile(const string &filename);
        void SetColumnWidth(int w);
        void SetFormatFlags(ios_base::fmtflags ff);
            	
        //These functions generate and track labels for labels, ints, and floats
        static string GetLabelName();
        static string GetIVarName();
        static string GetFVarName();

    private:
        //Called by the toTAC overloads to output the formatted three address code to a file
        void Emit(string CodeToEmit);

        ofstream fout;
        string commentStart; 
        string commentEnd;

        int width;

        ios_base::fmtflags flags;
            	
        static int lCount;
        static int iCount;
        static int fCount;
};

#endif // ! TAC_GENERATOR_H_





















