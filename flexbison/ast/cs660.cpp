#include <iostream>
#include <string>
#include "Ast.h"
#include "AstExpression.h"
#include "AstStatement.h"
#include "AstIfStatement.h"
#include "AstDoWhileStatement.h"
#include "AstWhileStatement.h"
#include "AstReturnStatement.h"
#include "AstGotoStatement.h"
#include "AstBreakStatement.h"
#include "AstLabelStatement.h"
#include "AstCaseStatement.h"
#include "AstDefaultStatement.h"
#include "AstEmptyStatement.h"
#include "AstStatementList.h"
#include "AstUnaryOperator.h"
#include "AstBinaryOperator.h" 

using namespace std;

int main()
{
    AstUnary anode(NULL, "blah");
    AstUnary anode2(NULL, "blah");
    AstUnary anode3(NULL, "blah");

    anode.setLabel("UnaryOperator1");
    anode2.setLabel("UnaryOperator2");
    anode3.setLabel("UnaryOperator3");

    //Build a test tree out of order to verify that it still works

    //Child 1
    AST::vis.addNode(anode2.getUID(), anode2.getLabel());

    //Parent
    AST::vis.addNode(anode.getUID(), anode.getLabel());
    AST::vis.addEdge(anode.getUID(), anode2.getUID());

    //Child 2
    AST::vis.addNode(anode3.getUID(), anode3.getLabel());
    AST::vis.addEdge(anode.getUID(), anode3.getUID());

    return 0;
}
