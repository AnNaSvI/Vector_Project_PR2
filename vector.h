#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;
template <typename T>
class Vector {
public:
    class ConstIterator ;
    class Iterator ;
    using value_type = T;
    using size_type = std :: size_t ;
    using difference_type = std :: ptrdiff_t ;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = Vector :: Iterator ;
    using const_iterator = Vector :: ConstIterator;
    
private:
    size_type sz;
    size_type max_sz;
    size_type min_capacity = 5;
    value_type* values;

public:

  Vector() {
      sz=0;
      max_sz=0;
      values=nullptr;
      reserve(min_capacity);
  }

 Vector(size_t n) {
        if (n < min_capacity) {
            n=min_capacity;
        }
     values= nullptr;
     max_sz=0;
     sz=0;
     reserve(n);
}

 Vector(std::initializer_list<value_type> list1): sz(list1.size()), max_sz(list1.size()) {
            if (list1.size() > 0) {
                values = new value_type [list1.size()];
                size_t i = 0;
                for (auto value : list1) {
                    values[i] = value;
                    i++;
                }
            }
   
}
    Vector (const Vector& other){
        max_sz=other.max_sz;
        sz=other.sz;
        values = new value_type [max_sz];
        for(size_type i=0; i<other.sz; i++){
            values[i]=other.values[i];
        }
    }
 ~Vector(){
   if (values) {
     delete[] values;
   }
}
  Vector& operator=(Vector other) {
            
    swap(max_sz, other.max_sz);
    swap(values, other.values);
    swap(sz, other.sz);
    return *this;
    }

   size_t size() const {
        return sz;
    }
    
    bool empty() const {
        return (sz == 0);
    }
    
    void clear() {
      
        sz = 0;
          shrink_to_fit();
        
    }

    
    void reserve(size_t n){
        if(n>max_sz){
            value_type* new_values = new value_type[n];
            for(size_t i=0; i<sz; ++i){
                new_values[i] = values[i];
            }
            max_sz = n;
            delete[] values;
            values = new_values;
    }

}

  void shrink_to_fit() {
        if (sz < max_sz) {
            value_type* new_values = new value_type[min_capacity];
            for(size_t i=0; i<sz; ++i){
                new_values[i] = values[i];
            }
            max_sz = min_capacity;
            delete[] values;
            values = new_values;
        }
    }

void push_back(value_type x) {
    if (sz == max_sz) {
        reserve(max_sz*2);
    }
    values[sz] = x;
    ++sz;
    }
    
  void pop_back() {
        if (sz == 0) {
            throw runtime_error("Der Vector ist leer. Es kann kein Element entfernt werden.");
        }else {
            --sz;
            value_type* new_values = new value_type[sz];
            for(size_t i=0; i<sz; ++i){
                new_values[i] = values[i];
            }
            max_sz = sz;
            delete[] values;
            values = new_values;
        }
        
    }
    
    value_type& operator[](size_t index) {
        if (index >= sz) {
            throw runtime_error("Der Index liegt außerhalb des erlaubten Bereichs.");
        }
        return values[index];
    }
    
    const value_type& operator[](size_t index) const {
        if (index >= sz) {
            throw runtime_error("Der Index liegt außerhalb des erlaubten Bereichs.");
        }
        return values[index];
    }
    
    ostream& print (ostream& o) const {
        bool erste= true;
        o<<"[";
        erste=false;
        if(!erste){
            for(size_type i=0; i<sz; i++){
                o<<i<<",";
            }
            o<<"]";
        }
      return o;
    }
    friend ostream& operator<<(ostream& o, const Vector& v){
        return v.print(o);
    }
    
    size_t capacity() const {
            return max_sz;
        }
    
    
    
    
    class Iterator {
    public:
        using value_type = Vector::value_type;
        using reference = Vector :: reference ;
        using  pointer = Vector :: pointer ;
        using  difference_type = Vector :: difference_type ;
        using  iterator_category = std :: forward_iterator_tag;
    private:
        pointer ptr;
        pointer end;
        
    public:
        Iterator():ptr(nullptr){}
        
        Iterator(pointer ptr1, pointer end=nullptr) : ptr(ptr1), end(end) {}
        
        reference operator*() const {
            if(ptr==nullptr){
               throw runtime_error("Uberlauf");
            }
                return *ptr;
            }
        pointer operator->() {
            if(ptr==nullptr){
               throw runtime_error("Uberlauf");
            }
                return ptr;
            }
        bool operator==(const const_iterator& other) const {
            return (ptr== other.getPtr());
        }
        bool operator!=(const const_iterator& other) const{
            return !(ptr== other.getPtr());
        }
        iterator& operator++(){
            if(ptr != nullptr && ptr !=end){
              ++ptr;
            }
            return *this;
        }
       
        iterator operator++(int) {
            pointer ptr_ursprung = ptr;
            if(ptr==nullptr && ptr !=end){
                return ptr_ursprung;
            }else {
                ++ptr;
                return ptr_ursprung;
                
            }
            
        }
        operator const_iterator() const {
            return ConstIterator(this->ptr, this->end);
        }
        
      
    };
    
class ConstIterator {
    public:
        using value_type = Vector::value_type;
        using reference = Vector :: const_reference ;
        using  pointer = Vector :: const_pointer ;
        using  difference_type = Vector :: difference_type ;
        using  iterator_category = std :: forward_iterator_tag;
    private:
    pointer ptr;
    pointer end;
    public:
    ConstIterator():ptr(nullptr){}
    
    ConstIterator(pointer ptr1, pointer end=nullptr): ptr(ptr1), end(end){}
    
    
    pointer getPtr() const {
            return ptr;
        }
    
    reference operator*() const {
        if(ptr==nullptr){
           throw runtime_error("Uberlauf");
        }
            return *ptr;
    }
    pointer operator->() const{
        if(ptr==nullptr){
           throw runtime_error("Uberlauf");
        }
        return ptr;
    }
    bool operator==(const const_iterator& other) const{
        return (ptr==other.ptr);
    }
    bool operator!=(const const_iterator& other) const{
        return !(ptr==other.ptr);
    }
    const_iterator& operator++(){
         if(ptr != nullptr && ptr !=end ){
              ++ptr;
            }
        return *this;
    }
    const_iterator operator++(int){
                  pointer ptr_ursprung = ptr;
            if(ptr==nullptr && ptr !=end){
                return ptr_ursprung;
            }else {
                ++ptr;
                return ptr_ursprung;
                
            }
    }
 
    
   
    
    };

       
    iterator begin() {
        pointer end=values+sz;
        return Iterator (values,end) ;
        
    }
    iterator end() {
        pointer end=values;
        return Iterator (values+sz,end) ;
        
    }
    const_iterator begin() const {
        pointer end=values+sz;
        return ConstIterator(values,end);
        
    }
    const_iterator end() const {
        pointer end=values;
        return ConstIterator(values+sz,end);
        
    }

    
    friend Vector :: difference_type operator-(const Vector :: ConstIterator& lop , const Vector :: ConstIterator& rop) {
    return lop.getPtr()-rop.getPtr() ;
    }
    
    iterator insert(const_iterator pos, const_reference val) {
    auto diff = pos - begin ();
    if (diff<0 || static_cast<size_type>(diff)>sz)
        throw std::runtime_error("Iterator out of bounds");
    size_type current{static_cast<size_type>(diff )};
    if (sz>=max_sz)
        reserve(max_sz*2);
    for(auto i {sz}; i-->current;)
        values[i+1]=values[i];
    values [current]=val ;
    ++sz ;
    return iterator{values+current};
    }
    
    iterator erase(const_iterator pos) {
        auto diff = pos - begin();
        if (diff<0 || static_cast<size_type>(diff)>=sz) {
          throw std::runtime_error("Iterator out of bounds");
        }
        size_type current{static_cast<size_type>(diff)};
        for (auto i{current}; i < sz-1; ++i) {
          values[i] = values[i+1];
        }
        --sz;
        return iterator{values+current};
      }

};
#endif
