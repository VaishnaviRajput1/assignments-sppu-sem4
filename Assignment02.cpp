/*A dictionary stores keywords and its meanings. Provide facility for 
adding new keywords, deleting keywords, updating values of any 
entry. Provide facility to display whole data sorted in ascending/ 
Descending order. Also find how many maximum comparisons may 
require for finding any keyword. Use Binary Search Tree for 
implementation.*/

#include<iostream>
#include<string.h>
using namespace std;

struct Node{
    char key[50];           //arrays to store key and meaning
    char meaning[50];
    Node* left;             //pointer to left and right nodes
    Node* right;
};

class dict{
    public:
    Node* root;

    void create();
    void display(Node*);
    void insert(Node* root, Node* temp);
    int search(Node*,char[]);
    int update(Node*, char[]);
    Node* del(Node*,char[]);
    Node* min(Node*);
};

void dict::create()                         //to create a node
{
    int ch;

    do{
        Node* temp=new Node;                //create new node as temp
        cout<<"Enter key:";
        cin>>temp->key;
        cout<<"Enter Meaning :";
        cin>>temp->meaning;

        temp->left=NULL;
        temp->right=NULL;

        if(root==NULL)                       //if root is NULL
        {                                    //make temp as root
            root=temp;
        }
        else{                               //if root is present
            insert(root,temp);              //then call insert function to place temp
        } 
        cout<<"\nDo you wanna continue, (yes =1, no=0) :";
        cin>>ch;                                  
    }while(ch==1);

   
}

void dict::insert(Node* root, Node* temp)   //to insert node in BSt when root node is present
{
    if(strcmp(temp->key,root->key)<0)
    {
        if(root->left==NULL)
        root->left=temp;
        else
        insert(root->left,temp);
    }
    else
    {
        if(root->right==NULL)
        root->right=temp;
        else
        insert(root->right,temp);
    }
}


void dict::display(Node* root)           //to display the bst
{
    if(root!=NULL)
    {
        display(root->left);
        cout<<"\nKey :"<<root->key<<"    ";
        cout<<"Meaning :"<<root->meaning<<"    ";
        display(root->right);
    }
}

int dict::search(Node* root,char key[50])
{
    int c=0;            //counts num of comparisons

    while(root!=NULL)
    {
        c++;
        if(strcmp(key,root->key)==0) //compare key to searcha nd key of root
        {
            cout<<"\nNumber of comparisons:"<<c;    //if matches,return 1 and print c
            return 1;
        } 

        if(strcmp(key,root->key)<0)
        {
            root=root->left;
        }

        if(strcmp(key,root->key)>0)
        {
            root=root->right;
        }
    }
    return -1;      //when no element is found
}

int dict::update(Node* root,char key[50])
{
    while(root!=NULL)
    {
        if(strcmp(root->key,key)==0)        //compare key to search with key of root
        {
            cout<<"Enter updated meaning :";    //if found update, meaning of specified key and return 1
            cin>>root->meaning;
            return 1;
        }
        else if(strcmp(root->key,key)<0)         //search towards left and now left node is root node
        {
            root=root->left;
        }
        else if(strcmp(root->key,key)>0)        //search towards right and right node is root node
        {
            root=root->right;
        }
    }

    return -1;          //if key not found
}

Node* dict::del(Node* root, char key[50])
{
    Node* temp;
    if(root==NULL)
    {
        cout<<"No element found...";
        return root;
    }

    if(strcmp(key,root->key)<0)     //if keyword is less than root node
    {
        root->left=del(root->left,key);   //apply del on left node
        return root;
    }
    if(strcmp(key,root->key)>0)         //if keyword is greater than root node
    {
        root->right=del(root->right,key);   //apply del on right node
        return root;
    }
    if(root->right==NULL && root->left==NULL) //if root node is leaf node
    {
        temp=root;          //delete that node
        delete temp;
        return NULL;
    }

    if(root->right==NULL)       //when right node is null
    {
        temp=root;
        root=root->left;
        delete temp;
        return root;
    }

    if(root->left==NULL)       //when left node is null
    {
        temp=root;
        root=root->right;
        delete temp;
        return root;
    }
    temp=root->right;
    strcpy(root->key,temp->key);
    root->right=del(root->right,temp->key);
    return root;
}

Node* dict::min(Node* p)
{
    while(p->left!=NULL)
    {
        p=p->left;
    }
    return p;
}

int main()
{
    dict d;
    int ch;
    int choice;
    d.root=NULL;

    do{
    cout<<"\n   ";
    cout<<"\nMenu:\n1.Create\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Exit\nEnter your choice :";
    cin>>ch;

   switch(ch)
    {
        case 1:d.create();
            break;
        
        case 2:if(d.root==NULL)
        {
            cout<<"\n No keyword";
        }
        else{
            d.display(d.root);
        }
        break;

        case 3:if(d.root==NULL)
        {
            cout<<"\nDictionary id empty...";
        }
        else{
            cout<<"\n Enter keyword you wanna search :";
            char key[50];
            cin>>key;

            if(d.search(d.root,key)==1)
            {
                cout<<"\nKeyword Found...";
            }
            else{
                cout<<"\nKeyword not found...";
            }
        }
        break;

        case 4:if(d.root==NULL)
        {
            cout<<"\n Dictionary is empty...";
        }
        else{
            cout<<"\nEnter keyword to update :";
            char key[50];
            cin>>key;
            if(d.update(d.root,key)==1)
        {
            cout<<"\n Meaning updated...";
        }
        else{
            cout<<"\nKeyword not found...";
        }
        break;

        case 5:if(d.root==NULL)
        {
            cout<<"\nDictionary is empty";
        }
        else{
            cout<<"\n Enter keyword you wanna delete :";
            char key[50];
            cin>>key;
            if(d.root==NULL)
            {
                cout<<"\n No such keyword";
            }
            else{
                d.root=d.del(d.root,key);
            }
            break;
        }
        }
    }
    }while(choice!=6);
    return 0;

}