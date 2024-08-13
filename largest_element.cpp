#include <iostream>
using namespace std;

int findLargest(int* arr, int size) {
    int* largest = arr;  // Start with the first element as the largest

    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *largest) {
            largest = arr + i;  // Update the largest pointer if a larger element is found
        }
    }

    return *largest;  // Dereference the pointer to get the largest value
}

int main() {
    int n;

    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];  // Declare an array of size n

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int largest = findLargest(arr, n);

    cout << "The largest element in the array is: " << largest << endl;

    return 0;
}

///////

// #include <iostream>
// using namespace std;

// int main() {
//     int n;
//     cout << "Enter the number of elements in the array: ";
//     cin >> n;

//     int arr[n];
//     cout << "Enter " << n << " elements: ";
//     for (int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }

//     int* max = &arr[0];  // Pointer to the first element, considered the largest initially

//     for (int i = 1; i < n; i++) {
//         if (*(arr + i) > *max) {  // Compare current element with the max using pointer arithmetic
//             max = arr + i;        // Update max to point to the current largest element
//         }
//     }

//     cout << "The largest element is " << *max << endl;  // Dereference max to get the largest element

//     return 0;
// }

