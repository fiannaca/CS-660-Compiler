#include "FunctionTable.h"

int FunctionTable::GetStackSpace(string name)
{
	auto it = functions.find(name);
	
	if(it != functions.end())
	{
		return it->second->stackSpace;
	}
	else
	{
		return -1;
	}
}

void FunctionTable::AddFunction(string fname, bool hasReturn)
{
	Function* func = new Function;
	
	func->name = fname;
	func->hasReturn = hasReturn;
	func->stackSpace = 0;
	
	functions[fname] = func;
}

Function* FunctionTable::GetFunction(string name)
{
	auto it = functions.find(name);
	
	if(it != functions.end())
	{
		return it->second;
	}
	else
	{
		cout << "FunctionTable Error: I couldn't find the requested function" << endl;
		return NULL;
	}
}

void FunctionTable::AddVariable(string fname, string vname, int size)
{
	Function* func = GetFunction(fname);
	
	if(func)
	{
		func->variables.push_back(pair<string, int>(vname, func->stackSpace));
		func->stackSpace += size;
	}
}

void FunctionTable::AddParameter(string fname, string pname, bool byValue)
{	
	Function* func = GetFunction(fname);
	
	if(func)
	{
		Parameter* param = new Parameter;
	
		param->name = pname;
		param->byValue = byValue;
		param->byRegister = true;
		
		stringstream ss;
		ss << "$a" << func->parameters.size();
		
		param->regName = ss.str();
		
		func->parameters.push_back(param);
	}
}

Parameter* FunctionTable::LookupParameter(string fname, string pname)
{
	Function* func = GetFunction(fname);
	
	if(func)
	{
		for(auto it = func->parameters.begin(); it != func->parameters.end(); ++it)
		{
			if((*it)->name == pname)
				return (*it);
		}
	}
	
	return NULL;
}

int FunctionTable::GetVarOffset(string fname, string vname)
{
	Function* func = GetFunction(fname);
	
	if(func)
	{
		for(auto it = func->variables.begin(); it != func->variables.end(); ++it)
		{
			if(it->first == vname)
				return it->second;
		}
		
		return -1;
	}
}
















