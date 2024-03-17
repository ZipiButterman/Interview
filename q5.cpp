// Question 5
//
//	we want to implement a logic class named MyBool to use in our logic
//	we would like to be able to use the logical and (&&) with instances of this class 
//  i.e. to be able to write in the form of myBool1 && myBool2
//	we have also implemented some function using this class
//	"notNull" checks if a pointer is null and return a corresponding MyBool
//  "greaterThanZero" checks if an int pointer points to a positive int and return a corresponding MyBool
//
//	1. Implement this addition in the MyBool class
//  2. Did it compile successfully?
//	3. Did it run successfully?
//	4. Explain the result, explain what happened and why
//
// useful links:
// https://en.cppreference.com/w/cpp/language/operators
// https://cplusplus.com/doc/tutorial/operators/
// https://isocpp.org/wiki/faq/operator-overloading
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// My Answer:
// There is no problem with the compile. (just we need to notice that the operator && can't get *two* parameters,
// but only *one*.
// The problem is that the overloading of && (and ||) checks all the expressions and not stops when there is a final answer.
// for example the expression (2 < 0 && 2 > 0) won't stop after (2 < 0) even though its false and thus the answer is false for sure.
// So, in the case of the pointer a that its value is nullptr, we will get false but continue to the next expression:
// greaterThanZero(a) that will collapse in case of nullptr.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

#include <iostream>

class MyBool
{
public:
	MyBool(bool b) : m_val(b) {};
	//TODO: Your code here
	bool operator&&(MyBool a)
	{
		return this->m_val && a.m_val;
	}

private:
	bool m_val;
};

MyBool notNull(int* intPtr)
{
	return intPtr != nullptr;
}

MyBool greaterThanZero(int* intPtr)
{
	return *intPtr > 0;
}

int main(int argc, char* argv[])
{

	int* a = nullptr;
	int val = 5;
	int* b = &val;
	// the long way to check
	if (a != nullptr && *a > 0)
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}

	// using our functions
	if (notNull(b) && greaterThanZero(b))
	{
		++* b;
		std::cout << "*b is " << *b << std::endl;
	}
	// using our functions again
	if (notNull(a) && greaterThanZero(a))
	{
		++* a;
		std::cout << "*a is " << *a << std::endl;
	}
	return 0;
}

