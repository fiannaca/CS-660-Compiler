#include "tac2mips.h"

using namespace std;

tac2mips::tac2mips(string filename)
    : regtab(8, "$t", &addtab)
{
    fname = filename;
    
    int lastindex = fname.find_last_of("."); 
    outfname = fname.substr(0, lastindex) + ".mips";
    
    fout.open(outfname, std::ios_base::out);
    
    regtab.SetFstream(&fout);
    
    this->OutputPreamble();
}

tac2mips::~tac2mips()
{
    fout.close();
}

void tac2mips::Run()
{
    yy::TAC_Parser parser(*this);
    
    scan_begin();
    
    int result = parser.parse();
    
    scan_end();
}


void tac2mips::error(const std::string& msg)
{
    cerr << endl << "3AC 2 MIPS error: " << msg << endl << endl;
    
    exit(EXIT_FAILURE);
}

string tac2mips::GetRegister(string tempName, bool &isNew)
{
    return regtab.GetRegister(tempName, isNew);
}

void tac2mips::OutputPreamble()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    
    fout << setw(80) << setfill('#') << "#" << endl;
    fout << "#" << endl;
    fout << "# MIPS Assembly Code" << endl;
    fout << "# Filename:     " << outfname << endl;
    fout << "# Input file:   " << fname << endl;
    fout << "# Generated on: " << dt << "#" << endl;
    fout << setw(80) << setfill('#') << "#" << endl;
    
    fout << endl << "\t.include \"macros.asm\"" << endl;
    
    fout << endl << "\t.data" << endl
         << "spills:\t.space " << regtab.GetSpillSize() << endl << endl;
}

void tac2mips::Comment(std::string txt)
{
    fout << "#" << txt << endl;
}












