#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include <iomanip>

// Function to convert a character to its 6-bit binary representation
std::string charTo6BitBinary(char c) {
    int decimalValue;

    // Define mappings for specific characters
    if (c >= '0' && c <= '9') {
        decimalValue = c - '0';  // '0' to '9' map to 0 to 9
    } else if (c == ':') {
        decimalValue = 10;  // ':' maps to 10
    } else if (c == ';') {
        decimalValue = 11;  // ';' maps to 11
    } else if (c == '<') {
        decimalValue = 12;  // '<' maps to 12
    } else if (c == '=') {
        decimalValue = 13;  // '=' maps to 13
    } else if (c == '>') {
        decimalValue = 14;  // '>' maps to 14
    } else if (c == '?') {
        decimalValue = 15;  // '?' maps to 15
    } else if (c == '@') {
        decimalValue = 16;  // '@' maps to 16
    } else if (c >= 'A' && c <= 'W') {
        decimalValue = c - 'A' + 17;  // 'A' to 'W' map to 17 to 39
    } else if (c >= 'a' && c <= 'w') {
        decimalValue = c - 'a' + 41;  // 'a' to 'w' map to 41 to 63
    } else if (c == '\'') {
        decimalValue = 96;  // '\'' maps to 96
    } else {
        decimalValue = 40;  // Default value for unrecognized characters (e.g., 101000 in decimal)
    }

    // Convert the decimal value to a 6-bit binary string
    return std::bitset<6>(decimalValue).to_string();
}

// Function to convert a binary string to a hexadecimal string
std::string binaryToHex(const std::string& binary) {
    std::stringstream hexStream;
    std::string hexChars = "0123456789ABCDEF";
    
    // Ensure the binary string is a multiple of 4 in length
    std::string paddedBinary = binary;
    while (paddedBinary.length() % 4 != 0) {
        paddedBinary = '0' + paddedBinary;
    }
    
    // Convert each 4-bit binary chunk to hexadecimal
    for (std::size_t i = 0; i < paddedBinary.length(); i += 4) {
        std::bitset<4> nibble(paddedBinary.substr(i, 4));
        hexStream << hexChars[nibble.to_ulong()];
    }
    
    return hexStream.str();
}

int main() {
    // Example AIVDM message
    std::string aivdm_message = "!AIVDM,1,1,,A,85Mwp`1Kf3aCnsNvBWLi=wQuNhA5t43N`5nCuI=p<IBfVqnMgPGs,0*47";

    // Vector to store the parts
    std::vector<std::string> parts;

    // String to store the continuous binary sequence
    std::string continuousBinarySequence;

    // Create a string stream from the AIVDM message
    std::stringstream ss(aivdm_message);
    std::string item;

    // Split the string by commas
    while (std::getline(ss, item, ',')) {
        parts.push_back(item);
    }

    // Print the separated parts
    std::cout << "Separated AIVDM Message Parts:" << std::endl;
    for (size_t i = 0; i < parts.size(); ++i) {
        std::cout << "Part " << i + 1 << ": " << parts[i] << std::endl;
    }

    // Check if there are enough parts
    if (parts.size() < 6) {
        std::cerr << "Not enough parts in the AIVDM message" << std::endl;
        return 1;
    }

    // Extract the 6th part (index 5 in 0-based index)
    std::string part6 = parts[5];

    // Convert each character to binary and append to the continuous binary sequence
    for (char c : part6) {
        std::string binary = charTo6BitBinary(c);
        continuousBinarySequence += binary;  // Append binary digits to the continuous sequence
    }

    // Print the continuous binary sequence
    std::cout << "\nContinuous 6-bit binary sequence for part 6:" << std::endl;
    std::cout << continuousBinarySequence << std::endl;

    // Extract the first 6-bit segment and convert to decimal
    if (continuousBinarySequence.length() >= 6) {
        std::string segment = continuousBinarySequence.substr(0, 6);
        int decimalValue = std::bitset<6>(segment).to_ulong();
        std::cout << "\nMessage Type - Decimal: " << decimalValue << std::endl;
    } else {
        std::cout << "Insufficient data to extract 6-bit segment." << std::endl;
    }

    // Extract the 6th and 7th bits (2-bit segment) from the continuous binary sequence
    if (continuousBinarySequence.length() >= 8) {  // Ensure there are at least 8 bits available
        std::string bitSegment = continuousBinarySequence.substr(6, 2);  // Extract bits 6 and 7
        int repeatIndicator = std::bitset<2>(bitSegment).to_ulong();  // Convert to decimal
        std::cout << "\nRepeat Indicator - Decimal: " << repeatIndicator << std::endl;
    } else {
        std::cout << "Insufficient data to extract 2-bit segment." << std::endl;
    }

    // Extract the 8th to 37th bits (30-bit segment) from the continuous binary sequence
    if (continuousBinarySequence.length() >= 38) {  // Ensure there are at least 38 bits available
        std::string bitSegment = continuousBinarySequence.substr(8, 30);  // Extract bits 8 to 37
        int sourceMMSI = std::bitset<30>(bitSegment).to_ulong();  // Convert to decimal
        std::cout << "\nSource MMSI - Decimal: " << sourceMMSI << std::endl;
    } else {
        std::cout << "Insufficient data to extract 30-bit segment." << std::endl;
    }

    // Extract the 38th and 39th bits (2-bit segment) from the continuous binary sequence
    if (continuousBinarySequence.length() >= 40) {  // Ensure there are at least 40 bits available
        std::string bitSegment = continuousBinarySequence.substr(38, 2);  // Extract bits 38 and 39
        int spare = std::bitset<2>(bitSegment).to_ulong();  // Convert to decimal
        std::cout << "\nSpare - Decimal: " << spare << std::endl;
    } else {
        std::cout << "Insufficient data to extract 2-bit segment." << std::endl;
    }

    // Extract the 40th to 49th bits (10-bit segment) from the continuous binary sequence
    if (continuousBinarySequence.length() >= 50) {  // Ensure there are at least 50 bits available
        std::string bitSegment = continuousBinarySequence.substr(40, 10);  // Extract bits 40 to 49
        int designatedAreaCode = std::bitset<10>(bitSegment).to_ulong();  // Convert to decimal
        std::cout << "\nDesignated Area Code - Decimal: " << designatedAreaCode << std::endl;
    } else {
        std::cout << "Insufficient data to extract 10-bit segment." << std::endl;
    }

    // Extract the 50th to 55th bits (6-bit segment) from the continuous binary sequence
    if (continuousBinarySequence.length() >= 56) {  // Ensure there are at least 56 bits available
        std::string bitSegment = continuousBinarySequence.substr(50, 6);  // Extract bits 50 to 55
        int functionalID = std::bitset<6>(bitSegment).to_ulong();  // Convert to decimal
        std::cout << "\nFunctional ID - Decimal: " << functionalID << std::endl;
    } else {
        std::cout << "Insufficient data to extract 6-bit segment." << std::endl;
    }

    // Extract the bits from the 55th position to the end and convert to hexadecimal
    if (continuousBinarySequence.length() > 55) {
        std::string bitSegment = continuousBinarySequence.substr(55,continuousBinarySequence.length()); 
        std::cout<<bitSegment<<std::endl; // Extract bits from 55 to end
        std::string hexValue = binaryToHex(bitSegment);  // Convert binary segment to hexadecimal
        std::cout << "\nData - Hexadecimal: " << hexValue << std::endl;
    } else {
        std::cout << "Insufficient data to extract bits from 55 to end." << std::endl;
    }
    

    return 0;
}

// #include <iostream>
// #include <sstream>
// #include <vector>
// #include <string>

// int main() {
//     // Example AIVDM message
//     std::string aivdm_message = "!AIVDM,1,1,,A,85Mwp`1Kf3aCnsNvBWLi=wQuNhA5t43N`5nCuI=p<IBfVqnMgPGs,0*47";

//     // Vector to store the parts
//     std::vector<std::string> parts;

//     // Create a string stream from the AIVDM message
//     std::stringstream ss(aivdm_message);
//     std::string item;

//     // Split the string by commas
//     while (std::getline(ss, item, ',')) {
//         parts.push_back(item);
//     }

//     // Display the parts
//     std::cout << "Split AIVDM Message Parts:" << std::endl;
//     for (size_t i = 0; i < parts.size(); ++i) {
//         std::cout << "Part " << i + 1 << ": " << parts[i] << std::endl;
//     }

//     return 0;
// }
