#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

class Student
{
    int roll;
    char name[20];
    char division;
    char add[50];

public:
    Student()
    {
        roll = 0;
        strcpy(name, "");
        division='\0';
        strcpy(add,"");
    }

    void getStudentData()
    {
        cout << "Enter Roll No: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 19);
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin.ignore(); // Clear input buffer
        cin.getline(add, 49);
    }

    void displayStudentData()
    {
        cout << "Roll No : " << roll << endl;
        cout << "Name    : " << name << endl;
        cout << "Division  : " << division << endl;
        cout << "Address   : " << add << endl;
        cout << "------------------------------------------" << endl;
    }
    friend class StudentDB;
};

class StudentDB
{
    Student s;

public:
    // store data in file
    int saveStudent()
    {
        s.getStudentData();
        if (s.roll == 0 && strcmp(s.name, "") && s.division == '\0' && strcmp(s.add, ""))
        {
            cout << "Please Add data to save!" << endl;
            return 0;
        }
        else
        {
            ofstream fout;
            fout.open("datafile.dat", ios::app | ios::binary);
            // write that object to file
            fout.write((char *)&s, sizeof(s));
            fout.close();
        }
        return 1;
    }

    // read data
    void readStudent()
    {
        ifstream fin;
        Student s;
        fin.open("datafile.dat", ios::in | ios::binary);

        if (!fin)
        {
            cout << "File Not Found!!" << endl;
        }
        else
        {
            fin.read((char *)&s, sizeof(s));
            while (!fin.eof())
            {
                s.displayStudentData();
                fin.read((char *)&s, sizeof(s));
            }
        }
    }


    void searchStudent(string name)
    {
        ifstream fin;
        Student s;
        fin.open("datafile.dat", ios::in | ios::binary);

        if (!fin)
        {
            cout << "File Not Found!!" << endl;
        }
        else
        {
            fin.read((char *)&s, sizeof(s));
            while (!fin.eof())
            {
                if (s.name == name)
                {
                    s.displayStudentData();
                    return;
                }
                fin.read((char *)&s, sizeof(s));
            }
        }
    }

    void deleteStudent(string name)
{
    ifstream fin("datafile.dat", ios::in | ios::binary);
    ofstream fout("tempfile.dat", ios::out | ios::binary);

    if (!fin)
    {
        cout << "File Not Found!" << endl;
        return;
    }

    Student s;

    bool deleted = false; // Flag to track if a student was deleted

    while (fin.read((char *)&s, sizeof(s))) // Read a student object from the input file
    {
        if (s.name == name) // Check if the name matches the name to be deleted
        {
            cout << "Student found and deleted: " << endl;
            s.displayStudentData(); // Display the details of the deleted student
            deleted = true; // Set the deleted flag to true
        }
        else
        {
            fout.write((char *)&s, sizeof(s)); // Write the student object to the output file
        }
    }

    fin.close(); // Close the input file
    fout.close(); // Close the output file

    if (!deleted) // If no student was deleted
    {
        cout << "Student with name '" << name << "' not found." << endl;
    }
    else
    {
        remove("datafile.dat"); // Remove the original file
        rename("tempfile.dat", "datafile.dat"); // Rename the temporary file to the original file name
    }
}

};

int main()
{
    cout << "Sequential Files in CPP" << endl; // prints Hashing

    StudentDB s1;

    bool flag = true;
    string data;

    while (flag)
    {
        cout << "1. Add new Student (save)" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Exit..." << endl;
        int ch;
        cout << "\nEnter Your Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            s1.saveStudent();
            break;
        case 2:
            s1.readStudent();
            break;

        case 3:
            cout << "Enter Name to search: ";
            cin >> data;
            s1.searchStudent(data);
            break;
        case 4:
            cout << "Enter Name to delete: ";
            cin >> data;
            s1.deleteStudent(data);
            break;
        case 5:
            cout << "Exiting...";
            flag = false;
            break;
        default:
            cout << "Invalid Entry" << endl;
            break;
        }
    }
    return 0;
}