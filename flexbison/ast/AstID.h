#ifndef _AST_ID_
#define _AST_ID_

#include "Ast.h"

class AstID : public AST
{
    string str;

    public:
    AstID(string s)
    {
        this->str = s;

        this->setLabel("Identifier");
    }

    void Visit()
    {
        AST::vis.addNode(this->getUID(), this->getLabel() + ": " + str);
    }
};

#endif 
