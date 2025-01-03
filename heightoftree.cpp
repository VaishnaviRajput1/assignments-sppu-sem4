//calculate height of binary tree

#include<iostream>
#include<math.h>
using namespace std;

struct Node
{
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

int calcHeight(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int rheight= calcHeight(root->right);
    int lheight= calcHeight(root->left);
    
    return max(rheight,lheight)+1;
    
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

    cout<<calcHeight(root);

    return 0;

}