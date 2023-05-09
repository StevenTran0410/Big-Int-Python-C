#include "Header.h"

void input(UintN& first, UintN& second)
{
	int n;
	cout << "Please select input method for first number: \n1. Input as string.\n2. Input as unsigned long long (less than 20 digits number).\n";
	cin >> n;
	switch (n)
	{
	case 1:
	{
		string s;
		cout << "Please input first number: ";
		cin >> s;
		first = UintN(s);
		break;
	}
	case 2:
	{
		unsigned long long l;
		cout << "Please input first number: ";
		cin >> l;
		first = UintN(l);
		break;
	}
	}
	cout << "Please select input method for second number.\n";
	cin >> n;
	switch (n)
	{
	case 1:
	{
		string s;
		cout << "Please input second number: ";
		cin >> s;
		second = UintN(s);
		break;
	}
	case 2:
	{
		unsigned long long l;
		cout << "Please input second number: ";
		cin >> l;
		second = UintN(l);
		break;
	}
	}
}

void function(UintN first, UintN second)
{
loop1:
	cout << "Please select function you want to do: \n1. Summation.\n2. Subtraction.\n3. Multiplication.\n4. Division.\n5. Mod.\n8. Primility test.\n9. Find next prime number.\n10. Menu display.\n0. Quit the app.\n";
	int n;
loop:
	cout << "Please select: ";
	cin >> n;
	auto start = high_resolution_clock::now();
	switch (n)
	{
	case 0: break;
	case 1:
	{
		cout << "Summation of 2 number is: " << first + second << endl;
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
		goto loop;
	}
	case 2:
	{
		if (first < second)
		{
			cout << "Can't subtract a smaller number to bigger one.\n";
			goto loop;
		}
		else
		{
			cout << "Subtraction of 2 number is: " << first - second << endl;
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
			goto loop;
		}
	}
	case 3:
	{
		cout << "Multiplication of 2 number is: " << first * second << endl;
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
		goto loop;
	}
	case 4:
	{
		cout << "Division of 2 number is: " << first / second << endl;
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
		goto loop;
	}
	case 5:
	{
		cout << "Mod of 2 number is: " << first % second << endl;
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
		goto loop;
	}
	case 8:
	{
		if (PrimeNumber_MillerRabinsImprove(first))
			cout << "First number could be a prime number.\n";
		else
			cout << "First number is composite.\n";
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
		start = high_resolution_clock::now();
		if (PrimeNumber_MillerRabinsImprove(second))
			cout << "Second number could be a prime number.\n";
		else
			cout << "Second number is composite.\n";
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
		cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
		goto loop;
	}
	case 9:
	{
		cout << NextPrime(first, second) << endl;
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "The operation took: " << double(duration.count()) / 1000000 << "seconds.\n";
		goto loop;
	}
	case 10: goto loop1;
	}

}

int main()
{
	optimize();
	UintN first, second;
	input(first, second);
	function(first, second);
	return 0;
}

//5077461915617371651811593607389848534613910665160223569902404065418076795944656510340577164207672426574638345121648036693344561339868694500127046808526397857391514634557427341972391976756821
//531137992816767098689588206552468627329593117727031923199444138200403559860852242739162502265229285668889329486246501015346579337652707239409519978766587351943831270835393219031728127