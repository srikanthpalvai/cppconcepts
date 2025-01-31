#include <iostream>
#include <string>

// Traditional enum for days of the week
enum DayOfWeek { MON, TUE, WED, THU, FRI, SAT, SUN };

// Strongly-typed enum for months
enum class Month {
    JAN = 1, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC
};

// Function using traditional enum
void scheduleEvent(DayOfWeek day) {
    // Problem: Accidental use of unrelated constant
    if (day == 3) { // This compiles, but it's logically incorrect
        std::cout << "Scheduling for Wednesday" << std::endl;
    }
}

// Function using enum class
std::string getMonthName(Month month) {
    switch (month) {
        case Month::JAN: return "January";
        case Month::FEB: return "February";
        // ... other months ...
        case Month::DEC: return "December";
        default: return "Invalid month";
    }
}

int main() {
    // Traditional enum issues
    DayOfWeek day = FRI;
    int dayNumber = day; // Implicit conversion allowed

    // Enum class benefits
    Month month = Month::MAY;
    // int monthNumber = month; // Error: no implicit conversion
    int monthNumber = static_cast<int>(month); // Explicit conversion required

    // Avoiding accidental comparisons
    // if (month == FRI) {} // Error: can't compare Month with DayOfWeek
    if (month == Month::MAY) {
        std::cout << "It's May!" << std::endl;
    }

    // Using the enum class in a function
    std::cout << "Month name: " << getMonthName(month) << std::endl;

    return 0;
}
/*
Type safety: Month enum class prevents implicit conversions and accidental comparisons with unrelated types.
Scoped access: Values must be accessed as Month::JAN, Month::FEB, etc., improving code clarity.
Explicit conversions: Converting enum class to int requires a cast, preventing unintended conversions.
Stronger typing in function parameters: getMonthName function can only accept Month enum class values.
Comparison safety: Can't accidentally compare Month with DayOfWeek or arbitrary integers.
*/
