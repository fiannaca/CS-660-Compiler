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
        Visualizer()
            : file("vis.dot", fstream::out)
            , gname("ASTvis")
        {
            if(file.good())
            {
                begin();
            }
            else
            {
                cout << "AST visualization .dot file could not be opened!" << endl;
                exit(EXIT_FAILURE);
            }
        }

        Visualizer(string fname)
            : file(fname.c_str(), fstream::out)
            , gname("ASTvis")
        {
            if(file.good())
            {
                begin();
            }
            else
            {
                cout << "AST visualization .dot file could not be opened!" << endl;
                exit(EXIT_FAILURE);
            }
        }

        ~Visualizer()
        {
            end();
            file.close();
        }

        void begin()
        {
            file << "digraph " << gname << " {" << endl;
        }

        void end()
        {
            file << "}" << endl;
        }

        void addNode(int uid, string label)
        {
            file << "    " << uid << " [label=\"" << label << "\"];" << endl;
        }

        void addNode(int parentid, int childid, string parent_label)
        {
            addNode(parentid, parent_label);

            file << "    " << parentid << " -> " << childid << ";" << endl;
        }

        void addEdge(int parent, int child)
        {
            file << "    " << parent << " -> " << child << ";" << endl;
        }

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

int Visualizer::nextUID = 0;

#endif // ! _VISUALIZER_
