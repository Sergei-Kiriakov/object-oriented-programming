#include <bits/stdc++.h>

using namespace std;

class A1
{
protected:
    int a1;
public:
    A1(int V1 = 0) { a1 = V1; cout << "Class A1 constructor\n";}
    virtual void print() { cout << "Variable of A1 class\n"; }
    virtual void show() { cout << "a1 = " << a1 << "\n"; }
};

class B1: virtual public A1
{
protected:
    int b1;
public:
    B1(int V1 = 0, int V2 = 0) : A1(V2) { b1 = V1; cout << "Class B1 constructor\n"; }
    virtual void print() { cout << "Variable of B1 class\n"; }
    virtual void show() { cout << "b1 = " << b1 <<", a1 =" << a1 << "\n"; }
};

class B2 : virtual public A1
{
protected:
    int b2;
public:
    B2(int V1 = 0, int V2 = 0) : A1(V2) { b2 = V1; cout << "Class B2 constructor\n"; }
    virtual void print() { cout << "Variable of B2 class\n"; }
    virtual void show() { cout << "b2 = " << b2 << ", a1 = " << a1 << "\n"; }
};

class B3 : virtual public A1
{
protected:
    int b3;
public:
    B3(int V1 = 0, int V2 = 0) : A1(V2) { b3 = V1; cout << "Class B3 constructor\n"; }
    virtual void print() { cout << "Variable of B3 class\n"; }
    virtual void show() { cout << "b3 = " << b3 << ", a1 = " << a1 << "\n"; }
};

class C1 : virtual public B1, virtual public B2, virtual public B3
{
protected:
    int c1;
public:
    C1(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0) : B1(V2), B2(V3), B3(V4) { c1 = V1; cout << "Class C1 constructor\n"; }
    virtual void print() { cout << "Variable of C1 class\n"; }
    virtual void show() { cout << "c1 = " << c1 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", a1 = " << a1 << "\n"; }
};

class C2 : virtual public B1, virtual public B2, virtual public B3
{
protected:
    int c2;
public:
    C2(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0) : B1(V2), B2(V3), B3(V4) { c2 = V1; cout << "Class C2 constructor\n"; }
    virtual void print() { cout << "Variable of C2 class\n"; }
    virtual void show() { cout << "c2 = " << c2 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", a1 = " << a1 << "\n"; }
};

class C3 : virtual public B1, virtual public B2, virtual public B3
{
protected:
    int c3;
public:
    C3(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0) : B1(V2), B2(V3), B3(V4) { c3 = V1; cout << "Class C3 constructor\n"; }
    virtual void print() { cout << "Variable of C3 class\n"; }
    virtual void show() { cout << "c3 = " << c3 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", a1 = " << a1 << "\n"; }
};

int main()
{
    B1 test(1, 2);
    test.show();
    test.print();
    A1* ptr = &test;
    ptr -> show();
    ptr -> print();
    C3 c3(1, 2, 3, 4);
    c3.print();
    c3.show();
    C2 c2(1, 5);
    c2.print();
    c2.show();
    char c;
    cin >> c;
    return 0;
}

// Практическая работа 3, вариант 15. Кирьяков Сергей КМБО-01-21.
