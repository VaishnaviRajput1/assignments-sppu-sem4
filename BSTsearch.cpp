//BST search
//time complexity O(log n)

#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val)
    {
        data=val;
        left=NULL;
        right=NULL;
    }
};

Node* insert(Node* root, int val)
{
    if(root==NULL)
    {
        return new Node(val);
    }
    if(val < root->data)
    {
        root->left=insert(root->left,val);
    }
    else
    {
        root->right=insert(root->right,val);
    }
    return root;
}

Node* searchBST(Node* root, int key)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->data==key)
    {
        return root;
    }
    if(root->data>key)
    {
        return searchBST(root->left,key);
    }
    return searchBST(root->right,key);
}

int main()
{
    Node* root=NULL;
    root=insert(root,5);
    insert(root,1);
    insert(root,3);
    insert(root,4);
    insert(root,2);
    insert(root,7);

    if(searchBST(root,3)==NULL)
    {
        cout<<"Key doesnt exists..";
    }
    else
    {
        cout<<"Key exists...";
    }
    return 0;
    
}