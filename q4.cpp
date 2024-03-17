//Question 4 - pointers

// There is a memory leak in the code below, where is it?, what class/solution can you use to fix it while ensuring that the object will be deleted only once and only when it's not used by any consumer
// Task: Modify the code to address the issues above. Please explain the changes you made and how they solve the memory allocation/deletion issue  

// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature


///////////////////////////////////////////////////////////////////////////////////
// My Answer:
// The memory leak is on the thread.detach() operation. This function causes the program to run 
// without waiting for threads will finish. (like join() function) This can cause problems 
// because the memory is freed but the program still doesn't end and then we can get an unexpected results.
// I fix this in a simple way, I sign with a flag when the threads run out and just then I let my head finish the run.
///////////////////////////////////////////////////////////////////////////////////
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <future>

struct Payload {

	Payload(uint64_t id_) :
		id(id_),
		veryLargeVector(1000 * 1000)
	{}

	uint64_t id;
	std::vector<int> veryLargeVector;
};
bool operation1_still_runing = true, operation2_still_runing = true;

void operation1(Payload* payload) {
	std::cout << "Performing operation1 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
	operation1_still_runing = false;
}

void operation2(Payload* payload) {
	std::cout << "Performing operation2 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
	operation2_still_runing = false;
}

void dispacher_thread(Payload* payload) {
	std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
	std::thread wt1(&operation1, payload);
	std::thread wt2(&operation2, payload);
	//Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
	wt1.detach();
	wt2.detach();
}

int main(int argc, char** argv)
{
	Payload* payload = new Payload(1);
	std::cout << "Calling dispatcher thread" << std::endl;
	std::thread t(&dispacher_thread, payload);
	t.join();
	while (operation1_still_runing || operation2_still_runing) { }
	delete payload;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}