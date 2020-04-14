// YOUR NAME.


#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"

#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  // cout << "TestFunctionForHashTables..." << endl;
  // cout << "Words filename: " << words_filename << endl;
  // cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  // insert own code... so you want to insert from words.txt and find from querywords.txt
  ifstream words_file, query;
  string line;
  words_file.open(words_filename);
  if(!words_file) {
    cout << "err opening file" << endl;
    exit(1);
  }

  while(getline(words_file, line)) {
    hash_table.Insert(line);
  }
  // all the table data had to manipulate some of the data to be the proper type (floats)
  cout << "number_of_elements: " << hash_table.Num_elements() << endl;//int
  cout << "size_of_table: "<< hash_table.table_size()<< endl;//int
  float load_factor = ((float)hash_table.Num_elements() / hash_table.table_size());
  cout << "load_factor: " << load_factor << endl; // number of elements/tablesize
  cout << "collisions: " << hash_table.Public_Count_Collisions() << endl;
  float avg_collision =( hash_table.Public_Count_Collisions()/(float)hash_table.Num_elements());
  cout << "avg_collisions: " << avg_collision << endl; //number of collisions/ number of elements in table (current size)
  cout << endl;
 // close file when finished
  words_file.close();
  query.open(query_filename);
  if(!query){
    cout<<"err opening file" << endl;
    exit(1);
  }
// get lines from query file and check if they are contained in the table
  while(getline(query,line)){
    if(hash_table.Contains(line) == true){
      cout << line << " Found " <<hash_table.public_get_probes(line) << endl;
    }
    else{
      cout << line << " Not_Found " << hash_table.public_get_probes(line) <<endl;
    }
  }

}
//second testfunction that takes in an extra parameters for double hashing get r_value
//r_value i chose to test was 73
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename, const string &r_value) {
  // cout << "TestFunctionForHashTables..." << endl;
  // cout << "Words filename: " << words_filename << endl;
  // cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  // insert own code... so you want to insert from words.txt and find from querywords.txt
  ifstream words_file, query;
  string line;
  words_file.open(words_filename);
  if(!words_file) {
    cout << "err opening file" << endl;
    exit(1);
  }
  stringstream r_value_holder(r_value);
  int r_value_int = 0;
  r_value_holder>>r_value_int;
  hash_table.set_r_value(r_value_int);

  while(getline(words_file, line)) {
    hash_table.Insert(line);
  }

  cout<< "r_value: " << r_value_int << endl;
  cout << "number_of_elements: " << hash_table.Num_elements() << endl;//int
  cout << "size_of_table: "<< hash_table.table_size()<< endl;//int
  float load_factor = ((float)hash_table.Num_elements() / hash_table.table_size());
  cout << "load_factor: " << load_factor << endl; // number of elements/tablesize
  cout << "collisions: " << hash_table.Public_Count_Collisions() << endl;
  float avg_collision =( hash_table.Public_Count_Collisions()/(float)hash_table.Num_elements());
  cout << "avg_collisions: " << avg_collision << endl; //number of collisions/ number of elements in table (current size)
  cout << endl;
 
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
      cout << line << " Not_Found " << hash_table.public_get_probes(line) <<endl;
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
    const string r_value(argument_list[4]);
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename,r_value);    
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

  if (argc != 4 && argc != 5) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  testFunctionWrapper(argc, argv);
  return 0;
}
