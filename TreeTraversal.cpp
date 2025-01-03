#include<iostream>
using namespace std;

struct node{
    int data;
    struct node* left;
    struct node* right;

    node(int val)
    {
        data=val;
        left=NULL;
        right=NULL;
    }
};

void preorder(struct node* root)
{
    if(root==NULL)
    {
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node* root)
{
    if(root==NULL)
    {
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void postorder(struct node* root)
{
    if(root==NULL)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

//Count of all nodes in a binary tree
int countnodes(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    return countnodes(root->left)+countnodes(root->right)+1;
}


//height of a binary tree 
int calheight(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    int lheight=calheight(root->left);
    int rheight=calheight(root->right);

    return max(lheight,rheight)+1;
}

//Sum of all nodes in a tree
int sumnodes(node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    return sumnodes(root->left)+sumnodes(root->right)+root->data;
}

//to swap a tree


//to copy a tree


//calculating leaf nodes




int main()
{
    struct node* root= new node(1);

    root->left=new node(2);
    root->right=new node(3);
    root->left->left=new node(4);
    root->left->right=new node(5);
    root->right->left=new node(6);
    root->right->right=new node(7);

    cout<<"\n\nPreorder Traversal :";
    preorder(root);
    
    cout<<"\n\nInorder Traversal :";
    inorder(root);

    cout<<"\n\nPostorder Traversal :";
    postorder(root);

    cout<<"\n\nThe counts of all nodes in the tree :"<<countnodes(root);

    cout<<"\n\nThe height of the tree is:"<<calheight(root);

    cout<<"\n\nThe sum of all node keys is :"<<sumnodes(root);


    
   
    cout<<"\n\n";
    return 0;
}