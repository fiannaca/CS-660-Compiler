#include "tac2mips.h"
#include <string>

using namespace std;

void usage(char** argv)
{
    cout << endl << "Usage: " << argv[0] << " [3AC filename]" << endl << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    string fname;
    
    if(argc == 2)
        fname = argv[1];
    else
        usage(argv);
        
    tac2mips driver(fname);
    
    driver.SetVerbose(false);
    driver.Run();
    
    return 0;
}
