#include <algorithm>
#include "Word.h"
using namespace std;


class Dictionary
{
protected:
    vector<Word> words;

public:
	// Constructor - Loads all words and populate data.
	Dictionary(string filename)
	{
        cout << "Attempting to read text file... Please wait...\n" << endl;
        ifstream file(filename);

        // Open file then sort and store data in Dictionary Vector.
        if (file.is_open())
        {
            // Variables to read data into.
            string data; // Hold's the currently read line.
            string type;
            string name;
            string definition;

            // Loops through each line of the text file and sort data until it reaches the End Of the File (eof).
            while (!file.eof())
            {
                // First line holds type.
                getline(file, data);
                type = data;

                // Second line holds name.
                getline(file, data);
                name = data;

                // Third line holds definition.
                getline(file, data);
                definition = data;

                // Fourth line holds break (nothing).
                getline(file, data);
                // Do nothing?

                Word newWord(type, name, definition);
                words.push_back(newWord);
            }        

            file.close();
        }

        // Print if file can't be opened or found.
        else
        {
            cout << "Unable to open file. \n";
        }
	}


// -- TASK FUNCTIONS -- 

     // Prints All Words - For Testing
    void printAllWords() {
        for (Word word : words)
        {
            word.printDefinition();
        }
    }


    // TASK 1 - Created 20th of March 2022 by Matthew Stasinowsky
    // Last Edited: 1st of May 2022
    // This function prompts the user to enter the word they'd like to find.
    // It then loops through the vector of words and if it finds a match it will display the word, it's type and definition.
    void TaskOne()
    {
        bool wordFound = false;

        // Prompt User for the word they'd like to find.
        string wordToFind;
        cout << "--------------------------------------------------------------------------------\n" << endl;
        cout << "TASK 1: \n" << endl;
        cout << "Please enter the word you'd like to find: " << endl;
        cin >> wordToFind;
        cout << endl;


        // Convert input to lowercase - from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case. 
        transform(wordToFind.begin(), wordToFind.end(), wordToFind.begin(),
            [](unsigned char c) { return std::tolower(c); });


        // Loop through Dictionary Vector and check if the word matches the user's input.
        for (size_t i = 0; i < words.size(); i++) {
            if (wordToFind == words[i].getName()) {

                wordFound = true;

                words[i].printDefinition();

            }
            // If the loop reaches the end of the Dictionary without finding the word:
            else if (i == words.size() - 1 && wordFound == false) {
                cout << "Word not found. \n";
                cout << endl;
            }
        }
    }


    // TASK 2 - Created 20th of March 2022 by Matthew Stasinowsky
    // Last Edited: 1st of May 2022
    // This function prompts the user to enter a letter and then the number of occurances of that letter.
    // It then loops through the vector of words, looping through each letter of every word, keeping track of the number of occurances per word.
    // Finally it displays the words with the letter with the same or more occurances. 
    void TaskTwo()
    {
        // Prompt User for the character and occurance amount they'd like to find.
        string charToFind;
        int charOccurrences;
        bool wordFound = false;
        string previousWord;

        cout << "--------------------------------------------------------------------------------\n" << endl;
        cout << "TASK 2: \n" << endl;
        cout << "Please enter the character you'd like to find: " << endl;
        cin >> charToFind;
        cout << endl;

        cout << "Please enter the minimum number of occurences of that character: " << endl;
        cin >> charOccurrences;
        cout << endl;


        // Loop through each word in the Dictionary.
        for (size_t i = 0; i < words.size(); i++) {

            // Get word name from Dictionary.
            string word = words[i].getName();

            // Counter to keep track of the number of occurnaces.
            int counter = 0;

            // Loop through each letter of the word.
            for (int i = 0; i < word.length(); i++) {

                // Convert each letter from a char to a string and store in 'letter'.
                string letter = string(1, word[i]);

                // If the letter is the same as the charToFind, add to counter.
                if (letter == charToFind) {

                    counter++;

                    // Print all the words that include that character the given number of times or greater
                    // AND that are not the previously printed word,
                    if (counter >= charOccurrences && word != previousWord) {
                        wordFound = true;

                        cout << word << endl;   // Print Word
                        previousWord = word;    // Set Word to PreviousWord
                    }
                }
            }
            // If at the end of the Dictionary and found NO words...
            if (i == words.size() - 1 && wordFound == false) {
                cout << "No word(s) found. \n";
            }
        }
    }


    // TASK 3 - Created 20th of March 2022 by Matthew Stasinowsky
    // Last Edited: 1st of May 2022
    // This function loops through every letter of every word, checking to see if there is a 'q' without a following 'u'.
    // It then displays the words it found.
    void TaskThree()
    {
        cout << "--------------------------------------------------------------------------------\n" << endl;
        cout << "TASK 3:" << endl;
        cout << "All words that contain a 'q' without a following 'u': \n" << endl;

        // Loop through each word in the Dictionary.
        for (size_t i = 0; i < words.size(); i++) {

            // Get word from Dictionary.
            string word = words[i].getName();

            // Loop through each letter of the word.
            for (int i = 0; i < word.length(); i++) {

                // If the letter is 'q' AND the next letter isnt a 'u'.
                if (word[i] == 'q' && word[i + 1] != 'u') {
                    cout << word << endl;
                }
                else {
                    //cout << "Word(s) not found. \n";
                }
            }
        }
    }


// -- END TASK FUNCTIONS --













    // EXAM Stuff

    // Find anagrams
    void findAnagrams() {
        for (Word &word : words) {
            string currentWord = word.getName();

            for (Word &anagramWord : words) {
                string possibleAnagram = anagramWord.getName();

                // Checks if the words are the same length.
                if (currentWord.length() == possibleAnagram.length()) {

                    // Sort words
                    sort(currentWord.begin(), currentWord.end());
                    sort(possibleAnagram.begin(), possibleAnagram.end());

                    // If sorted words match AND isn't the User's original word...
                    if (currentWord == possibleAnagram && word.getName() != anagramWord.getName()) {

                        // Add anagram
                        cout << word.getName() << endl;
                        cout << "Anagram: " << anagramWord.getName() << " " << anagramWord.getType() << " " << anagramWord.getDefinition() << "\n" << endl;
                        word.anagrams.push_back(anagramWord);
                    }
                }
                
            }
        }
    }


    void FindAWord()
    {
        bool wordFound = false;
        string wordToFind;
        cout << "Please enter the word you'd like to find: " << endl;
        cin >> wordToFind;
        cout << endl;

        const string NoWord = "Word not found!!!";

        // Convert input to lowercase - from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case. 
        transform(wordToFind.begin(), wordToFind.end(), wordToFind.begin(),
            [](unsigned char c) { return std::tolower(c); });

        // Loop through Dictionary Vector and check if the word matches the user's input.
        for (Word word : words) {
            if (wordToFind == word.getName()) {
                //word.printDefinition();
                cout << word;
                wordFound = true;
            }
        }
        if (!wordFound) {
            throw(NoWord);
        }

    }



    // SAVING DICTIONARY - Created 28th of May 2022 by Matthew Stasinowsky
    // This function prompts the user for a filename and then adds '.txt' to the end to make sure the file is saved as a text file.
    // It then creates a file using the specified name from the user and opens it.
    // If the file could not be opened an error message is displayed otherwise it loops through each word in the Dictionary printing the name, type and definition each on a new line followed by an empty string. 
    // Then the file is closed and a "File saved." message is displayed to the user.
    void saveDictionary() {

        // User Specifies Filename
        string filename;
        cout << "Please enter a file name: ";
        cin >> filename;
        filename += ".txt";

        // Data being written to file.
        ofstream file;

        file.open(filename); // Opens the file

        if (!file) {
            cout << "File could not be opened/created." << endl;
        }
        else {
            cout << "Saving file. Please wait..." << endl;
            for (Word word : words) {
                file << word.getName() << endl;
                file << word.getType() << endl;
                file << word.getDefinition() << endl;
                file << "" << endl;
            }
            file.close();
            cout << "File saved." << endl;
        }
    }
};
