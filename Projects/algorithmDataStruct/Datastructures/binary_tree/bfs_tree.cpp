#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<queue>

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


void breadth_first(tree_node* root)
{
 if(root==NULL)
    {
      return;
    }
std::queue<tree_node*> q;
q.push(root); 

while(!q.empty())
{
tree_node* present = q.front();

std::cout << "The present element is " << present->data << " " <<std::endl; 

q.pop();

if(present->left != NULL)
    {
      q.push(present->left);
      
    }

if(present->right != NULL)
    {
      q.push(present->right);
      
    }

}

}

int main(int argc, char* argv[])
{
tree_node* root = NULL;
	root = insert_node(root,25); root = insert_node(root,15);
	root = insert_node(root,45); root = insert_node(root,50); 
	root = insert_node(root,8); root = insert_node	(root,100);
	
	breadth_first(root);

  return 0;
}
