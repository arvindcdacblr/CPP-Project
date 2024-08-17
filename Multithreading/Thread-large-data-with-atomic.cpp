/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

using namespace std;

void count_num_zero_one(const vector<int>& array, int start, int end, atomic<int>& num_zero, atomic<int>& num_one)
{
    int local_zero_count = 0;
    int local_one_count = 0;
    
    for(int i = start; i < end; ++i)
    {
        if(array[i] == 0)
        {
            local_zero_count++;
        }
        else
        local_one_count++;
    }
    
    num_one += local_one_count;
    num_zero += local_zero_count;
}

int main()
{
    int num_thread = thread::hardware_concurrency();
    cout<<num_thread<<endl;
    
    const int num_element = 100000;
    vector<int> array(num_element);
    
    for(int i = 0; i < num_element; ++i)
    {
        array[i] = rand() % 2;    
    }
    
    vector<thread> threads;
    atomic<int> num_zero(0);
    atomic<int> num_one(0);
    
    int chunk_size = num_element / num_thread;
    
    for(int i = 0; i < num_thread; ++i)
    {
        int start = i * chunk_size;
        int end = (i == num_thread - 1) ? num_element : start + chunk_size;
        
        threads.push_back(thread(count_num_zero_one, ref(array), start, end, ref(num_one), ref(num_zero)));
    }
    
    for(auto& thread1 : threads)
    {
        thread1.join();
    }
    
    cout<<"num_zero"<<num_zero<< endl;
    cout<<"num_one"<<num_one<< endl;
    
    return 0;
}