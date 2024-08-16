#include <iostream>
#include <vector>
#include <sstream>
#include <bitset>
#include <iomanip>
#include <unordered_map>

using namespace std;

// Function to map characters to 6-bit binary values
string charTo6BitBinary(char ch) {
    if (ch >= '0' && ch <= '9') {
        return bitset<6>(ch - '0').to_string(); // 0-9 -> 000000-000101
    } else if (ch >= 'A' && ch <= 'W') {
        return bitset<6>(ch - 'A' + 17).to_string(); // A-W -> 010001-100111
    } else if (ch >= 'a' && ch <= 'w') {
        return bitset<6>(ch - 'a' + 41).to_string(); // a-w -> 101001-111111
    } else if (ch == ':') {
        return "001010"; // : -> 001010 (58 in decimal)
    } else if (ch == ';') {
        return "001011"; // ; -> 001011 (59 in decimal)
    } else if (ch == '<') {
        return "001100"; // < -> 001100 (60 in decimal)
    } else if (ch == '=') {
        return "001101"; // = -> 001101 (61 in decimal)
    } else if (ch == '>') {
        return "001110"; // > -> 001110 (62 in decimal)
    } else if (ch == '?') {
        return "001111"; // ? -> 001111 (63 in decimal)
    } else if (ch == '@') {
        return "010000"; // @ -> 010000 (64 in decimal)
    } else {
        return "000000"; // Default or unrecognized characters to 000000
    }
}

vector<string> splitAISMessage(const string &message) {
    vector<string> result;
    stringstream ss(message);
    string item;

    while (getline(ss, item, ',')) {
        result.push_back(item);
    }

    return result;
}

vector<string> get6BitBinaryValues(const string &combinedPart) {
    vector<string> binaryValues;
    for (char ch : combinedPart) {
        binaryValues.push_back(charTo6BitBinary(ch));
    }
    return binaryValues;
}

// Function to map 6-bit binary values to AIS characters
char binaryToAISChar(const string &binary) {
    int value = bitset<6>(binary).to_ulong();
    if (value >= 0 && value <= 9) {
        return '0' + value;
    } else if (value >= 10 && value <= 33) {
        return 'A' + (value - 10);
    } else if (value == 34) {
        return ' ';
    } else if (value == 35) {
        return ' ';
    } else {
        return '?'; // Default or unrecognized characters
    }
}

// Function to map the ship type (from 8-bit binary value) to the ship type name
string getShipType(int shipTypeCode) {
    unordered_map<int, string> shipTypeMap = {
        // Ship types map (same as before)
        {0, "Not available (default)"},
        {20, "Wing in ground (WIG), all ships of this type"},
        {21, "WIG, Hazardous category A"},
        {22, "WIG, Hazardous category B"},
        {23, "WIG, Hazardous category C"},
        {24, "WIG, Hazardous category D"},
        {25, "WIG, Reserved for future use"},
        {26, "WIG, Reserved for future use"},
        {27, "WIG, Reserved for future use"},
        {28, "WIG, Reserved for future use"},
        {29, "WIG, Reserved for future use"},
        {30, "Fishing"},
        {31, "Towing"},
        {32, "Towing, length exceeds 200m or breadth exceeds 25m"},
        {33, "Dredging or underwater ops"},
        {34, "Diving ops"},
        {35, "Military ops"},
        {36, "Sailing"},
        {37, "Pleasure craft"},
        {50, "Pilot vessel"},
        {51, "Search and rescue vessel"},
        {52, "Tug"},
        {53, "Port tender"},
        {54, "Anti-pollution equipment"},
        {55, "Law enforcement"},
        {56, "Spare – Local Vessel"},
        {57, "Spare – Local Vessel"},
        {58, "Medical Transport"},
        {59, "Noncombatant ship according to RR Resolution No. 18"},
        {60, "Passenger, all ships of this type"},
        {61, "Passenger, Hazardous category A"},
        {62, "Passenger, Hazardous category B"},
        {63, "Passenger, Hazardous category C"},
        {64, "Passenger, Hazardous category D"},
        {65, "Passenger, Reserved for future use"},
        {66, "Passenger, Reserved for future use"},
        {67, "Passenger, Reserved for future use"},
        {68, "Passenger, Reserved for future use"},
        {69, "Passenger, Reserved for future use"},
        {70, "Cargo, all ships of this type"},
        {71, "Cargo, Hazardous category A"},
        {72, "Cargo, Hazardous category B"},
        {73, "Cargo, Hazardous category C"},
        {74, "Cargo, Hazardous category D"},
        {75, "Cargo, Reserved for future use"},
        {76, "Cargo, Reserved for future use"},
        {77, "Cargo, Reserved for future use"},
        {78, "Cargo, Reserved for future use"},
        {79, "Cargo, Reserved for future use"},
        {80, "Tanker, all ships of this type"},
        {81, "Tanker, Hazardous category A"},
        {82, "Tanker, Hazardous category B"},
        {83, "Tanker, Hazardous category C"},
        {84, "Tanker, Hazardous category D"},
        {85, "Tanker, Reserved for future use"},
        {86, "Tanker, Reserved for future use"},
        {87, "Tanker, Reserved for future use"},
        {88, "Tanker, Reserved for future use"},
        {89, "Tanker, Reserved for future use"},
        {90, "Other types, all ships of this type"},
        {91, "Other types, Hazardous category A"},
        {92, "Other types, Hazardous category B"},
        {93, "Other types, Hazardous category C"},
        {94, "Other types, Hazardous category D"},
        {95, "Other types, Reserved for future use"},
        {96, "Other types, Reserved for future use"},
        {97, "Other types, Reserved for future use"},
        {98, "Other types, Reserved for future use"},
        {99, "Other types, Reserved for future use"}
    };

    return shipTypeMap[shipTypeCode];
}

int decodeDimensionToBow(const string &dimensionToBowBits) {
    // Convert the 8-bit segment to an integer
    int value = bitset<8>(dimensionToBowBits).to_ulong();

    // The value is in decimeters (0.1 meters)
    // Convert to meters
    return value / 10;
}

// Function to convert a 6-bit binary string to its corresponding character
char decode6BitChar(const string& sixBitBinary) {
    int decimalValue = bitset<6>(sixBitBinary).to_ulong();
    if (decimalValue < 10) {
        return '0' + decimalValue;
    } else if (decimalValue < 36) {
        return 'A' + (decimalValue - 10);
    } else if (decimalValue < 62) {
        return 'a' + (decimalValue - 36);
    } else {
        return '?'; // Handle cases for values 62 and 63 if needed
    }
}

// Function to convert a 1-bit binary string to its corresponding status
string decode1BitStatus(const string& oneBitBinary) {
    int decimalValue = bitset<1>(oneBitBinary).to_ulong();
    if (decimalValue == 0) {
        return "Data terminal ready";
    } else if (decimalValue == 1) {
        return "Not ready";
    } else {
        return "Unknown"; // Handle unexpected values
    }
}

// Function to convert a 1-bit binary string to its decimal representation
int decode1BitToDecimal(const string& oneBitBinary) {
    return bitset<1>(oneBitBinary).to_ulong();
}

// Function to convert an integer to a base-36 string
string intToBase36(unsigned long long value) {
    const string base36Chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    do {
        result = base36Chars[value % 36] + result;
        value /= 36;
    } while (value > 0);
    return result;
}

// Function to decode AIS name from a 120-bit binary segment
string decodeAISName(const string &binaryMessage) {
    string decodedName;
    const string AIS_CHARSET = " ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^- !\"#$%&'()*+,-./0123456789:;<=>?";

    for (size_t i = 0; i < 120; i += 6) {
        string chunk = binaryMessage.substr(i, 6);
        bitset<6> bits(chunk);
        int value = static_cast<int>(bits.to_ulong());
        char decodedChar = AIS_CHARSET[value];
        if (decodedChar != ' ')
            decodedName += decodedChar;
    }

    return decodedName;
}

// Function to convert a binary string to a hexadecimal string
string binaryToHex(const string& binaryString) {
    // Ensure the binary string length is a multiple of 4
    size_t length = binaryString.length();
    size_t padding = (4 - (length % 4)) % 4;
    string paddedBinaryString = string(padding, '0') + binaryString;

    // Convert binary string to unsigned long long
    unsigned long long binaryValue = bitset<64>(paddedBinaryString).to_ullong(); // Assumes binary string fits in 64 bits

    // Convert to hexadecimal string
    stringstream ss;
    ss << hex << uppercase << binaryValue;

    return ss.str();
}

// Function to decode the call sign from a binary message
string decodeCallSign(const string& binaryMessage) {
    if (binaryMessage.length() < 42) {
        cerr << "Binary message too short for extraction!" << endl;
        return "";
    }

    // Extract the 42-bit segment starting from bit 70 to 111 (0-based indexing)
    string callSignBinary = binaryMessage.substr(69, 42); // Extract 42 bits starting from 70th bit

    cout << "Extracted Call Sign Binary: " << callSignBinary << endl; // Debugging output

    string callSign;
    for (size_t i = 0; i < callSignBinary.length(); i += 6) {
        string chunk = callSignBinary.substr(i, 6);
        char decodedChar = decode6BitChar(chunk);
        callSign += decodedChar;
    }

    return callSign;
}


int main() {
    string aisMessage1 = "!AIVDM,2,1,1,A,55?MbV02;H;s<HtKR20EHE:0@T4@Dn2222222216L961O5Gf0NSQEp6ClRp8,0*1C";
    string aisMessage2 = "!AIVDM,2,2,1,A,88888888880,2*25";

    vector<string> splitMessage1 = splitAISMessage(aisMessage1);
    vector<string> splitMessage2 = splitAISMessage(aisMessage2);

    // Combine part 6 of both splits
    string combinedPart6;
    if (splitMessage1.size() >= 6 && splitMessage2.size() >= 6) {
        combinedPart6 = splitMessage1[5] + splitMessage2[5];
        cout << "Combined Part 6: " << combinedPart6 << endl;
    } else {
        cout << "One of the messages doesn't have a part 6!" << endl;
        return 1;
    }

    // Get the 6-bit binary values of each character in combinedPart6
    vector<string> binaryValues = get6BitBinaryValues(combinedPart6);

    // Concatenate all binary values into a single string
    string concatenatedBinary;
    for (const string &binaryValue : binaryValues) {
        concatenatedBinary += binaryValue;
    }

    // Print the 6-bit binary values and the concatenated binary string
    cout << "\n6-bit Binary values of each character in Combined Part 6:" << endl;
    for (size_t i = 0; i < binaryValues.size(); ++i) {
        cout << "Character: " << combinedPart6[i] << " -> 6-bit Binary: " << binaryValues[i] << endl;
    }

    cout << "\nConcatenated Binary String: " << concatenatedBinary << endl;

    // Extract the first 6-bit segment and convert to decimal
    if (concatenatedBinary.length() >= 6) {
        string segment = concatenatedBinary.substr(0, 6);
        int decimalValue = bitset<6>(segment).to_ulong();
        cout << "\nMessage Type - Decimal: " << decimalValue << endl;
    } else {
        cout << "Insufficient data to extract 6-bit segment." << endl;
    } 

    // Extract the 6th and 7th bits (indices 5 and 6) and convert to decimal
    if (concatenatedBinary.length() >= 7) {
        string repeatIndicatorBits = concatenatedBinary.substr(5, 2);
        int repeatIndicatorValue = bitset<2>(repeatIndicatorBits).to_ulong();
        cout << "\nRepeat Indicator - Decimal: " << repeatIndicatorValue << endl;
    } else {
        cout << "Insufficient data to extract 2-bit repeat indicator." << endl;
    } 

    // Extract the 30-bit segment from position 8 to 37 and convert to decimal
    if (concatenatedBinary.length() >= 38) {
        string mmsiBits = concatenatedBinary.substr(8, 30);
        long long mmsiValue = bitset<30>(mmsiBits).to_ullong();
        cout << "\nMMSI - Decimal: " << mmsiValue << endl;
    } else {
        cout << "Insufficient data to extract 30-bit MMSI." << endl;
    } 

    // Extract the 2-bit segment from position 38 to 39 and convert to decimal
    if (concatenatedBinary.length() >= 40) {
        string aisVersionBits = concatenatedBinary.substr(38, 2);
        int aisVersionValue = bitset<2>(aisVersionBits).to_ulong();
        cout << "\nAIS Version - Decimal: " << aisVersionValue << endl;
    } else {
        cout << "Insufficient data to extract 2-bit AIS version." << endl;
    }

    // Extract the 42-bit segment from position 70 to 111 and convert to base-36
    if (concatenatedBinary.length() >= 112) {
        string callSignBits = concatenatedBinary.substr(70, 42);
        // Convert to an unsigned long long to handle the large value
        unsigned long long callSignValue = bitset<42>(callSignBits).to_ullong();
        // Convert to base-36
        string callSignBase36 = intToBase36(callSignValue);
        // Print the base-36 Call Sign
        cout << "\nCall Sign - Base-36: " << callSignBase36 << endl;
    } else {
        cout << "Insufficient data to extract 42-bit Call Sign." << endl;
    } 

    // // Example usage in main
    // if (concatenatedBinary.length() >= 112) {
    // string callSignBits = concatenatedBinary.substr(69, 42); // Corrected index for 42-bit extraction

    // // Decode the 42-bit binary segment to a readable call sign
    // string callSign = decodeCallSign(callSignBits);

    // // Print the decoded Call Sign
    // cout << "\nCall Sign: " << callSign << endl;
    // } else {
    // cout << "Insufficient data to extract 42-bit Call Sign." << endl;
    // }

    
    // Extract the 120-bit segment from position 112 to 231
    if (concatenatedBinary.length() >= 231) {
        string vesselNameBits = concatenatedBinary.substr(112, 120);
        
        // Call the decodeAISName function to decode the vessel name
        string vesselName = decodeAISName(vesselNameBits);
        
        cout << "\nVessel Name: " << vesselName << endl;
    } else {
        cout << "Insufficient data to extract 120-bit Vessel Name." << endl;
    }

    // Extract the 8-bit segment from position 232 to 239 and convert to decimal
    if (concatenatedBinary.length() >= 240) { // Ensure there are at least 240 bits
        string shipTypeBits = concatenatedBinary.substr(232, 8);
        int shipTypeValue = bitset<8>(shipTypeBits).to_ulong();

        // Map the 8-bit value to a ship type
        string shipType = getShipType(shipTypeValue);

        cout << "\nShip Type - Decimal: " << shipTypeValue << endl;
        cout << "Ship Type: " << shipType << endl;
    } else {
        cout << "Insufficient binary data length!" << endl;
    }

    if (concatenatedBinary.length() >= 249) {
    string dimensionToBowBits = concatenatedBinary.substr(240, 9);
    
    // Convert the 9-bit segment to decimal
    int decimalValue = bitset<9>(dimensionToBowBits).to_ulong();
    
    // Map the decimal value to meters
    // Adjust the conversion factor based on your specific application or data scale
    float dimensionToBowMeters = static_cast<float>(decimalValue); // Assume direct conversion

    // Print the result
    cout << "\nDimension to Bow in meters: " << dimensionToBowMeters << " meters" << endl;
    } else {
    cout << "Insufficient data to extract 9-bit Dimension to Bow." << endl;
    }


    // Extract the 9-bit segment from position 249 to 257
    if (concatenatedBinary.length() >= 258) {
    string dimensionToSternBits = concatenatedBinary.substr(249, 9);
    
    // Convert the 9-bit segment to decimal
    int decimalValue = bitset<9>(dimensionToSternBits).to_ulong();
    
    // Map the decimal value to meters
    // Adjust the conversion factor based on your specific application or data scale
    float dimensionToSternMeters = static_cast<float>(decimalValue); // Assume direct conversion

    // Print the result
    cout << "\nDimension to Stern in meters: " << dimensionToSternMeters << " meters" << endl;
    } else {
    cout << "Insufficient data to extract 9-bit Dimension to Stern." << endl;
    }

    // Extract the 6-bit segment from position 258 to 263
    if (concatenatedBinary.length() >= 264) {
    string dimensionToPortBits = concatenatedBinary.substr(258, 6);
    
    // Convert the 6-bit segment to decimal
    int decimalValue = bitset<6>(dimensionToPortBits).to_ulong();
    
    // Map the decimal value to meters
    // Adjust the conversion factor based on your specific application or data scale
    float dimensionToPortMeters = static_cast<float>(decimalValue); // Assume direct conversion

    // Print the result
    cout << "\nDimension to Port in meters: " << dimensionToPortMeters << " meters" << endl;
    } else {
    cout << "Insufficient data to extract 6-bit Dimension to Port." << endl;
    }

    // Extract the 6-bit segment from position 264 to 269
    if (concatenatedBinary.length() >= 270) {
    string dimensionToStarboardBits = concatenatedBinary.substr(264, 6);
    
    // Convert the 6-bit segment to decimal
    int decimalValue = bitset<6>(dimensionToStarboardBits).to_ulong();
    
    // Map the decimal value to meters
    // Adjust the conversion factor based on your specific application or data scale
    float dimensionToStarboardMeters = static_cast<float>(decimalValue); // Assume direct conversion

    // Print the result
    cout << "\nDimension to Starboard in meters: " << dimensionToStarboardMeters << " meters" << endl;
    } else {
    cout << "Insufficient data to extract 6-bit Dimension to Starboard." << endl;
    }

    // Extract the 3-bit segment from position 270 to 273
    if (concatenatedBinary.length() >= 274) {
    string positionFixTypeBits = concatenatedBinary.substr(270, 3);
    
    // Convert the 3-bit segment to decimal
    int positionFixTypeValue = bitset<3>(positionFixTypeBits).to_ulong();
    
    // Print the result
    cout << "\nPosition Fix Type: " << positionFixTypeValue << endl;
    } else {
    cout << "Insufficient data to extract 3-bit Position Fix Type." << endl;
    }

    // Extract the 4-bit segment from position 274 to 277
    if (concatenatedBinary.length() >= 278) {
    string etaMonthBits = concatenatedBinary.substr(274, 4);
    
    // Convert the 4-bit segment to decimal
    int etaMonthValue = bitset<4>(etaMonthBits).to_ulong();
    
    // Print the result
    cout << "\nETA month (UTC): " << etaMonthValue << endl;
    } else {
    cout << "Insufficient data to extract 4-bit ETA month (UTC)." << endl;
    }

    // Extract the 5-bit segment from position 278 to 282
    if (concatenatedBinary.length() >= 283) {
    string etaDayBits = concatenatedBinary.substr(278, 5);
    
    // Convert the 5-bit segment to decimal
    int etaDayValue = bitset<5>(etaDayBits).to_ulong();
    
    // Print the result as "ETA day (UTC)"
    cout << "\nETA day (UTC): " << etaDayValue << endl;
    } else {
    cout << "Insufficient data to extract 5-bit ETA day (UTC)." << endl;
    }

    // Extract the 5-bit segment from position 283 to 287
    if (concatenatedBinary.length() >= 288) {
    string etaHourBits = concatenatedBinary.substr(283, 5);
    
    // Convert the 5-bit segment to decimal
    int etaHourValue = bitset<5>(etaHourBits).to_ulong();
    
    // Convert to hours with 24 as default
    if (etaHourValue == 24) {
        etaHourValue = 24; // Default value for '24' if needed
    } else if (etaHourValue > 23) {
        etaHourValue = 24; // Default value for out-of-bounds
    }
    
    // Print the result as "ETA hour (UTC)"
    cout << "\nETA hour (UTC) - Decimal: " << etaHourValue << endl;
    } else {
    cout << "Insufficient data to extract 5-bit ETA hour (UTC)." << endl;
    }

    // Extract the 6-bit segment from position 288 to 293
    if (concatenatedBinary.length() >= 294) { // Ensure we have enough bits
        string minuteBits = concatenatedBinary.substr(288, 6);
        
        // Convert the 6-bit segment to decimal
        int minuteValue = bitset<6>(minuteBits).to_ulong();
        
        // Convert to minutes with 60 as default
        if (minuteValue == 60) {
            minuteValue = 60; // Default value for '60' if needed
        } else if (minuteValue > 59) {
            minuteValue = 60; // Default value for out-of-bounds
        }
        
        // Print the result as "ETA minute (UTC)"
        cout << "\nETA minute (UTC): " << minuteValue << endl;
    } else {
        cout << "Insufficient data to extract 6-bit ETA minute (UTC)." << endl;
    }

    // Extract the 8-bit segment from position 294 to 301
    if (concatenatedBinary.length() >= 302) { // Ensure we have enough bits
        string draughtBits = concatenatedBinary.substr(294, 8);
        
        // Convert the 8-bit segment to decimal
        int draughtValue = bitset<8>(draughtBits).to_ulong();
        
        // Convert to meters/10
        double draughtInMeters = draughtValue / 10.0;
        
        // Print the result
        cout << fixed << setprecision(1); // Print with 1 decimal place
        cout << "\nDraught: " << draughtInMeters << " meters" << endl;
    } else {
        cout << "Insufficient data to extract 8-bit Draught." << endl;
    }

    // Extract the 120-bit segment for Destination from position 302 to 421
    if (concatenatedBinary.length() >= 422) {
        string destinationBits = concatenatedBinary.substr(302, 120);
        
        // Decode the destination
        string destination = decodeAISName(destinationBits);
        
        cout << "Destination: " << destination << endl;
    } else {
        cout << "Insufficient data to extract 120-bit Destination." << endl;
    }

    if (concatenatedBinary.length() >= 423) { // Length check for 423 bits including position 422
        string dteBit = concatenatedBinary.substr(422, 1);
        
        string dteStatus = decode1BitStatus(dteBit);
        
        cout << "DTE: " << dteStatus << endl;
    } else {
        cout << "Insufficient data to extract 1-bit DTE." << endl;
    }

    if (concatenatedBinary.length() >= 424) { // Length check for 424 bits including position 423
        string spareBit = concatenatedBinary.substr(423, 1);
        
        int spareValue = decode1BitToDecimal(spareBit);
        
        cout << "Spare: " << spareValue << endl;
    } else {
        cout << "Insufficient data to extract 1-bit Spare." << endl;
    }

    return 0; 
} 
