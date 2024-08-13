#include <iostream>
#include <string>
using namespace std;

class Patient {
public: // Change private to public
    string name;
    int age;
    string ailment;

    // Constructors as before...
    Patient() : name("Unknown"), age(0), ailment("Unknown") {
        cout << "Default Constructor called!" << endl;
        cout << "Name: " << name << ", Age: " << age << ", Ailment: " << ailment << endl;
    }

    Patient(string n, int a, string ail) : name(n), age(a), ailment(ail) {
        cout << "Parameterized Constructor called!" << endl;
        cout << "Name: " << name << ", Age: " << age << ", Ailment: " << ailment << endl;
    }

    Patient(const Patient& other) : name(other.name), age(other.age), ailment(other.ailment) {
        cout << "Copy Constructor called!" << endl;
        cout << "Name: " << name << ", Age: " << age << ", Ailment: " << ailment << endl;
    }

    Patient(Patient&& other) noexcept : name(move(other.name)), age(other.age), ailment(move(other.ailment)) {
        cout << "Move Constructor called!" << endl;
        cout << "Name: " << name << ", Age: " << age << ", Ailment: " << ailment << endl;
        other.age = 0;
    }
};

int main() {
    // Code as before...
    Patient patient1;
    cout << endl;

    Patient patient2("John Doe", 45, "Flu");
    cout << endl;

    Patient patient3 = patient2;
    cout << endl;

    Patient patient4 = move(patient2);
    cout << endl;

    // Direct access now that members are public
    cout << "Name: " << patient2.name << ", Age: " << patient2.age << ", Ailment: " << patient2.ailment << endl;

    return 0;
}
