using namespace std;
#include "ExtendedDictionary.h"



// -- VALIDATE/CONVERT INPUT -- 

// INTEGER - Created 26th of March by Matthew Stasinowsky
// This function asks the user to enter a NUMBER and ensures it's a valid integer between the minInt and maxInt paramters.
int ValidateInteger(int minInt, int maxInt)
{
    bool validInt = false;

    while (!validInt) {
        int input;
        cin >> input;

        // Check if the input is between the min and max integer.
        if (input >= minInt && input <= maxInt) {
            return input;
        }
        else {
            // Clear input (to avoid infinite loop)
            // From: https://www.daniweb.com/programming/software-development/threads/487663/infinite-loop
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input \n";
            cout << endl;
            cout << "Enter a NUMBER between " << minInt << " - " << maxInt << ": \n";
        }
    }
}


// STRING - Created 8th of May by Matthew Stasinowsky
// This function asks the user to enter a STRING and ensures each LETTER is a valid letter between the startChar and endChar paramters.
// For instance, a string with letters between A - Z
string ValidateStringIsBetweenLetters(char startChar, char endChar) {
    
    bool validInput = false;

    while (!validInput) {

        string input;
        getline(cin, input);

        // Remove Spaces - Source: https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
        input.erase(remove_if(input.begin(), input.end(), isspace), input.end());

        // Convert to Lower Case
        for_each(input.begin(), input.end(), [](char& c) {
            c = ::tolower(c);
            });

        // To find end of string
        int counter = 0;
        int stringLength = input.length();

        // Loop through each letter of input (string)
        for (char letter : input) {
            // Check if the letter is between start/end Char
            if (letter >= startChar && letter <= endChar) {
                // Check if we have reached the end of the string
                if (counter == stringLength - 1) {
                    return input;
                }
                else {
                    counter += 1;
                }
            }
            // If input has a letter outside of the parameters, asks for new input
            else {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid letter(s). Enter letters between "<< char(toupper(startChar)) << " - " << char(toupper(endChar)) << ":" << endl;
            }
        }
    }
}


// CHAR VECTOR - Created 8th of May by Matthew Stasinowsky
// This function takes any string and adds each character to a Char Vector
// It then sorts the vector and removes any duplicates, returning the organised Vector.
vector<char> ConvertStringToCharVectorAndSort(string characters) {

    // Create Vector
    vector<char> Chars;
    
    // Add letters to 'Chars' Vector
    for (char letter : characters) {
        Chars.push_back(letter);
    }

    // Sort the Vectore and remove duplicates
    // Source: https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
    sort(Chars.begin(), Chars.end());
    Chars.erase(unique(Chars.begin(), Chars.end()), Chars.end());

    return Chars;
}

// ------- END -------




// EXIT - Created 27th of March by Matthew Stasinowsky
// This function displays a going away message and kills the program.
void Exit() {
    cout << endl;
    cout << "Closing program - Goodbye! \n";
    cout << "Developed by Matthew Stasinowsky \n";
    cout << endl;

    exit(0);

}


// ALL TASKS - Re-Created 26th of March by Matthew Stasinowsky
// This function takes a vector (The Dictionary) and then displays the available tasks the user can perform on that Dictionary.
// The user is then prompted to enter an integer which is validated to execute the corresponding task function.
void DisplayAllTasks (ExtendedDictionary& dict) {
    cout << "-------------------------------------- \n";
    cout << endl;

    // Print out Task options.
    cout << "AVAILABLE TASKS: \n" << endl;
    cout << "1. Find a word." << endl;
    cout << "2. List all words with specific character(s)." << endl;
    cout << "3. List all words that contain a 'q' without a following 'u'." << endl;
    cout << "4. List all words that are palindromes." << endl;
    cout << "5. Find anagrams." << endl;
    cout << "6. Guessing Game." << endl;
    cout << "7. Cheat at Wordle." << endl;
    cout << "8. Exit. \n" << endl;

    int taskNumber;

    // Prompt user for Task choice.
    cout << "Please enter the Tasks's NUMBER you would like to perform: " << endl;
    taskNumber = ValidateInteger(1, 8);
    cout << endl;

    // If '1' execute Task 1 and end loop.
    if (taskNumber == 1) {
        try {
            dict.FindAWord();
        }
        catch (string msg) {
            cout << msg;
        }

    }
    // If '2' execute Task 2 and end loop.
    else if (taskNumber == 2) {
        dict.TaskTwo();
    }
    // If '3' execute Task 3 and end loop.
    else if (taskNumber == 3) {
        dict.TaskThree();
    }
    else if (taskNumber == 4) {
        dict.TaskFour();
    }
    else if (taskNumber == 5) {
        dict.TaskFive();
    }
    else if (taskNumber == 6) {
        dict.GuessingGame();
    }
    else if (taskNumber == 7) {
        dict.CheatAtWordle();
    }
    else if (taskNumber == 8) {
        dict.saveDictionary();
    }
}


