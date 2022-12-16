// CSP2104 - Assignment 2 - By Matthew Stasinowsky [10471721] 
// This program allows the user to perform tasks on a Dictionary file. 

// Included Libraries
#include "Header.h"
using namespace std;

int main()
{
    // Initialize random seed (For Guessing Game)
    srand(time(NULL));

    ExtendedDictionary extendedDictionary("dictionary2022_S1.txt"); 

    while (true) {
        DisplayAllTasks(extendedDictionary);
    }



    // EXAM STUFF

    //TestExtendedDictionary exam("dictionary2022_S1.txt");
    //exam.getDictionary().FindAWord();



}

 


