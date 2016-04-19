

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
