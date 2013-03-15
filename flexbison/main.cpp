#include <iostream>
#include "CCompiler.h"

void usage(char** argv)
{
    std::cout << "Usage: " << argv[0] << " -d [ls] -o" << std::endl;
}

int main(int argc, char** argv)
{
    std::string fname;

//    std::cout << "Starting up" << std::endl;

    CCompiler driver;

//    std::cout << "Created driver..." << std::endl;

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
            ++i;
            if(i < argc)
            {
                std::string fname(argv[i]);

                driver.out_fname = fname;
            }
            else
            {
                driver.out_fname = "output";
            }
        }
        else
        {
            fname = argv[i];
        }
    }

    return driver.parse(fname);
}
