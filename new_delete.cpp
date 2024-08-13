#include <iostream>
using namespace std;

int main() {
    // 1. Allocate memory for a single integer
    int* a = new int; // Allocates memory for one integer
    *a = 10;          // Assign a value to the allocated integer

    cout << "Value of singleInt: " << *a << endl;

    // 2. Deallocate memory for the single integer
    delete a;         // Releases the memory allocated for the single integer

    // 3. Allocate memory for an array of integers
    int size = 5;
    int* intArray = new int[size]; // Allocates memory for an array of integers

    // Initialize the array
    for (int i = 0; i < size; ++i) {
        intArray[i] = i * 2; // Assign values to each element
    }

    // Print the array
    cout << "Contents of intArray: ";
    for (int i = 0; i < size; ++i) {
        cout << intArray[i] << " ";
    }
    cout << endl;

    // 4. Deallocate memory for the array
    delete[] intArray; // Releases the memory allocated for the array

    return 0;
}
