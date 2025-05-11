#include <iostream>
#include <cstdio>  // For printf (violation)
#include <memory>  // For auto_ptr (violation)

using namespace std;  // Violation: No Using Namespace Std

// Global Variable Violation
int globalVar = 42;  

void testGoto() {
    // Goto Violation
    goto label;
label:
    std::cout << "Goto used!" << std::endl;
}

void testMagicNumbers() {
    // Magic Number Violation
    int result = 100 + 25;  // Magic number '100' and '25'
    std::cout << "Result: " << result << std::endl;
}

void testPrintf() {
    // printf Violation
    printf("This is a C-style printf\n");
}

void testCStyleCast() {
    // C-style Cast Violation
    double value = 3.14;
    int intValue = (int)value;  // C-style cast violation
    std::cout << "Cast value: " << intValue << std::endl;
}

int main() {
    testGoto();
    //testAutoPointer();
    testMagicNumbers();
    testPrintf();
    testCStyleCast();
    
    return 0;
}
