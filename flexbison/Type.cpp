/*
 * See description in Type.h!
 */
 
#include "Type.h"

/*****************************************************************************/
/* Base Type Class - All types derive from this so that they can be referred */
/*                   to using Type* pointers                                 */
/*****************************************************************************/

Type::Type(string n, int s)
{
    name = n;
    size = s;
    t = BASE;
}

Type::Type(Type &t)
{
    name = t.name;
    size = t.size;
    this->t = t.t;
}

bool Type::CheckType(Type* rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(this->t == rhs->t)
    {
        switch(this->t)
        {
            case BASE: break;
            case PODTYPE:
                return ((PODType*)this)->CheckType((PODType*)rhs, isConvertable, t);
                break;
                
            case TYPEDEFTYPE:
                return ((TypedefType*)this)->CheckType((TypedefType*)rhs, isConvertable, t);
                break;
                
            case ENUMTYPE:
                return ((EnumType*)this)->CheckType((EnumType*)rhs, isConvertable, t);
                break;
                
            case ARRAYTYPE:
                return ((ArrayType*)this)->CheckType((ArrayType*)rhs, isConvertable, t);
                break;
                
            case STRUCTTYPE:
                return ((StructType*)this)->CheckType((StructType*)rhs, isConvertable, t);
                break;
                
            case UNIONTYPE:
                return ((UnionType*)this)->CheckType((UnionType*)rhs, isConvertable, t);
                break;
                
            case FUNCTIONTYPE:
                return ((FunctionType*)this)->CheckType((FunctionType*)rhs, isConvertable, t);
                break;
                
            case POINTERTYPE:
                return ((PointerType*)this)->CheckType((PointerType*)rhs, isConvertable, t);
                break;
        }
    }
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}
Type* Type::GetResultingType(CONVERSIONTYPE ct, bool castUp)
{
    if(castUp)
    {
        switch(ct)
        {
            case INT2FLT:
                return new Type("FLOAT", FLOAT_SIZE);
                break;
            case INT2DBL:
                return new Type("DOUBLE", DOUBLE_SIZE);
                break;
            case SHT2FLT:
                return new Type("FLOAT", FLOAT_SIZE);
                break;
            case SHT2DBL:
                return new Type("DOUBLE", DOUBLE_SIZE);
                break;
            case LNG2FLT:
                return new Type("FLOAT", FLOAT_SIZE);
                break;
            case LNG2DBL:
                return new Type("DOUBLE", DOUBLE_SIZE);
                break;
            case FLT2INT:
                return new Type("INT", INT_SIZE);
                break;
            case FLT2SHT:
                return new Type("SHORT", SHORT_SIZE);
                break;
            case FLT2LNG:
                return new Type("LONG", LONG_SIZE);
                break;
            case DBL2INT:
                return new Type("INT", INT_SIZE);
                break;
            case DBL2SHT:
                return new Type("SHORT", SHORT_SIZE);
                break;
            case DBL2LNG:
                return new Type("LONG", LONG_SIZE);
                break;
        }
    }
    else
    {
        switch(ct)
        {
            case INT2FLT:
                return new Type("INT", INT_SIZE);
                break;
            case INT2DBL:
                return new Type("INT", INT_SIZE);
                break;
            case SHT2FLT:
                return new Type("SHORT", SHORT_SIZE);
                break;
            case SHT2DBL:
                return new Type("SHORT", SHORT_SIZE);
                break;
            case LNG2FLT:
                return new Type("LONG", LONG_SIZE);
                break;
            case LNG2DBL:
                return new Type("LONG", LONG_SIZE);
                break;
            case FLT2INT:
                return new Type("FLOAT", FLOAT_SIZE);
                break;
            case FLT2SHT:
                return new Type("FLOAT", FLOAT_SIZE);
                break;
            case FLT2LNG:
                return new Type("FLOAT", FLOAT_SIZE);
                break;
            case DBL2INT:
                return new Type("DOUBLE", DOUBLE_SIZE);
                break;
            case DBL2SHT:
                return new Type("DOUBLE", DOUBLE_SIZE);
                break;
            case DBL2LNG:
                return new Type("DOUBLE", DOUBLE_SIZE);
                break;
        }
    }
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
    this->t = PODTYPE;
    is_signed = true; 
}

bool PODType::CheckType(PODType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    //Default the ref return values
    t = NONE;
    isConvertable = false;
    
    //Check if the types are the same or if conversion is possible
    if(name == rhs->name && size == rhs->size)
    {
        return true;
    }
    else
    {                
        if(name == "INT")
        {
            if(rhs->name == "FLOAT")
            {
                t = INT2FLT;
                isConvertable = true;
            }
            else if(rhs->name == "DOUBLE")
            {
                t = INT2DBL;
                isConvertable = true;
            }
        }
        else if(name == "SHORT")
        {
            if(rhs->name == "FLOAT")
            {
                t = SHT2FLT;
                isConvertable = true;
            }
            else if(rhs->name == "DOUBLE")
            {
                t = SHT2DBL;
                isConvertable = true;
            }
        }
        else if(name == "LONG")
        {
            if(rhs->name == "FLOAT")
            {
                t = LNG2FLT;
                isConvertable = true;
            }
            else if(rhs->name == "DOUBLE")
            {
                t = LNG2DBL;
                isConvertable = true;
            }
        }
        else if(name == "FLOAT")
        {
            if(rhs->name == "INT")
            {
                t = FLT2INT;
                isConvertable = true;
            }
            else if(rhs->name == "SHORT")
            {
                t = FLT2SHT;
                isConvertable = true;
            }
            else if(rhs->name == "LONG")
            {
                t = FLT2LNG;
                isConvertable = true;
            }
        }
        else if(name == "DOUBLE")
        {
            if(rhs->name == "INT")
            {
                t = DBL2INT;
                isConvertable = true;
            }
            else if(rhs->name == "SHORT")
            {
                t = DBL2SHT;
                isConvertable = true;
            }
            else if(rhs->name == "LONG")
            {
                t = DBL2LNG;
                isConvertable = true;
            }
        }
        else if(name == "CHAR")
        {
            t = CHARFLAG;
        }
        
        return false;
    }
}

/*****************************************************************************/
/* Typedef Type Class - This type allows for a type (or an object of a       */
/*                   class derived from Type) to be renamed. This points to  */
/*                   the actual type                                         */
/*****************************************************************************/
TypedefType::TypedefType(Type* actual, string tdname)
    : Type(*actual)
{
    this->t = TYPEDEFTYPE;
    typedefName = tdname;
    actualType = actual;
}

bool TypedefType::CheckType(TypedefType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}
        
/*****************************************************************************/
/* Enum Type Class - This type allows for the creation of enumerations       */
/*****************************************************************************/

EnumType::EnumType(string n, int startVal=0)
    : Type(n,INT_SIZE)
{
    this->t = ENUMTYPE;
    currentVal = startVal;
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

bool EnumType::CheckType(EnumType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}

/*****************************************************************************/
/* Array Type Class - This type allows for arrays of any type and dimension  */
/*                   to be created                                           */
/*****************************************************************************/
ArrayType::ArrayType(Type* baseType,string name,int dims)
    : Type(name,0)
{
    this->t = ARRAYTYPE;
    this->baseType = baseType; 
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

bool ArrayType::CheckType(ArrayType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}

/*****************************************************************************/
/* Struct Type Class - This type allows for structs to be created containing */
/*                   members of any predeclared type                         */
/*****************************************************************************/
StructType::StructType(string n)
    : Type(n,0)
{
    this->t = STRUCTTYPE;
}

void StructType::AddMember(string s, Type* t)
{
    //The name and type must be push (or popped) concurrently so that cooresponding
    // names and types are at the same index in the name and type vectors
    memberNames.push_back(s);
    memberTypes.push_back(t);

    //Accumulate the size of the sum of the component types in the struct
    size += t->GetSize(); 
}

bool StructType::MemberExists(string s)
{
    auto it = std::find(memberNames.begin(), memberNames.end(), s);

    if(it != memberNames.end())
        return true;
    else
        return false;
}

bool StructType::CheckType(StructType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}
        
/*****************************************************************************/
/* Union Type Class - This type allows for unions to be created containing   */
/*                   members of any predeclared type                         */
/*****************************************************************************/
UnionType::UnionType(string n)
    : Type(n,0)
{
    this->t = UNIONTYPE;    
}

void UnionType::AddMember(string s, Type* t)
{
    //The name and type must be push (or popped) concurrently so that cooresponding
    // names and types are at the same index in the name and type vectors
    memberNames.push_back(s);
    memberTypes.push_back(t);

    //Accumulate the size of the sum of the component types in the struct
    size += t->GetSize(); 
}

bool UnionType::MemberExists(string s)
{
    auto it = std::find(memberNames.begin(), memberNames.end(), s);

    if(it != memberNames.end())
        return true;
    else
        return false;
}

bool UnionType::CheckType(UnionType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}

/*****************************************************************************/
/* Function Type Class - This type allows for functions to be declared       */
/*                   containing parameters of any predeclared type           */
/*****************************************************************************/
FunctionType::FunctionType(string n)
    : Type(n,0)
{
    this->t = FUNCTIONTYPE;
}

void FunctionType::AddParam(Type* t)
{
    params.push_back(t);
}

void FunctionType::SetReturnType(Type* t)
{
    returnType = t;
}

bool FunctionType::CheckType(FunctionType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}

/*****************************************************************************/
/* Pointer Type Class - Allows for pointers to be created towards other      */
/*                      types.                                               */
/*****************************************************************************/
PointerType::PointerType(Type* base, bool baseIsPtr, string n)
    : Type(n,0)
{
    this->t = POINTERTYPE;
    
    baseType = base;
    

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
            :Type(n,0)  
{
    baseType = base;
    ptrDepth = d;
    
}


bool PointerType::CheckType(PointerType *rhs, bool &isConvertable, CONVERSIONTYPE &t)
{
    t = NONE;
    isConvertable = false;
    
    if(name == rhs->name && size == rhs->size)
        return true;
        
    return false;
}
        
Type* GetInnerType(Type *arrayOrPointer)
{
    Type *innerType = arrayOrPointer;
    while( innerType->GetName() == "POINTER" || innerType->GetName() == "ARRAY" )
    {
        if ( innerType->GetName() == "POINTER")
            innerType = ((PointerType *)innerType)->GetBase();
        else
            innerType = ((ArrayType*)innerType)->GetBase();   
    }   
    return innerType;  
}
