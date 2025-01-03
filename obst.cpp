#include <iostream>
using namespace std;
#define INT_MAX = 9999;

class Node
{
    int data;
    int prob;
    Node *left;
    Node *right;

public:
    Node() 
    {

    }
    Node(int data, int prob, Node *left = NULL, Node *right = NULL)
    {
        this->data = data;
        this->prob = prob;
        this->left = left;
        this->right = right;
    }
    friend class OBST;
};

class Pair
{
    int weight;
    int root;

public:
    Pair()
    {
        weight = -1;
        root = -1;
    }
    Pair(int weight, int root = -1)
    {
        this->weight = weight;
        this->root = root;
    }
    friend class OBST;
};

class OBST
{
    Pair **matrix;
    Node *index;
    int nodes;

public:
    OBST() {}
    OBST(int n)
    {
        nodes = n + 1;
        matrix = new Pair *[nodes];
        index = new Node[nodes];
        for (int w = 0; w < nodes; w++)
        {
            matrix[w] = new Pair[nodes];
            for (int v = 0; v < nodes; v++)
            {
                if (v == w)
                    matrix[w][v] = Pair(0, -1);
            }
        }
    }

    void enterNode()
    {
        index[0] = Node(-1, -1);
        for (int i = 1; i < nodes; i++)
        {
            cout << "Enter data and probability of search:";
            int data;
            int prob;
            cin >> data >> prob;
            index[i] = Node(data, prob);
        }
    }

    void optimize()
    {
        for (int diff = 0; diff < nodes; diff++)
        {
            for (int i = 0; i < nodes; i++)
            {
                for (int j = 0; j < nodes; j++)
                {
                    if (j - i == diff)
                        calcMin(i, j);
                }
            }
        }
    }

    // Calculate minimum cost for i to j by taking a node k inbetween i and j

    int calcMin(int i, int j)
    {
        if (i >= j)
            return 0;

        if (matrix[i][j].weight != -1)
            return matrix[i][j].weight;

        int result = 9999;
        int curr = 0;
        int root = -1;
        for (int k = i + 1; k <= j; k++)
        {
            curr = calcMin(i, k - 1) + calcMin(k, j) + calcWeight(i, j);
            if (curr < result)
            {
                result = curr;
                root = k;
            }
        }
        matrix[i][j].weight = result;
        matrix[i][j].root = root;
        return result;
    }

    // Calculate the summation of weights from ith to jth node

    int calcWeight(int i, int j)
    {
        if (i >= j)
            return 0;
        int sum = 0;
        for (int x = i + 1; x <= j; x++)
            sum += index[x].prob;
        return sum;
    }

    void print()
    {
        optimize();
        cout << endl;
        for (int i = 0; i < nodes; i++)
        {
            for (int j = 0; j < nodes; j++)
            {
                cout << matrix[i][j].weight << "  (" << matrix[i][j].root << ") ";
            }
            cout << endl;
        }
    }

    Node *buildTree(int i, int j)
    {
        if (i == j)
            return NULL;
        int temp = matrix[i][j].root;
        Node *node = &index[temp];
        node->left = buildTree(i, temp - 1);
        node->right = buildTree(temp, j);
        return node;
    }

    void inorder(Node *root)
    {
        if (!root)
            return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void preorder(Node *root)
    {
        if (!root)
            return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
};

int main()
{
    OBST t1(4);
    t1.enterNode();
    t1.print();
    Node *root = t1.buildTree(0, 4);
    t1.preorder(root);
    cout << endl;
    t1.inorder(root);
    return 0;
}