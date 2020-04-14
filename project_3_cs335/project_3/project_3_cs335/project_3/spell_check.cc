// YOUR NAME.

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>


using namespace std;

int testSpellingWrapper(int argument_count, char** argument_list) {

  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);
 
  // Call functions implementing the assignment requirements.
  HashTable<string> Dictionary_table;
  Dictionary_table.MakeEmpty();

  string diction_word;
  string document_word;
  ifstream document_stream;
  ifstream dictionary_stream;
// opening txt files
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
  string line;
  while(getline(document_stream,document_word)){
     //if contains then just print <word1> is CORRECT
    // for(int i = 0; i < document_word.length(); i++){
    //   document_word[i] = tolower(document_word[i]);

    stringstream streamdocument(document_word);
    string word;
    // stringstream gets rid of whitespace
    while(streamdocument >> word ){
      
      for(int i = 0; i < word.size(); i++){
        word[i] = tolower(word[i]);
      }

    if(ispunct(word[word.length()-1])){
        word.pop_back();
      }
    if(ispunct(word[0])){
      word = word.substr(1);
    }
    
    if(Dictionary_table.Contains(word)){
      cout << word << " is CORRECT" << endl;
    }
  
  //if not do error checkings

  if(!Dictionary_table.Contains(word)){
    
    cout << word << " is INCORRECT" << endl;

    //a) Adding one character in any possible position
    for (int i = 0; i < word.length(); i++){
      for(char ch = 'a'; ch <='z'; ch++){
        string modified_wordA = word;
        modified_wordA.insert(i,1,ch);
        if(Dictionary_table.Contains(modified_wordA)){
          // <word3> -> <alternate word> ** case <TYPE: A, B or C>
          cout <<"** " << word << " -> " << modified_wordA << " ** case A" << endl;
        }
      }
      // b) Removing one character from the word
      //duplicates orr == or and or
      string modified_wordB = word;
      modified_wordB.erase(modified_wordB.begin()+i);
      if(Dictionary_table.Contains(modified_wordB)){
        cout <<"** " << word << " -> " << modified_wordB << " ** case B" << endl;
      }
    // c) Swapping adjacent characters in the word
      if(i< document_word.length()){
        string modified_wordC = word;
        swap(modified_wordC[i],modified_wordC[i+1]);

        if(Dictionary_table.Contains(modified_wordC)){
          cout << "** " << word << " -> " << modified_wordC << " ** case C" << endl;
        }
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
