/*
 * This file serves as an entry point to the compiler. It simply creates a compiler object, parses the command-line
 * arguments and starts the compiler.
 */

#include <iostream>
#include "CCompiler.h"

void usage(char** argv)
{
    std::cout << "Usage: " << argv[0] << " -d [ls] -o" << std::endl;
}

int main(int argc, char** argv)
{
    std::string fname;

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
            std::string ofname;
            ++i;
            if(i < argc)
            {
                ofname = argv[i];
            }
            else
            {
                ofname = "test.out";
            }

            driver.setOutfile(ofname);
        }
        else if(argv[i] == std::string("-v"))
	{
            std::cout << "turning on debug";
	    driver.turnDebugOn(true);
	}
        else
        {
            fname = argv[i];
        }
    }

    //Run the parsing
    int retValue =  driver.parse(fname);
    
    //Get ready for 3AC generation
    AST::tacGen.WriteComment("");
    AST::tacGen.WriteComment("3AC For the Input Code File: " + fname);
    AST::tacGen.WriteComment("");
    
    //Walk the AST to generate 3AC
    driver.source_ast->Visit();
    
    return retValue;
}


























