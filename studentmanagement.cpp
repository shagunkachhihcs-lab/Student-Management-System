#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Student
{
    int rollNo;
    string name;
    string course;
    float marks;
    float percentage;
    char grade;
};

Student students[100];
int count = 0;

// Calculate percentage and grade
void calculateResult(Student &s)
{
    s.percentage = s.marks;

    if (s.percentage >= 90)
        s.grade = 'A';
    else if (s.percentage >= 80)
        s.grade = 'B';
    else if (s.percentage >= 70)
        s.grade = 'C';
    else if (s.percentage >= 60)
        s.grade = 'D';
    else if (s.percentage >= 50)
        s.grade = 'E';
    else
        s.grade = 'F';
}

// Check whether roll number already exists
bool rollNumberExists(int rollNo)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
            return true;
    }

    return false;
}

// Save data to file
void saveData()
{
    ofstream file("students.txt");

    if (!file)
    {
        cout << "\nError while saving data!\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        file << students[i].rollNo << endl;
        file << students[i].name << endl;
        file << students[i].course << endl;
        file << students[i].marks << endl;
    }

    file.close();
}

// Load data from file
void loadData()
{
    ifstream file("students.txt");

    if (!file)
        return;

    while (file >> students[count].rollNo)
    {
        file.ignore();

        getline(file, students[count].name);
        getline(file, students[count].course);

        file >> students[count].marks;

        calculateResult(students[count]);

        count++;

        if (count >= 100)
            break;
    }

    file.close();
}

// Add student
void addStudent()
{
    if (count >= 100)
    {
        cout << "\nStudent limit reached!\n";
        return;
    }

    Student s;

    cout << "\n===== ADD STUDENT =====\n";

    cout << "Enter Roll No: ";
    cin >> s.rollNo;

    if (rollNumberExists(s.rollNo))
    {
        cout << "\nThis Roll No already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Course: ";
    getline(cin, s.course);

    cout << "Enter Marks (0-100): ";
    cin >> s.marks;

    if (s.marks < 0 || s.marks > 100)
    {
        cout << "\nInvalid marks! Enter marks between 0 and 100.\n";
        return;
    }

    calculateResult(s);

    students[count] = s;
    count++;

    saveData();

    cout << "\nStudent added successfully!\n";
}

// Display students
void displayStudents()
{
    if (count == 0)
    {
        cout << "\nNo students found.\n";
        return;
    }

    cout << "\n================ STUDENT LIST ================\n";

    cout << left
         << setw(10) << "Roll No"
         << setw(20) << "Name"
         << setw(15) << "Course"
         << setw(10) << "Marks"
         << setw(15) << "Percentage"
         << setw(8) << "Grade"
         << endl;

    cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        cout << left
             << setw(10) << students[i].rollNo
             << setw(20) << students[i].name
             << setw(15) << students[i].course
             << setw(10) << students[i].marks
             << setw(15) << students[i].percentage
             << setw(8) << students[i].grade
             << endl;
    }
}

// Search student
void searchStudent()
{
    int rollNo;

    cout << "\nEnter Roll No to search: ";
    cin >> rollNo;

    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            cout << "\n===== STUDENT FOUND =====\n";

            cout << "Roll No     : " << students[i].rollNo << endl;
            cout << "Name        : " << students[i].name << endl;
            cout << "Course      : " << students[i].course << endl;
            cout << "Marks       : " << students[i].marks << endl;
            cout << "Percentage  : " << students[i].percentage << "%" << endl;
            cout << "Grade       : " << students[i].grade << endl;

            return;
        }
    }

    cout << "\nStudent not found!\n";
}

// Update student
void updateStudent()
{
    int rollNo;

    cout << "\nEnter Roll No to update: ";
    cin >> rollNo;

    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            cin.ignore();

            cout << "\nEnter New Name: ";
            getline(cin, students[i].name);

            cout << "Enter New Course: ";
            getline(cin, students[i].course);

            cout << "Enter New Marks (0-100): ";
            cin >> students[i].marks;

            if (students[i].marks < 0 || students[i].marks > 100)
            {
                cout << "\nInvalid marks!\n";
                return;
            }

            calculateResult(students[i]);

            saveData();

            cout << "\nStudent updated successfully!\n";

            return;
        }
    }

    cout << "\nStudent not found!\n";
}

// Delete student
void deleteStudent()
{
    int rollNo;

    cout << "\nEnter Roll No to delete: ";
    cin >> rollNo;

    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            for (int j = i; j < count - 1; j++)
            {
                students[j] = students[j + 1];
            }

            count--;

            saveData();

            cout << "\nStudent deleted successfully!\n";

            return;
        }
    }

    cout << "\nStudent not found!\n";
}

// Main function
int main()
{
    loadData();

    int choice;

    do
    {
        cout << "\n\n============================================";
        cout << "\n       STUDENT MANAGEMENT SYSTEM";
        cout << "\n============================================";

        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";

        cout << "\n--------------------------------------------";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}