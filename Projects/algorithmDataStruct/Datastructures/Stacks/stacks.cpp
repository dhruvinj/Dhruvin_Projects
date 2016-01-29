#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>
class Stack
{
private:
int max_size; 
std::vector<int> A;
int top, rear; 

public:
	// Constructor - creating queue of user size, set front and rear as -1. 
	// We are assuming that for an empty Queue, both front and rear will be -1.
	Stack(int size)
	{

	 max_size = size; 
	 A.reserve(max_size); 
		top = -1; 
		
	}

// To check wheter Queue is empty or not
	bool IsEmpty()
	{
		return (top == -1 ); 
	}

	// To check whether Queue is full or not
	bool IsFull()
	{
		return top == max_size-1 ? true : false;
	}

void push(int x)
	{
		std::cout<<"Adding elements to stack "<<x<<" \n";
		if(IsFull())
		{
			std::cout<<"Error: Stack is Full\n";
			return;
		}
		if (IsEmpty())
		{ 
			top = 0; 
		}
		else
		{
		    top = top+1;
		}
		A[top] = x;
	}
void pop()
	{
		std::cout<<"Unstacking \n";
		if(IsEmpty())
		{
			std::cout<<"Error: stack is Empty\n";
			return;
		}
		else if(top == 0 ) 
		{
			top = -1;
		}
		else
		{
			top = top-1;
		}
	}

	// Returns element at front of queue. 
	int Top()
	{
		if(top == -1)
		{
			std::cout<<"Error: cannot return front from empty stack\n";
			return -1; 
		}
		return A[top];
	}
	/* 
	   Printing the elements in queue. 

	*/
	void Print()
	{
		// Finding number of elements in queue  
		int count = (max_size-top) - 1;
		std::cout<<"stack      : ";
		for(int i = 0; i <count; i++)
		{
			//int index = (front+i) % max_size; // Index of element while travesing circularly from front
			std::cout<<A[i]<<" ";
		}
		std::cout<<"\n\n";
	}

};



int main(int argc, char* argv[])
{
int length = 20;

   Stack Q(length); // creating an instance of Queue. 
   Q.push(2);  Q.Print();  
   Q.push(4);  Q.Print();  
   Q.push(6);  Q.Print();
   Q.pop();	  Q.Print();
   Q.push(8);  Q.Print();

  return 0;
}
