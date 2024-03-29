#ifndef _AST_CONSTANTS_
#define _AST_CONSTANTS_

#include <sstream>
#include "Ast.h"

class AstTypeName : public AST
{
    //TODO implement later

    //Place the children nodes here

    public:
        //Constructor
        AstTypeName()
        {
            this->setLabel("TypeName");
        }

        //Traversal
        void Visit()
        {
            //Visit children nodes

            //Output visualization
            //AST::vis.addNode(this->getUID(), this->getLabel());
            //AST::vis.addEdge(this->getUID(), child->getUID());

            //Output 3AC
        }
};

class AstString : public AST
{
    string val;

    public:

    AstString(string str)
    {
        this->val = str;

        this->setLabel("StringLiteral");
    }

    void Visit()
    {
        AST::vis.addNode(this->getUID(), this->getLabel());

        //Add an extra node to the visualization to see the actual data
        int tmp = Visualizer::GetNextUID();
        AST::vis.addNode(tmp, "Value: " + val);
        AST::vis.addEdge(this->getUID(), tmp);
    }
};

class AstConstant : public AST
{
    enum ConstType
    {
        INT,
        CHAR,
        FLOAT,
        ENUM,
    };

    ConstType type;

    int ival;
    string str;
    double dval; 

    public:
    
    AstConstant(int val)
    {
        this->type = INT;
        this->ival = val;

        this->setLabel("IntegerConstant");
    }

    AstConstant(string val)
    {
        this->type = CHAR;
        this->str = val;

        this->setLabel("CharacterConstant");
    }

    AstConstant(double val)
    {
        this->type = FLOAT;
        this->dval = val;

        this->setLabel("FloatConstant");
    }

    AstConstant(int val, string name)
    {
        this->type = ENUM;
        this->ival = val;
        this->str = name;

        this->setLabel("EnumerationConstant");
    }

    void Visit()
    {
        AST::vis.addNode(this->getUID(), this->getLabel());

        //Add an extra node to the visualization to see the actual data
        stringstream ss;
        int tmp = Visualizer::GetNextUID();

        switch(this->type)
        {
            case INT:
                ss << "Value: " << ival;
                break;

            case CHAR:
                ss << "Value: " << str;
                break;

            case FLOAT:
                ss << "Value: " << dval;
                break;

            case ENUM:
                ss << "Name: " << str << ", Value: " << ival;
                break;
        }

        AST::vis.addNode(tmp, ss.str());
        AST::vis.addEdge(this->getUID(), tmp);
    }
};

class AstUnaryOp : public AST
{
    //Place the children nodes here
    public:
        enum Operator
        {
            BIN_AND,
            STAR,
            PLUS,
            MINUS,
            TILDE,
            BANG
        };

    private:
        Operator op;

    public:
        //Constructor
        AstUnaryOp(Operator o)
        {
            this->op = o;

            this->setLabel("UnaryOperator");
        }

        //Traversal
        void Visit()
        {
            //Visit children nodes

            //Output visualization
            AST::vis.addNode(this->getUID(), this->getLabel());

            //Output 3AC
        }
};
#endif 
