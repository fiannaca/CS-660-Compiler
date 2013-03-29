#ifndef _CODEGEN_H_
#define _CODEGEN_H_

#include <string>
#include <fstream>
using namespace std;
class CodeGen
{
        ofstream fileToWrite;
        string commentStart; 
        string commentEnd; 
     public:
        CodeGen(const string &fileName);
        void SetCommentStart(string commentStart);
        void SetCommentEnd(string commentEnd); 
        void Emit(string &CodeToEmit);
        void WriteComment(string &comment);
        ~CodeGen()
        {
          fileToWrite.close();
        }
          

};
#endif
