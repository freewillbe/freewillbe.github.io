#include <iostream>
#include <string>
#include <vector>
#include <map>
                                    using namespace std;                
// Define a class called SymbolicAI
class SymbolicAI {                  private:
    map<string, vector<string>> dictionary;

public:
    // Define a method for adding words and their meanings to the dictionary                                    void add_word(string word, vector<string> meanings) {                       dictionary[word] = meanings;    }
                                        // Define a method for getting the meanings of a word from the dictionary                                   vector<string> get_meanings(string word) {                                  if (dictionary.count(word) > 0) {
            return dictionary[word];
        }
        else {                                  return {"Word not found in dictionary."};
        }
    }

    // Define a method for checking if a word is in the dictionary          bool has_word(string word) {
        return dictionary.count(word) > 0;
    }                               };
                                    
                                                                        

                                    


int main()
{
    SymbolicAI ai;

    // Add some words and their meanings to the dictionary                  ai.add_word("apple", {"a round fruit with red or green skin"});
    ai.add_word("book", {"a written or printed work consisting of pages glued or sewn together along one side and bound in covers"});
    ai.add_word("computer", {"an electronic device that can accept, process, and store data"});

    string command;                     string word;

    // Loop until the user enters the "exit" command                        while (command != "exit") {             // Prompt the user for input
        cout << "Enter a command (add, get, has, or exit): ";
        cin >> command;

        if (command == "add") {                 // Prompt the user for the word to add and its meanings
            cout << "Enter a word to add: ";
            cin >> word;            
            vector<string> meanings;            string meaning;         
            cout << "Enter the meanings of the word (enter 'done' to finish): " << endl;                    
            // Loop until the user enters "done" to finish entering the meanings                                        while (meaning != "done") {                                                 cin >> meaning;     
                if (meaning != "done") {
                    meanings.push_back(meaning);                                        }
            }
                                                // Add the word and its meanings to the dictionary
            ai.add_word(word, meanings);
            cout << "Word added to the dictionary." << endl;
        }
        else if (command == "get") {
            // Prompt the user for the word to get the meanings of
            cout << "Enter a word to get the meanings of: ";
            cin >> word;            
            // Get the meanings of the word from the dictionary
            vector<string> meanings = ai.get_meanings(word);
                                                // Display the meanings of the word                                     for (string meaning : meanings) {
                cout << meaning << endl;                                            }                               }
        else if (command == "has") {
            // Prompt the user for the word to check if it's in the dictionary
            cout << "Enter a word to check if it's in the dictionary: ";
            cin >> word;

            // Check if the word is in the dictionary and display the result
            if (ai.has_word(word)) {
                cout << word << " is in the dictionary." << endl;
            }
            else {                                  cout << word << " is not in the dictionary." << endl;               }                               }
        else if (command == "exit") {
            // Exit the program
            cout << "Exiting program." << endl;
        }
        else {                                  // Invalid command
            cout << "Invalid command. Valid commands are 'add', 'get', 'has', and 'exit'." << endl;                 }
    }                               
    return 0;                       }
