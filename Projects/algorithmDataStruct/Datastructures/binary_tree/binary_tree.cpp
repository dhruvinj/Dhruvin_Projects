#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>

struct tree_node
{
  int data; 
  tree_node* left; 
  tree_node* right;

};


tree_node* new_node(int data)
{

  tree_node* newnode = new tree_node(); 
  newnode->data = data; 
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;


}




tree_node* insert_node(tree_node* root, int data)
{
  if(root==NULL)
    {
      root =new_node(data);
      return root;
    }
  else if(data <= root->data){

    root->left = insert_node(root->left, data);
  }


  else if (data >root->data){

    root->right = insert_node(root->right, data);
  }

  return root;
}

bool node_search(tree_node* root, int data)
{
  if(root == NULL)
    {
      std::cout << "The tree is empty" << std::endl;
      return false;
    }

  else if(root->data == data)
    {
      std::cout << "The number is found at the root of the binary tree" << std::endl;
      return true;
    }
  else if( data <= root->data )
    {
      return node_search(root->left, data);

    }

  else if( data > root->data )
    {
      return node_search(root->right, data);

    }

}

int main(int argc, char* argv[])
{
  tree_node* root = NULL;
  root = insert_node(root,15);
  root = insert_node(root,5);
  root = insert_node(root,4);
  root = insert_node(root,150);
  root = insert_node(root,111);
  root = insert_node(root,120);

	int num; 

std::cout << "Please enter the number you want to search" << std::endl;

std::cin >> num ; 

if(node_search(root, num))
{
std::cout << "Number is found" << std::endl; 
}
else 
{
std::cout << "not found" << std::endl; 

}
  

  return 0;
}
