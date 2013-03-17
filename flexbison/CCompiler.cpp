#include "CCompiler.h"
#include "CParser.hpp"
#include <iomanip>

CCompiler::CCompiler()
    : trace_scanning(false)
    , trace_parsing(false)
    , trace_symtab(false)
    , outfile_set(false)
{

}

CCompiler::~CCompiler()
{
    if(outfile_set)
        fclose(stderr);
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

void CCompiler::setOutfile(std::string fname)
{
    out_fname = fname;

    if(!freopen(fname.c_str(), "w", stderr))
    {
        outfile_set = true;
    }

}

void CCompiler::set_insert_mode(bool iMode)
{
    insert_mode = iMode;
}

bool CCompiler::get_insert_mode()
{
    return insert_mode;
}

void CCompiler::error(const yy::location& loc, const std::string& msg)
{
    std::cerr << std::endl;
    std::cerr << "Error in " << *loc.begin.filename << " at "
              << loc.begin.line << ":" << loc.begin.column
              << " : (see location below)" <<  std::endl
	      << "   " << msg << std::endl << std::endl;

    std::cerr << std::setw(4) << loc.begin.line << " | " << linebuf << std::endl;
    std::cerr << "     | " << std::setfill('-') << std::setw(loc.begin.column);
    std::cerr << "^" << std::endl << std::endl;

    exit(EXIT_FAILURE);
}

void CCompiler::error(const std::string& msg)
{
    std::cerr << msg << std::endl;

    exit(EXIT_FAILURE);
}
