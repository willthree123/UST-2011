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
    rename("temp.txt", "student_list.txt");
}

void ffh_remove(char filename[] = "student_list.txt")
{
    remove(filename);
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
    //set up input stream
    ifstream ifs("student_list.txt");
    int line;
    int posCount = 0;
    bool isFound = false;
    // Check if the student already exists in the list
    while (ifs >> line)
    {
        if (line == student_id)
        {
            ifs.close();
            isFound = true;
            break;
        }
        // Count which line should the sid insert to
        posCount++;
    }
    
    if(!isFound){
        cout << "Student " << student_id << " is not taking the course!" << endl;
        return;
    }

    // Create a temp(output) file
    ofstream ofs;
    ofs.open("temp.txt"); // Another way to create a fstream object
    if (!ofs)
    {
        cerr << "Error: Can’t open \""
             << "temp.txt"
             << "\"\n";
        return;
    }

    // Reset the position of ifstream
    ifs.close();
    ifs.open("student_list.txt");

    //Perform file Copy
    int oPosCount =0;
    while (ifs >> line)
    {
        //Insert new records
        if (posCount!=oPosCount){
            ofs << line <<endl;
        }
        oPosCount++;
    }
    
    ifs.close();
    ofs.close();
    ffh_remove();
    ffh_rename();
    cout << "Student " << student_id << " is removed from the course!"<< endl;
    return;
}

// TODO: insert a student in the input file such that the student ids are in ascending order
// It should not insert duplicate student id.
// Please check the section "Hint" in the lab page for how to rename a file or remove a file.
void insert_student(int student_id)
{
    //set up input stream
    ifstream ifs("student_list.txt");
    int line;
    int posCount = 0;
    // Check if the student already exists in the list
    while (ifs >> line)
    {
        if (line == student_id)
        {
            cout << "Student " << student_id << " is already taking the course!"<< endl;
            ifs.close();
            return;
        }
        // Count which line should the sid insert to
        else if (line < student_id)
        {
            posCount++;
        }
    }

    // Create a temp(output) file
    ofstream ofs;
    ofs.open("temp.txt"); // Another way to create a fstream object
    if (!ofs)
    {
        cerr << "Error: Can’t open \""
             << "temp.txt"
             << "\"\n";
        return;
    }
    // Reset the position of ifstream
    ifs.close();
    ifs.open("student_list.txt");

    //Perform file Copy
    int oPosCount =0;
    while (ifs >> line)
    {
        //Insert new records
        if (posCount==oPosCount){
            ofs << student_id <<endl;
        }
        ofs << line <<endl;
        oPosCount++;
    }
    
    ifs.close();
    ofs.close();
    ffh_remove();
    ffh_rename();
    cout << "Student " << student_id << " is inserted successfully!"<< endl;
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