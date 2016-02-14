#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<queue>
#include <cstdint> 
#include <limits.h>
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


void depth_first_preorder(tree_node* root)
{
  if(root==NULL)
    {
      return;
    }


  std::cout << "The present element is " << root->data << " " <<std::endl; 

  depth_first_preorder(root->left);
  depth_first_preorder(root->right);


}


void depth_first_postorder(tree_node* root)
{
  if(root==NULL)
    {
      return;
    }



  depth_first_postorder(root->left);
  depth_first_postorder(root->right);

  std::cout << "The present element is " << root->data << " " <<std::endl; 

}

void depth_first_inorder(tree_node* root)
{
  if(root==NULL)
    {
      return;
    }

  depth_first_inorder(root->left);
  std::cout << "The present element is " << root->data << " " <<std::endl; 
  depth_first_inorder(root->right);


}

bool tree_check_binary(tree_node* root, int min, int max)
{

  if(root==NULL)
    {
      return true;
    }

  if(root->data > min && root->data < max && tree_check_binary(root->left, min, root->data)  && tree_check_binary(root->right, root->data, min ) )
    {
      return true;
    }
  else
    return false; 

}

bool check_binary(tree_node* root)
{

  return tree_check_binary( root, INT_MIN, INT_MAX);

}


tree_node* FindMin(tree_node* root)
{
  while(root->left != NULL) root = root->left;
  return root;
}

// Function to search a delete a value from tree.
tree_node* node_delete( tree_node *root, int data) {
  if(root == NULL) 
    {
      return root; 
    }
  else if(data < root->data) 
    {
      root->left = node_delete(root->left,data);
    }
  else if (data > root->data) 
    {
      root->right = node_delete(root->right,data);
    }
		
  else {
    // Case 1:  No child
    if(root->left == NULL && root->right == NULL) { 
      delete root;
      root = NULL;
    }
    //Case 2: One child 
    else if(root->left == NULL) {
      tree_node *temp = root;
      root = root->right;
      delete temp;
    }
    else if(root->right == NULL) {
      tree_node *temp = root;
      root = root->left;
      delete temp;
    }
    // case 3: 2 children
    else { 
      tree_node *temp = FindMin(root->right);
      root->data = temp->data;
      root->right = node_delete(root->right,temp->data);
    }
  }
  return root;
}

int main(int argc, char* argv[])
{
  tree_node* root = NULL;
  root = insert_node(root,25); root = insert_node(root,15);
  root = insert_node(root,45); root = insert_node(root,50); 
  root = insert_node(root,8); root = insert_node	(root,100);
	
  depth_first_inorder(root);

  return 0;
}
