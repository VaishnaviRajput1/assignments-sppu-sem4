#include <iostream>
using namespace std;

class Heap {
    int arr[100];
   

public:
 int size;
    Heap() {
        arr[0] = -1;
        size = 0;
    }

    void insert(int values[], int numValues) {
        for (int i = 0; i < numValues; ++i) {
            size = size + 1;
            int index = size;
            arr[index] = values[i];

            while (index > 1) {
                int parent = index / 2;
                if (arr[parent] < arr[index]) {
                    swap(arr[parent], arr[index]);
                    index = parent;
                } else {
                    break;
                }
            }
        }
    }

 void deltee1() {
    if (size == 0) {
        cout << "Heap is empty\n";
        return;
    }
    arr[1] = arr[size];
    size--;
    heapify(arr, size, 1);
    heapsort();
    display();// Sort the heap after deleting the top element
}
    void display() {
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }
    }

    void heapsort() {
        for (int i = size; i > 1; i--) {
            swap(arr[i], arr[1]); // swap last element and first element
            heapify(arr, i - 1, 1);
        }
    }

    void heapify(int arr[], int n, int i) {
        int largest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= n && arr[largest] < arr[left]) {
            largest = left;
        }
        if (right <= n && arr[largest] < arr[right]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[largest], arr[i]);
            heapify(arr, n, largest);
        }
    }
};


int main() {
    Heap h;
    int choice, numValues;
    int values[100]; // Declare values array outside switch block

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Display\n";
        cout << "4. Sort\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the number of values to insert: ";
                cin >> numValues;
                cout << "Enter " << numValues << " values: ";
                for (int i = 0; i < numValues; ++i) {
                    cin >> values[i];
                }
                h.insert(values, numValues);
                break;
            case 2:
                h.deltee1();
                cout << "Deleted top element\n";
                break;
            case 3:
                cout << "Heap elements: ";
                h.display();
                cout << endl;
                break;
            case 4:
                h.heapsort();
                cout << "Sorted heap: ";
                h.display();
                cout << endl;
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 5);

    return 0;
}