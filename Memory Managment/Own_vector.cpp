/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class myVector{
    private:
        T* data_;
        size_t size_;
        size_t capacity_;
        
        void resize(size_t new_capacity)
        {
            auto newData = new T[new_capacity];
            std::move(data_, data_ + size_, newData);
            
            delete[](data_);
            data_ = newData;
            capacity_ = new_capacity;
        }
        
    public:
        myVector() : data_(nullptr), size_(0), capacity_(0){
            
        }
        
        //copy constructor 
        myVector(const myVector& other) : size_(other.size_), capacity_(other.capacity_)
        {
            data_ = new T[capacity_];
            copy(other.data_, other.data_ + size_, data_);
        }
        
        //move constructor
        myVector(myVector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_){
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        
        //Assignmemt operator
        myVector& operator=(const myVector& other) {
            if(&other != this)
            {
                delete[](data_);
                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = new T[capacity_];
                
                copy(other.data_, other.data_ + size_, data_);
            }
            
            return *this;
        }
        
        //Move assignment operator
        myVector& operator=(myVector&& other) noexcept {
            if(&other != this)
            {
                delete[](data_);
                
                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = std::move(other.data);
                
                other.data_ = nullptr;
                other.size_ = other.capacity_ = 0;
            }
            
            return *this;
        }
        
        T& operator[](size_t index)
        {
            if(index >= size_)
                throw out_of_range("out of range");
                
            return data_[index];
            
        }
                
        const T& operator[](size_t index) const
        {
            if(index >= size_)
                throw out_of_range("out of range");
                
            return data_[index];
        }
        
        void push_back(T value){
            if(size_ == capacity_)
            {
                resize(capacity_ == 0? 1 : capacity_ * 2);
            }
            
            data_[size_++] = value;
        }
        
        void pop()
        {
            if(size_ == 0)
            {
                throw out_of_range("no element");
            }
            
            --size_;
        }
        
        size_t size(){
            return size_;
        }
};

int main()
{
    std::cout<<"Hello World";
    
    myVector<int> vec;
    vec.push_back(10);
    vec.push_back(0);
    vec.push_back(110);
     
    myVector<int> vec2;
    vec2 = vec;
    
    for(int i = 0; i < vec2.size(); i++)
    {
       cout<<vec2[i]<<endl; 
    }
    
    vec.pop();
    
    for(int i = 0; i < vec.size(); i++)
    {
       cout<<vec[i]<<endl; 
    }
    
    

    return 0;
}
