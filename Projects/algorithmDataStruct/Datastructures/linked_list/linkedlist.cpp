#include<iostream>

class Node
{
public:
  int data; 
  Node* next; 

  Node* insertatstart(Node* head, int x)
  {
    Node* temp = new Node; 
    temp->data = x;
    temp->next = head;
    head = temp; 
    return head; 

  }


  void insertmiddle(Node* head, int n , int x)
  {
    Node* temp1 = new Node; 
    temp1->data = x;
    temp1->next = head;
 	
    Node* temp2 = head;
    for(int i =0; i< n-2; i++)
      {
	temp2 = temp2->next;
      } 
    temp1->next = temp2->next;
    temp2->next = temp1;
  }


void deletenode(Node** head, int n )
  {
	Node* temp1 = *head;
 
	if(n ==1)
	{
	*head = temp1->next;
	delete temp1;
	return;
	}
  
 	
    Node* temp2 = *head;
    for(int i =0; i< n-2; i++)
      {
	temp1 = temp1->next;
	Node* temp2 = temp1->next; 
	temp1->next = temp2->next;
	delete temp2;
      } 
 
  }


 Node* reversenode(Node* head )
  {
	Node *current, *prev, *next_node;
	current = head;
	prev = NULL;
	while(current != NULL)
	{
	next_node = current->next;	
	current->next = prev;
	prev = current;
	current = next_node;
	

	}
	head = prev;
	return head;
  }


  void print(Node* head)
  {

    Node* temp1 = head; 
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
  Node* head; 
  head = NULL ;
  head = head->insertatstart( head, 75);
  head =  head->insertatstart( head, 56);
  head =  head->insertatstart( head, 54);
  head =  head->insertatstart( head, 50);
  head =  head->insertatstart(head, 51);
head->print(head);
   head->deletenode(&head, 1);
 // head->insertmiddle(head, 3 ,  40);
head->print(head);
  //  head =  head->reversenode(head);
  //head->print(head);
  return 0;
}
