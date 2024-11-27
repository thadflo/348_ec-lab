#include <iostream>
#include <iomanip>  // for fixed and setprecision
#include <string>   // for string manipulation

// avoids repeating std::
using namespace std;

// prototype for the extractNumeric function
double extractNumeric(const string& str);

int main() {
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        // check if the user wants to exit
        if (input == "END") {
            break;
        }

        // extract numeric value from the input string
        double number = extractNumeric(input);

        if (number != -999999.99) {
            // valid number: display with fixed-point notation and 4 decimal places
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            // invalid input
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}

// function to extract a valid double-precision floating-point number
double extractNumeric(const string& str) {
    bool hasDigits = false;       // Flag to check if there are digits
    bool hasDecimal = false;      // Flag to check if there's a decimal point
    bool isNegative = false;      // Flag for negative sign
    int signCount = 0;            // Count of '+' or '-' signs
    double result = 0.0;          // Final numeric result
    double decimalFactor = 0.1;   // Multiplier for decimal places

    // iterate through the string to validate and extract the number
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];

        // handle sign characters '+' or '-'
        if (c == '+' || c == '-') {
            if (i != 0 || signCount > 0) {
                return -999999.99;  // invalid: '+' or '-' must be at the start and appear only once
            }
            isNegative = (c == '-');
            signCount++;
        }
        // handle digits '0' to '9'
        else if (c >= '0' && c <= '9') {
            hasDigits = true;
            if (hasDecimal) {
                result += (c - '0') * decimalFactor;
                decimalFactor /= 10;
            } else {
                result = result * 10 + (c - '0');
            }
        }
        // handle the decimal point '.'
        else if (c == '.') {
            if (hasDecimal) {
                return -999999.99;  // Invalid: multiple decimal points
            }
            hasDecimal = true;
        }
        // invalid character
        else {
            return -999999.99;
        }
    }

    // if no digits are found, return invalid
    if (!hasDigits) {
        return -999999.99;
    }

    // apply negative sign if needed
    if (isNegative) {
        result = -result;
    }

    return result;
}
