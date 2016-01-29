#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>
class Queue
{
private:
int max_size; 
std::vector<int> A;
int front, rear; 

public:
	// Constructor - creating queue of user size, set front and rear as -1. 
	// We are assuming that for an empty Queue, both front and rear will be -1.
	Queue(int size)
	{

	max_size = size; 
	 A.reserve(max_size); 
		front = -1; 
		rear = -1;
	}

// To check wheter Queue is empty or not
	bool IsEmpty()
	{
		return (front == -1 && rear == -1); 
	}

	// To check whether Queue is full or not
	bool IsFull()
	{
		return (rear+1)%max_size == front ? true : false;
	}

void Enqueue(int x)
	{
		std::cout<<"Enqueuing "<<x<<" \n";
		if(IsFull())
		{
			std::cout<<"Error: Queue is Full\n";
			return;
		}
		if (IsEmpty())
		{ 
			front = rear = 0; 
		}
		else
		{
		    rear = (rear+1)%max_size;
		}
		A[rear] = x;
	}
void Dequeue()
	{
		std::cout<<"Dequeuing \n";
		if(IsEmpty())
		{
			std::cout<<"Error: Queue is Empty\n";
			return;
		}
		else if(front == rear ) 
		{
			rear = front = -1;
		}
		else
		{
			front = (front+1)%max_size;
		}
	}

	// Returns element at front of queue. 
	int Front()
	{
		if(front == -1)
		{
			std::cout<<"Error: cannot return front from empty queue\n";
			return -1; 
		}
		return A[front];
	}
	/* 
	   Printing the elements in queue. 

	*/
	void Print()
	{
		// Finding number of elements in queue  
		int count = (rear+max_size-front)%max_size + 1;
		std::cout<<"Queue       : ";
		for(int i = 0; i <count; i++)
		{
			int index = (front+i) % max_size; // Index of element while travesing circularly from front
			std::cout<<A[index]<<" ";
		}
		std::cout<<"\n\n";
	}

};



int main(int argc, char* argv[])
{
int length = 20;

   Queue Q(length); // creating an instance of Queue. 
   Q.Enqueue(2);  Q.Print();  
   Q.Enqueue(4);  Q.Print();  
   Q.Enqueue(6);  Q.Print();
   Q.Dequeue();	  Q.Print();
   Q.Enqueue(8);  Q.Print();

  return 0;
}
