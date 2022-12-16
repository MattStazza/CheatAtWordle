#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ostream>
using namespace std;


class Word
{
friend ostream& operator<<(ostream& out, Word& word);
private:
    string type;
    string name;
    string definition;

public:
    // Constructor 
    Word(string type, string name, string definition) {
        Word::type = type;
        Word::name = name;
        Word::definition = definition;
    }

    vector<Word> anagrams;  // Exam

    // Getters
    string getName() {
        return name;
    }
    string getType() {
        return type;
    }
    string getDefinition() {
        return definition;
    }


    // Setter(s)
    string formatType(string type) {
        // Print Type - Displayed in the appropriate format (special case for Noun & Verb).
        if (type == "n_and_v") {
            type = "(n. v.)";
        }
        else {
            type = "(" + type + ".)";
        }
        return type;
    }


    // Function(s)
    void printDefinition() {
        cout << name << " " << formatType(type) << "\n";
        cout << definition << "\n";
        cout << endl;
    }


    // Eligible Wordle Word Function - Created 8th of May by Matthew Stasinowsky
    // This function takes in 5 Vectors (3 for Characters, 2 for Integers).
    // Using these parameters on a word, this function checks to see if the word meets various requirements from; length, letters and positions of letters.
    // If the requirments are met, this function will return TRUE
    bool eligibleWordleWord(vector<char> doesntContain, vector<char> contains, vector<char> found, vector<int> yellowPositions, vector<int> greenPositions)
    {
        // Only check words with a length of 5 AND without a hyphen '-'
        if (name.length() == 5 && name.find('-') == std::string::npos) {

            // 1. CHECK GREY LETTERS
            // Remove Words with 'Grey Letters'
            // Check each letter in the Word against the letters from 'doesntContain'
            for (char wordLetter : name) {
                for (char letter : doesntContain) {
                    if (wordLetter == letter) {
                        return false;
                    }
                }
            }
            
            // 2. CHECK YELLOW LETTERS
            // Remove words that don't have 'Yellow Letters'
            // Check the word and make sure it contains the letter(s) from 'contains'
            // AND that the given letter ISN'T in the specified position.
            // Limitation: Can only specify 1 location while there may be multiple known...
            int counter = 0;
            for (char letter : contains) {
                // If the letter ISN'T in the word OR the letter IS in the specified position... it's not the word (false)
                if (name.find(letter) == std::string::npos || letter == name[yellowPositions[counter]]) {
                    return false;
                }
                // Otherwise, it could be the word... check the next letter.
                else {
                    counter += 1;
                }
            }

            // 3. CHECK GREEN LETTERS
            // Check the word and make sure the given green letter IS in the specified position.
            counter = 0;
            for (char letter : found) {
                if (letter != name[greenPositions[counter]]) {
                    return false;
                }
                else {
                    counter += 1;
                }                            
            }

            // The word meets the requirements/parameters!
            return true;
        }
        return false;
    }

};





// EXAM stuff

ostream& operator<<(ostream& out, Word& word) {
    cout << word.name << " " << word.formatType(word.type) << "\n" << word.definition << "\n";
    return out;
}