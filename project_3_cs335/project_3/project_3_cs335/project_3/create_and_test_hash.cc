// YOUR NAME.


#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"

#include <iostream>
#include <fstream>
#include <string>
#include <fstream>


using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  // insert own code... so you want to insert from words.txt and find from querywords.txt
  ifstream words_file, query;
  string line;
  int word_count =0;
  words_file.open(words_filename);
  if(!words_file) {
    cout << "err opening file" << endl;
    exit(1);
  }

  while(getline(words_file, line)) {
    hash_table.Insert(line);
    word_count++;
  }

  if(hash_table.r_value == 73){
    cout << "r_value: " << hash_table.r_value << endl;
  }
  cout << "Number of items: " << hash_table.Num_elements() << endl;
  cout << "Size of hash table: " << hash_table.table_size()<< endl;
  float load_factor = ((float)hash_table.Num_elements() / hash_table.table_size());
  cout << "Load factor: "<< load_factor << endl; // number of elements/tablesize
  cout << "Collisions: " << hash_table.Public_Count_Collisions() << endl;
  float avg_collision =( hash_table.Public_Count_Collisions()/(float)hash_table.Num_elements());
  cout << "Avg. number of collisions: " << avg_collision << endl; //number of collisions/ number of elements in table (current size)

  words_file.close();
  query.open(query_filename);
  if(!query){
    cout<<"err opening file" << endl;
    exit(1);
  }

  while(getline(query,line)){
    if(hash_table.Contains(line) == true){
      cout << line << " Found " <<hash_table.public_get_probes(line) << endl;
    }
    else{
      cout << line << " Not Found " << hash_table.public_get_probes(line) <<endl;
    }
  }
}

int testFunctionWrapper(int argument_count, char **argument_list) {
  const string words_filename(argument_list[1]);
  const string query_filename(argument_list[2]);
  const string param_flag(argument_list[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testFunctionWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {

  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  testFunctionWrapper(argc, argv);
  return 0;
}
