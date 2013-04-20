#include "TAC_Generator.h"

//Convenient typedef
typedef TAC_Generator t;

int main(int argc, char* argv[])
{
    string label;
    TAC_Generator tac("output");
    
    tac.SetFormatFlags(ios_base::left);
    tac.SetColumnWidth(15);
    
    //0 OP Commands
    //tac.WriteComment("Test no op 3AC commands...");
    
    tac.toTAC(t::HALT, "Test no op 3AC commands...");
    tac.toTAC(t::ENDPROC);
    tac.toTAC(t::RETURN);
    tac.Blank();
    
    //1 OP Commands
    tac.WriteComment("Test single op 3AC commands...");
    
    for(int i = 0; i < 3; i++)
    {
        label = t::GetLabelName();
    
        tac.toTAC(t::LABEL, (void*) &label);
    }
    
    label = "L00000001";
    tac.toTAC(t::BR, (void*) &label);
    
    label = t::GetIVarName();
    tac.toTAC(t::REFOUT, (void*) &label);
    
    label = t::GetIVarName();
    tac.toTAC(t::VALOUT, (void*) &label);
    
    label = t::GetLabelName();
    tac.toTAC(t::CALL, (void*) &label);
    
    tac.toTAC(t::ARGS, (void*) 3);
    
    tac.Blank();
    
    //2 OP Commands
    //tac.WriteComment("Test double op 3AC commands...");
    
    string lbl1 = t::GetIVarName();
    string lbl2 = t::GetIVarName();
    tac.toTAC(t::NEG, (void*) &lbl1, (void*) &lbl2, "Test double op 3AC commands...");
    
    lbl1 = t::GetIVarName();
    lbl2 = t::GetIVarName();
    tac.toTAC(t::NOT, (void*) &lbl1, (void*) &lbl2);
    
    lbl1 = t::GetIVarName();
    lbl2 = t::GetIVarName();
    tac.toTAC(t::ADDR, (void*) &lbl1, (void*) &lbl2);
    
    lbl1 = t::GetIVarName();
    tac.toTAC(t::GLOBAL, (void*) &lbl1, (void*) 4);
    
    lbl1 = t::GetIVarName();
    lbl2 = t::GetIVarName();
    tac.toTAC(t::STRING, (void*) &lbl1, (void*) &lbl2);
    
    tac.Blank();
    
    //3 OP Commands
    tac.WriteComment("Test triple op 3AC commands...");
    
    tac.Blank();
    
    return 0;
}
