#include "CCompiler.h"
#include "CParser.hh"

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
    file = fname;
    scan_begin();

    yy::CParser parser (*this);
    parser.set_debug_level(trace_parsing);
    int result = parser.parser();

    scan_end();
    return result;
}

void CCompiler::error(const yy::location& loc, const std::string& msg)
{
    std::cerr << loc << ": " << msg << std::endl;
}

void CCompiler::error(const std::string& msg)
{
    std::cerr << msg << std::endl;
}
