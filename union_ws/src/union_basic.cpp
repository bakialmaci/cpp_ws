#include <iostream>
using namespace std;

// Union definition: It can store either an int or a float in the same memory area
union Value {
    int i;
    float f;
};

// We use an enum to keep track of which type is stored in the union
enum Type { INT, FLOAT };

struct Entry {
    Type t;    // Data type: int or float
    Value v;   // Data value
};

// Print the value of an Entry by checking its type
void print_entry(const Entry& e) {
    if (e.t == INT) {
        cout << "Integer value:" << e.v.i << endl;
    } else if (e.t == FLOAT) {
        cout << "Float value:" << e.v.f << endl;
    }
}

int main() {
    // First Entry stores an integer value
    Entry e1;
    e1.t = INT;
    e1.v.i = 42;

    // Second Entry stores a float value
    Entry e2;
    e2.t = FLOAT;
    e2.v.f = 3.14f;

    // Print the values of the entries
    print_entry(e1);
    print_entry(e2);

    // Update the value of the first entry
    e1.v.f = 2.71f;     // This will cause an error because the type is not updated!
    print_entry(e1);    // This will print a wrong value because the type is not updated!

    return 0;
}
