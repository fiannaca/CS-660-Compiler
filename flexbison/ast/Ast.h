#ifndef _AST_H_
#define _AST_H_ 

#include <string>
#include "Visualizer.h"

class AST
{
    public:
        AST()
        {
            uid = Visualizer::GetNextUID();
            label = "LabelNotSet";
        }

        void setLabel(string l)
        {
            label = l;
        }

        int getUID() { return uid; }

        string getLabel() { return label; }

        static Visualizer vis;

	virtual void Visit(){};

    protected:
        int uid;
        string label;
};

//Visualizer AST::vis;

#endif 
