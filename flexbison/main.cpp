#include <iostream>
#include <fstream>
#include "CCompiler.h"

void usage(char** argv)
{
    std::cout << "Usage: " << argv[0] << " -d [ls] -o" << std::endl;
}

int main(int argc, char** argv)
{
    std::string fname;
//    std::streambuf* orig = std::cerr.rdbuf();
//    std::fstream out;

    CCompiler driver;

    for(int i = 1; i < argc; ++i)
    {
        if(argv[i] == std::string("-d"))
        {
            ++i;
            if(i < argc)
            {
                std::string flags(argv[i]);
                if(flags.find("l") != std::string::npos)
                    driver.trace_scanning = true;
                if(flags.find("s") != std::string::npos)
                    driver.trace_symtab = true;
                if(flags.find("p") != std::string::npos)
                    driver.trace_parsing = true;
            }
            else
            {
                usage(argv);
                exit(EXIT_FAILURE);
            }
        }
        else if(argv[i] == std::string("-o"))
        {

/*            std::string ofname;
            ++i;
            if(i < argc)
            {
                ofname = argv[i];
            }
            else
            {
                ofname = "output";
            }

            out.open(fname.c_str(), ios_base::out);
            orig = std::cerr.rdbuf(out.rdbuf());
*/
        }
        else
        {
            fname = argv[i];
        }
    }

    int result = driver.parse(fname);
//    std::cerr.rdbuf(orig);

//    if(out.is_open())
//        out.close();

    return result;
}
