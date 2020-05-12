#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>

class SharedArray {
private:
	char *array;
	int index;
	int size;
	omp_lock_t *lock;

public:
	SharedArray(int n, omp_lock_t *lock) : size(n), index(0), lock(lock) {
		array = new char[size];
		std::fill(array, array + size, '-');

		if (lock != nullptr)
			omp_init_lock(lock);
	}

	~SharedArray() {
		delete[] array;
	}

	void addChar(char c) {
		if (lock != nullptr)
			omp_set_lock(lock);
		array[index] = c;
		spendSomeTime();
		index++;
		if (lock != nullptr)
			omp_unset_lock(lock);
	}

	int countOccurrences(char c) {
		return std::count(array, array + size, c);
	}

	std::string toString() {
		return std::string(array, size);
	}

private:
	void spendSomeTime() {
		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < 100; j++) {
				// These loops shouldn't be removed by the compiler
			}
		}
	}
};

class ArrayFiller {
private:
	static const int nThreads = 3;
	static const int nTimes = 20;
	SharedArray *array;
	omp_lock_t lock;

public:
	ArrayFiller(bool usemutex) {
		if (usemutex)
			omp_init_lock(&lock);

		array = new SharedArray(nThreads * nTimes, usemutex ? &lock : nullptr);
	}

	void fillArrayConcurrently() {
#pragma omp parallel num_threads(nThreads) default(none)
		{
			ArrayFiller::run('A' + omp_get_thread_num());
		}
	}

	void printStats() {
		std::cout << array->toString() << std::endl;
		for (int i = 0; i < nThreads; ++i)
			std::cout << (char) ('A' + i) << "=" << array->countOccurrences('A' + i) << " ";
		std::cout << std::endl;
	}

	~

	ArrayFiller() {
		delete array;
	}

private:

	void run(char c) {
		for (int i = 0; i < nTimes; i++) {
			array->addChar(c);
		}
	}

};

int main() {
	std::cout << "Each thread should add its char to the array n times (n=20)" << std::endl;
	std::cout << "Correct results should total exactly nThreads*nTimes chars" << std::endl;
	std::cout << "Case 1: no mutex, default scheduling (expecting wrong results)" << std::endl;
	ArrayFiller m1(false);
	m1.fillArrayConcurrently();
	m1.printStats();

	std::cout << "Case 2: same as case 1 (possibly getting different results due to scheduling)" << std::endl;
	ArrayFiller m2(false);
	m2.fillArrayConcurrently();
	m2.printStats();

	std::cout << "Case 3: using mutex (expecting correct results)" << std::endl;
	ArrayFiller m3(true);
	m3.fillArrayConcurrently();
	m3.printStats();

	return 0;
}
