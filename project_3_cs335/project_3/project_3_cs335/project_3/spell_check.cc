// YOUR NAME.

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int testSpellingWrapper(int argument_count, char** argument_list) {

  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);
  
  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;

  // Call functions implementing the assignment requirements.
  HashTable<string> Dictionary_table;
  Dictionary_table.MakeEmpty();

  string diction_word;
  string document_word;
  ifstream document_stream;
  ifstream dictionary_stream;

  document_stream.open(document_filename);
    if(document_stream.fail()){
      cerr << "error on opening";
  }

  dictionary_stream.open(dictionary_filename);
    if(dictionary_stream.fail()){
      cerr << "error on opening";
  }
  // insert all dictionary words into quadratic hashtable
  while(getline(dictionary_stream,diction_word)){
    Dictionary_table.Insert(diction_word);
  }

  //implementation for reading each line in document file and then checking
  //if containts in the hashtable
  while(getline(document_stream,document_word)){
     //if contains then just print <word1> is CORRECT
    for(int i = 0; i < document_word.length(); i++){
      document_word[i] = tolower(document_word[i]);
    }
    
    if(Dictionary_table.Contains(document_word)){
      cout << document_word << " is CORRECT" << endl;
    }
  
  //if not do error checkings
  
  // b) Removing one character from the word
  // c) Swapping adjacent characters in the word
  if(!Dictionary_table.Contains(document_word)){

    //a) Adding one character in any possible position
    for (int i = 0; i < document_word.length()+1; i++){
      for(char ch = 'a'; ch <'z'; ch++){
        string modified_word = document_word;
        modified_word.insert(i,1,ch);
        if(Dictionary_table.Contains(modified_word)){
          // <word3> -> <alternate word> ** case <TYPE: A, B or C>
          cout << document_word << " -> " << modified_word << " ** case A" << endl;
        }
   

      }
    }
  }
  }
} 


// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);

  return 0;
}
