#include "tac2mips.h"

using namespace std;

tac2mips::tac2mips(string filename)
    : regtab(8, "$t")
    , addtab(&regtab)
{
    fname = filename;
    
    int lastindex = fname.find_last_of("."); 
    outfname = fname.substr(0, lastindex) + ".mips";
    
    fout.open(outfname, std::ios_base::out);
    
    regtab.SetFstream(&fout);
    addtab.SetFstream(&fout);
    
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

string tac2mips::GetRegister(string name, bool &isNew)
{
	Address* addr = addtab.Lookup(name);
	
	if(addr)
		return addtab.Load(addr);
	else
		return regtab.GetRegister(name, isNew);
}

void tac2mips::FreeRegister(std::string name)
{
	Address* addr = addtab.Lookup(name);
	
	if(addr)
		addtab.Store(name);
	else
		regtab.FreeRegister(name);
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

bool tac2mips::LabelExists(std::string name)
{
	auto it = labels.find(name);
	
	if(it != labels.end())
		return true;
	
	return false;
}

void tac2mips::AddLabel(std::string name)
{
	labels.insert(name);
}

void tac2mips::Comment(std::string txt)
{
    fout << "#" << txt << endl;
}

void tac2mips::toMIPS(std::string txt)
{
	fout << "\t" << txt << endl;
}

void tac2mips::Label(std::string txt)
{
	AddLabel(txt);
	fout << endl << txt << ":";
}












