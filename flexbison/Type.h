//Base class for types and then derived classes for types of types (arrays and what not)
#include <string>
#include <list>
#include <vector>

using namespace std;

class Type
{
    public:
        Type(string n, int s); //sets the name and size of the type
        Type(Type &t);
        void GetName(string n) { return name; }
        int GetSize() { return size; }

    private:
        string name;
        int size; //Size of the type in bytes
}

class PODType : public Type //int (long, short, (un)signed), float, double, long double, char ((un)signed)
{
    public:
        PODType(string n, int s);
        bool isSigned() { return is_signed; }

    private:
        bool is_signed;
}

class TypedefType : public Type //any typedef
{
    public:
        TypedefType(Type* actual, string tdname); //Pointer to the actual type
        Type* GetActual() { return actualType; }
        string GetTypedefName() { return typedefName; }
    private:
        Type* actualType;
        string typedefName;
}

class ArrayType : public Type
{
    public:
        ArrayType(Type* baseType, int dims);
        int SetCapacity(int cap); //These must be set in the order of the dimensions (they are pushed onto the vector)
        int GetCapacity(int dim);

    private:
        Type* baseType;
        int dimensions;
        vector<int> capacities;
}

class StructType : public Type
{
    public:
        StructType(string n);
        void AddMember(string s, Type* t);
        bool MemberExists(string s);

    private:
        map<string, Type*> types;
}

class UnionType : public Type
{

}

class FunctionType : public Type
{

}

class PointerType : public Type
{

}
