#pragma once

#define HAVE_STRUCT_TIMESPEC

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <sstream>
#include <cmath>
#include <pthread.h>
#include <chrono>
#include <time.h>
#include <queue>

#define optimize()                \
	ios_base::sync_with_stdio(0); \
	cin.tie(0);                   \
	cout.tie(0);

using namespace std;
using namespace std::chrono;

static int test_base[15] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
static int test_base_small[4] = { 2, 3, 5, 7 };

class UintN
{
private:
	string BigInt;
	friend struct arg;
	/**
	* Removes all occurrences of a character from the beginning of a string. This is useful for stripping characters from an end of a string that are not part of a string.
	* 
	* @param str - The string to remove the characters from. Must be non - null.
	* @param c - The character to remove. Must be non - null.
	* 
	* @return The string with the characters removed from the beginning of the string. If the character is not found the string is returned
	*/
	string remove_leading(string str, char c)
	{
		str.erase(0, str.find_first_not_of(c));
		return str;
	}

public:
	//Constructor
	UintN(string a);
	UintN(const UintN& a) : BigInt(a.BigInt) {}
	UintN(unsigned long long n)
	{
		do
		{
			BigInt.push_back(n % 10);
			n /= 10;
		} while (n);
	}
	UintN() { BigInt.push_back(0); }

	//Helper
	friend int size(const UintN& a) { return a.BigInt.size(); }
	friend bool Null(const UintN& a)
	{
		if (a.BigInt.size() == 1 && a.BigInt[0] == 0)
			return true;
		return false;
	}
	/**
	* Sum digits of a. This is used for summing the digits of an unsigned integer. The result is in big - endian format.
	* 
	* @param a - number to be summed ( BigInt )
	*/
	friend long long sum_digits(UintN a)
	{
		long long sum = 0;
		for (int i = a.BigInt.size() - 1; i >= 0; --i)
			sum += (short)a.BigInt[i];
		return sum;
	}
	friend bool sign_dividable_7(UintN a);
	friend bool sign_dividable_11(UintN a);

	//Assignment
	UintN& operator =(const UintN& a)
	{
		if (this != &a)
		{
			BigInt.erase();
			BigInt = a.BigInt;
		}
		return *this;
	}

	UintN& operator++();
	UintN operator++(int temp)
	{
		UintN aux = *this;
		++(*this);
		return aux;
	}
	UintN& operator--();
	UintN operator--(int temp)
	{
		UintN aux = *this;
		--(*this);
		return aux;
	}

	//Comparison
	friend bool operator<(const UintN&, const UintN&);
	friend bool operator<=(const UintN& a, const UintN& b)
	{
		return !(a > b);
	}
	friend bool operator>(const UintN& a, const UintN& b)
	{
		return b < a;
	}
	friend bool operator>=(const UintN& a, const UintN& b)
	{
		return !(a < b);
	}


	friend bool operator==(const UintN& a, const UintN& b)
	{
		return a.BigInt == b.BigInt;
	}
	friend bool operator!=(const UintN& a, const UintN& b)
	{
		return !(a == b);
	}

	// Cout
	//friend ostream& operator<<(ostream&, const UintN&);
	friend ostream& operator<<(ostream& out, const UintN& a)
	{
		string s;
		for_each(a.BigInt.rbegin(), a.BigInt.rend(), [&](char c) {
			s.push_back(c + '0');
			});
		return out << s;
	}

	//Summation
	UintN operator+(const UintN& b)
	{
		UintN temp;
		temp = *this;
		temp += b;
		return temp;
	}
	UintN& operator+=(const UintN&);

	//Subtraction
	UintN operator-(const UintN& b)
	{
		UintN temp;
		temp = *this;
		temp -= b;
		return temp;
	}
	UintN& operator-=(const UintN&);

	//Multiplication
	UintN operator*(const UintN& b)
	{
		UintN temp;
		temp = *this;
		temp *= b;
		return temp;
	}
	UintN& operator*=(const UintN&);

	//Division
	UintN operator/(const UintN& b)
	{
		UintN temp;
		temp = *this;
		temp /= b;
		return temp;
	}
	UintN& operator/=(const UintN&);

	//Mod
	UintN operator%(const UintN& b)
	{
		UintN temp;
		temp = *this;
		temp %= b;
		return temp;
	}
	UintN& operator%=(const UintN& b);

	friend bool PrimeNumber_MillerRabinsImprove(UintN&);					//Miller Rabin test

	friend void* ModularExponentiation(void* arg);

	friend UintN NextPrime(UintN a, UintN b)
	{
		UintN temp = a > b ? a : b;
		if (temp % 2 == 0)
		{
			++temp;
			if (PrimeNumber_MillerRabinsImprove(temp))
				return true;
		}
		temp += 2;
		while (!PrimeNumber_MillerRabinsImprove(temp))
			temp += 2;
		return temp;
	}
};

struct arg4mod
{
	UintN number, exponent, n;
	UintN res;
};

void* ModularExponentiation(void* arg);