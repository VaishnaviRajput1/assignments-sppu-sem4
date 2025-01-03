#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class node
{
    string keyword;
    string meaning;
    int height;
    int balanceFactor; // New member to store balance factor
    node *left;
    node *right;
public:
    node(string key, string mean)
    {
        keyword = key;
        meaning = mean;
        height = 1;
        balanceFactor = 0; // Initialize balance factor to 0
        left = NULL;
        right = NULL;
    }
    friend class avl;
};

class avl
{
    node *root;
public:
    avl()
    {
        root = NULL;
    }
    int Update_height(node *c);
    int balance_factor(node *c);
    node* balance(node *c);
    node* insert(node *&c, string key, string mean);
    node* LLrotation(node *c);
    node* RRrotation(node *c);
    node* LRrotation(node *c);
    node* RLrotation(node *c);
    void inorder(node *c);
    void inorderReverse(node *c);
    bool search(node *c, string key);
    void level_traverse(node *c);
    void displaydata(node*c);
    node* get_root();
    int maxComparisons(node *c, string key);
};

//avl functions

node* avl::get_root()
{
    return root;
}

int avl::Update_height(node *c)
{
    if (c == NULL)
    {
        return 0;
    }
    c->height = (max((Update_height(c->left)), (Update_height(c->right))) + 1);
    c->balanceFactor = balance_factor(c); // Update balance factor
    return c->height;
}

int avl::balance_factor(node *c)
{
    if (c == NULL)
    {
        return 0;
    }
    return ((Update_height(c->left)) - (Update_height(c->right)));
}

node* avl::balance(node *c)
{
    if (balance_factor(c) == 2)
    {
        if (balance_factor(c->left) < 0)
        {
            c = LRrotation(c);
        }
        else
        {
            c = LLrotation(c);
        }
    }
    else if (balance_factor(c) == -2)
    {
        if (balance_factor(c->right) > 0)
        {
            c = RLrotation(c);
        }
        else
        {
            c = RRrotation(c);
        }
    }
    Update_height(c);
    return c;
}

node* avl::insert(node *&c, string key, string mean)
{
    if (c == NULL)
    {
        c = new node(key, mean);
        return c;
    }
    if (c->keyword < key)
    {
        c->right = insert(c->right, key, mean);
    }
    else if (c->keyword > key)
    {
        c->left = insert(c->left, key, mean);
    }
    return balance(c);
}

node* avl::LLrotation(node *c)
{
    node *new1 = c->left;
    c->left = new1->right;
    new1->right = c;
    Update_height(c);
    Update_height(new1);
    return new1;
}

node* avl::RRrotation(node *c)
{
    node *new1 = c->right;
    c->right = new1->left;
    new1->left = c;
    Update_height(c);
    Update_height(new1);
    return new1;
}

node* avl::LRrotation(node *c)
{
    c->left = RRrotation(c->left);
    return LLrotation(c);
}

node* avl::RLrotation(node *c)
{
    c->right = LLrotation(c->right);
    return RRrotation(c);
}

void avl::inorder(node *c)
{
    if (c == NULL)
    {
        return;
    }
    inorder(c->left);
    cout << c->keyword << ": " << c->meaning << " (Balance Factor: " << c->balanceFactor << ")" << endl;
    inorder(c->right);
}

void avl::inorderReverse(node *c)
{
    if (c == NULL)
    {
        return;
    }
    inorderReverse(c->right);
    cout << c->keyword << ": " << c->meaning << " (Balance Factor: " << c->balanceFactor << ")" << endl;
    inorderReverse(c->left);
}

bool avl::search(node *c, string key)
{
    if (c == NULL)
    {
        return false;
    }
    else if (c->keyword < key)
    {
        return search(c->right, key);
    }
    else if (c->keyword > key)
    {
        return search(c->left, key);
    }
    else
    {
        return true;
    }
}

void avl::level_traverse(node *c)
{
    if (c == NULL)
    {
        return;
    }
    node *queue[1000];
    int front = 0;
    int rear = 0;
    queue[rear++] = c;
    while (front != rear)
    {
        node *new1 = queue[front++];
        cout << new1->keyword << ": " << new1->meaning << " (Balance Factor: " << new1->balanceFactor << ")" << endl;
        if (new1->left != NULL)
        {
            queue[rear++] = new1->left;
        }
        if (new1->right != NULL)
        {
            queue[rear++] = new1->right;
        }
    }
}

void avl::displaydata(node *c)
{
    if (c == NULL)
    {
        return;
    }
    displaydata(c->left);
    cout << c->keyword << ": " << c->meaning<<"(Balance Factor : "<<c->balanceFactor<<" )" << endl;
    displaydata(c->right);
}


int avl::maxComparisons(node *c, string key)
{
    if (c == NULL)
    {
        return 0;
    }
    else if (c->keyword < key)
    {
        return 1 + maxComparisons(c->right, key);
    }
    else if (c->keyword > key)
    {
        return 1 + maxComparisons(c->left, key);
    }
    else
    {
        return 1;
    }
}

int main()
{
    int c = 1;
    avl t;
    string key, meaning;
    node *p = NULL;
    while (c > 0)
    {
        cout << "MENU" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Search" << endl;
        cout << "3.Display Entered Data" << endl;
        cout << "4.Inorder (Ascending)" << endl;
        cout << "5.Inorder (Descending)" << endl;
        cout << "6.Level Order Traversing" << endl;
        cout << "7.Exit" << endl;
        cout << "Enter Your Choice:";
        cin >> c;
        if (c == 1)
        {
                cout << "Enter keyword:" << endl;
                cin >> key;
                cout << "Enter meaning:" << endl;
                cin >> meaning;
                p = t.insert(p, key, meaning);
            
        }
        else if (c == 2)
        {
            cout << "Enter keyword to search:" << endl;
            cin >> key;
            if (t.search(p, key))
            {
                cout << "Keyword Found" << endl;
            }
            else
            {
                cout << "Keyword not found" << endl;
            }
            cout << "Maximum comparisons required: " << t.maxComparisons(p, key) << endl;
        }
        else if (c == 3)
        {
            t.displaydata(p);
        }
        else if (c == 4)
        {
            cout << "Inorder traversal (Ascending):" << endl;
            t.inorder(p);
            cout << endl;
        }
        else if (c == 5)
        {
            cout << "Inorder traversal (Descending):" << endl;
            t.inorderReverse(p);
            cout << endl;
        }
        else if (c == 6)
        {
            cout << "Level Order Traversing:" << endl;
            t.level_traverse(p);
            cout << endl;
        }
        else if (c == 7)
        {
            cout << "Exiting..." << endl;
        }
        else
        {
            cout << "Wrong Choice" << endl;
        }
    }
    return 0;
}
