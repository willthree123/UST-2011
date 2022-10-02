#include <iostream>
#include <fstream>

using namespace std;

// Do not change this function. It is used for checking the lab.
void prepare_files()
{
    ofstream ofs("student_list.txt");

    if (ofs)
    {
        ofs << 20185639 << endl;
        ofs << 22435497 << endl;
        ofs << 23143658 << endl;
        ofs << 29372413 << endl;
        ofs << 29567638 << endl;
        ofs << 29576389 << endl;
    }
}

// Do not change this function. It is used for checking the lab.
void check_final_list()
{
    ifstream ifs("student_list.txt");
    if (ifs)
    {
        int line;
        while (ifs >> line)
        {
            cout << line << endl;
        }
        ifs.close();
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

void ffh_copy()
{
    ifstream ifs("student_list.txt"); // One way to create a fstream object
    if (!ifs)
    {
        cerr << "Error: Can’t open \""
             << "student_list.txt"
             << "\"\n";
        return;
    }
    ofstream ofs;
    ofs.open("temp.txt"); // Another way to create a fstream object
    if (!ofs)
    {
        cerr << "Error: Can’t open \""
             << "temp.txt"
             << "\"\n";
        return;
    }

    char c;
    ifs.get(c);        // Try to get the first char
    while (!ifs.eof()) // Check if EOF is reached
    {
        ofs.put(c); // Copy one char at a time
        ifs.get(c); // Try to get the next char
    }
    ifs.close();
    ofs.close();
    return;
}
void ffh_rename()
{
    if (rename("temp.txt", "student_list.txt") == 0)
        cout << "The file is successfully renamed" << endl;
    else
        cout << "Error renaming file" << endl;
}

void ffh_remove(char filename[] = "student_list.txt")
{
    if (remove(filename) == 0)
        cout << "The file is successfully removed" << endl;
    else
        cout << "Error removing file" << endl;
}

void getValueToArray()
{
    ifstream ifs("student_list.txt");

    int line;
    while (ifs >> line)
    {
        cout << line << endl;
    }
    ifs.close();
}
// TODO: search for a student in the input file, student_list.txt, return true if found.
bool student_lookup(int student_id)
{
    ifstream ifs("student_list.txt");

    int line;
    while (ifs >> line)
    {
        if (line == student_id)
        {
            ifs.close();
            return true;
        }
    }
    ifs.close();
    return false;
}

// TODO: delete a student id from the input file.
// The result should not contain blank lines
// Please check the section "Hint" in the lab page for how to rename a file or remove a file.
void delete_student(int student_id)
{
}

// TODO: insert a student in the input file such that the student ids are in ascending order
// It should not insert duplicate student id.
// Please check the section "Hint" in the lab page for how to rename a file or remove a file.
void insert_student(int student_id)
{
    ifstream ifs("student_list.txt");
    int line;
    int count = 0;
    // Check if the student already exists in the list
    while (ifs >> line)
    {
        count ++;
        if (line == student_id)
        {
            cout << "Student " << student_id << " is already taking the course!";
            ifs.close();
            return;
        }
        else if ()
        {
        }
    }
    ifs.close();
    
    // Insert the SID in the list

    ifstream ifs("student_list.txt");
    
    cout << "Student " << student_id << " is inserted successfully!";
}

int main()
{

    const char filename[] = "student_list.txt";
    char choice;
    int student_id;

    prepare_files();

    while (true)
    {

        cout << "1 for lookup; 2 for insertion; 3 for deletion; q for quit: ";
        cin >> choice;

        if (choice == '1')
        {
            cout << "Please enter the id of the student you want to search for: ";
            cin >> student_id;
            if (student_lookup(student_id))
            {
                cout << "Student " << student_id << " is found!" << endl;
            }
            else
            {
                cout << "Student " << student_id << " is not found!" << endl;
            }
        }
        else if (choice == '2')
        {
            cout << "Please enter the id of the student you want to insert: ";
            cin >> student_id;
            insert_student(student_id);
        }
        else if (choice == '3')
        {
            cout << "Please enter the id of the student you want to delete: ";
            cin >> student_id;
            delete_student(student_id);
        }
        else if (choice == 'q')
        {
            check_final_list();
            break;
        }
        else
        {
            cout << "Invalid input. Please input again." << endl;
        }
        cout << endl;
    }

    return 0;
}