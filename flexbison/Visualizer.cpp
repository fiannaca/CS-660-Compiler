#include "Visualizer.h"

int Visualizer::nextUID = 0;

Visualizer::Visualizer()
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

Visualizer::Visualizer(string fname)
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

Visualizer::~Visualizer()
{
    end();
    file.close();
}

void Visualizer::begin()
{
    file << "digraph " << gname << " {" << endl;
}

void Visualizer::end()
{
    file << "}" << endl;
}

void Visualizer::addNode(int uid, string label)
{
    file << "    " << uid << " [label=\"" << label << "\"];" << endl;
}

void Visualizer::addNode(int parentid, int childid, string parent_label)
{
    addNode(parentid, parent_label);

    file << "    " << parentid << " -> " << childid << ";" << endl;
}

void Visualizer::addEdge(int parent, int child)
{
    file << "    " << parent << " -> " << child << ";" << endl;
}
