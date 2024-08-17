#include <iostream>

using namespace std;

template<typename T>
class sharedPtr{
    private:
        T* ptr_;
        size_t* refCount_;
        
        void cleanup()
        {
            if(--(*refCount_) == 0)
            {
                delete(ptr_);
                delete(refCount_);
            }
            
            refCount_ = nullptr;
            ptr_ = nullptr;
        }
        
    public:
        explicit sharedPtr(T* ptr = nullptr) : ptr_(ptr), refCount_(ptr ? new size_t(1) : nullptr){
        }
        
        ~sharedPtr()
        {
            cleanup();    
        }
        
        sharedPtr(const sharedPtr& other) : ptr_(other.ptr_), refCount_(other.refCount_){
            if(refCount_)
            {
                ++(*refCount_);
            }
        } 
        
        sharedPtr& operator=(const sharedPtr& other)
        {
            if(this != &other)
            {
                cleanup();
                ptr_ = other.ptr_;
                refCount_ = other.refCount_;
                if(refCount_)
                {
                    ++(*refCount_);
                }
            }
            
            return *this;
        }
        
        //move constructor
        sharedPtr(sharedPtr&& other) noexcept : ptr_(other.ptr_), refCount_(other.refCount_){
            other.ptr_ = other.refCount_ = nullptr;
        }
        
        sharedPtr& operator=(sharedPtr&& other) noexcept
        {
            if(this != &other)
            {
                cleanup();
                ptr_= other.ptr_;
                refCount_= other.refCount_;
                other.refCount_ = other.ptr_ = nullptr;
            }
            
            return *this;
        }
        
        int useCount()
        {
            return *refCount_;
        }
        
        T* get()
        {
            return ptr_;
        }
        
        T* operator->(){
            return ptr_;
        }
        
        T& operator*()
        {
            return *ptr_;
        }
};

int main()
{
    sharedPtr<int> P1{new int(5)};
    
    cout<<*P1 <<"   "<<P1.useCount()<<endl;
    
    sharedPtr<int> p2= P1;
    
    cout<<*p2 <<"   "<<p2.useCount()<<endl;
    
    sharedPtr<int> p3 = sharedPtr<int>{new int(6)};
    sharedPtr<int> p4 = p3;
    
    cout<<*p3 <<"   "<<p3.useCount()<<endl;
    
    cout<<*p4 <<"   "<<p4.useCount()<<endl;
    p3 = p2;
    
    cout<<*p4 <<"   "<<p4.useCount()<<endl;
    
    cout<<*p3 <<"   "<<p3.useCount()<<endl;
}
