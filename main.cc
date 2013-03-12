#include <stdio.h>

#include "Parser.h"

int main(int argc, char **argv)
{
    if(argc > 1)
    {
        freopen(argv[1], "r", stdin);
//        freopen("error.out", "w", stderr);
//        freopen("output.out", "w", stdout);
    }
    else
    {
        printf("\nUsage: ./CFrontEnd [filename.c]\n\n");
        return 1;
    }

    Parser parser;

    parser.parse();

    fclose(stdin);
//    fclose(stderr);
//    fclose(stdout);

    return 0;
}
