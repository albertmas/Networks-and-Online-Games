#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <windows.h>

void function(int arg1, int arg2, int arg3) {
	Sleep(1000);
	std::cout << arg1;
	std::cout << arg2;
	std::cout << arg3;
	std::cout << std::endl;
}

int counter = 0;
std::mutex mtx; // Mutex object

void increment(int iterations) {
	for (int i = 0; i < iterations; ++i) {
		std::unique_lock<std::mutex> lock(mtx); // Denies the execution of the next lines when another thread is already executing it
		counter++;
	}
}

int main()
{
	/*std::thread t = std::thread(function, 1, 2, 3);

	t.join();*/

	std::thread t1(increment, 100000); // Execute 'increment' in a thread
	std::thread t2(increment, 100000); // Execute 'increment' in a thread
	t1.join(); // Wait for t1
	t2.join(); // Wait for t2
	std::cout << "Counter = " << counter << std::endl;
	system("pause");
	return 0;
}