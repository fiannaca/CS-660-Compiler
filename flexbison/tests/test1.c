#Tests variable declarations
int main(int argc, char** argv)
{
    //These declarations should all work correctly
    int a;
    int b = 1234ul;
    float c;
    float d = 1234.5678;

    //Check the symbol table for the above declarations
    !!S

    a = b + c;

    //This next line should fail
    char e;

    return 0;
}
