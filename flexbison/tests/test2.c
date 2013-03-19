//Tests shadowing
int a = 0; //first declaration

int main(int argc, char** argv)
{
    int a = 1; //shadows line 2

    if(a == 1)
    {
        int a = 2; //shadows line 6

        if(a == 2)
        {
            int a = 3; //shadows line 10
        }
    }

    return 0;
}
