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
/* Typedef Type Class - This type allows for an type (or an object of a      */
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
    types[s] = t;
    size += t->size; //Accumulate the size of the sum of the component types in the struct
}

bool StructType::MemberExists(string s)
{
    auto it = types.find(s);

    if(it != map::end)
        return true;
    else
        return false;
}

