/*
 * This set of classes is used for storing descriptive type information for a given symbol. These classes store 
 * auxillary info such as the size of a data type or the capacity of an array. All Type classes derive from the
 * base Type class so that types can be associated with symbols using Type* vars.
 */
 
#ifndef _TYPE_H_
#define _TYPE_H_

#include "Platform.h"

#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

enum CONVERSIONTYPE {
    NONE,
    CHARFLAG,
    INT2FLT,
    INT2DBL,
    SHT2FLT,
    SHT2DBL,
    LNG2FLT,
    LNG2DBL,
    FLT2INT,
    FLT2SHT,
    FLT2LNG,
    DBL2INT,
    DBL2SHT,
    DBL2LNG
};

enum StorageSpecifiers {
	AUTO,
	REGISTER,
	STATIC,
	EXTERN,
	TYPEDEF
};

enum TypeQualifier {
	CONST,
	VOLATILE
};

enum BaseTypes {
	VOID,
	INT,
	SHORT,
	LONG,
	FLOAT,
	DOUBLE,
	CHAR
};

class Type
{
    public:
        enum DerivedType {
            BASE,
            PODTYPE,
            TYPEDEFTYPE,
            ENUMTYPE,
            ARRAYTYPE,
            STRUCTTYPE,
            UNIONTYPE,
            FUNCTIONTYPE,
            POINTERTYPE
        } t;
        
        Type(string n, int s); //sets the name and size of the type
        Type(Type &t);
        string GetName() { return name; }
        int GetSize() { return size; }
        void SetName(string n) { name  = n ; }
        bool CheckType(Type* rhs, bool &isConvertable, CONVERSIONTYPE &t);
        
        static Type* GetResultingType(CONVERSIONTYPE ct, bool castUp);
        
    protected:
        string name;
        int size; //Size of the type in bytes
};

class PODType : public Type //int (long, short, (un)signed), float, double, long double, char ((un)signed)
{
    public:
        PODType(string n, int s);
        bool isSigned() { return is_signed; }
        void SetSigned(bool isSigned) { is_signed = isSigned; } 
        bool CheckType(PODType *rhs, bool &isConvertable, CONVERSIONTYPE &t);
        
    protected:
        bool is_signed;
};

class TypedefType : public Type //any typedef
{
    public:
        TypedefType(Type* actual, string tdname); //Pointer to the actual type
        Type* GetActual() { return actualType; }
        string GetTypedefName() { return typedefName; }
        bool CheckType(TypedefType *rhs, bool &isConvertable, CONVERSIONTYPE &t);

    protected:
        Type* actualType;
        string typedefName;
};

class EnumType : public Type //provides the value for enum constants
{
    public:
        EnumType(string n, int startVal);
        int GetConstVal(string s); //returns the int value of a enum_constant
        void AddEnumConst(string s);
        void AddEnumConst(string s, int val);
        bool CheckType(EnumType *rhs, bool &isConvertable, CONVERSIONTYPE &t);

    protected:
        map<string, int> enumConsts; //The names of the enum_constants in the enum
        int currentVal;
};

class ArrayType : public Type //any array (any # of dimensions)
{
    public:
        ArrayType(Type* baseType,string name , int dims);
        int SetCapacity(int cap); //These must be set in the order of the dimensions (they are pushed onto the vector)
        int GetCapacity(int dim);
        Type *GetBase() { return baseType;}  
        void SetBase(Type *base) { this->baseType = base; } 
        bool CheckType(ArrayType *rhs, bool &isConvertable, CONVERSIONTYPE &t);
         
    protected:
        Type* baseType;
        int dimensions;
        vector<int> capacities;
};

class StructType : public Type //essential just a collection of types and names for each
{
    public:
        StructType(string n);
        void AddMember(string s, Type* t);
        bool MemberExists(string s);
        bool CheckType(StructType *rhs, bool &isConvertable, CONVERSIONTYPE &t);

    protected:
        vector<string> memberNames;
        vector<Type*> memberTypes;
};

class UnionType : public Type //currently the same as struct, may need more members later
{
    public:
        UnionType(string n);
        void AddMember(string s, Type* t);
        bool MemberExists(string s);
        bool CheckType(UnionType *rhs, bool &isConvertable, CONVERSIONTYPE &t);

    protected:
        vector<string> memberNames;
        vector<Type*> memberTypes;
};

class FunctionType : public Type //function type - allows for type checking when calling functions
{
    public:
        FunctionType(string n);
        void AddParam(Type* t);
        void SetReturnType(Type* t);
        int GetParamCount() { return params.size(); }
        Type* GetReturnType() { return returnType; }
        bool CheckType(FunctionType *rhs, bool &isConvertable, CONVERSIONTYPE &t);

    protected:
        vector<Type*> params;
        Type* returnType;
};

class PointerType : public Type //acts as a layer of indirection towards a predeclared type
{
    public:
        PointerType(Type* base, string n, int d);
        PointerType(Type* base, bool baseIsPtr, string n);
        Type* GetBase() { return baseType; }
        void SetBaseType( Type *base) { this->baseType = base; }  
        bool CheckType(PointerType *rhs, bool &isConvertable, CONVERSIONTYPE &t);
         
    protected:
        Type* baseType;
        int ptrDepth;
        
};

Type *GetInnerType(Type* arrayOrPointer); 
#endif 
