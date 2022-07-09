// Практическая работа 6, Вариант 15. Кирьяков Сергей КМБО-01-21.

#include <bits/stdc++.h>

using namespace std;

class Equation
{
protected:
    double (*f)(double x);
    double step;
    double left, right;
public:
    Equation(double g(double x), double s, double l, double r)
    {
        f = g;
        step = s;
        left = l;
        right = r;
    }
    ~Equation() {};
    vector<double> Get_Solution ()
    {
        vector<double> ans;
        for (double i = left; i < right; i += step)
        {
            if (f(i) == 0)
            {
                ans.push_back(i);
            }
        }
        return ans;
    }
};

template<class T> class Element
{
protected:
    Element* next;
	Element* prev;
	T info;
public:
	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}
	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}
	Element(const Element& el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}
	template<class T1> friend ostream& operator<<(ostream& s, Element<T1>& el);

};

template<class T> ostream& operator<<(ostream& s, Element<T>& el)
{
	s << el.info;
	return s;
}

template<class T> class LinkedList
{
protected:
    Element<T>* head;
	Element<T>* tail;
	int count;
public:
	LinkedList<T>()
	{
		head = tail = nullptr;
		count = 0;
	}
	//деструктор
	virtual ~LinkedList<T>()
	{
	    Element<T>* q = head;
        for (Element<T>* p = head; p != nullptr; p = q)
        {
            q = p->next;
            delete p;
        }
        head = tail = nullptr;
		count = 0;
	}
	template<class T1> friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
};

template<class T> ostream& operator<<(ostream& s, LinkedList<T>& el)
{
    s << "{";
    Element<T>* p = el.head;
    while (p != NULL)
    {
        s << p->info << ", ";
        p = p->next;
    }
    s << "}";
    return s;
}

template<class T> class Stack : public LinkedList<T>
{
public:
    Stack<T>():LinkedList<T>() {}
    virtual ~Stack<T>() {}
    // удаление с начала, возвращает удаленный элемент
    // работает за O(1)
    virtual Element<T>* pop()
    {
        if (LinkedList<T>::count == 0)
            return nullptr;
        Element<T>* res = LinkedList<T>::head;
        if (LinkedList<T>::count == 1)
        {
            LinkedList<T>::head = LinkedList<T>::tail = nullptr;
        }
        else
        {
            LinkedList<T>::head = res->next;
        }
        LinkedList<T>::count--;
        return res;
    }
    // добавление в конец, возвращает добавленный элемент
    // работает за O(1)
    virtual Element<T>* push(T value)
    {
        if (LinkedList<T>::count == 0)
        {
            LinkedList<T>::tail = new Element<T>(value);
            LinkedList<T>::head = LinkedList<T>::tail;
        }
        else
        {
            Element<T>* newElem = new Element<T>(value);
            LinkedList<T>::tail->next = newElem;
            LinkedList<T>::tail = LinkedList<T>::tail->next;
        }
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }
};

template<class T> class Queue : public Stack<T>
{
public:
    Queue<T>() : Stack<T>() {};
    virtual ~Queue<T>() {};

    virtual Element<T>* pop()
    {
        if (LinkedList<T>::count == 0)
            return nullptr;
        Element<T>* res = LinkedList<T>::head;
        if (LinkedList<T>::count == 1)
        {
            LinkedList<T>::head = LinkedList<T>::tail = nullptr;
        }
        else
        {
            LinkedList<T>::head = res->next;
        }
        LinkedList<T>::count--;
        return res;
    }
    // добавление в конец, возвращает добавленный элемент
    // работает за O(1)
    virtual Element<T>* push(T value)
    {
        if (LinkedList<T>::count == 0)
        {
            LinkedList<T>::tail = new Element<T>(value);
            LinkedList<T>::head = LinkedList<T>::tail;
        }
        else
        {
            Element<T>* newElem = new Element<T>(value);
            LinkedList<T>::tail->next = newElem;
            LinkedList<T>::tail = LinkedList<T>::tail->next;
        }
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }
};

int32_t main()
{

}

// Практическая работа 6, Вариант 15. Кирьяков Сергей КМБО-01-21.
