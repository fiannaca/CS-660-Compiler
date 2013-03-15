int funcTest1(int paramA, short paramB, unsigned long paramC);
void funcTest2(float paramA, ... );

//

int main(int argc, char **argv)
{
    int test1a = 1;
    int test2a = 0x2;
    int test3a = 0123;
// /* */

    int test1b = 1u;
    int test2b = 0x2u;
    int test3b = 0123u;

    int test1c = 1l;
    int test2c = 0x2l;
    int test3c = 0123l;

    int test1d = 1uLL;
    int test2d = 0x2uLL;
    int test3d = 0123uLL;

    float test4a = 1234.5678;
    float test5a = 1234e5678;
    float test6a = 0x123ABC.567DEFp89;

    float test4b = 1234.5678f;
    float test5b = 1234e5678f;
    float test6b = 0x123ABC.567DEFp89f;

    float test4c = 1234.5678l;
    float test5c = 1234e5678l;
    float test6c = 0x123ABC.567DEFp89l;

    char test7a = 'a';
//    char test8a = '\abcd';
    char test9a = '\0123';
    char test10a = '\0';

    char test7b = L'a';
//    char test8b = L'\abcd';
    char test9b = L'\0123';
    char test10b = L'\0';

    char *test11 = "This is a string";
//    char *test12 = "This is a \t string";
    char *test13 = "This is a \" string";

    char *test11 = L"This is a string";
//    char *test12 = L"This is a \t string";
    char *test13 = L"This is a \" string";

//    /** This is a big multiline comment
//      *
//      */
    funcTest1(1, 2, 4);

    int a;

    return 0;
}

int funcTest1(int paramA, short paramB, unsigned long paramC)
{
    return 0;
}

void funcTest2(float paramA, ...)
{
    //No return value
}
