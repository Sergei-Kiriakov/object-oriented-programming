#include <bits/stdc++.h>

using namespace std;

class Vector
{
private:
    double x, y, z;

public:
    Vector () { x = 0; y = 0; z = 0; }
    Vector (double a) { x = a; y = a; z = a; }
    Vector (double a, double b, double c) { x = a; y = b; z = c; }

    void print() { cout << x << " " << y << " " << z << endl; }

    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
};

class Point
{
private:
    double x, y, z;

public:
    Point() { x = 0; y = 0; z = 0; }

    Point(double a) { x = a; y = a; z = a; }

    Point(double a, double b, double c) { x = a; y = b; z = c; }

    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }

    void setX(double a) {x = a; }
    void setY(double a) {y = a; }
    void setZ(double a) {z = a; }

    void print() { cout << x << " " << y << " " << z << endl; }

    Point operator+ (Vector a) { return Point(a.getX() + x, a.getY() + y, a.getZ() + z); }

    Point operator+ (double a) { return Point(x + a, y + a, z + a); }

    Point operator- (Vector a) { return Point(a.getX() + x, a.getY() + y, a.getZ() + z); }

    Point operator- (double a) { return Point(x - a, y - a, z - a); }

    double operator* () {return x; } // �������� �� ��� x

    double operator& () {return sqrt(x * x + y * y); } // �������� �� ��������� OXY

    friend Point operator+ (double a, Point b);
};

Point operator+ (double a, Point b)
{
    return Point(b.x + a, b.y, b.z);
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0), cerr.tie(0);
    Point A(4, 3, 5);
    cout << *A << "\n"; // �������� �� ��� x
    cout << &A << "\n"; // �������� �� ��������� OXY
    Vector B(1, 1, 1);
    Point C = A + B; // �������� ����� � �������
    C.print(); // ����� ����������
    Point D = 4 + A; // �������� ����� � �����
    D.print(); // ����� ����������
}

// ������������ ������ 1, ������� 15. �������� ������ ����-01-21.
