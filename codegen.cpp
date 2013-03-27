#include "codegen.h"
#include <fstream>
CodeGen::CodeGen(const string &fileName)
{

    commentStart = "#";
    commentEnd = "" ; 
	fileToWrite.open(fileName.c_str());
    fileToWrite.clear(); 

}
void CodeGen::SetCommentStart(string commentStart)
{
	 this->commentStart = commentStart;
}
void CodeGen::SetCommentEnd(string commentEnd)
{
	 this->commentEnd = commentEnd; 
}

void CodeGen::WriteComment(string &comment)
{
      string commentString = commentStart + comment + commentEnd;
      fileToWrite<<commentString<<endl ;
      fileToWrite.flush(); 

}
void CodeGen::Emit(string &codeToEmit)
{
      fileToWrite<<codeToEmit<<endl;
      fileToWrite.flush();    
}

