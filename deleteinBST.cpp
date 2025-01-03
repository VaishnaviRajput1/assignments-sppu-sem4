//delete a node : 3 cases

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

Node* inordersuc(Node* root){
    Node* curr=root;
    while(curr && curr->left !=NULL)
    {
        curr=curr->left;
    }
    return curr;
}

Node* deleteinBST(Node* root, int key)
{
    if(key<root->data)
    {
        root->left=deleteinBST(root->left,key);
    }
    else if(key>root->data)
    {
        root->right=deleteinBST(root->right,key);
    }
    else{
        //for cases 1 & 2
        if(root->left==NULL)
        {
            Node* temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            Node* temp=root->left;
            free(root);
            return temp;
        }
        Node* temp=inordersuc(root->right);       //case 3
        root->data=temp->data;
        root->right=deleteinBST(root->right, temp->key);
    }
    return root;
}

void inorder(Node* root)
{
    if(root==NULL)
    {
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
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

    inorder(root);
    root=deleteinBST(root,5);
    inorder(root);
    
    return 0;
    
}
