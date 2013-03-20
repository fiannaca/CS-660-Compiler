#include "Type.h"

/*****************************************************************************/
/* Base Type Class - All types derive from this so that they can be referred */
/*                   to using Type* pointers                                 */
/*****************************************************************************/

Type::Type(string n, int s)
{
    name = n;
    size = s;
}

Type::Type(Type &t)
{
    name = t.name;
    size = t.size;
}

/*****************************************************************************/
/* Plain Old Data Type Class - These are the data types that come by default */
/*                   with the C programming language. These include:         */
/*                                                                           */
/*                   int, long int, short int (all either signed or unsigned)*/
/*                   float                                                   */
/*                   double, long double (both will be the same in this comp)*/
/*                   char, w_char (all either signed or unsigned             */
/*****************************************************************************/
PODType::PODType(string n, int s)
    : Type(n, s)
{
}

/*****************************************************************************/
/* Typedef Type Class - This type allows for a type (or an object of a       */
/*                   class derived from Type) to be renamed. This points to  */
/*                   the actual type                                         */
/*****************************************************************************/
TypedefType::TypedefType(Type* actual, string tdname)
    : Type(*actual)
{
    typedefName = tdname;
    actualType = actual;
}

/*****************************************************************************/
/* Enum Type Class - This type allows for the creation of enumerations       */
/*****************************************************************************/

EnumType::EnumType(string n, int startVal = 0)
{
    currentVal = startVal
}

int EnumType::GetConstVal(string s)
{
    return enumConsts[s];
}

void EnumType::AddEnumConst(string s)
{
    enumConsts[s] = currentVal;
    ++currentVal;
}

void EnumType::AddEnumConst(string s, int val)
{
    if(val >= currentVal)
    {
        enumConsts[s] = val;
        currentVal = val + 1;
    }
    else
    {
        enumConsts[s] = currentVal;
        currentVal++;
    }
}

/*****************************************************************************/
/* Array Type Class - This type allows for arrays of any type and dimension  */
/*                   to be created                                           */
/*****************************************************************************/
ArrayType::ArrayType(Type* baseType, int dims)
    : Type(*baseType);
{
    dimensions = dims;
}

int ArrayType::SetCapacity(int cap)
{
    capacities.push_back(cap);
}

int ArrayType::GetCapacity(int dim)
{
    if(dim < capacities.size())
        return capacities[dim];
    else
        return -1;
}

/*****************************************************************************/
/* Struct Type Class - This type allows for structs to be created containing */
/*                   members of any predeclared type                         */
/*****************************************************************************/
StructType::StructType(string n)
{
    name = n;
    size = 0;
}

void StructType::AddMember(string s, Type* t)
{
    //The name and type must be push (or popped) concurrently so that cooresponding
    // names and types are at the same index in the name and type vectors
    memberNames.push_back(s);
    memberTypes.push_back(t);

    //Accumulate the size of the sum of the component types in the struct
    size += t->size; 
}

bool StructType::MemberExists(string s)
{
    auto it = std::find(memberNames.begin(), memberNames.end(), s);

    if(it != memberNames.end())
        return true;
    else
        return false;
}

/*****************************************************************************/
/* Union Type Class - This type allows for unions to be created containing   */
/*                   members of any predeclared type                         */
/*****************************************************************************/
UnionType::UnionType(string n)
{
    name = n;
    size = 0;
}

void UnionType::AddMember(string s, Type* t)
{
    //The name and type must be push (or popped) concurrently so that cooresponding
    // names and types are at the same index in the name and type vectors
    memberNames.push_back(s);
    memberTypes.push_back(t);

    //Accumulate the size of the sum of the component types in the struct
    size += t->size; 
}

bool UnionType::MemberExists(string s)
{
    auto it = std::find(memberNames.begin(), memberNames.end(), s);

    if(it != memberNames.end())
        return true;
    else
        return false;
}

/*****************************************************************************/
/* Function Type Class - This type allows for functions to be declared       */
/*                   containing parameters of any predeclared type           */
/*****************************************************************************/
FunctionType::FunctionType(string n)
{
    name = n;
}

void FunctionType::AddParam(Type* t)
{
    params.push_back(t);
}

void FunctionType::SetReturnType(Type* t)
{
    returnType = t;
}

/*****************************************************************************/
/* Pointer Type Class - Allows for pointers to be created towards other      */
/*                      types.                                               */
/*****************************************************************************/
PointerType::PointerType(Type* base, bool baseIsPtr, string n)
{
    baseType = base;
    name = n;

    if(baseIsPtr)
    {
        ptrDepth = ((PointerType*)base)->ptrDepth + 1;
    }
    else
    {
        ptrDepth = 1;
    }
}

PointerType::PointerType(Type* base, string n, int d)
{
    baseType = base;
    ptrDepth = d;
    name = n;
}
