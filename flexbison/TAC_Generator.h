#ifndef TAC_GENERATOR_H_
#define TAC_GENERATOR_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <list>

#include "SymTab.h" 
using namespace std;




/**
 * A class for generating three address code. The TAC_Generator class is 
 * responsible for generating well-formatted three address code (3AC or TAC). 
 * The generator stores all generated 3AC in a STL list of strings during 
 * runtime, and outputs the 3AC to a file when the destructor is called. This
 * allows for the 3AC to be manipulated prior to output (i.e. putting all 
 * function decls at the top of the 3AC).
 */
class TAC_Generator
{
    public:
        /**
         * Enumeration of 3 operand instructions.
         * These enum values serve as flags to the toTAC functions in order to 
         * indicate which 3AC statement should be generated, and what the types
         * of the void * parameters to the toTAC functions are.
         */
        enum ThreeOpInstructions
        {
            ADD, /**< Add the value of two temps */
            SUB, /**< Subtract the value of two temps */
            MULT, /**< Multiply the value of two temps */
            DIV, /**< Divide the value of two temps */
            REM , /** < Reminder of the value of two temps */
            SHIFTL ,  /**< left shift the value of two temps */
            SHIFTR ,  /**< right shift the value of two temps */
            AND , /**< biwise and the value of two temps */
            XOR , /**< biwise xor  the value of two temps */
            OR  ,  /**< biwise OR  the value of two temps */
            LOR , /**< logical OR  the value of two temps */
            LAND , /**< logical OR  the value of two temps */
            EQ, /**< Set op3 to 1 is op1 == op2, or 0 otherwise */
            GT, /**< Set op3 to 1 is op1 > op2, or 0 otherwise */
            LT, /**< Set op3 to 1 is op1 < op2, or 0 otherwise */
            GE, /**< Set op3 to 1 is op1 >= op2, or 0 otherwise */
            LE, /**< Set op3 to 1 is op1 <= op2, or 0 otherwise */
            NE, /**< Set op3 to 1 is op1 != op2, or 0 otherwise */
            BREQ, /**< If(op1 == op2) goto op3 */
            BRGT, /**< If(op1 > op2) goto op3 */
            BRLT, /**< If(op1 < op2) goto op3 */
            BRGE, /**< If(op1 >= op2) goto op3 */
            BRLE, /**< If(op1 <= op2) goto op3 */
            BRNE, /**< If(op1 != op2) goto op3 */
            BOUND, /**< Checks the bounds of an array access */
	    ALLOC, /** Allocate on procedure stack */
	    PARAM /** Denotes a parameter **/ 
	   
        };

        /**
         * Enum of 2 operand instructions.
         * These enum values serve as flags to the toTAC functions in order to 
         * indicate which 3AC statement should be generated, and what the types
         * of the void * parameters to the toTAC functions are.
         */
        enum TwoOpInstructions
        {
            NEG, /**< op2 = -(op1) */
            NOT, /**< Set op2 to 1 if op1 == 0, or 0 otherwise */
            ASSIGN, /**< Assign the value of op1 to op2 */
            ADDR, /**< Assign the address of op1 to op2 */
            GLOBAL, /**< Declare op1 as a global of size op2 */
            STRING, /**< Associate string op1 with label op2 */
            IMMEDIATE_I, /**< Load an integer into a register */
            IMMEDIATE_F, /**< Load a float into a register */
            TILDE , /** does op2 = ~(op1) */
            MOV  /** does op2 = op21 */ 
        };

        /**
         * Enum of 1 operand instructions.
         * These enum values serve as flags to the toTAC functions in order to 
         * indicate which 3AC statement should be generated, and what the types
         * of the void * parameters to the toTAC functions are.
         */
        enum OneOpInstructions
        {
            LABEL, /**< Generate a label */
            BR, /**< Branch to a label */
            ARGS, /**< Specify the number of arguments being sent to the next call */
            REFOUT, /**< Pass op1 by reference */
            VALOUT, /**< Pass op1 by value */
            CALL, /**< Call the procedure named op1 */
            PROCENTRY, /**< Marks the beginning of a procedure */
            COMMENT, /**< Output op1 as a comment */
            BEGINFRAME, /**< Marks the beginning of a new stack frame, and passes in the size of the memory required on the stack*/
	    FPAR,  /** Denotes a passed parameter value **/
	    RETURN , /** Denotes the return value **/ 
	};

        /**
         * Enum of instructions without operands.
         * These enum values serve as flags to the toTAC functions in order to 
         * indicate which 3AC statement should be generated, and what the types
         * of the void * parameters to the toTAC functions are.
         */
        enum NoOpInstructions
        {
            HALT, /**< Immediately halt execution */
            ENDPROC, /**< Mark the end of a procedure */
            ENDFRAME /**< Marks the end of a stack frame */
        };

        /**
         * The paramaterized constructor.
         * This constructor opens the 3AC file with the given filename.
         *
         * @param filename The name of the file in which to output 3AC
         */
        TAC_Generator(const string &filename);
        
        /**
         * The default constructor.
         * This constructor does not open an output file. If this constructor is
         * used, then the function SetFile must be called.
         *
         * @see SetFile()
         */
        TAC_Generator();
        
        /**
         * The destructor.
         * This destructor is responsible for outputting the 3AC from the list
         * of strings to the output file and then closing the output file.
         */
        ~TAC_Generator();

        /**
         * Generate a 3AC string.
         * The toTAC overloads take in a flag to indicate the type of three 
         * address code statement and a series of parameters required by
         * the particular statement, in order to generate a formatted 3AC 
         * statement. NOTE: this function determines the type of the operands
         * based on the flag passed as the first parameter. If the incorrect
         * flag is passed, then the program will cast the address to the wrong 
         * type, so be careful.
         *
         * @param t Flag indicating the type of 3AC statement to generate
         * @param op1 A pointer to the first operand (cast as a void*)
         * @param op2 A pointer to the second operand (cast as a void*)
         * @param op3 A pointer to the third operand (cast as a void*)
         * @param c An optional comment to prepend to the 3AC statement (useful 
         *        for outputting the original input code as comments to the 3AC 
         *        file)
         */
        void toTAC(ThreeOpInstructions t, void* op1, void* op2, void* op3, string c = "" );
        
        /**
         * Generate a 3AC string.
         * The toTAC overloads take in a flag to indicate the type of three 
         * address code statement and a series of parameters required by
         * the particular statement, in order to generate a formatted 3AC 
         * statement. NOTE: this function determines the type of the operands
         * based on the flag passed as the first parameter. If the incorrect
         * flag is passed, then the program will cast the address to the wrong 
         * type, so be careful.
         *
         * @param t Flag indicating the type of 3AC statement to generate
         * @param op1 A pointer to the first operand (cast as a void*)
         * @param op2 A pointer to the second operand (cast as a void*)
         * @param c An optional comment to prepend to the 3AC statement (useful 
         *        for outputting the original input code as comments to the 3AC 
         *        file)
         */
        void toTAC(TwoOpInstructions t, void* op1, void* op2, string c = "" );
        
        /**
         * Generate a 3AC string.
         * The toTAC overloads take in a flag to indicate the type of three 
         * address code statement and a series of parameters required by
         * the particular statement, in order to generate a formatted 3AC 
         * statement. NOTE: this function determines the type of the operand
         * based on the flag passed as the first parameter. If the incorrect
         * flag is passed, then the program will cast the address to the wrong 
         * type, so be careful.
         *
         * @param t Flag indicating the type of 3AC statement to generate
         * @param op1 A pointer to the first operand (cast as a void*)
         * @param c An optional comment to prepend to the 3AC statement (useful 
         *        for outputting the original input code as comments to the 3AC 
         *        file)
         */
        void toTAC(OneOpInstructions t, void* op1, string c = "" );
        
        /**
         * Generate a 3AC string.
         * The toTAC overloads take in a flag to indicate the type of three 
         * address code statement and a series of parameters required by
         * the particular statement, in order to generate a formatted 3AC 
         * statement.
         *
         * @param t Flag indicating the type of 3AC statement to generate
         * @param c An optional comment to prepend to the 3AC statement (useful 
         *        for outputting the original input code as comments to the 3AC 
         *        file)
         */
        void toTAC(NoOpInstructions t, string c = "");

        /**
         * Sets the symbol which should appear at the end of all comments.
         *
         * @param commentStart String to be place at the beginning of every comment
         */
       
        void Fetch(string varName , SymTab *symbolTable , string targetTemp);  

        void SetCommentStart(string commentStart);

        /**
         * Sets the symbol which should appear at the beginning of all comments.
         *
         * @param commentEnd String to be placed at the end of every comment
         */
        void SetCommentEnd(string commentEnd);

        /**
         * Writes a comment string to the 3AC output.
         *
         * @param comment String to output as a comment
         */
        void WriteComment(string comment);

        /**
         * Puts a blank line in the 3AC output.
         */
        void Blank();

        /**
         * Sets the name of the file in which the output 3AC should be saved
         *
         * @param filename The name of the file in which to output 3AC
         */
        void SetFile(const string &filename);

        /**
         * Sets the fixed column width for outputting 3AC statements.
         *
         * @param w Integer indicating the width of the columns to print the 3AC in.
         */
        void SetColumnWidth(int w);

        /**
         * Sets the ios_base format flags used when generating formatted 3AC 
         * strings.
         *
         * @param ff Format flags (i.e. left, right, etc.)
         */
        void SetFormatFlags(ios_base::fmtflags ff);

        /**
         * Sets the blankBeforeComments flag. If true, a blank line will be 
         * output in the final 3AC before each comment.
         * 
         * @param flag True if there should be an empty line before each comment
         */
        void SetBlankBeforeComments(bool flag);
        
          	

        /**
         * Generates a unique label string.
         */
        static string GetLabelName();

        /**
         * Generates a unique string for integer temps.
         */
        static string GetIVarName();

        /**
         * Generates a unique string for floating-point temps.
         */
        static string GetFVarName();

    private:
        /**
         * This function saves the string passed in to a STL list for later
         * output.
         *
         * NOTE: The 3AC Generator "emits" code to a list first, and then after 
         * all code has been emitted, it is pushed to a file. This is done so as
         * to allow for changes to be made to the 3AC before it is finalized 
         * (ie: moving all function decls to the top of the code)
         */
        void Emit(string CodeToEmit);

        list<string> buffer; /**< A buffer for the generated 3AC */
        ofstream fout; /**< Output stream */
        
        string commentStart; /**< String to be placed at the beginning of every comment */
        string commentEnd; /**< String to be placed at the end of every comment */
        bool blankBeforeComment; /**< Flag for placing blank lines before comments */
        
        int width; /**< Fixed column width of the output 3AC */

        ios_base::fmtflags flags; /**< Format flags */
            	
        static int lCount; /**< Current label counter for generating unique labels */
        static int iCount; /**< Current integer counter for generating unique integer labels */
        static int fCount; /**< Current float counter for generating unique float labels */
        
        string CurrentLabel;
};

extern void GenGlobals (  SymTab &symTab ,  TAC_Generator &tacGen);

#endif // ! TAC_GENERATOR_H_





















