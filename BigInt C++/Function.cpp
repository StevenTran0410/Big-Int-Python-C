#include "Header.h"

//string remove_leading(string str, char c)
//{
//	for (auto i = str.begin(); i != str.end(); i++)
//		if (*i != c)
//			return string(i, str.end());
//	return string();
//}

UintN::UintN(string s)
{
	BigInt = "";
	string temp = remove_leading(s, '0');
	if (temp.size() == 0)
		temp = "0";
	int n = temp.size();
	for (int i = n - 1; i >= 0; --i)
	{
		if (!isdigit(temp[i]))
			throw("Not a valid number");
		BigInt.push_back(temp[i] - '0');
	}
}

bool operator<(const UintN& a, const UintN& b)
{
	size_t n = size(a), m = size(b);
	if (n != m)
		return n < m;
	while (n--)
		if (a.BigInt[n] != b.BigInt[n])
			return a.BigInt[n] < b.BigInt[n];
	return false;
}

UintN& UintN::operator++()
{
	size_t i, n = BigInt.size();
	for (i = 0; i < n && BigInt[i] == 9; ++i)
		BigInt[i] = 0;
	if (i == n)
		BigInt.push_back(1);
	else
		BigInt[i]++;
	return *this;
}

UintN& UintN::operator--()
{
	if (BigInt[0] == 0 && BigInt.size() == 1)
		throw("UNDERFLOW");
	size_t i, n = BigInt.size();
	for (i = 0; BigInt[i] == 0 && i < n; ++i)
		BigInt[i] = 9;
	BigInt[i]--;
	if (n > 1 && BigInt[n - 1] == 0)
		BigInt.pop_back();
	return *this;
}

UintN& UintN::operator+=(const UintN& b)
{
	size_t t = 0, s;
	size_t n = size((*this)), m = size(b);
	if (m > n)
		(*this).BigInt.append(m - n, 0);
	n = size((*this));
	for (size_t i = 0; i < n; ++i)
	{
		if (i < m)
			s = (*this).BigInt[i] + b.BigInt[i] + t;
		else
			s = (*this).BigInt[i] + t;
		t = s / 10;
		(*this).BigInt[i] = (s % 10);
	}
	if (t)
		(*this).BigInt.push_back(t);
	return (*this);
}

UintN& UintN::operator-=(const UintN& b)
{
	size_t n = size((*this)), m = size(b);
	int t = 0, s;
	for (size_t i = 0; i < n; ++i)
	{
		if (i < m)
			s = (*this).BigInt[i] - b.BigInt[i] + t;
		else
			s = (*this).BigInt[i] + t;
		if (s < 0)
			s += 10, t = -1;
		else
			t = 0;
		(*this).BigInt[i] = s;
	}
	while (n > 1 && (*this).BigInt[n - 1] == 0)
	{
		(*this).BigInt.pop_back();
		--n;
	}
	return (*this);
}

UintN& UintN::operator*=(const UintN& b)
{
	if (Null((*this)) || Null(b))
	{
		(*this) = UintN();
		return (*this);
	}
	size_t n = (*this).BigInt.size(), m = b.BigInt.size();
	int* v = new int[n + m]();
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
			v[i + j] += ((*this).BigInt[i]) * (b.BigInt[j]);

	n += m;
	(*this).BigInt.resize(n);
	for (size_t s, i = 0, t = 0; i < n; ++i)
	{
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		(*this).BigInt[i] = v[i];
	}
	for (int i = n - 1; i >= 1 && !v[i]; --i)
		(*this).BigInt.pop_back();
	delete[] v;
	return (*this);
}

UintN& UintN::operator/=(const UintN& b)
{
	if ((*this) < b)
	{
		(*this) = UintN();
		return (*this);
	}
	if ((*this) == b)
	{
		(*this) = UintN(1);
		return (*this);
	}
	size_t i, lgcat = 0;
	int cc;
	const size_t n = size((*this));
	int* cat = new int[n]();
	UintN t;
	for (i = n - 1; t * 10 + (*this).BigInt[i] < b; --i)
	{
		t *= 10;
		t += (*this).BigInt[i];
	}
	for (; i != 4294967295; --i)
	{
		t = t * 10 + (*this).BigInt[i];
		for (cc = 9; UintN(cc) * b > t; cc--)
			;
		t -= UintN(cc) * b;
		cat[lgcat++] = cc;
	}
	(*this).BigInt.resize(n);
	for (i = 0; i < lgcat; ++i)
		(*this).BigInt[i] = cat[lgcat - i - 1];
	(*this).BigInt.resize(lgcat);
	delete[] cat;
	return (*this);
}

UintN& UintN::operator%=(const UintN& b)
{
	if ((*this) < b)
	{
		return (*this);
	}
	if ((*this) == b)
	{
		(*this) = UintN();
		return (*this);
	}
	size_t i, cc;
	const size_t n = size((*this));
	UintN t;
	for (i = n - 1; t * 10 + (*this).BigInt[i] < b; --i)
	{
		t *= 10;
		t += (*this).BigInt[i];
	}
	for (; i != 4294967295; --i)
	{
		t = t * 10 + (*this).BigInt[i];
		for (cc = 9; UintN(cc) * b > t; --cc)
			;
		t -= UintN(cc) * b;
	}
	(*this) = t;
	return (*this);
}

// ostream& operator<<(ostream& out, const UintN&	a)
// {
// 	for (size_t i = a.BigInt.size() - 1; i != 4294967295; i--)
// 		cout << (short)a.BigInt[i];
// 	return cout;
// }

void* ModularExponentiation(void* arg)
{
	struct arg4mod* a = (struct arg4mod*)arg;
	UintN n = a->n;
	UintN number = a->number;
	UintN exponent = a->exponent;

	if (n < 2)
		throw("Cannot perform a modulo operation against number less than 2");

	if (number == 0)
		a->res = number;
	if (number >= n)
		number %= n;

	UintN res = UintN(1);
	while (exponent > 0)
	{
		if (exponent % 2 == 1)
			res = (res * number) % n;
		exponent /= 2;
		number = (number * number) % n;
	}
	a->res = res;
	pthread_exit(0);
}

bool sign_dividable_7(UintN a)
{
	long long res = short(a.BigInt[a.BigInt.size() - 1]) * 3;
	for (int i = a.BigInt.size() - 2; i >= 0; --i)
	{
		while (res > 7)
			res -= 7;
		res += short(a.BigInt[i]);
		res *= 3;
	}
	return res % 7 == 0;
}

bool sign_dividable_11(UintN a)
{
	long long even = 0;
	long long odd = 0;
	for (int i = a.BigInt.size() - 1; i >= 0; --i)
	{
		if (i % 2 == 0)
			even += short(a.BigInt[i]);
		else
			odd += short(a.BigInt[i]);
	}
	return abs(even - odd) % 11 == 0;
}

bool PrimeNumber_MillerRabinsImprove(UintN& number)
{
	if (number == 2)
		return true;
	else if (number < 2 || short(number.BigInt[0]) % 2 == 0 || (sum_digits(number) % 3 == 0 && number > 3) || (short(number.BigInt[0]) == 5 && number > 5) || sign_dividable_7(number) || sign_dividable_11(number))
		return false;
	else if (number <= 7)
		return true;

	int n = size(number);
	int index;
	vector<int> list_base;
	if (n < 3)
	{
		index = 1;
		list_base.push_back(test_base_small[rand() % 4]);
	}
	else
	{
		if (n < 5)
		{
			index = 1;
			list_base.push_back(test_base[rand() % 20]);
		}
		else
		{
			if (n < 13)
				index = n / 2 - 1;
			else
			{
				index = n / 2;
				if (index > 10)
					index = 5;
			}
			int index_base = rand() % 20;
			for (int i = 0; i < index; ++i)
			{
				list_base.push_back(test_base[index_base]);
				index_base += 4;
				if (index_base >= 15)
					index_base -= 15;
			}
		}
	}

	UintN d = number - 1;
	UintN comparision = number - 1;
	int num_exponent = 0;
	while (short(d.BigInt[0]) % 2 == 0)
	{
		++num_exponent;
		d /= 2;
	}
	bool flag = true;
	struct arg4mod* args_1 = new arg4mod[index];
	pthread_t* tids_1 = new pthread_t[index];
	for (int i = 0; i < index; ++i)
	{
		args_1[i].number = UintN(list_base[i]);
		args_1[i].exponent = d;
		args_1[i].n = number;

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids_1[i], &attr, ModularExponentiation, &args_1[i]);
		pthread_attr_destroy(&attr);
	}
	for (int i = 0; i < index; ++i)
		pthread_join(tids_1[i], NULL);

	vector<int> index_wrong;
	for (int i = 0; i < index; ++i)
		if (args_1[i].res != 1 && args_1[i].res != comparision)
			index_wrong.push_back(i);

	delete[] args_1;
	delete[] tids_1;

	if (index_wrong.size())
		flag = false;
	else
		return true;

	if (num_exponent < 13)
	{
		struct arg4mod* args_2 = new arg4mod[index_wrong.size() * (num_exponent - 1)];
		pthread_t* tids_2 = new pthread_t[index_wrong.size() * (num_exponent - 1)];
		for (int i = 0; i < index_wrong.size(); ++i)
			for (int r = 0; r < num_exponent - 1; ++r)
			{
				UintN number_base = UintN(list_base[index_wrong[i]]);
				args_2[i * (num_exponent - 1) + r].number = number_base;
				long long temp = pow(2, r + 1);
				UintN exponent = UintN(temp) * d;
				args_2[i * (num_exponent - 1) + r].exponent = exponent;
				args_2[i * (num_exponent - 1) + r].n = number;

				pthread_attr_t attr;
				pthread_attr_init(&attr);
				pthread_create(&tids_2[i * (num_exponent - 1) + r], &attr, ModularExponentiation, &args_2[i * (num_exponent - 1) + r]);
				pthread_attr_destroy(&attr);
			}

		for (int i = 0; i < index_wrong.size(); ++i)
			for (int r = 0; r < num_exponent - 1; ++r)
				pthread_join(tids_2[i * (num_exponent - 1) + r], NULL);

		for (int i = 0; i < index_wrong.size(); ++i)
		{
			for (int r = 0; r < num_exponent - 1; ++r)
			{
				if (args_2[i * (num_exponent - 1) + r].res != 1 && args_2[i * (num_exponent - 1) + r].res != comparision)
					flag = false;
				else
				{
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				delete[] args_2;
				delete[] tids_2;
				return flag;
			}
		}
		delete[] args_2;
		delete[] tids_2;
		return flag;
	}
	else
	{
		int loop_todo = num_exponent / 12 + 1;
		for (int i = 0; i < index_wrong.size(); ++i)
		{
			bool flag1 = false;
			int temp_exponent = 0;
			for (int l = 0; l < loop_todo; ++l)
			{
				if ((l + 1) * 12 + 1 > num_exponent)
				{
					temp_exponent = num_exponent;
					flag1 = true;
				}
				else
					temp_exponent = (l + 1) * 12 + 1;

				struct arg4mod* args_2 = new arg4mod[temp_exponent - (l * 12 + 1)];
				pthread_t* tids_2 = new pthread_t[temp_exponent - (l * 12 + 1)];

				for (int r = l * 12 + 1; r < temp_exponent; ++r)
				{
					UintN number_base = UintN(list_base[index_wrong[i]]);
					args_2[r - l * 12 - 1].number = number_base;
					long long temp = pow(2, r + 1);
					UintN exponent = UintN(temp) * d;
					args_2[r - l * 12 - 1].exponent = exponent;
					args_2[r - l * 12 - 1].n = number;

					pthread_attr_t attr;
					pthread_attr_init(&attr);
					pthread_create(&tids_2[r - l * 12 - 1], &attr, ModularExponentiation, &args_2[r - l * 12 - 1]);
					pthread_attr_destroy(&attr);
				}

				for (int r = 0; r < temp_exponent - l * 12 - 1; ++r)
					pthread_join(tids_2[r], NULL);

				for (int r = 0; r < temp_exponent - l * 12 - 1; ++r)
				{
					if (args_2[r].res != 1 && args_2[r].res != comparision)
						flag = false;
					else
					{
						flag = true;
						break;
					}
				}
				delete[] args_2;
				delete[] tids_2;
				if (flag)
					break;
				if (flag1 && !flag)
					return flag;
			}
		}
		return flag;
	}
}