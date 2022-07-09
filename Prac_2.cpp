// Практическая работа 2, Вариант 15. Кирьяков Сергей КМБО-01-21.

#include <bits/stdc++.h>

using namespace std;

class MyArrayParent
{
protected:
	int capacity; // кол-во памяти
	int count; // размер
	double* ptr; // массив
public:

	MyArrayParent(int Dimension = 1000)
	{
		cout << "MyArrayParent constructor\n";
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}

	MyArrayParent(double* arr, int len)
	{
		cout << "MyArrayParent constructor\n";
		capacity = (len > 1000) ? len << 1 : 1000;
		count = len;
		ptr = new double[capacity];
		for (int i = 0; i < len; ++i)
        {
            ptr[i] = arr[i];
        }
	}

	MyArrayParent(const MyArrayParent& P) // Конструктор копий
	{
        cout << "Copy constructor\n";
		capacity = P.capacity;
		count = P.count;
		ptr = new double[capacity];
		for (int i = 0; i < count; ++i)
        {
            ptr[i] = P.ptr[i];
        }
	}

	~MyArrayParent()
	{
		cout << "MyArrayParent destructor\n";
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}

	int Capacity() { return capacity; }
	int Size() { return count; }

	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		return -1;
	}

	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
	}

	virtual void push(double value)
	{
	    if (count >= capacity)
        {
            capacity <<= 1;
        }
        ptr[count++] = value;
	}

	void RemoveLastValue()
	{
		if (count >= 0)
        {
            ptr[--count] = 0;
        }
	}

	double& operator[](int index)
	{
	    index = min(max(0, index), count - 1);
        return ptr[index];
	}

	MyArrayParent& operator=(const MyArrayParent& P)
	{
	    if (capacity != P.capacity)
        {
            delete[] ptr; // Удаляем старый участок памяти
            ptr = new double[P.capacity]; // Выделяем новый участок памяти
        }
        capacity = P.capacity;
        count = P.count;
        for (int i = 0; i < count; ++i)
        {
            ptr[i] = P.ptr[i];
        }
        return *this;
	}

	void print()
	{
		cout << "values: {";
		for (int i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
		cout << "\n";
	}
};

class MyArrayChild : public MyArrayParent
{
public:
	MyArrayChild(int Dimension = 1000) : MyArrayParent(Dimension) {}
	MyArrayChild(double* arr, int len) : MyArrayParent(arr, len) {}

	~MyArrayChild() {}

	void RemoveAt(int index = -1) // функция удаления из произвольного места
	{
	    if (index == -1)
        {
            return;
        }
        for (int i = index; i < count - 1; ++i)
        {
            ptr[i] = ptr[i + 1];
        }
        --count;
	}

	virtual int IndexOf(double value, bool bFindFromStart = true) // функция поиска
	{
        if (bFindFromStart)
        {
            int i = 0;
            for (; i < count && ptr[i] != value; ++i);
            if (i == count)
                return -1;
            else
                return i;
        }
        else
        {
            int i = count - 1;
            for (; i > -1 && ptr[i] != value; --i);
            if (i == -1)
                return -1;
            else
                return i;
        }
        // Возвращаем индекс элемента
	}

	void InsertAt(double value, int index = -1) // функция вставки
	{
	    if (count + 1 >= capacity)
        {
            capacity <<= 1;
        }
        if (index < 0 || index >= count)
        {
            push(value);
            return;
        }
        for (int i = count - 1; i >= index; --i)
        {
            ptr[i + 1] = ptr[i];
        }
        ptr[index] = value;
        ++count;
	}

	// выделение подпоследовательности
	MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)
	{
	    MyArrayChild P;
	    for (int i = StartIndex; i < count && Length > 0; --Length, ++i)
        {
            P.push(ptr[i]);
        }
        return P;
	}

	// Входной массив содержит 5-значные целые числа abcde. Поместить в выходной массив только те, у которых a * b = d * e = c
	MyArrayChild special_function()
	{
	    MyArrayChild P(capacity);
        for (int i = 0; i < count; ++i)
        {
            int n = ptr[i];
            int a = n / 10000, b = n / 1000 % 10, c = n / 100 % 10, d = n / 10 % 10, e = n % 10;
            if (a * b == d * e == c)
            {
                P.push(ptr[i]);
            }
        }
        return P;
	}
};

class MySortedArray : public MyArrayChild
{
public:
    MySortedArray(int Dimension = 1000) : MyArrayChild(Dimension) {}

	MySortedArray(double* arr, int len)
	{
	    capacity = (len > 1000) ? len << 1 : 1000;
		count = len;
		ptr = new double[capacity];
		for (int i = 0; i < len; ++i)
        {
            ptr[i] = arr[i];
        }
        sort(&ptr[0], &ptr[0] + count);
	}

	~MySortedArray() {}

	int IndexOf(double value) // перегрузка функции поиска
	{
	    // бин поиск за O(log n)
        int l = -1, r = count;
	    while (r - l > 1)
        {
            int mid = (r + l) / 2;
            if (ptr[mid] >= value)
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }
        if (r == count || ptr[r] != value)
        {
            // Такого элкемента нет в массиве
            // Возвращаем -1
            return -1;
        }
        return r;
        // Возвращаем индекс элемента
	}

	int bin_search (double value)
	{
	    // бин поиск за O(log n)
        int l = -1, r = count;
	    while (r - l > 1)
        {
            int mid = (r + l) / 2;
            if (ptr[mid] >= value)
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }
        return r;
        // Возвращаем индекс первого больше или равного элемента
	}

    void push (double value)
    {
        int ind = bin_search(value);
        InsertAt(value, ind);
    }
};


int32_t main()
{
    double a[] = {1, 3, 4, 2, 7, 8, 5, 9, 1, 2};
    MyArrayParent arr(a, 10);
    MyArrayParent* p = &arr;
    cout << p -> GetComponent(2) << "\n";
    p -> SetComponent(2, 0);
    cout << p -> GetComponent(2) << "\n";
    p -> push(32);
    cout << (*p)[10] << "\n";
    p -> RemoveLastValue();
    (*p).print();
    double a1[] = {11111, 12345, 54321, 12345, 12221, 21212, 65965};
    MySortedArray sort_arr(a1, 7);
    p = &sort_arr;
    p -> print();
    p -> push(1); p -> print(); // работа указателя на базовый класс
    ((MyArrayChild*)p) -> RemoveAt(8);
    ((MyArrayChild*)p) -> special_function().print();
    ((MySortedArray*)p) -> SubSequence(2, 3).print();
    // Эти функции не определенны в MyArrayParent поэтому используеться преобразование типа указателя
}

// Практическая работа 2, Вариант 15. Кирьяков Сергей КМБО-01-21.
