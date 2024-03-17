// Question 3 - implementation
// 
//	without using STL containers implement the following:
//	A class for a dynamic int array, let's call it "CVectorInt" that -
//  1. doubles its size automatically when its full (allocates twice the size and moves the data),
//	2. halves its size when it is half empty (allocates half of the size and moves the data)
//  3. can be told the initial capacity (num of ints) in a constructor
//  4. have a method called "reserve" - that Requests that the vector capacity be at least enough to contain n elements.
//     If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n
//  5. have a method called "capacity" - that returns the number of int elements allocated
//  6. have a method called "size" - that returns the number of elements actually inserted
//  7. have a method called "empty" - that returns true/false according to amount of actual elements in the data
//  8. have a method called "clear" - that frees all the data and resets the size
//  9. have a method called "push_back" - that adds an int elements at the end
// 10. have a method called "pop_back" - that removes an int elements at the end and return it
// 11. have a method called "remove"  - that removes an int elements at specific index
// 12. have an interface to access the data at a specific index using subscript "[]"
//
// make sure to handle edge cases such as memory issues, size issues etc.



#include <iostream>
#include <stdexcept>
// NOTICE:
// I have initial the array with value "0"
class CVectorInt
{
	// TODO: your code here
public:
	CVectorInt(int n) //Constructor as requested (can be told the initial capacity (num of ints) in a constructor)
	{
		init(n); //private function, initial the array.
	}
	void reserve(int n) //reserve function as requested
	{
		if (n > capacity()) //need to initial new arr with length of n.
		{
			rellocate_array(n, size());
		}
	}
	int capacity() //capacity function as requested
	{
		return arr_size; //private variable
	}
	int size() //size function as requested
	{
		return iterator; //private variable
	}
	bool empty() //empty function as requested
	{
		return iterator == 0;
	}
	void clear() //clear function as requested
	{
		init(0); //initial new array, and resets the length
		iterator = 0; //initial iterator to the first of the array
	}
	void push_back(int val) //push_back function as requested
	{
		if (size() == capacity()) //no more place in the array. double the size.
		{
			doubles_array_size();
		}
		arr[iterator++] = val;
	}
	int pop_back() //pop_back function as requested
	{
		int val = arr[iterator]; //save the value to return
		arr[iterator--] = 0;
		if (size() * 2 == capacity()) //too much place in the array. halves the size.
		{
			halves_array_size();
		}
		return val;
	}
	void remove(int index) //remove function as requested
	{
		for (int i = index; i < size() - 1; i++) {
			arr[i] = arr[i + 1];
		}
		iterator--;
		if (size() * 2 == capacity())
		{
			halves_array_size();
		}
	}
	int& operator[](int index) //overloading operator [] as requested
	{
		return arr[index];
	}
private:
	int* arr;
	int iterator = 0; //current place in array
	int arr_size = 0; //array total size
	void init(int n)
	{
		free(arr);
		arr = new int[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = 0;
		}
		arr_size = n;
	}
	void halves_array_size() 
	{
		rellocate_array(iterator / 2, iterator / 2);
	}
	void doubles_array_size() 
	{
		rellocate_array(iterator * 2, iterator);
	}
	void rellocate_array(int size, int end)
	{
		int* new_arr = new int[size];
		for (int i = 0; i < end; i++)
			new_arr[i] = arr[i];
		init(size);
		for (int i = 0; i < end; i++)
			arr[i] = new_arr[i];
		free(new_arr);
	}
};

int main(int argc, char* argv[])
{
	// some code to use the class
	try
	{
		CVectorInt v(5);
		for (int i = 0; i < 5; i++)
		{
			v.push_back(i);
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.push_back(1);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		while (!v.empty())
		{
			v.pop_back();
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.reserve(15);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}
		v[5] = 3;
		for (int i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
		v.clear();
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

