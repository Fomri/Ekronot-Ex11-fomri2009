#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Threads.h"

using std::cout;
using std::endl;


std::string readFileToString(const std::string fileName)
{
	std::ifstream inFile;
	inFile.open(fileName); //open the input file

	std::stringstream strStream;
	strStream << inFile.rdbuf(); //read the file
	std::string str = strStream.str(); //str holds the content of the file

	return str;
}

std::string vectorToString(const std::vector<int> v)
{
	std::string result = "";
	for (unsigned int i = 0; i < v.size(); i++)
	{
		result += std::to_string(v[i]);
		if (i < v.size() - 1)
			result += ", ";
	}
	return result;
}

int test1Primes()
{

	try
	{
		// Tests Ex11 - threads & primes

		cout <<
			"*******************\n" <<
			"Test 1 - Primes	\n" <<
			"*******************\n" << endl;

		cout <<
			"Calling I_Love_Threads() ... \n" << endl;

		std::streambuf* psbuf, * backup;
		std::stringstream ss;

		backup = std::cout.rdbuf();			// backup cout's streambuf

		psbuf = ss.rdbuf();					// get the string stream streambuf
		std::cout.rdbuf(psbuf);      // assign streambuf to cout

		I_Love_Threads();

		std::cout.rdbuf(backup);     // restore cout's original streambuf

		std::string expected = "I Love Threads\n";
		std::string got = ss.str();
		if (got == expected)
		{
			cout << "\033[1;32mTest Passed\033[0m\n \n" << endl;
		}
		else
		{
			cout << "\033[1;31mTest Failed\033[0m\n \n" << endl;
			cout << "Expected: " << expected << endl;
			cout << "Got     : " << got << endl;
			std::cout << " \n" << endl;
			system("./printMessage 11101");
			std::cout << " \n" << endl;
			return 11101;
		}

		cout <<
			"\nInitializing empty vector v and calling getPrimes(0, 1000, v)... \n" << endl;

		std::vector<int> v;
		getPrimes(1, 1000, v);

		expected = readFileToString("output1.txt");
		got = vectorToString(v);
		if (got == expected)
		{
			cout << "\033[1;32mTest Passed\033[0m\n \n" << endl;
		}
		else
		{
			cout << "\033[1;31mTest Failed\033[0m\n \n" << endl;
			cout << "Expected: \n" << expected << endl;
			cout << "Got     : \n" << got << endl;
			std::cout << " \n" << endl;
			system("./printMessage 11102");
			std::cout << " \n" << endl;
			return 11102;
		}

		cout <<
			"\nInitializing empty vector v2 and calling getPrimes(1, 100000, v)... \n" << endl;
		std::vector<int> v2;
		getPrimes(1, 100000, v2);

		expected = readFileToString("output2.txt");
		got = vectorToString(v2);

		if (got == expected)
		{
			cout << "\033[1;32mTest Passed\033[0m\n \n" << endl;
		}
		else
		{
			cout << "\033[1;31mTest Failed\033[0m\n \n" << endl;
			cout << "Expected: " << "9592 prime numbers" << endl;
			cout << "Got     : " << std::to_string(v2.size()) << " prime numbers" << std::endl;
			std::cout << " \n" << endl;
			system("./printMessage 11102");
			std::cout << " \n" << endl;
			return 11102;
		}

		cout <<
			"\nInitializing vector v3 = callGetPrimes(1, 100000)... \n" << endl;
		std::vector<int> v3;
		v3 = callGetPrimes(1, 100000);

		expected = readFileToString("output2.txt");
		got = vectorToString(v3);
		if (got == expected)
		{
			cout << "\033[1;32mTest Passed\033[0m\n \n" << endl;
		}
		else
		{
			cout << "\033[1;31mTest Failed\033[0m\n \n" << endl;
			cout << "Expected: " << "9592 prime numbers" << endl;
			cout << "Got     : " << std::to_string(v3.size()) << " prime numbers" << std::endl;
			std::cout << " \n" << endl;
			system("./printMessage 11103");
			std::cout << " \n" << endl;
			return 11103;
		}

	}
	catch (...)
	{
		std::cerr << "\033[1;31mTest crashed\033[0m\n \n" << endl;
		std::cerr << "\033[1;31mFAILED: The program crashed, check the following things:\n\033[0m\n \n" <<
			"1. Did you delete a pointer twice?\n2. Did you access index out of bounds?\n" <<
			"3. Did you remember to initialize array before accessing it?";
		return 2;
	}

	return 0;

}

int main()
{
	std::cout <<
		"###########################\n" <<
		"Exercise 11 - Threads\n" <<
		"Test - Primes\n" <<
		"###########################\n" << std::endl;

	int testResult = test1Primes();

	cout << (testResult == 0 ? "\033[1;32m \n****** Ex11 Tests Passed ******\033[0m\n \n" : "\033[1;31mEx11 Tests Failed\033[0m\n \n") << endl;

	return testResult;
}