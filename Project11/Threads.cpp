#include "Threads.h"
#include <cmath>
#include <chrono>
#include <iomanip>

using std::string;
using std::cout;
using std::thread;
using std::endl;
using std::sqrt;
using std::vector;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

bool isPrime(const int &num) {
	/*
	Helper function who checks if number is prime or not by the fastest way.
	input: 1 const reference int
	output: bool
	*/
	if (num < 2) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;
	int i = 0;
	for (i = 3; i <= sqrt(num); i += 2) {
		if (num % i == 0) return false;
	}
	return true;
}

void I_Love_Threads() {
	string str = "I Love Threads";
	cout << str << endl;
}

void call_I_Love_Threads() {
	thread t(I_Love_Threads);
	t.join();
}

void getPrimes(const int &begin, const int &end, std::vector<int> &primes) {
	primes.clear();
	if (begin > end) return;
	int num = 0;
	for (num = begin; num <= end; num++) {
		if (isPrime(num)) primes.push_back(num);
	}
}

void printVector(const std::vector<int>& primes) {
	int i = 0;
	for (i = 0; i < primes.size(); i++) {
		cout << primes[i] << ", ";
	}
}


std::vector<int> callGetPrimes(int begin, int end)
{
	vector<int> primes;
	thread t(getPrimes, begin, end, std::ref(primes));
	auto start = high_resolution_clock::now();
	t.join();
	auto finish = std::chrono::high_resolution_clock::now();
	duration<double> runtime = finish - start;
	cout << std::fixed << std::setprecision(6);
	cout <<"\nTime taken : " << runtime.count() << " seconds" << std::endl;
	return primes;
}


