#include "Threads.h"
#include <cmath>
#include <chrono>
#include <iomanip>
//mutex must for making few treads writing to one file (for ensure sync and prevent data races)
#include <mutex>

using std::string;
using std::cout;
using std::thread;
using std::endl;
using std::sqrt;
using std::vector;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::mutex;

mutex fileMutex;

bool isPrime(const int& num) {
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
	/*
	function print text.
	*/
	string str = "I Love Threads";
	cout << str << endl;
}

void call_I_Love_Threads() {
	/*
	function make a thread and join him.
	*/
	thread t(I_Love_Threads);
	t.join();
}

void getPrimes(const int& begin, const int& end, std::vector<int>& primes) {
	/*
	Function pushing to inputed vector the prime numbers between the begin and end number which is inputed.
	input: 2 const reference int, 1 reference int vector.
	*/
	primes.clear();
	if (begin > end) return;
	int num = 0;
	for (num = begin; num <= end; num++) {
		if (isPrime(num)) primes.push_back(num);
	}
}

void printVector(const std::vector<int>& primes) {
	/*
	Function print a vector.
	input: const reference int vector
	*/
	int i = 0;
	for (i = 0; i < primes.size(); i++) {
		cout << primes[i] << ", ";
	}
}


std::vector<int> callGetPrimes(const int& begin, const int& end)
{
	/*
	Function make a thread, join him and then print the time he worked.
	input: 2 const reference int
	output: int verctor.
	*/
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

void writePrimesToFile(const int& begin, const int& end, std::ofstream& file)
{
	/*
	Function write the prime numbers to some inputed file.
	input: 2 const reference int, 1 reference file.
	*/
    if (!file.is_open()) return;

    for (int num = begin; num <= end; ++num)
    {
        if (isPrime(num))
        {
            file << num << "\n";
        }
    }
}

void callWritePrimesMultipleThreads(int begin, int end, const std::string& filePath, int N)
{
	/*
	Function write the prime number to file using a multi-threaded way and printing runtime. 
	input: 3 int, 1 const reference string
	*/
	std::ofstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "\ncannot open file: " << filePath << std::endl;
		return;
	}
	int totalRange = end - begin + 1;
	int rangePerThread = totalRange / N;
	int start = begin;
	int finish;
	vector<std::thread> threads;
	auto startTime = high_resolution_clock::now();
	for (int i = 0; i < N; ++i)
	{
		finish = (i == N - 1) ? end : start + rangePerThread - 1;
		threads.emplace_back(writePrimesToFile, start, finish, std::ref(file));
		start = finish + 1;
	}
	for (auto& t : threads)
		t.join();
	auto finishTime = high_resolution_clock::now();
	duration<double> runtime = finishTime - startTime;
	cout << "\nTotal time taken: " << runtime.count() << " seconds" << std::endl;
	file.close();
}


//Bonus 3: 
void threadsRecursion(int num) {
	/*
	recursive function who print number and then calling her again for print number + 1 until number is bigger than 50.
	input: int
	*/
	if (num > 50) {
		return;
	}
	std::cout << "Hello from Thread #" << num << std::endl;
	std::thread nextThread(threadsRecursion, num + 1);
	if (nextThread.joinable()) {
		nextThread.join();
	}
}