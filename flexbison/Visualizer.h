#ifndef _VISUALIZER_
#define _VISUALIZER_

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

class Visualizer
{
    public:
        Visualizer();
        Visualizer(string fname);
        ~Visualizer();

        void begin();
        void end();
        void addNode(int uid, string label);
        void addNode(int parentid, int childid, string parent_label);
        void addEdge(int parent, int child);

        static int GetNextUID()
        {
            int tmp = nextUID;

            ++nextUID;

            return tmp;
        }

    private:
        fstream file;
        string gname;
        static int nextUID;
};

#endif // ! _VISUALIZER_
