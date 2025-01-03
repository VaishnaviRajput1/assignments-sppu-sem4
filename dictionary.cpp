//dictionary

#include<iostream>
#include<string.h>
using namespace std;

class node{
    friend class dict;

    char key[50];
    char meaning[50];
    node* left;
    node* right;

public:
    node()
    {
        left=NULL;
        right=NULL;
    }
};

class dict{
    node* root;

    void insert(node* root, node* temp);
    void display(node* root);
    void displayasc(node* root);
    void displaydesc(node*root);
    int search(node* root,char[]);
    int update(node* root,char[]);
    node* del(node* root, char[]);
    node*min(node* p);
    node*max(node* p);

    public:
        dict(){
            root=NULL;
        }

        void create();
        void displaydict();
        void searchkey();
        void updatemean();
        void delkey();
        void printmax();
        void printmin(); 
        void dispascwrap();
        void dispdescwrap(); 
};

void dict::create(){
    int ch;
    do{
        node* temp=new node();

        cout<<"Enter key :";
        cin>>temp->key;

        cout<<"Enter meaning :";
        cin>>temp->meaning;

        if(root==NULL)
        {
            root=temp;
        }
        else{
            insert(root,temp);
        }
        cout<<"Do you wanna continue ? (yes=1, no=0) :";
        cin>>ch;
    }while(ch==1);
}


void dict::insert(node* root, node* temp)
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

void dict::display(node* root)
{
    if(root!=NULL){
        display(root->left);
        cout<<"\nKey :"<<root->key<<" "<<"Meaning :"<<root->meaning;
        display(root->right);
    }
}

void dict::displaydict()
{
    if(root==NULL)
    {
        cout<<"No Keywords";
    }
    else
        display(root);
}

void dict::displayasc(node* root)
{
    if(root!=NULL)
    {
        displayasc(root->left);
        cout<<"\n Key :"<<root->key<<" "<<"\n Meaning :"<<root->meaning;
        displayasc(root->right);
    }
}

void dict::displaydesc(node* root)
{
    if(root!=NULL)
    {
        displaydesc(root->right);
        cout<<"\n Key :"<<root->key<<" "<<"\n Meaning :"<<root->meaning;
        displaydesc(root->left);
    }
}

int dict::search(node* root, char key[50])
{
    int c=0;
    while(root!=NULL)
    {
        c++;
        if(strcmp(key,root->key)==0)
        {
            cout<<"\n Number of comparisons :"<<c;
            return 1;
        }
        if(strcmp(key,root->key)<0)
            root=root->left;
        else
            root=root->right;
    }
    return -1;
}

int dict::update(node* root, char key[50])
{
    while(root!=NULL)
    {
        if(strcmp(key,root->key)==0)
        {
            cout<<"\n Enter updated meaning :";
            cin>>root->meaning;
            return 1;
        }
        else if(strcmp(key,root->key)<0)
        {
            root=root->left;
        }
        else
            root=root->right;
    }
}

node* dict::del(node* root, char key[50])
{
    node* temp;
    if(root==NULL){
        cout<<"\n No elements found...";
        return root;
    }

    if(strcmp(key,root->key)<0)
    {
        root->left=del(root->left,key);
        return root;
    }

    if (strcmp(root->key,key)>0)
    {
        root->right=del(root->right,key);
        return root;
    }

    if(root->right==NULL && root->left==NULL)
    {
        temp=root;
        delete temp;
        return NULL;
    }
    if(root->right==NULL)
    {
        temp=root;
        root=root->left;
        delete temp;
        return root;
    }
    if(root->left==NULL)
    {
        temp=root;
        root=root->right;
        delete temp;
        return root;
    }

    temp=min(root->right);
    strcpy(root->key,temp->key);
    root->right=del(root->right,temp->key);
    return root;
}

node* dict::min(node* p)
{
    while(p->left!=NULL)
        p=p->left;
    return p;
}

node* dict::max(node* p)
{
    while(p->right!=NULL)
        p=p->right;
    return p;
}

void dict::printmax() {
    if (root==NULL) {
        cout<<"\nDictionary is empty";
        return;
    }
    node* maxnode = max(root);
    cout <<"\nMaximum key :"<<maxnode->key<<" "<<"Meaning :" << maxnode->meaning;
}

void dict::printmin(){
    if(root==NULL)
    {
        cout<<"\nDictionary is empty";
    }
    node* minnode=min(root);
    cout<<"\nMinimum Key :"<<minnode->key<<" "<<"Meaning :"<<minnode->meaning;
}

void dict::searchkey() {
    if (root==NULL) {
        cout<<"\nDictionary is empty";
        return;
    }
    char key[50];
    cout <<"\nEnter the keyword to search: ";
    cin >>key;

    if (search(root,key) == 1)
        cout << "\nKeyword Found";
    else
        cout << "\nKeyword not found";
}

void dict::updatemean() {
    if (root==NULL) {
        cout<<"\nDictionary is empty";
        return;
    }
    char key[50];
    cout<<"\nEnter the keyword to update: ";
    cin >> key;

    if (update(root, key) == 1)
        cout<<"\nMeaning updated";
    else
        cout<<"\nKeyword not found";

}

void dict::delkey() {
    if (root==NULL) {
        cout << "\nDictionary is empty";
        return;
    }
    char key[50];
    cout<<"\nEnter the keyword to delete: ";
    cin >> key;

    if (root==NULL) {
        cout<<"\nNo such keyword";
    } else {
        root = del(root, key);
        cout<<"Key deleted successfully!";
    }
}

void dict::dispdescwrap() 
{
    if (root == nullptr) {
        cout << "\nDictionary is empty";
        return;
    }
    displaydesc(root);
}


void dict::dispascwrap() 
{
    if(root==NULL)
    {
        cout<<"\nDictionary is empty...";
    }
    cout<<"\nSorted Data in Ascending Order:";
    displayasc(root);  
}

int main() {
    dict d;
    int choice;
    do {
        cout << "\nMenu:\n1.Create\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Print Maximum\n7.Print Minimum\n8.Display Sorted Ascending\n9.Display Sorted Descending\n10.Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                d.create();
                break;
            case 2:
                d.displaydict();
                break;
            case 3:
                d.searchkey();
                break;
            case 4:
                d.updatemean();
                break;
            case 5:
                d.delkey();
                break;
            case 6:
                d.printmax();
                break;
            case 7:
                d.printmin();
                break;
            case 8:
                cout<<"\nSorted Data in Ascending Order:";
                d.dispascwrap();
                break;
            case 9:
                cout<<"\nSorted Data in Descending Order:";
                d.dispdescwrap();
                break;
            case 10:
                cout << "\nExiting...";
                break;
            default:
                cout << "\nInvalid choice!";
        }
    } while (choice != 10);

    return 0;
}




