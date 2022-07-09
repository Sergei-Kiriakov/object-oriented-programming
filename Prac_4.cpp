#include <bits/stdc++.h>

using namespace std;

class BaseString
{
protected:
    char* p; int len; int capacity;
public:
    BaseString(char* ptr)
    {
        cout << "Base Constructor 1\n";
        len = strlen(ptr) + 1;
        capacity = 256;
        p = new char[capacity];
        for(int i = 0; i < len; i++)
        {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }
    BaseString(int Capacity = 256)
    {
        cout << "Base Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }
    ~BaseString()
    {
        cout << "Base Destructor\n";
        if(p != NULL)
            delete[] p;
        len = 0;
        capacity = 0;
    }
    int Length() { return len; }
    int Capacity() { return capacity; }
    char& operator[] (int i) { return p[i]; }
    BaseString& operator=(BaseString& s)
    {
        cout << "Base Operator = \n";
        len = s.Length();
        p = new char[s.capacity];
        capacity = s.capacity;
        for(int i = 0; i < s.Length(); i++)
        {
            p[i] = s[i];
        }
        p[len - 1] = '\0';
        return *this;
    }
    BaseString(BaseString& s)
    {
        cout << "Base Copy Constructor\n";
        len = s.Length();
        p = new char[s.capacity];
        capacity = s.capacity;
        for(int i = 0; i < s.Length() - 1; i++)
        {
            p[i] = s[i];
        }
        p[len - 1] = '\0';
    }
    virtual void print()
    {
        int i = 0;
        while(p[i] != '\0')
        {
            cout << p[i];
            i++;
        }
        cout << "\n";
    }
};

class ChildString : public BaseString
{
public:
    ChildString(char* ptr) : BaseString(ptr) {}
    ChildString(int Dimension) : BaseString(Dimension) {}

    ~ChildString()
    {
        cout << "Child Destructor\n";
        if(p != NULL)
            delete[] p;
        len = 0;
    }

    int count_words ()
    {
        int cnt = 0;
        bool has_numbers = false;
        int l = 0, r = 0;
        for (int i = 0; i < len; ++i)
        {
            if (p[i] == ' ' || p[i] == ',' || p[i] == '.' || p[i] == '?' || p[i] == ';' || p[i] == ':')
            {
                r = i;
                if (r - l >= 3 && !has_numbers)
                {
                    ++cnt;
                }
                l = r + 1;
                has_numbers = false;
            }
            if (p[i] >= '0' && p[i] <= '9')
            {
                has_numbers = true;
            }
        }
        r = len;
        if (r - l >= 3 && !has_numbers)
        {
            ++cnt;
        }
        return cnt;
    }
};

int main()
{
    //"abacaba: test3 lol 123 p,,? hello. pearl"
    char s[] = "abacaba: test3 lol 123 p,,? hello. pearl asd 993";
    ChildString P(s);
    cout << P.count_words() << "\n";
    P.print();
    return 0;
}

// Практическая работа 3, вариант 15. Кирьяков Сергей КМБО-01-21.
