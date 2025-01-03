#include <iostream>
#include <string>
using namespace std;

class Student {
    string name;
    int marks;

public:
    Student() {
        name = "";
        marks = 0;
    }

    Student(string name, int marks) {
        this->name = name;
        this->marks = marks;
    }

    void setStudent() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    int getMarks() { return marks; }
    string getName() { return name; }

    void display() { cout << "Name: " << name << " Marks: " << marks << endl; }

    friend class MinHeap;
};

class MinHeap {
    Student **heap;
    int capacity; // capacity of heap
    int size;     // current no of data

    int parent(int i) {
        return (i - 1) / 2;
    }
    int leftChild(int i) {
        return 2 * i + 1;
    }
    int rightChild(int i) {
        return 2 * i + 2;
    }

    void swap(Student *&a, Student *&b) {
        Student *temp = a;
        a = b;
        b = temp;
    }

    void minHeapify(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;

        if (left < size && heap[left]->marks < heap[smallest]->marks) {
            smallest = left;
        }

        if (right < size && heap[right]->marks < heap[smallest]->marks) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            minHeapify(smallest);
        }
    }

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        heap = new Student *[capacity];
        size = 0;
    }

    void insert(Student *student) {
        if (size == capacity) {
            return;
        }
        size++;

        int currentIndex = size - 1;
        heap[currentIndex] = student;

        while (currentIndex > 0 && heap[currentIndex]->marks < heap[parent(currentIndex)]->marks) {
            swap(heap[currentIndex], heap[parent(currentIndex)]);
            currentIndex = parent(currentIndex);
        }
    }

    Student *extractMin() {
        if (size == 0)
            return nullptr;

        Student *minStudent = heap[0];

        heap[0] = heap[size - 1]; // replace root with last element

        size--;
        minHeapify(0); // again heapify

        return minStudent;
    }
};

void heapSort(Student *arr[], int n) {
    MinHeap minHeap(n);

    for (int i = 0; i < n; i++) {
        minHeap.insert(arr[i]);
    }

    for (int i = 0; i < n; i++) {
        arr[i] = minHeap.extractMin();
    }
}

int main() {
    int ch;
    int numStudents;

    cout << "Enter No. of Students: ";
    cin >> numStudents;
    bool flag = true;

    Student *students[numStudents];

    while (flag) {
        cout << "\n===== Heap Sort =====" << endl;
        cout << "1. Add Students" << endl;
        cout << "2. Sort Students (Minimum Marks First)" << endl;
        cout << "3. Print Min Marks" << endl;
        cout << "4. Exit" << endl;
        cout << "----------------------" << endl;
        cout << "\nEnter Your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: {
                for (int i = 0; i < numStudents; i++) {
                    Student *new_student = new Student();
                    new_student->setStudent();
                    students[i] = new_student;
                }
                cout << "Students Added!" << endl;
                break;
            }
            case 2: {
                cout << "Sorted Students (Minimum Marks First): " << endl;
                heapSort(students, numStudents);
                for (int i = 0; i < numStudents; i++) {
                    cout << i + 1 << ". " << students[i]->getName() << " - " << students[i]->getMarks() << endl;
                }
                break;
            }
            case 3: {
                cout << "Student with Min Marks: " << endl;
                cout << "Name: " << students[0]->getName() << endl;
                cout << "Marks: " << students[0]->getMarks() << endl;
                break;
            }
            case 4: {
                cout << "Exiting... Thank You" << endl;
                flag = false;
                break;
            }
            default: {
                cout << "Invalid Input" << endl;
                break;
            }
        }
    }

    return 0;
}
