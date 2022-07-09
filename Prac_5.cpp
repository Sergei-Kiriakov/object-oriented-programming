// Практическая работа 5, Вариант 15. Кирьяков Сергей КМБО-01-21.

#include <bits/stdc++.h>

using namespace std;

class Exception: public std::exception
{
protected:
    //сообщение об ошибке
    char* str;
public:
    Exception()
	{
		str = nullptr;
	}

    Exception(const char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    // конструктор копий
    Exception(const Exception& e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }

	// деструктор
	virtual ~Exception()
	{
		delete[] str; str = nullptr;
	}

	virtual void print()
	{
		cout << "{Exception}: " << str << "; " << std::exception::what() << "\n";
	}
};

class IndexOutOfBounds : public Exception
{
protected:
	int ind_row;
	int ind_column;
public:

	// конструктор
	IndexOutOfBounds(const char *s, const int &row, const int &column) : Exception(s)
	{
		ind_row = row;
		ind_column = column;
	}

	// конструктор копий
	IndexOutOfBounds(const IndexOutOfBounds &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
		ind_row = e.ind_row;
		ind_column = e.ind_column;
	}

	// деструктор
	~IndexOutOfBounds() = default;

	virtual void print()
	{
	    cout << str << "Index out of range, row: " << ind_row << " column: " << ind_column << "\n";
    }
};

class WrongDimension : public  Exception
{
public:
	// конструктор
	WrongDimension(const char* s) : Exception(s) {}

	// деструктор
	~WrongDimension() {}
};

class WrongSize : public WrongDimension
{
protected:
	int size_row; int size_column;
public:
	WrongSize(const char *s, const int &r, const int &c) : WrongDimension(s)
	{
		size_row = r;
		size_column = c;
	}

	~WrongSize() = default;

	void print()
	{
		cout << str << "WrongSize, size_row: " << size_row << " size_column " << size_column << "\n";
	}
};

template<class T> class BaseMatrix
{
protected:
	T** ptr;
	int rows;
	int columns;
public:
	BaseMatrix<T>(int r = 2, int c = 2)
	{
	    if (r < 0 || c < 0)
            throw WrongSize("BaseMatrix<T>(int r = 2, int c = 2): ",  r, c);
		rows = r;
		columns = c;
		ptr = new T* [rows];
		for (int i = 0; i < rows; i++)
		{
			ptr[i] = new T [columns];
		}
	}

	BaseMatrix<T>(const BaseMatrix<T> &M)
	{
		rows = M.rows;
		columns = M.columns;
		ptr = new T* [rows];
		for (int i = 0; i < rows; i++)
		{
			ptr[i] = new T [columns];
			for (int j = 0; j < columns; j++)
			{
				ptr[i][j] = M.ptr[i][j];
			}
		}
	}

	~BaseMatrix<T>()
	{
		if (ptr != nullptr)
		{
			for (int i = 0; i < rows; i++)
            {
                delete[] ptr[i];
            }
			delete[] ptr;
			ptr = nullptr;
			rows = columns = 0;
		}
	}

	int GetColumns() { return columns; }
	int GetRows() { return rows; }

	void SetValue(int r, int c, int value)
	{
		if (r < 0 || c < 0 || r >= rows || c >= columns)
		{
			throw IndexOutOfBounds("SetValue(int r, int c, int value): ", r, c);
		}
		else
        {
            ptr[r][c] = value;
        }
	}

	void print()
	{
		for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << ptr[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
	}

	T* operator() (int r, int c)
	{
		if (r < 0 || c < 0 || c >= columns || r >= rows)
		{
		    throw IndexOutOfBounds("operator() (int r, int c): ", rows, columns);
		}
        return &ptr[r][c];
	}

	bool operator== (BaseMatrix<T> M)
	{
        if (M.rows != rows || M.columns != columns)
        {
            return false;
        }
        bool ans = true;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (ptr[i][j] != M.ptr[i][j])
                    return false;
            }
        }
        return true;
	}

	BaseMatrix<T> operator= (BaseMatrix<T> M)
	{
        if (M.rows != rows || M.columns != columns)
        {
            for (int i = 0; i < rows; ++i)
            {
                delete[] ptr[i];
                ptr[i] = nullptr;
            }
            delete ptr;
            ptr = nullptr;
            rows = M.rows;
            columns = M.columns;
            ptr = new T* [rows];
            for (int i = 0; i < rows; ++i)
            {
                ptr[i] = new T [columns];
            }
        }
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                ptr[i][j] = M.ptr[i][j];
            }
        }
        return (*this);
	}

	template<class T1> friend ostream& operator<< (ostream &ustream, const BaseMatrix<T1> obj);
	template<class T1> friend istream& operator>> (istream &ustream, BaseMatrix<T1> &obj);
};

template<class T> class ChildMatrix : public BaseMatrix<T>
{
public:
	ChildMatrix<T> (int r = 2, int c = 2) : BaseMatrix<T>(r, c) {}

	ChildMatrix<T> (const ChildMatrix<T> &M) : BaseMatrix<T> (M) {}

	~ChildMatrix<T>() {};

	// заполняем матрицу случайными значениями от 0 до 9
	// такой маленький разброс, чтобы было больше нулей
	ChildMatrix<T> RandFill()
	{
	    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	    uniform_int_distribution <int> range(0, 9);

		for (int i = 0; i < BaseMatrix<T>::rows; i++)
		{
			for (int j = 0; j < BaseMatrix<T>::columns; j++)
			{
				BaseMatrix<T>::ptr[i][j] = range(rng);
			}
		}
		return (*this);
	}

	ChildMatrix<T> del_zero_rows()
	{
		ChildMatrix<T> res(*this);
		int r = res.rows;
		for (int i = 0; i < res.rows; ++i)
        {
            int cnt_zeros = 0;
            for (int j = 0; j < res.columns; ++j)
            {
                if (res.ptr[i][j] == 0)
                    ++cnt_zeros;
            }
            if (cnt_zeros > 0)
            {
                delete[] res.ptr[i];
                res.ptr[i] = nullptr;
                --r;
            }
        }
        ChildMatrix<T> ans(r, res.columns);
        int last_ind = 0;
        for (int i = 0; i < res.rows; ++i)
        {
            if (res.ptr[i] != nullptr)
            {
                for (int j = 0; j < res.columns; ++j)
                {
                    ans.ptr[last_ind][j] = res.ptr[i][j];
                }
                ++last_ind;
            }
        }
		return ans;
	}
};

template<class T> ostream& operator<< (ostream& ustream, BaseMatrix<T> obj)
{
    //ustream<<my_manip;
    ustream << obj.rows << " " << obj.columns << "\n";
    for (int i = 0; i < obj.rows; i++)
    {
        for (int j = 0; j < obj.columns; j++)
        {
            ustream << obj.ptr[i][j] << " ";
        }
        ustream << "\n";
    }
    return ustream;
}

template<class T> istream& operator >> (istream& ustream, BaseMatrix<T>& obj)
{
    int r, c;
    ustream >> r >> c;
    BaseMatrix<T> A(r, c);
    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < A.columns; j++)
            ustream >> A.ptr[i][j];
    obj = A;
    return ustream;
}

ostream& my_manip(ostream& s)
{
    s.precision(4);
    s.fill('%');
    s.width(10);
    return s;
}

int32_t main()
{
	// Задание 5.1
	cout << "Testing Part 1: " << "\n";
	{ // тест 1
	    cout << "Test 1:" << "\n";
	    ChildMatrix<int> test(4, 4);
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                test.SetValue(i, j, 1);
            }
        }
        test.print();
        ChildMatrix<int> ans = test.del_zero_rows();
        ans.print();
	}
	{ // тест 2
	    cout << "Test 2:" << "\n";
	    ChildMatrix<int> test(5, 3);
        test.RandFill();
        test.print();
        ChildMatrix<int> ans = test.del_zero_rows();
        ans.print();
	}
	cout << "End of testing part 1" << "\n";
	cout << "----------------------------------" << "\n\n";

	// Задание 5.2
	cout << "Testing Part 2: " << "\n";
	{ //тест 1
	    cout << "Test 1:" << "\n";
	    BaseMatrix<int> test(4, 4);
        try
        {
            cout << test(5, 5);
            // Пытемся получить элемент test.ptr[5][5]	
        }
        catch (IndexOutOfBounds e)
        {
            e.print();
        }
	}
	{ // тест 2
	    cout << "Test 2:" << "\n";
        try
        {
            BaseMatrix<int> test(-2, -2);
            // Пытемся создать матрицу с отрицательными размерами
        }
        catch (WrongSize e)
        {
            e.print();
        }
	}
	cout << "End of testing part 2" << "\n";
	cout << "----------------------------------" << "\n\n";

	// Задание 5.3
	cout << "Testing Part 3: " << "\n";
	ofstream fout("output.txt");
    ChildMatrix<int> test1(4, 4), test2(5, 5);
    test1.RandFill(); test2.RandFill();
    fout << test1 << test2;
    fout.close();
    ifstream fin("output.txt");
    ChildMatrix<int> test3, test4;
    fin >> test3 >> test4;
    test1.print();
    test3.print();
    test2.print();
    test4.print();
    cout << (test1 == test3) << "\n";
    // Выведем 1 если test1 == test3

    cout << (test2 == test4) << "\n";
    // Выведем 1 если test2 == test4

    cout << "End of testing part 3" << "\n";
	cout << "----------------------------------" << "\n\n";
}

// Практическая работа 5, Вариант 15. Кирьяков Сергей КМБО-01-21.
