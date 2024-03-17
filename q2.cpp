//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

//////////////////////////////////////////////////////////////////////////////////
// My Answer:
// The first change: instead of performing operation1 and just after it operation2
// I created 2 threads, and then they run in parallel.
// The second is: using lock. because we have no control over the CPU, and the line: "gSum += (arg + i);"
// is not atomic action, then we can get bad results (for example:
// we will start with operation1, and before gSum we will updated, a contex swicth will be occured to t2 - operation2 -
// and then the gSum will be updated with the value of OP2_PARAM + i.) So this line is critical section and we need to use lock to solve it..*/
//////////////////////////////////////////////////////////////////////////////////
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>

constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t gSum = 0;
std::mutex m;


void operation1(size_t arg) {
	std::cout << "Performing operation1" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		m.lock();
		gSum += (arg + i);
		m.unlock();
	}
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		m.lock();
		gSum += (arg * i);
		m.unlock();
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	std::thread t1(operation1, OP1_PARAM);
	std::thread t2(operation2, OP2_PARAM);
	t1.join();
	t2.join();
	/*operation1(OP1_PARAM);
	operation2(OP2_PARAM);*/
	auto end = std::chrono::steady_clock::now();auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(start);
	size_t sum = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Total execution duration in milliseconds: " << sum << std::endl;
	std::cout << "Result:  " << gSum << ", " << (gSum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}