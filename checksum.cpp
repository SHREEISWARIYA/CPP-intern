#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Function to compute checksum with detailed output
unsigned char computeChecksum(const string& message) {
    unsigned char checksum = 0;
    cout << "Computing checksum for message: " << message << endl;
    
    for (char ch : message) {
        unsigned char charValue = static_cast<unsigned char>(ch);
        cout << "Character: " << ch << " (ASCII: " << hex << static_cast<int>(charValue) << ") ";
        checksum ^= charValue;
        cout << "Intermediate Checksum: " << hex << static_cast<int>(checksum) << endl;
    }
    
    return checksum;
}

// Function to convert a hexadecimal string to an integer
unsigned char hexToInt(const string& hexStr) {
    unsigned int hexValue;
    stringstream ss;
    ss << hex << hexStr;
    ss >> hexValue;
    return static_cast<unsigned char>(hexValue);
}

// Function to verify the checksum with detailed output
bool verifyChecksum(const string& messageWithChecksum) {
    // Extract the message and checksum parts
    size_t asteriskPos = messageWithChecksum.find('*');
    if (asteriskPos == string::npos || asteriskPos + 1 >= messageWithChecksum.length()) {
        cerr << "Checksum part missing or incorrect format." << endl;
        return false; // No checksum found
    }

    string message = messageWithChecksum.substr(1, asteriskPos - 1); // Remove leading '!' and get message
    string checksumStr = messageWithChecksum.substr(asteriskPos + 1); // Get checksum part

    // Compute the checksum for the message
    unsigned char computedChecksum = computeChecksum(message);
    cout << "Computed Checksum: " << hex << static_cast<int>(computedChecksum) << endl;

    // Convert the given checksum from hexadecimal string to integer
    unsigned char givenChecksum = hexToInt(checksumStr);
    cout << "Given Checksum: " << hex << static_cast<int>(givenChecksum) << endl;

    // Compare computed and given checksum
    return computedChecksum == givenChecksum;
}

int main() {
    string aisMessage;
    
    // Prompt the user for input
    cout << "Enter the AIS message including the checksum: ";
    getline(cin, aisMessage);
    
    // Verify and output the result
    if (verifyChecksum(aisMessage)) {
        cout << "Checksum is valid." << endl;
    } else {
        cout << "Checksum is invalid." << endl;
    }
    
    return 0;
}
