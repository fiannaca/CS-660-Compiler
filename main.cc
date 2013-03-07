#include <stdio.h>

#include "Parser.h"

int main(int argc, char **argv)
{
    if(argc > 1)
    {
        freopen(argv[1], "r", stdin);
    }
    else
    {
        printf("\nUsage: ./CFrontEnd [filename.c]\n\n");
        return 1;
    }

    Parser parser;

    parser.parse();
    return 0;
}
