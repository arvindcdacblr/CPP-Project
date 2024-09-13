//Swap two strings without using third
//Swapping two strings without using a third variable can be done by manipulating the strings themselves. 

#include <iostream>
#include <string>

int main() {
    std::string str1, str2;
    
    std::cout << "Enter first string: ";
    std::cin >> str1;
    std::cout << "Enter second string: ";
    std::cin >> str2;

    // Swapping without a third variable
    str1 = str1 + str2;        // Concatenate str2 at the end of str1
    str2 = str1.substr(0, str1.length() - str2.length());  // Extract original str1
    str1 = str1.substr(str2.length());  // Extract original str2

    std::cout << "After swapping:" << std::endl;
    std::cout << "First string: " << str1 << std::endl;
    std::cout << "Second string: " << str2 << std::endl;

    return 0;
}