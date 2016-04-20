
// test funcptr to lambda conversion in such pattern. Some old compiler may not compile the following code
// comment : direct lambda assignment to function ptr in the main() may still works for the same compilers, however.
using func_type = int();
struct A
{
    int foo(func_type* f)
    {
        return f();
    }
};

struct B
{
    int bar(A& a) 
    {
        return a.foo([](){return 42;});
    }
};

int main() 
{
    A a;
    B b;
    return (42==b.bar(a)) ? 0 : 1;
}
