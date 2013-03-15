#include "CCompiler.h"
#include "CParser.hpp"
#include <iomanip>

CCompiler::CCompiler()
    : trace_scanning(false)
    , trace_parsing(false)
    , trace_symtab(false)
{

}

CCompiler::~CCompiler()
{
}

int CCompiler::parse(const std::string& fname)
{
    in_fname = fname;
    scan_begin(trace_scanning);

    yy::CParser parser (*this);
    parser.set_debug_level(trace_parsing);
    int result = parser.parse();

    scan_end();
    return result;
}

void CCompiler::error(const yy::location& loc, const std::string& msg)
{
    std::cerr << std::endl;
    std::cerr << "Error at "
              << loc.begin.line << ":" << loc.begin.column
              << " : " << msg << " (see location below)"
              << std::endl << std::endl;

    std::cerr << std::setw(4) << loc.begin.line << " | " << linebuf << std::endl;
    std::cerr << "     | " << std::setfill('-') << std::setw(loc.begin.column);
    std::cerr << "^" << std::endl << std::endl;

//    std::cerr << loc << ": " << msg << std::endl;
}

void CCompiler::error(const std::string& msg)
{
    std::cerr << msg << std::endl;
}
