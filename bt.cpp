#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node {
	int data;
	Node *left, *right;

public:
	Node(int val) {
		data = val;
		left = right = NULL;
	}
	void print() {
		cout << data;
	}
	friend class BinaryTree;
};

class BinaryTree {
	Node *root;

public:
	BinaryTree() {
		root = NULL;
	}

	// setRoot
	void setRoot(Node *node) {
		root = node;
	}

	// getRoot
	Node* getRoot() {
		return root;
	}

	// Recursive Functions
	Node* buildTree(Node* root) {
		cout << "Enter the data: " << endl;
		int data;
		cin >> data;
		root = new Node(data);

		if (data == -1) {
			return NULL;
		}

		cout << "Enter data for inserting in left of " << data << endl;
		root->left = buildTree(root->left);
		cout << "Enter data for inserting in right of " << data << endl;
		root->right = buildTree(root->right);
		return root;
	}

	// Traversal
	// Inorder (Non-Recursive)
	void inorderNonRecursive() {
		stack<Node*> s;
		Node* current = root;

		while (current != NULL || !s.empty()) {
			while (current != NULL) {
				s.push(current);
				current = current->left;
			}

			current = s.top();
			s.pop();

			current->print();

			current = current->right;
		}
	}

	// Preorder (Non-Recursive)
	void preorderNonRecursive() {
		stack<Node*> s;
		s.push(root);

		while (!s.empty()) {
			Node* current = s.top();
			s.pop();

			current->print();

			if (current->right)
				s.push(current->right);
			if (current->left)
				s.push(current->left);
		}
	}

	// Postorder (Non-Recursive)
	void postorderNonRecursive() {
		stack<Node*> s;
		s.push(root);
		stack<Node*> output;

		while (!s.empty()) {
			Node* current = s.top();
			s.pop();
			output.push(current);

			if (current->left)
				s.push(current->left);
			if (current->right)
				s.push(current->right);
		}

		while (!output.empty()) {
			Node* temp = output.top();
			output.pop();
			temp->print();
		}
	}

    Node* mirror(Node* root) {
        if (root == NULL)
            return NULL;

        mirror(root->left);
        mirror(root->right);

        Node* temp=root->left;
        root->left=root->right;
        root->right=temp;
        
        return temp;
    }

    void eraseTree(Node* root) {
        if (root == NULL)
            return;

        eraseTree(root->left);
        eraseTree(root->right);
        delete root;
    }

    int countLeafNodes(Node* root) {
        if (root == NULL)
            return 0;
        if (root->left == NULL && root->right == NULL)
            return 1;
        return countLeafNodes(root->left) + countLeafNodes(root->right);
    }

    int countInternalNodes(Node* root) {
        if (root == NULL || (root->left == NULL && root->right == NULL))
            return 0; 
        return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
    }


    int calculateHeight(Node* root) {
        if (root == NULL)
            return 0;
        return 1 + max(calculateHeight(root->left), calculateHeight(root->right));
    }

    Node* copyTree(Node* root) {
        if (root == NULL)
            return NULL;

        Node* copy = new Node(root->data);
        copy->left = copyTree(root->left);
        copy->right = copyTree(root->right);
        return copy;
    }



};

int main() {
    BinaryTree bt;
    int choice;
    bool flag = true;

    while (flag) {
        cout << "\n====== Binary Tree Menu ======\n";
        cout << "1. Create Tree (Recursive)\n";
        cout << "2. Print Inorder Traversal (Non-Recursive)\n";
        cout << "3. Print Preorder Traversal (Non-Recursive)\n";
        cout << "4. Print Postorder Traversal (Non-Recursive)\n";
        cout << "5. Create Mirror Tree\n";
        cout << "6. Copy Tree\n";
        cout << "7. Erase Tree\n";
        cout << "8. Calculate Leaf Nodes\n";
        cout << "9. Calculate Internal Nodes\n";
        cout << "10. Calculate Height\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Creating Tree (Recursive)\n";
                bt.setRoot(bt.buildTree(bt.getRoot()));
                break;
            case 2:
                 bt.inorderNonRecursive();
                 break;
            case 3:
                 bt.preorderNonRecursive();
                 break;
            case 4:
                 bt.postorderNonRecursive();
                 break;
            case 5:
                bt.setRoot(bt.mirror(bt.getRoot()));
                cout << "Mirror tree created.\n";
                break;
            case 6:
                bt.setRoot(bt.copyTree(bt.getRoot()));
                cout << "Tree copied.\n";
                break;
            case 7:
                bt.eraseTree(bt.getRoot());
                cout << "Tree erased.\n";
                break;
            case 8:
                cout << "Leaf Nodes: " << bt.countLeafNodes(bt.getRoot()) << endl;
                break;
            case 9:
                cout << "Internal Nodes: " << bt.countInternalNodes(bt.getRoot()) << endl;
                break;
            case 10:
                cout << "Height of the tree: " << bt.calculateHeight(bt.getRoot()) << endl;
                break;
            case 11:
                flag = false;
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    }

    return 0;
}
