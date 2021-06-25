#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
using namespace std;
template
	<typename T> // Assume Vector only takes in int or double for T
class Vector {
private:
	int sz; 	// the number of elements in this Vector
	T* buf; 	// the base of the array of Ts, you must allocate it
public:
	Vector(int n) // Vector v1(10); -- create a 10 element Vector
	{
		sz = n;
		buf = new T[n];
		for (int i = 0; i < n; i++)
		{
			buf[i] = 0; 
		}
	}
	Vector(initializer_list<T> L) // Vector v1{T1, T2, T3};
	{
		sz = L.size();
		buf = new T[sz];
		int i = 0; 
		for (auto n : L)
		{
			buf[i] = n;
			i++;
		}
	}
	~Vector() // destructor called automatically when a Vector dies 
	{
		// Implementation Here;
		delete[] buf;
	}
	//Destructor should free memory used. your program should have no leak/lost/still-reachable/errors(suppressed or not), besides 72704 bytes in one still-reachable block (a g++/valgrind bug on some versions). */
	Vector(const Vector & v) // Vector v2(v1); deep-copy
	{
		sz = v.size(); 
		buf = new T[sz];
		for (int i = 0; i < sz; i++)
		{
			buf[i] = v.buf[i];
		}
	}
	int size() const // v1.size() returns 10 for v1 example above
	{
		return sz;
	}
	T & operator [] (const int i) // T x = V[i]; 
	{
		return buf[i];
	}
	/*Access out-of-bound index should throw an error to be caught in outside scope */
	T operator * (const Vector & v) const
	{
		T total = 0; 
		int numSize = (sz <= v.size() ? sz : v.size());
		for(int i = 0; i < numSize; i++)
		{
			total += buf[i] * v.buf[i];
		}
		return total;
	}
	// T x = V1 * V2; dot product
	// e.g. [1, 2] * [3, 4, 5] = 1 * 3 + 2 * 4 + 0 = 11
	// Assume an empty Vector will cause the product to be 0.
	Vector operator + (const Vector & v) const 
	// V3 = V1 + V2; [1, 2, 3] + [4, 5, 6, 7] = [5, 7, 9, 7]
	{	
		int resultSz = (v.sz >= sz ? v.sz : sz); 
		Vector<T> result(resultSz);

		for(int i = 0; i < resultSz; i++)
		{
			if(i< v.size())
			{
				result[i] = v.buf[i];
			}
			if(i < sz)
			{
				result[i] += buf[i];
			}
		}
		return result;
	}
	const Vector & operator = (const Vector & v) // V1 = V2;
	{
		sz = v.size(); 
		buf = new T[sz];
		for (int i = 0; i < sz; i++)
		{
			buf[i] = v.buf[i];
		}
		return *this;
	}
	bool operator == (const Vector & v) const // if (V1 == V2)...
	{
		if (sz == v.size())
		{
			for (int i = 0; i < sz; i++)
			{
				if(buf[i] != v.buf[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	bool operator != (const Vector & v) const // if (V1 != V2)...
	{
		if (sz == v.size())
		{
			for (int i = 0; i < sz; i++)
			{
				if(buf[i] != v[i])
				{
					return true;
				}
			}
			return false;
		}
		return true;
	}
	friend Vector operator * (const int n, const Vector & v)
	// V1 = 20 * V2; -- each element of V1 is element of V2 * 20
	{
		Vector<T> result(v.size());
		for (int i = 0; i < v.size(); i++)
		{
			result[i] = v.buf[i] * n;
		}
		return result;
	}
	friend Vector operator + (const int n, const Vector & v)
	// V1 = 20 + V2; -- each element of V1 is element of V2 + 20
	{
		Vector<T> result(v.size());
		for (int i = 0; i < v.size(); i++)
		{
			result[i] = v.buf[i] + n;
		}
		return result;
	}
	friend ostream& operator << (ostream & o, const Vector & v)
	// cout << V2; -- prints the vector in this format 
	// (v0, v1, v2, ... vn-1);
	{
		o << "(";
		for (int i = 0; i < v.size(); i++)
		{
			o << v.buf[i];
			if(i != v.size() - 1)
			{
				o << ",";
			}
			else 
			{
				o << ")";
			}
		}
		return o;
	}
};
#endif
