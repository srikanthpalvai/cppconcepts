/*
What Does [[fallthrough]] Add?
Explicit Intent for Developers:

The [[fallthrough]] attribute makes it clear to anyone reading the code that the fallthrough
is intentional and not an oversight. Without it, readers may assume that a missing break was accidental.

Suppresses Compiler Warnings:

Many modern compilers (e.g., GCC, Clang) issue warnings for implicit fallthroughs because they are often unintentional
and can lead to bugs. Using [[fallthrough]] explicitly tells the compiler that the fallthrough is deliberate, suppressing these warnings.

Improves Code Maintainability:

By documenting intentional fallthroughs directly in the code,
it becomes easier for future developers (or even yourself) to understand and maintain the code without needing additional comments.

Standardized Syntax:

Before C++17, developers used comments like // fall through to indicate intentional fallthroughs.
 However, comments are not understood by compilers and do not suppress warnings. The [[fallthrough]] attribute provides a standardized way to achieve this.
*/
#include <iostream>
using namespace std;
void switch_statement(int x){

    switch (x)
    {
    case 1:
    cout << "case 1" << endl;
    [[fallthrough]];
    case 2:
    cout << "case 2" << endl;
    case 3:
    cout << "case 3" << endl;
    case 4:
    cout << "case 4" << endl;
    case 5:
    cout << "case 5" << endl;
    case 6:
    cout << "case 6" << endl;
    case 7:
    cout << "case 7" << endl;
    default:
        break;
    }
}

int main (){

    int c;
    cout << "Enter the case number" << endl;
    cin >> c;
    switch_statement(c);
}