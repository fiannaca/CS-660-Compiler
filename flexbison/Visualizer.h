#ifndef _VISUALIZER_
#define _VISUALIZER_

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * A class for visualizing the generation of the AST. The Visualizer class
 * provides a method for generating a GraphViz output file which can be 
 * converted to a graphic representing the AST.
 */
class Visualizer
{
    public:
        /**
         * Default constructor. This version of the constructor defaults the 
         * output filename to "vis.dot". It attempts to open the file, and exits
         * with EXIT_FAILURE if the file cannot be opened.
         */
        Visualizer();
        
        /**
         * Parameterized constructor. This version of the constructor takes the 
         * output filename as a parameter. It attempts to open the file, and 
         * exits with EXIT_FAILURE if the file cannot be opened.
         *
         * @param fname The output GraphVis file filename
         */
        Visualizer(string fname);
        
        /**
         * Destructor. Completes the GraphViz file and closes the filestream.
         */
        ~Visualizer();

        /**
         * Creates the opening part of the GraphViz file.
         */
        void begin();
        
        /**
         * Creates the closing part of the GraphViz file
         */
        void end();
        
        /**
         * Adds a node to the graph with a unique id and a label
         *
         * @param uid A unique id
         * @param label The label to go inside the node in the graph
         */
        void addNode(int uid, string label);
        
        /**
         * Adds a node to the graph with a unique id and a label, then creates
         * an edge from the new node to a child node.
         *
         * @param parentid A unique id for the new node
         * @param childid The unique id of the child node to create an edge to
         * @param parent_label The label to go inside the node in the graph
         */
        void addNode(int parentid, int childid, string parent_label);
        
        /**
         * Adds a node to the graph which is only for visualizing extra info
         * rather than visualizing an actual node in the AST.
         *
         * @param uid The unique id of the parent node off of which the dummy
         *            node should be attached
         * @param label The label to go inside the dummy node
         */
        void addDummyNode(int parentid, string label);
        
        /**
         * Adds an edge from a parent node to a child node
         * 
         * @param parent The unique id of the parent
         * @param child The unique id of the child
         */
        void addEdge(int parent, int child);


        /**
         * Gets a unique id to be used in adding nodes to the AST
         * 
         * @return A unique integer valued id
         */
        static int GetNextUID()
        {
            int tmp = nextUID;

            ++nextUID;

            return tmp;
        }

    private:
        fstream file; /**< The filename of the output GraphViz file */
        string gname; /**< The name of the graph in the GraphViz file */
        static int nextUID; /**< The next unique id value */
};

#endif // ! _VISUALIZER_
