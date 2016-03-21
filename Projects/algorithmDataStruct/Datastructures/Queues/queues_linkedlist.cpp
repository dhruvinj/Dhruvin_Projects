#include<iostream>
#include<vector>
class Node
{
public:
  int data; 
  Node* next; 
  Node* front; 
  Node* rear; 

   Node() {
   front = NULL;
   rear = NULL;
}


  void Enqueue( int x)
  {

	Node* temp = new Node; 
    temp->data = x;
    temp->next = NULL;
	if(front== NULL && rear == NULL)
	{
	 front = rear=temp;	
	 return;
	}
   
   	rear->next = temp;
	rear = temp;
  }


 

void Dequeue()
  {
	Node* temp1 = front;

	if(front == NULL) {
		std::cout << "The queue is empty " << std::endl;
		return;
	}
 else if(front == rear) {
		front = rear = NULL;
	}
	else {
		front = front->next;
	}
 	delete temp1;
  }

int Front() {
	if(front == NULL) {
		std::cout << "The queue is empty " << std::endl;
		return 0;
	}
	return front->data;
}

  void Print()
  {

    Node* temp1 = front; 
    std::cout << "The List is " << std::endl;
    while(temp1 != NULL)
      {
	std::cout << temp1->data << std::endl;
	temp1 = temp1->next;
      }
    std::cout <<  std::endl;
  }
};



int main(int argc, char* argv[])
{
	Node a;
    a.Enqueue(2); a.Print(); 
	a.Enqueue(4); a.Print();
	a.Enqueue(6); a.Print();
	a.Dequeue();  a.Print();
	a.Enqueue(8); a.Print();

  return 0;
}
