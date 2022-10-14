#include <iostream>
#include <ctime>
using namespace std;

/* -------------------------------------------------------------- */
/* This part serves as a pseudo random number generator for auto grade purpose only */
/* You are suggested not to refer to these codes in this assignment. */
/* You are not allowed to use global variables in this course. */
unsigned int next_num = 1; // Here we initiate an unsigned integer to be used in the following functions.

unsigned int pa1_rand() // This function is used to return a pseudo random number from 0 to 32767.
{
    next_num = next_num * 1103515245 + 2011;
    return static_cast<unsigned int>(next_num / 65536) % 32768;
}
void pa1_srand(unsigned int seed) // This function is used to set a seed of the pseudo random number generator.
{
    next_num = seed;
}
/* Everytime you call pa1_rand(), you will get a new pseudo random number. For the same seed, the sequence of pseudo
   random number is fixed. For example, when seed = 3, the sequence of pseudo random number is fixed to be [17746,
   30897, 9622, 18921, 4034, 17510, 24152, 14388, 23665, 31532, ...]. When seed = 5, the sequence of pseudo random
   number is fixed to be [18655, 32247, 9873, 9718, 26373, 27678, 5314, 22512, 31845, 22885, ...] */
/* -------------------------------------------------------------- */

const int MAX_BOXES = 1000; // This constant stores the largest length of boxes[]. You can use it in your code.

// This function is used to fill the 1D array with a random sequence of unique numbers from 1 to the user input for the number of prisoners
void placeSlips(int boxes[], int num_prisoners)
{
    for (int i = 0; i < num_prisoners; i++)
        boxes[i] = -1;
    int counter = 0;
    while (counter < num_prisoners)
    {
        int num = pa1_rand() % (num_prisoners);
        if (boxes[num] == -1)
        {
            boxes[num] = counter;
            counter++;
        }
    }
}

// TASK 1: Simulate an actual riddle room
bool simulateRoom(const int boxes[], int num_prisoners, int num_trials)
{
    /* Please replace this to your own code below */
    int tempNo;   // To store a temp box number
    bool isFound; // Indicates whether the prisioner found the correct box
    // for all prisoners
    for (int i = 0; i < num_prisoners; i++)
    {
        // init variables
        isFound = false;
        // Start with the box with the same number as the prisoner
        // if the paper in side is the same
        if (boxes[i] == i)
        {
            continue;
            // to the next prisoner
        }
        else
        {
            // store the number on the paper to tempNo
            tempNo = boxes[i];

            // for the remaining try
            for (int j = 0; j < num_trials - 1; j++)
            {
                // cout<<j+2<<". box "<<tempNo<<": "<<boxes[tempNo]<<endl;

                // Open the box with the pervious number
                // if the paper in that box is the prisoner's own number
                if (boxes[tempNo] == i)
                {
                    // set isFound to true, indicating that prisoner found its own number paper
                    isFound = true;
                    // break the for loop, discarding the remaining try
                    break;
                }
                // if the paper in that box is not the prisoner's own number
                else
                {
                    // store the number on the paper to tempNo
                    tempNo = boxes[tempNo];
                }
            }
            // if prisoner could not find its own number paper
            // the simulation is over, return false
            if (!isFound)
            {
                return false;
            }
        }
    }
    // after all the loops, means all prisnor found its own number paper
    // so we can return the result, that all prisnors found its own number paper
    return true;
}

int task2_getCount(const int boxes[], int num_prisoners, int num_trials)
{
    int counter = 0;
    int tempNo;
    for (int i = 0; i < num_prisoners; i++)
    {
        // cout<<"1. box "<<i<<": "<<boxes[i]<<endl;
        if (boxes[i] == i)
        {
            counter++;
            continue;
        }
        else
        {
            tempNo = boxes[i];
            for (int j = 0; j < num_trials - 1; j++)
            {
                // cout<<j+2<<". box "<<tempNo<<": "<<boxes[tempNo]<<endl;
                if (boxes[tempNo] == i)
                {
                    counter++;
                    break;
                }
                else
                {
                    tempNo = boxes[tempNo];
                }
            }
        }
    }
    return counter;
}

void task2_minmaxPath(const int boxes[], int num_prisoners, int num_trials, int &longestPath, int &shortestPath, int longestPathArray[], int &loopCount, int &longestStartingPoint)
{
    /* Please replace this to your own code below */
    int tempNo;   // To store a temp box number
    bool isFound; // Indicates whether the prisioner found the correct box
    bool recording[MAX_BOXES];
    // an array indicating if the prisoners already been counted
    for (int init = 0; init < MAX_BOXES; init++)
    {
        recording[init] = false;
    }
    // cout << endl;
    // for all prisoners
    for (int i = 0; i < num_prisoners; i++)
    {
        if (recording[i])
            continue; // If the prisnor is already in a loop
        // cout << "i loop: " << i;
        // init variables
        int stepsCount = 0; // count the steps of the path

        // Start with the box with the same number as the prisoner
        tempNo = i;
        // the paper in the box is not prisoner's nubmer
        while (boxes[tempNo] != i)
        {
            recording[tempNo] = true;
            tempNo = boxes[tempNo];
            stepsCount++;
        }

        recording[tempNo] = true;
        stepsCount++;
        loopCount++;
        if (stepsCount > longestPath) // if prisnor has the longest path
        {
            // cout << "LONGEST ";
            longestPath = stepsCount;
            // cout << longestPath << " ";
            longestStartingPoint = i;
            // cout<<"starting :"<<longestStartingPoint<<"\t";
        }
        if (shortestPath > stepsCount) // if prisnor has the shortest path
        {
            // cout << "SHORTEST ";
            shortestPath = stepsCount;
            // cout << shortestPath << " ";
        }
        // cout << "steps: " << stepsCount << endl;
    }
    // Write the longest path into the array
    int idx = 0;
    // Start with the box with the same number as the prisoner
    tempNo = longestStartingPoint;

    // the paper in the box is not prisoner's nubmer
    while (boxes[tempNo] != longestStartingPoint)
    {
        longestPathArray[idx] = tempNo;
        tempNo = boxes[tempNo];
        idx++;
    }
    longestPathArray[idx] = tempNo;
}
// TASK 2: Display certain statistics for a given room
void statsRoom(const int boxes[], int num_prisoners, int num_trials)
{
    /* Here in this task, we provide some lines of code for your reference. Please write your code below and replace some of the given code */

    // init variables for the shortestPath/ longestPat
    int shortestPath = MAX_BOXES, longestPath = 0, loopCount = 0, longestStartingPoint = 0;
    // init the array that stores the longest path
    int longestPathArray[MAX_BOXES];
    for (int init = 0; init < MAX_BOXES; init++)
    {
        longestPathArray[init] = -1;
    }

    task2_minmaxPath(boxes, num_prisoners, num_trials, longestPath, shortestPath, longestPathArray, loopCount, longestStartingPoint);

    cout << "The number of prisoners who find their slips: " << task2_getCount(boxes, num_prisoners, num_trials) << endl;
    cout << "Number of loops: " << loopCount << endl;
    cout << "Smallest loop length: " << shortestPath << endl;
    cout << "Longest loop length: " << longestPath << endl;
    cout << "Largest loop: ";

    int idx = 0;
    while (longestPathArray[idx] != -1)
    {
        cout << longestPathArray[idx] << " ";
        idx++;
    }

    /* Please replace this to your own code */

    cout << endl;
}

// TASK 3: Find the number of instances in 1000 rooms when the prisoners will all be able to escape
double successRooms(int boxes[], int num_prisoners, int num_trials) //  suceess rate of 1000 rooms basically repeating it a 1000 times
{
    /* Please replace this to your own code below */
    double count = 0;
    for (int j = 1; j <= 1000; j++)
    {
        placeSlips(boxes, num_prisoners);
        if (simulateRoom(boxes, num_prisoners, num_trials) == true)
            count++;
    }
    return count;
}

// TASK 4: Nice guard will help the prisoners to successfully leave the room by breaking any loop which is greater than the number of trials
//         Return true if the intervention was applied, else return false
bool niceGuard(int boxes[], int num_prisoners, int num_trials)
{

    /* Please replace this to your own code below */
    int shortestPath = MAX_BOXES, longestPath = 0, loopCount = 0, longestStartingPoint = 0;
    // init the array that stores the longest path
    int longestPathArray[MAX_BOXES];

    task2_minmaxPath(boxes, num_prisoners, num_trials, longestPath, shortestPath, longestPathArray, loopCount, longestStartingPoint);

    if (longestPath > num_trials)
    {
        // cout << "SWAP" << endl;
        int swapTemp = boxes[longestPathArray[0]];
        boxes[longestPathArray[0]] = boxes[longestPathArray[0+longestPath/2]];
        // cout << "box: "<< longestPathArray[0] << " = "<<boxes[longestPathArray[0+longestPath/2]];
        boxes[longestPathArray[0+longestPath/2]] = swapTemp;
        // cout << "box: "<< longestPathArray[0+longestPath/2]  << " = "<<swapTemp;

        return true;
    }
    return false;
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED.

int main()
{

    int num_prisoners, num_trials, seed;
    // set boxes, priosoners

    cout << "Enter the number of prisoners (from 1 to 1000) :" << endl;
    cin >> num_prisoners;
    cout << "Enter the number of boxes each prisoner can open (from 1 to 1000) :" << endl;
    cin >> num_trials;
    cout << "Enter the seed for randomization else enter 0 and the system will randomize for you :" << endl;
    cin >> seed;

    if (seed == 0)
    {
        pa1_srand(time(NULL));
    }
    else
    {
        pa1_srand(seed);
    }

    int boxes[MAX_BOXES]; // array for the boxes
    for (int i = 0; i < MAX_BOXES; i++)
        boxes[i] = 0;

    int choice;
    cout << "Please choose an option:" << endl;
    cout << "0.Print the boxes" << endl;
    cout << "1.Simulate a room" << endl;
    cout << "2.Compute statistics of a room:" << endl;
    cout << "3.Compute success rate over 1000 rooms" << endl;
    cout << "4.Apply nice guard intervention in a room" << endl;
    cin >> choice;

    switch (choice)
    {
    case 0:
        placeSlips(boxes, num_prisoners);
        for (int i = 0; i < num_prisoners; i++)
            cout << boxes[i] << " ";
        cout << endl;
        break;
    case 1:
        placeSlips(boxes, num_prisoners);
        if (simulateRoom(boxes, num_prisoners, num_trials) == true)
        {
            cout << "Success! All prisoners found their slip." << endl;
        }
        else
        {
            cout << "Failure! Not all prisoners were able to find their slip." << endl;
        }
        break;
    case 2:
        placeSlips(boxes, num_prisoners);
        statsRoom(boxes, num_prisoners, num_trials);
        break;
    case 3:
    {

        double prisoners_left = successRooms(boxes, num_prisoners, num_trials);
        cout << "All prisoners were able to leave " << prisoners_left << "/1000 of the rooms." << endl;
    }
    break;
    case 4:
    {
        placeSlips(boxes, num_prisoners);
        int copy_arr[MAX_BOXES];
        for (int i = 0; i < num_prisoners; i++)
        {
            copy_arr[i] = boxes[i]; // copying the array for checking if no more than 2 swaps are made
        }

        bool nice_guard_val = niceGuard(boxes, num_prisoners, num_trials);

        int swap_count = 0;
        for (int j = 0; j < num_prisoners; j++)
        {
            if (copy_arr[j] != boxes[j])
            {
                swap_count++;
            }
        }
        if (swap_count > 2)
        {
            cout << "Illegal intervention as you have more than 1 swap " << endl;
        }
        else
        {
            if (nice_guard_val == false)
                cout << "No intervention needed." << endl;
            else
            {
                cout << "Intervention applied." << endl;
                // validity function
                bool prisoners_left = simulateRoom(boxes, num_prisoners, num_trials);
                // should return true
                if (prisoners_left == true)
                    cout << "All the prisoners were able to escape" << endl;
                else
                {
                    cout << "All the prisoners were not able to escape" << endl;
                }
            }
        }
    }
    break;
    }

    return 0;
}