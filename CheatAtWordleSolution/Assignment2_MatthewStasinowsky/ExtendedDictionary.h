#include "Dictionary.h"
#include <random>
#include <time.h>
using namespace std;


class ExtendedDictionary : public Dictionary {
private:


public:
	// Constructor
	ExtendedDictionary(string filename) : Dictionary(filename) {}


	// TASK 4 - Created 1st of May 2022 by Matthew Stasinowsky
	// This function reverses every word in the Dictionary and checks if it has the same spelling from before it was reversed.
	// If so, it then displays the words it found.
	void TaskFour() {
		cout << "--------------------------------------------------------------------------------\n" << endl;
		cout << "TASK 4: \n" << endl;
		cout << "All words that are palindromes: " << endl;
		cout << "(Words that read the same backward or forward.) \n" << endl;

		bool foundWord = false;

		for (Word word : words)
		{
			// To store the reversed word
			string reversedWord;

			// Loop backwards through the word.
			for (int i = word.getName().length() - 1; i >= 0; i--) {
				// Concatenate characters in reverse.
				reversedWord = reversedWord + word.getName()[i];
			}

			// Check if the original word and the reversed word are the same.
			if (word.getName() == reversedWord) {
				// Print word and set found to true.
				cout << word.getName() << endl;
				foundWord = true;
			}
		}

		// If no word is found.
		if (!foundWord) {
			cout << "Word(s) not found. \n";
			cout << endl;
		}
	}


	// TASK 5 - Created 1st of May 2022 by Matthew Stasinowsky
	// This function prompts the user for a word that they'd like to find anagrams for.
	// It then loops through the dictionary, sorting the current word and checking it against the sorted user's word.
	// If there is a match, it prints the dictionary word (as long as it isn't the user's original word.)
	void TaskFive() {
		cout << "--------------------------------------------------------------------------------\n" << endl;
		// Prompt User for the word they'd like to find anagrams for.
		string usersWord;
		cout << "TASK 5: \n" << endl;
		cout << "Please enter the word you'd like to find anagrams for: " << endl;
		cin >> usersWord;
		cout << endl;

		cout << "Anagrams for " << "'" << usersWord << "'" << ":\n" << endl;

		bool foundWord = false;	// To keep track if any anagrams are found.
		string usersWordCopy = usersWord;	// Keep's a copy of the user's word before sorting changes it.

		// Loop thorugh words in the Dictionary
		for (Word word : words)
		{
			// Store Dictionary word
			string dictWord = word.getName();
			// Sort user's word.
			sort(usersWord.begin(), usersWord.end());

			// Checks if the words are the same length.
			if (dictWord.length() == usersWord.length()) {

				// Sort the current Dictionary's word.
				sort(dictWord.begin(), dictWord.end());

				// If sorted words match AND isn't the User's original word...
				if (usersWord == dictWord && word.getName() != usersWordCopy) {
					// Print the Dictionary Word.
					cout << word.getName() << endl;
					// Set found to true
					foundWord = true;
				}
			}
		}

		// If no Anagrams were found...
		if (!foundWord) {
			cout << "Couldn't find anagrams for " << "'" << usersWordCopy << "'" << "\n";
			cout << endl;
		}
	}

	
	// TASK 6 (Guessing Game) - Created 7th of May by Matthew Stasinowsky
	// This function creates a Vector of nouns from the Dictionary and then picks one at random and displays the noun's definition and length.
	// The user is then prompted for their guess. The user has three attempts to guess the word with one letter being revealled for every incorrect guess. 
	void GuessingGame()
	{
		cout << "--------------------------------------------------------------------------------\n" << endl;
		cout << "TASK 6: GUESSING GAME \n" << endl;
		cout << "You have 3 guesses to find the NOUN with the following definition: " << endl;

		// Create nouns Vector
		vector<Word> nouns;	

		// Find all Nouns in the Dictionary and add to the nouns vector
		for (Word word : words) {
			if (word.getType() == "n") {
				nouns.push_back(word);
			}
		}

		// Grab a random noun
		// Note: Random isn't very random. Didn't get any words starting from N - Z. Seems to favour lower half of the vector.
		int random = rand() % nouns.size() + 1;
		Word noun = nouns[random];

		// Print Definition & Length of Noun
		cout << "\nDEFINITION:" << endl;
		cout << noun.getDefinition() << '\n' << endl;
		cout << "The NOUN is " << noun.getName().length() << " characters long." << endl;
		for (int i = 0; i < noun.getName().length(); i++) {
			cout << "_ ";
		}

		// Create Guessing required Variables
		string guessWord = "";
		int guessNum = 0;

		// Start Game. Continue loop until the word is guessed correctly or the user has run out of guesses.
		while (guessWord != noun.getName())
		{
			// First Guess: Prompt user for first guess.
			if (guessNum == 0) {
				cout << endl;
				cout << "\nType your guess and press ENTER: ";
				cin >> guessWord;
			}

			// Second Guess: If 1st guess was incorrect, reveal first letter and prompt for second guess. 
			if (guessNum == 1)
			{
				cout << "\nIncorrect. You have 2 guesses remaining." << endl;
				cout << "Revealing the first letter: " << endl;

				cout << "\n" << noun.getName()[0] << " ";
				for (int i = 0; i < noun.getName().length() - guessNum; i++) {
					cout << "_ ";
				}

				cout << endl;
				cout << "\nType your guess and press ENTER: ";
				cin >> guessWord;
			}

			// Third Guess: If 2nd guess was incorrect, reveal second letter and prompt for final guess.
			if (guessNum == 2)
			{
				cout << "\nIncorrect. This is your last guess!" << endl;
				cout << "Revealing the second letter: " << endl;

				cout << "\n" << noun.getName()[0] << " ";
				cout << noun.getName()[1] << " ";
				for (int i = 0; i < noun.getName().length() - guessNum; i++) {
					cout << "_ ";
				}

				cout << "\nType your guess and press ENTER: ";
				cin >> guessWord;
			}

			// If out of guesses, reveal the whole word.
			if (guessNum == 3) {
				cout << "\nSorry, that was incorrect and you are out of guesses.\n" << endl;
				cout << "The noun was: " << noun.getName() << endl;
				break;
			}

			// Add 1 every guess
			guessNum += 1;
		}

		// Winning message
		if (guessWord == noun.getName()) {
			cout << "\nCongratulations! You guessed the NOUN!\n" << endl;
		}
	}


	// TASK 7 (Cheat at Wordle) - Created 7th of May by Matthew Stasinowsky
	// This function prompts the user to input letters and their positions into multiple Vectors. This input is verified and sorted. 
	// Using the Vectors, each word in the dirctionary is checked using the 'eligibleWordleWord' function in Word.h
	// Words that return true from this function are displayed to the user.
	void CheatAtWordle()
	{
		// Declaring required Functions from Header.h
		int ValidateInteger(int minInt, int maxInt);
		string ValidateStringIsBetweenLetters(char startChar, char endChar);
		vector<char> ConvertStringToCharVectorAndSort(string characters);

		// Variables for entering and managing letters
		string currentCharacters;
		int currentPos;
		vector<char> doesntContain;
		vector<char> contains;
		vector<char> found;
		vector<int> yellowPositions;
		vector<int> greenPositions;

		// Variables for skipping
		int skip = 0;


		// Display Instructions
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "TASK 7: CHEAT AT WORDLE\n" << endl;
		cout << "To use this program you need to have started a game of Wordle, having entered at least ONE word.\n" << endl;

		cout << "HOW IT WORKS:" << endl;
		cout << "1. Enter the LETTERS that the WORD DOESN'T contain (Grey Letters)" << endl;
		cout << "2. Enter the LETTERS that the WORD DOES contain (Yellow Letters)" << endl;
		cout << "3. Enter the POSITIONS of the YELLOW LETTERS" << endl;
		cout << "4. Enter the KNOWN LETTERS in the WORD (Green Letters)" << endl;
		cout << "5. Enter the POSITIONS of the GREEN LETTERS" << endl;
		cout << "6. The program will then display all the possible words! :D" << endl;

		cout << "\nHappy Wordling!\n" << endl;

		cout << "\nWhen ready ";
		system("pause");



		// ENTERING GREY LETTERS
		cout << "--------------------------------------------------------------------------------\n" << endl;
		// Display Information
		cout << "STEP 1 - GREY LETTERS" << endl;
		cout << "Enter the letters that the word DOESN'T contain.\n" << endl;

		// Prompt for Letters
		cout << "Enter letter(s): ";

		// Validate input is between A - Z
		currentCharacters = ValidateStringIsBetweenLetters('a', 'z');

		// Sort input to remove duplicates
		doesntContain = ConvertStringToCharVectorAndSort(currentCharacters);

		// Print Entered Letters
		cout << "\n\nEntered GREY Letter(s):" << endl;
		for (char letter : doesntContain) {
			cout << char(toupper(letter)) << ", ";
		}
		cout << endl;



		// ENTERING YELLOW LETTERS
		cout << "\n--------------------------------------------------------------------------------\n" << endl;
		// Display Information
		cout << "STEP 2 - YELLOW LETTERS" << endl;
		cout << "Enter the letters that the word DOES contain (unknown positions)." << endl;
		// Ask the user if they have yellow letters to input.
		cout << "\nDo you have Yellow Letters to enter?:" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No\n" << endl;
		cout << "Choice: ";

		skip = ValidateInteger(1, 2);
		if (skip == 1) {

			// Prompt for Letters
			cout << "Enter letter(s): ";

			// Validate input is between A - Z
			currentCharacters = ValidateStringIsBetweenLetters('a', 'z');

			// Sort input to remove duplicates
			contains = ConvertStringToCharVectorAndSort(currentCharacters);

			// Print Entered Letters
			cout << "\n\nEntered YELLOW Letter(s):" << endl;
			for (char letter : contains) {
				cout << char(toupper(letter)) << ", ";
			}
			cout << endl;
		}
		else if (skip == 2) {
			cout << "\nSkipping Steps 2 & 3, continuing to Step 4 - Green Letters..." << endl;
			skip = 0;
		}
		// ENTER YELLOW LETTER POSITIONS
		if (skip == 1) {
			// Displaying Information
			cout << "--------------------------------------------------------------------------------\n" << endl;
			cout << "STEP 3 - YELLOW POSITIONS" << endl;
			cout << "Enter the POSITION of the Yellow Letters.\n" << endl;

			for (char letter : contains) {
				cout << "Enter the position for " << char(toupper(letter)) << ": ";
				currentPos = ValidateInteger(1, 5);

				yellowPositions.push_back(currentPos - 1);
				cout << endl;
			}
		}



		// ENTERING GREEN LETTERS
		cout << "\n--------------------------------------------------------------------------------\n" << endl;
		// Display Information
		cout << "STEP 4 - GREEN LETTERS" << endl;
		cout << "Enter the KNOWN letters." << endl;
		// Ask the user if they have yellow letters to input.
		cout << "\nDo you have Green Letters to enter?:" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No\n" << endl;
		cout << "Choice: ";

		skip = ValidateInteger(1, 2);
		if (skip == 1) {

			// Prompt for Letters
			cout << "Enter letter(s): ";

			// Validate input is between A - Z
			currentCharacters = ValidateStringIsBetweenLetters('a', 'z');

			// Sort input to remove duplicates
			found = ConvertStringToCharVectorAndSort(currentCharacters);

			// Print Entered Letters
			cout << "\n\nEntered GREEN Letter(s):" << endl;
			for (char letter : found) {
				cout << char(toupper(letter)) << ", ";
			}
			cout << "\n" << endl;
		}
		else if (skip == 2) {
			cout << "\nSkipping Steps 4 & 5...\n" << endl;
			skip = 0;
		}		
		// ENTER GREEN LETTER POSITIONS
		if (skip == 1) {		
		// Displaying Information
			cout << "--------------------------------------------------------------------------------\n" << endl;
			cout << "STEP 5 - GREEN POSITIONS" << endl;
			cout << "Enter the POSITION of the Green Letters.\n" << endl;

			for (char letter : found) {
				cout << "Enter the position for " << char(toupper(letter)) << ": ";
				currentPos = ValidateInteger(1, 5);

				greenPositions.push_back(currentPos - 1);
				cout << endl;
			}
		}



		// DISPLAYING POSSIBLE WORDS!
		cout << "Ready to display possible words!" << endl;
		cout << "\n|=====================================|\n" << endl;
		cout << "YOUR INPUT:\n" << endl;

		// Print Green Letter(s) in Word format
		if (found.size() >= 1) {
			cout << "Green Letter(s):" << endl;
			for (char letter : found) {
				cout << char(toupper(letter)) << ", ";
			} cout << "\n" << endl;
		}
		
		// Print Yellow Letters
		if (contains.size() >= 1) {
			cout << "Yellow Letter(s):" << endl;
			for (char letter : contains) {
				cout << char(toupper(letter)) << ", ";
			} cout << "\n" << endl;
		}

		// Print Grey Letters
		if (doesntContain.size() >= 1) {
			cout << "Grey Letter(s):" << endl;
			for (char letter : doesntContain) {
				cout << char(toupper(letter)) << ", ";
			} cout << "\n" << endl;
		}

		cout << "\n|=====================================|\n" << endl;

		system("pause");
		cout << "\n" << endl;
		cout << "POTENTIAL WORDS:\n" << endl;

		// Loop through each word and execute the eligibleWordleWord function on it to determine if it meets the criteria
		// If it does (returns true) the word is printed!
		for (Word word : words) {
			if (word.eligibleWordleWord(doesntContain, contains, found, yellowPositions, greenPositions)) {
				cout << word.getName() << ", ";
			}
		}
		cout << "\n\n" << endl;
	}

	// Possible Improvements (For CheatAtWordle):
	// - Instead if inputting the data from scratch if the user wants to add more letters they could add to their existing input. Then the possible words would be updated.
	// - Displaying their input of Green letters in a Wordle like format eg:  W _ _ D _
};





//class TestExtendedDictionary
//{
//private:
//	Dictionary dictionary;
//
//public:
//	TestExtendedDictionary(string);
//
//	// Because dictionary is private.
//	Dictionary getDictionary() {
//		return dictionary;
//	}
//};
//
//TestExtendedDictionary::TestExtendedDictionary(string filename) : dictionary(filename) {}