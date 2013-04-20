/*
 * See description in CCompiler.h!
 */

#include "CCompiler.h"
#include "CParser.hpp"

TAC_Generator CCompiler::tacGen;

//
//Begin CCompiler implementation
//

CCompiler::CCompiler()
    : trace_scanning(false)
    , trace_parsing(false)
    , trace_symtab(false)
    , outfile_set(false)
    , debug_on(false)
    , SymbolTable(this)
{
    printDebug("Initializing the global scope...");
    globalScope();
    structUnionMode = 0 ;
    structVarCount = 0 ;  
    //C starts in insert mode
    allocateSymbol(); 
    anonymousEnum = false;      
    set_insert_mode(true);
       
}

CCompiler::~CCompiler()
{
}

int CCompiler::parse(const std::string& f)
{
    fname = f;
    tFile.open((fname + ".tok").c_str(), ios_base::out);
    rFile.open((fname + ".red").c_str(), ios_base::out);

    if(trace_parsing)
        ydbFile.open((fname + ".ydb").c_str(), ios_base::out);

    scan_begin(trace_scanning);

    yy::CParser parser (*this);
    parser.set_debug_level(trace_parsing);

    if(trace_parsing)
        parser.set_debug_stream(ydbFile);

    int result = parser.parse();

    scan_end();
    return result;
}

void CCompiler::setOutfile(std::string file)
{
    outfile.open(file.c_str(), ios_base::out);
    outfile_set = true;
}

/*****************************************************************************/
/* SYMBOL TABLE HANDLERS *****************************************************/
/*****************************************************************************/

void CCompiler::globalScope()
{
    //call the symtab function for initializing the global scope
}

void CCompiler::enterScope()
{
    //call the symtab function for entering a scope
    SymbolTable.EnterScope();
}

void CCompiler::leaveScope()
{
    //Call the symtab function for leaving a scope
    SymbolTable.LeaveScope(); 
}

void CCompiler::set_insert_mode(bool iMode)
{
    insert_mode = iMode;
}

bool CCompiler::get_insert_mode()
{
    return insert_mode;
}

yy::CParser::token::yytokentype CCompiler::checkType(char* key, const yy::location& loc, SymbolInfo* sym)
{
    //For the time being this will return IDENTIFIER, but it should 
    // check if the provided key is related to an identifier, an
    // enum_constant, or a typedef_name

    int level;
    SymbolInfo symToFind;
    symToFind.symbol_name = std::string(key);
    if(!SymbolTable.find_symbol(symToFind, level))
    {
        //The symbol was not in the table
        if(insert_mode)
        {
            //If we are in insert mode, then insert it
            //sym->symbol_name = key;
            //SymbolTable.insert_symbol(*sym);
            //cout << "Inside checkType insert" << endl;
        }
        else
        {
            //Otherwise, declare the error -- Supress this for the time being 
            //error(loc, "All variables must be declared at the top of a block!");
        }
    }

    //The symbol was in the table

    //Check if it is an enum, a typedef name, or just an identifier

    //This is the temp return...
    sym->symbol_name = string(key);
    printTok("IDENTIFIER", key);

    return yy::CParser::token::IDENTIFIER;
}

void CCompiler::allocateSymbol()
{
   this->currentSymbol = new SymbolInfo(); 
   this->currentSymbol->symbolType = NULL;   
}


/*****************************************************************************/
/* DEBUGGING AND ERROR OUTPUT ************************************************/
/*****************************************************************************/

void CCompiler::error(const yy::location& loc, const std::string& msg)
{
    if(outfile_set)
    {
        outfile << std::endl;
        outfile << "Error in " << *loc.begin.filename << " at "
                << loc.begin.line << ":" << loc.begin.column
                << " : (see location below)" <<  std::endl
	        << "   " << msg << std::endl << std::endl;

        outfile << std::setw(4) << std::setfill(' ') << loc.begin.line << " | " << input_text[loc.begin.line] << std::endl;
        outfile << "     | " << std::setfill('-') << std::setw(loc.begin.column);
        outfile << "^" << std::endl << std::endl;
    }
    else
    {
        std::cerr << std::endl;
        std::cerr << "Error in " << *loc.begin.filename << " at "
                  << loc.begin.line << ":" << loc.begin.column
                  << " : (see location below)" <<  std::endl
	          << "   " << msg << std::endl << std::endl;

        std::cerr << std::setw(4) << std::setfill(' ') << loc.begin.line << " | " << input_text[loc.begin.line] << std::endl;
        std::cerr << "     | " << std::setfill('-') << std::setw(loc.begin.column);
        std::cerr << "^" << std::endl << std::endl;
    }

    exit(EXIT_FAILURE);
}

void CCompiler::error(const std::string& msg)
{
    if(outfile_set)
        outfile << msg << std::endl;
    else
        std::cerr << msg << std::endl;

    exit(EXIT_FAILURE);
}

void CCompiler::warning(const yy::location& loc, const std::string& msg)
{
    if(outfile_set)
    {
        outfile << std::endl;
        outfile << "Warning in " << *loc.begin.filename << " at "
                << loc.begin.line << ":" << loc.begin.column
                << " : (see location below)" <<  std::endl
	        << "   " << msg << std::endl << std::endl;

        outfile << std::setw(4) << std::setfill(' ') << loc.begin.line << " | " << input_text[loc.begin.line] << std::endl;
        outfile << "     | " << std::setfill('-') << std::setw(loc.begin.column);
        outfile << "^" << std::endl << std::endl;
    }
    else
    {
        std::cerr << std::endl;
        std::cerr << "Warning in " << *loc.begin.filename << " at "
                  << loc.begin.line << ":" << loc.begin.column
                  << " : (see location below)" <<  std::endl
	          << "   " << msg << std::endl << std::endl;

        std::cerr << std::setw(4) << std::setfill(' ') << loc.begin.line << " | " << input_text[loc.begin.line] << std::endl;
        std::cerr << "     | " << std::setfill('-') << std::setw(loc.begin.column);
        std::cerr << "^" << std::endl << std::endl;
    }
}

void CCompiler::warning(const std::string& msg)
{
    if(outfile_set)
        outfile << "Warning: " << msg << std::endl;
    else
        std::cerr << "Warning: " << msg << std::endl;
}

void CCompiler::printTok(std::string ttxt)
{
    tFile << "<" << ttxt << ">" << std::endl;
}

void CCompiler::printTok(std::string ttxt, char* yytext)
{
    tFile << "<" << ttxt << "> - " << yytext << std::endl;
}

void CCompiler::printRed(std::string ptxt)
{
    rFile << ptxt << std::endl;
}

void CCompiler::turnDebugOn(bool flag)
{
    debug_on = flag;
}

void CCompiler::printDebug(std::string txt)
{
    if(debug_on)
    {
        if(outfile_set)
            outfile << txt << std::endl;
        else
            std::cout << txt << std::endl;
    }
}

void CCompiler::save_line(int i, string s)
{
    //Don't store blank lines. Only store the actual code
    if(s.size() > 0)
    {
        //InputLine in(i, s);
        input_text[i] = s;
    }
}

























