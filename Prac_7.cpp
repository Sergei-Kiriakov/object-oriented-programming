// Практическая работа 7, Вариант 15. Кирьяков Сергей КМБО-01-21.

#include <bits/stdc++.h>

using namespace std;

class Fraction
{
protected:
    int p = 0, q = 1;
public:
    Fraction ()
    {
        p = 0;
        q = 1;
    }
    Fraction (string s)
    {
        int i = 0;
        p = 0;
        while(s[i] != '/')
        {
            p *= 10;
            p += s[i] - '0';
            ++i;
        }
        ++i;
        q = 0;
        while (i < s.size())
        {
            q *= 10;
            q += s[i] - '0';
            ++i;
        }
    }
    Fraction (int a, int b)
    {
        p = a;
        q = b;
    }
    Fraction operator= (Fraction a)
    {
        p = a.p;
        q = a.q;
        return (*this);
    }
    friend istream& operator>> (istream &ustream, Fraction &a);
    friend ostream& operator<< (ostream &ustream, Fraction &a);
};

istream& operator >> (istream& ustream, Fraction& a)
{
    string s;
    ustream >> s;
    a = Fraction(s);
    return ustream;
}

ostream& operator << (ostream& ustream, Fraction& a)
{
    cout << a.p << "/" << a.q << "\n";
    return ustream;
}

template<class T> void scanf(int n, T* a, ...)
{
    T* p = a;
	for (int i = 0; i < n; ++i)
    {
        cin >> *p;
        ++p;
    }
}

int main()
{
	Fraction Fa, Fb, Fc;
	int Ia;
	double Da;
	scanf<Fraction>(3, &Fa, &Fb, &Fc);
	scanf<int>(1, &Ia);
	scanf<double>(1, &Da);
	cout << Fa << Fb << Fc;
	cout << Ia << "\n";
	cout << Da << "\n";
}

// Практическая работа 7, Вариант 15. Кирьяков Сергей КМБО-01-21.
