#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "node.h"

using namespace std;

// checks if character is a punctuation charcter
bool isPunct(char c) {
	// outside of range that has lower case and upper case ASCII values
	if((int)c < 65 || (int)c > 122) {
		return true;
	}
	// case for the punctuation characters within that first range
	else if ((int)c > 90 && (int)c < 97) {
		return true;
	}
	// if it wasn't a punctuation character
	else {
		return false;
	}
}

// removes punctuation from the string
string removePunct(string input) {
	// iterates through length of the string
	for (int i = 0; i < input.size(); i++) {
		// outside of range that has lower and upper case ASCII values
		if ((int)input[i] < 65 || (int)input[i] > 122) {
			// erases punctuation outside of range
			input.erase(i--, 1);
		}
		// erases punctuation inside the range
		if ((int)input[i] > 90 && (int)input[i] < 97) {
			input.erase(i--, 1);
		}
	}
	// returns the string without punctuation
	return input;
}

// bool to let program know if a string needs to be split in two
// passes back a returnStr through pass-by-reference to make it easier
bool splitStrings(string & input, string & returnStr) {
	bool isPunctSS = false; // tells if there was punctuation
	bool isChar = false; // tells if there was a character

	// iterates through length of string
	for (int i = 0; i < input.size(); i++) {
		// case for if string needs to be split
		// if there was punctuation and the next char isn't punctuation
		if (isChar && isPunctSS && isPunct(input[i]) == false) {
			// gets a substring from where i is to the end of string
			returnStr = input.substr(i, input.size() - (i-1));
			// sets original string from start of string to
			// where the other string starts at i
			input = input.substr(0, i);
			return true;
		}
		// case to erase punctuation from the middle of string
		// if there was a char and next char is punctuation
		else if (isChar == true && isPunct(input[i]) == true) {
			// if there is a single quote and the next char is
			// an s, makes sure it doesn't split the string
			// on accident
			if ((int)input[i] == 39 && (int)input[i+1] == 115) {
				return false;
			}
			input.erase(i--, 1);
			isPunctSS = true; // remembers there was punctuation
		}
		// case if the char isn't punctuation
		else if (isPunct(input[i]) == false) {
			isChar = true; // remembers there was a char
		}
	}
	return false; // if string didn't need to be split
}

// reads in strings to hash table
void hashIn(string input, node * hashTable[2000]) {
	// iterates through the hash table
	for (int i = 0; i < 2000; i++) {
		// if the word existed already in the table, increase its count
		if (hashTable[i]->word == removePunct(input)) {
			hashTable[i]->count++;
			return;
		}
		// if the word didn't exist, insert it in and increase count
		else if (hashTable[i]->word == "") {
			hashTable[i]->word = removePunct(input);
			hashTable[i]->count++;
			return;
		}
	}
}

// prints out the hash table
void printHashTable(node * hashTable[2000]) {
        // iterates through hash table
        for (int i = 0; i < 2000; i++) {
                // if there is a word stored, prints word and count
                if (!hashTable[i]->word.empty()) {
                        cout << hashTable[i]->word << " ";
                        cout << hashTable[i]->count << endl;
                }
        }
}

// sorts the hash table in reverse numerical order
// translated from my alphabetical selection sort which was translated
// from a failed insertion sort method, is this what's meant by
// lost in translation?
void numericalSelectionSort(node * hashTable[2000]) {
	node * combNode, * sortedNode;
	node * swapNode; // used to swap nodes instead of comparing one by one
	int combIndex;
	int minIndex = 0;
	int sortedIndex = 0;

	// while there is a word stored in that node
	while (!hashTable[sortedIndex]->word.empty()) {
		minIndex = sortedIndex;
		combIndex = sortedIndex + 1; // puts comb one ahdad of sorted	

		// while there is a word stored where the comb is
		while (!hashTable[combIndex]->word.empty()) {
			// stores nodes just for clarity
			combNode = hashTable[combIndex];
        	        sortedNode = hashTable[minIndex]; 
			
			// if the combNode count is higher than what is sorted
			// sets the minIndex to the value of the comb
			if (combNode->count > sortedNode->count) {
				minIndex = combIndex;
			}
			combIndex++; // increments comb
		}
		// performs the swap
		swapNode = hashTable[sortedIndex];
                hashTable[sortedIndex] = hashTable[minIndex];
                hashTable[minIndex] = swapNode;
		sortedIndex++; // increments the sortedIndex
	}
}

// sorts hash table in alphabetical order
// partly translated from my failed insertion sort method for this
void alphabeticalSelectionSort(node * hashTable[2000]) {
        node *swapNode; // used to swap nodes instead of comparing one by one
	string combNodeStr, sortedNodeStr; // holds the strings
        int sortedIndex = 0; 
        int minIndex = 0;
	int combIndex;

	// while there is a word stored in that node
        while (!hashTable[sortedIndex]->word.empty()) {
		minIndex = sortedIndex;	
               	combIndex = sortedIndex + 1; // puts comb one ahead of sorted
		
		// while there is a word stored where the comb is
		while (!hashTable[combIndex]->word.empty()) {
			// stores strings
			combNodeStr = hashTable[combIndex]->word;
			sortedNodeStr = hashTable[minIndex]->word;
			
			// next two if statements fix strings to make comparison
			// easier by making the first letter lower case
			if ((int)combNodeStr[0] > 96) {
				combNodeStr[0] = (int)combNodeStr[0] - 32;
			}

			if ((int)sortedNodeStr[0] > 96) {
				sortedNodeStr[0] = (int)sortedNodeStr[0] - 32;
			}
			
			// uses strcmp to compare strings, if the first different
			// char has a greater value in the first string, sets
			// minIndex to the value of the comb
                	if (strcmp(sortedNodeStr.c_str(), combNodeStr.c_str()) > 0) {
				minIndex = combIndex;
	        	}

			combIndex++; // increments comb
		}
		// swaps the nodes to proper places
		swapNode = hashTable[sortedIndex];
                hashTable[sortedIndex] = hashTable[minIndex];
                hashTable[minIndex] = swapNode;
		sortedIndex++; // increments the sortedIndex
        }
}

// small UI to get user's choice of file
string chooseFile() {
	string fileChoice; // string for getting user's choice of file

	// outputs instructions for user
	cout << "Please enter the text file you would like to use." << endl;
        cout << "For my data, enter paper.txt." << endl;
        cout << "For Dr. Finkel's data, enter poem.txt." << endl;
        cout << "Choice: ";

        cin >> fileChoice; // gets user input for the file
	
	// outputs more instructions
        cout << endl;
        cout << "Thank you for choosing. To continue, press enter." << endl;
        cin.get();
        cin.get();

	return fileChoice; // sends back the file choice
}

int main () {
	node * hashTable[2000];
	string chosenFile; // string to store user choice of file
	ifstream file;
        string fromFile; // string to read in words from file

	// initializes hash table with new nodes
	for (int i = 0; i < 2000; i++) {
		hashTable[i] = new node;
	}

	chosenFile = chooseFile(); // gets the user's choice

	if (chosenFile == "poem.txt") {
		file.open("poem.txt");
		// if the file opened correctly
		if (!file.fail()) {
			// until end of file, read in
			while (file >> fromFile) {
				// for possible split off string
				string secondStr = "";
			
				// checks if there was a string split
				bool doesSplit = splitStrings(fromFile, secondStr);
				// if there was, inserts the split off string
				// into table
				if (doesSplit) {
					hashIn(secondStr, hashTable);
				}
				// inserts the first/only string
				hashIn(fromFile, hashTable);
			}
		}
		file.close();
	}
	else if (chosenFile == "paper.txt") {
		// refer to above comments if needed
		file.open("paper.txt");
                if (!file.fail()) {
                        while (file >> fromFile) {
                                string secondStr = "";

                                bool doesSplit = splitStrings(fromFile, secondStr);
                                if (doesSplit) {
                                        hashIn(secondStr, hashTable);
                                }
                                hashIn(fromFile, hashTable);
                        }
                }
                file.close();
	}
	
	// prints in alphabetical order
	cout << "Alphabetical Order" << endl;
	alphabeticalSelectionSort(hashTable);
	printHashTable(hashTable);
	cout << endl;

	// prints in reverse numerical order
	cout << "Reverse Numerical Order" << endl;
	numericalSelectionSort(hashTable);
	printHashTable(hashTable);
}
