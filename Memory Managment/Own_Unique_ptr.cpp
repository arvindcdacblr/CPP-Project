/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
//=========================================UniquePtr--------------------------------
#include <iostream>
#include <memory>
//#include <template>
using namespace std;

template<typename T>
class unitquePtr
{
    public:
       explicit unitquePtr(T* ptr = nullptr) : ptr_(ptr) {
           cout<<"obj const"<<endl;
       }
       
       //disable assignment and copy constructor 
       //unitquePtr(const unitquePtr&) = delete;
       //unitquePtr& operator=(const unitquePtr&) = delete;
       
       unitquePtr(unitquePtr&& newPtr) noexcept : ptr_(newPtr.ptr_)
       {
           cout<<"copy move"<<endl;
           newPtr.ptr_ = nullptr;
       }
       
       unitquePtr& operator=(unitquePtr&& newPtr) noexcept{
           cout<<"move assignment"<<endl;
           if(this != &newPtr)
           {
               delete(ptr_);
               this->ptr_ = newPtr.ptr_;
               newPtr.ptr_ = nullptr;
           }
           return *this;
       }
       
       T* get() const
       {
           return ptr_;    
       }
       
       T& operator*() const
       {
           return *ptr_;
       }
       
       T* operator->() const{
           return ptr_;
       }
       
       unitquePtr* reset(T *newPtr = nullptr)
       {
           if(newPtr != nullptr)
           {
          delete(ptr_);
          ptr_ = newPtr;
           }
          return *this;
       }
        T* release()
        {
            T* temp = move(ptr_);
            ptr_ = nullptr;
            return temp;
        }
        
       ~unitquePtr()
       {
           cout<<"delete";
           delete(ptr_);    
       }
       
    private: 
        T *ptr_;
        
       //disable assignment and copy constructor 
       unitquePtr(const unitquePtr&){}
       unitquePtr& operator=(const unitquePtr&){}
};

int main()
{
    unique_ptr<int> p1 = unique_ptr<int>(new int(6));
    p1 = unique_ptr<int>(new int(7));;
    unitquePtr<int> p = unitquePtr<int>(new int(5));
    
    p = unitquePtr<int>(new int(8));;
    std::cout<<"Hello World " << *p;
    
    auto p11 = p.release();
    
    std::cout<<"Hello World " << *p11;

    return 0;
}
