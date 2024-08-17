/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>

using namespace std;

class mystring {
    private:
        char* data_;
        size_t size_;
        size_t capacity_;
        
        void reserve(size_t new_capacity) {
            auto new_data = new char[new_capacity];
            copy(data_, data_ + size_, new_data);
            delete[] data_;
            
            capacity_ = new_capacity;
            data_ = new_data;
        }
        
    public:
        //default cunstructor
        mystring() : size_(0), capacity_(1), data_(new char[1]){
            data_[0] = '\0';                
        }
          
        //constructor for c-string
        mystring(const char* str) : size_(strlen(str)), capacity_(size_+1), data_(new char[capacity_]){
            copy(str, str + size_, data_);
            data_[size_] = '\0';
        }
            
        //copy constructor
        mystring(const mystring& other) : size_(other.size_), capacity_(other.capacity_), data_(new char[capacity_]){
            copy(other.data_, other.data_ + size_, data_);
            data_[size_] = '\0';
        }
            
        //move constructor
        mystring(mystring&& other) noexcept : size_(other.size_), capacity_(other.capacity_), data_(other.data_){
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
            
        //assignment operator
        mystring& operator=(const mystring& other){
            if(&other != this){
                delete[] data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = new char[capacity_];
                
                copy(other.data_, other.data_ + size_, data_);
                data_[size_] = '\0';
            }
                
            return *this;
        }
            
        // Move assignment operator
        mystring& operator=(mystring&& other) noexcept {
            if(this != &other){
                data_ = other.data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                
                other.data_ = nullptr;
                other.capacity_ = other.size_ = 0;
            }
            
            return * this;
        }
            
        //access operator
        char& operator[](size_t index)
        {
            if(index > size_){
                throw out_of_range("accessing out of range");
            }
                
            return data_[index];
        }
            
        const char& operator[](size_t index) const{
            if(index > size_){
                throw out_of_range("accessing out of range");
            }
                
            return data_[index];
        }
            
        //append 
        void append(const mystring& newStr)
        {
            if(size_ + newStr.size_+1 > capacity_)
                reserve((size_ + newStr.size_ + 1) * 2);
                    
            copy(newStr.data_, newStr.data_ + newStr.size_, data_ + size_);
            size_ = size_ + newStr.size_;
            data_[size_] = '\0';
        }
        
        size_t strlength() const{
            return size_;
        }
            
        const char* c_string() const{
            return data_;
        }
            
        ~mystring(){
            delete[] data_;
        } 
};


int main()
{
    std::cout<<"Hello World"<<endl;

    mystring s1;
    s1 = "arvind";
    s1.append("yada");
    cout<<s1.c_string()<<endl;
    return 0;
}