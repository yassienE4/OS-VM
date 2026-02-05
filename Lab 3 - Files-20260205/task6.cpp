#include <iostream>
#include <cstdlib>

using namespace std;

extern char** environ;

int main() {
    const char* var = "MYVAR";
    // Read EV
    char* value = getenv(var);
    if (value)
        cout << var << " = " << value << endl;
    else
        cout << var << " is not set" << endl;
    // Set EV
    setenv(var, "HelloWorld", 1);
    // Read EV again
    cout << "After setenv:" << endl;
    cout << var << " = " << getenv(var) << endl;
    return 0;
}
