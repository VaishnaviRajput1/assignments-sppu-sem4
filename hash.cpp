#include <iostream>
#include <cstring>
#define max 10
using namespace std;

class hashtable {
    int phone;
    int ht[max];
public:
    hashtable() {
        for (int i = 0; i < max; i++) {
            ht[i] = 0;
        }
    }
    int hash(long int);
    void insertwithreplacement();
    void insertwithoutreplacement();
    void display();
    void search();
    void remove();
};

int hashtable::hash(long int key) {
    return (key % max);
}

void hashtable::insertwithreplacement() {
    int idx;
    long int key;
    char ch;
    do {
        cout << "Enter the Phone number: " << endl;
        cin >> key;
        idx = hash(key);
        if (ht[idx] == 0) 
        {
            ht[idx] = key;
        }
        else 
        {
            // Linear probing with replacement
            int startPos = idx;
            do {
                idx = (idx + 1) % max;
            }while (ht[idx] != 0 && idx != startPos);

            if (ht[idx] == 0) 
            {
                ht[idx] = key;
            } 
            else 
            {
                cout << "Hash table is full. Cannot insert." << endl;
                break;
            }
        }
        cout << "Do you want to continue? (Y/N): ";
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');
}

void hashtable::insertwithoutreplacement() {
    int ipos;
    long int key;
    char ans;
    do {
        cout << "Enter the phone number: " << endl;
        cin >> key;
        ipos = hash(key);
        int startpos = ipos;

        while (ht[ipos] != 0 && ht[ipos] != key && ipos != startpos) {
            ipos = (ipos + 1) % max;
        }

        if (ht[ipos] == 0) {
            ht[ipos] = key;
        } else if (ht[ipos] == key) {
            cout << "Duplicate entry. Cannot insert." << endl;
        } else {
            // Continue probing for the next available slot
            int original_ipos = ipos;
            do {
                ipos = (ipos + 1) % max;
            } while (ht[ipos] != 0 && ipos != original_ipos);
            
            if (ht[ipos] == 0) {
                ht[ipos] = key;
            } else {
                cout << "Hash table is full. Cannot insert." << endl;
                break;
            }
        }

        cout << "do you want to continue? (y/n): ";
        cin >> ans;
    } while (ans == 'y');
}

void hashtable::display() {
    cout << "------------------------" << endl;
    cout << "Location\t PhoneNumber\n";
    cout << "------------------------" << endl;
    for (int i = 0; i < max; i++) {
        cout << i << "\t\t" << ht[i] << endl;
    }
}

void hashtable::search() {
    int key;
    cout << "Enter the value you want to search: ";
    cin >> key;

    int comparisons = 0;
    int idx = hash(key);

    while (ht[idx] != key && ht[idx] != 0 && comparisons < max) {
        idx = (idx + 1) % max;
        comparisons++;
    }
    if (ht[idx] == key) {
        cout << "Number found at index " << idx << endl;
        cout << "Number of comparisons: " << comparisons + 1 << endl;
    } else {
        cout << "Number is not present" << endl;
        cout << "Number of comparisons: " << comparisons << endl;
    }
}

void hashtable::remove() {
    int key;
    cout << "Enter the value you want to delete: ";
    cin >> key;
    int comparisons = 0;
    int idx = hash(key);

    while (ht[idx] != key && ht[idx] != 0 && comparisons < max) {
        idx = (idx + 1) % max;
        comparisons++;
    }
    if (ht[idx] == key) {
        ht[idx] = 0;
        cout << "Number deleted" << endl;
        cout << "Number of comparisons: " << comparisons + 1 << endl;
    } else {
        cout << "Number is not present" << endl;
        cout << "Number of comparisons: " << comparisons << endl;
    }
}

int main() {
    hashtable ht;
    int choice;
    do {
        cout << "\nMENU\n";
        cout << "1. Insert with replacement\n";
        cout << "2. Insert without replacement\n";
        cout << "3. Delete\n";
        cout << "4. Search\n";
        cout << "5. Display\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                ht.insertwithreplacement();
                break;
            case 2:
                ht.insertwithoutreplacement();
                break;
            case 3:
                ht.remove();
                break;
            case 4:
                ht.search();
                break;
            case 5:
                ht.display();
                break;
            case 6:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice. Please try again.";
        }
    } while (choice != 6);

    return 0;
}
