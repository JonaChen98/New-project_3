#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

//change offset and find probes to accomodate for linear probing otherwise same as quadratic probing
namespace {

// Internal method to test if a positive number is prime.
bool IsPrimes(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrimes(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimes(n)) n += 2;  
  return n;
}

}  // namespace


// Quadratic probing implementation.
template <typename HashedObj>
class HashTableLinear {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrimes(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x); // finds a position thats empty to insert the  element
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;
    

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }
  
  size_t Public_Count_Collisions(){
    int count_collisions = collisions;
    return count_collisions;
  }
  int table_size(){
    int table_size = array_.size();
    return table_size;
  }

  int Num_elements(){
    int Number_of_elements = current_size_;
    return Number_of_elements;
  }

  float Loadfactor(){
    return Num_elements()/table_size();
  }
 
  size_t public_get_probes(const HashedObj& x){

    return private_get_probes(x);
  }

  int r_value = 1111;

  

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
  mutable size_t collisions = 0;

  std::vector<HashEntry> array_;
  size_t current_size_;
  
 
  size_t private_get_probes(const HashedObj& x) const{
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      int probes = 0;
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      probes++;
      current_pos += offset;  // Compute ith probe
      if (current_pos >= array_.size())
	current_pos -= array_.size();  
    }
    return probes + 1;
  }



  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
       collisions++;
      current_pos += offset;  // Compute ith probe.
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimes(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // LINEAR_PROBING_H
