//Count nodes of a binary tree and sum of nodes
//return countnodes(root->left)+countnodes(root->right)+1

#include <iostream>
using namespace std;

struct Node{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int val)
    {
        data=val;
        left=NULL;
        right=NULL;
    }
};

int countnodes(struct Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    return countnodes(root->left)+countnodes(root->right)+1;
}

int sumNodes(struct Node* root)
{
    if(root==NULL)
    {
       return 0;
    }
    return sumNodes(root->left)+sumNodes(root->right)+root->data;
}

int main()
{
    struct Node* root=new Node(1);
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    root->right->left=new Node(6);
    root->right->right=new Node(7);

    cout<<"Total Nodes :"<<countnodes(root)<<" ";
    cout<<"\n\n";
    cout<<"Sum of Nodes :"<<sumNodes(root)<<" ";

    return 0;
}