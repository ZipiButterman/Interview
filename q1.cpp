// Question 1 - functions
// 
//	you are given the following missing implementation:
//	float applyF(float a, float b, ??????)
//	{
//		return f(a, b);
//	}
//	
//	1) list at least 3 different ways to replace the qustion marks (??????)
//		1. float f(float, float)					//My Answer
//		2. float (* f)(float, float)				//My Answer
//		3. std::function<float(float, float)> f		//My Answer
//	
//	2) replace the qustion marks in the following implementations with the solutions you listed
//
//	3) using one of those options create an add operation and a multiply operation and implement the following computation:
//		(2 * 3) + (4 * 5) + 6
//
//	you may not change the functions' implementation, only complete the signature
#include <iostream>
#include <functional>


float applyF1(float a, float b, float f(float, float))
{
	return f(a, b);
}

float applyF2(float a, float b, std::function<float(float, float)> f)
{
	return f(a, b);
}

float applyF3(float a, float b, float (* f)(float, float))
{
	return f(a, b);
}


int main(int argc, char* argv[])
{
	float fNum = 0;
	// calculate fNum = (2 * 3) + (4 * 5) + 6

	//TODO: Your code here
	auto lambada_mul = [](float a, float b) { return a * b; };
	auto lambada_add = [](float a, float b) { return a + b; };
	fNum = applyF1(applyF1(applyF1(2, 3, lambada_mul), applyF1(4, 5, lambada_mul), lambada_add), 6, lambada_add);
	std::cout << fNum;
	return 0;
}

