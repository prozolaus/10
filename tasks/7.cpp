#include "std_lib_facilities.h"

void skip_to_int()
{
    if (cin.fail())
    {
        cin.clear();
        for (char ch; cin >> ch;)
        {
            if (isdigit(ch) || ch == '-')
            {
                cin.unget();
                return;
            }
        }
    }
    error("No input"); //state eof or bad
}

int get_int()
{
    int n = 0;
    while (true)
    {
        if (cin >> n)
            return n;
        cout << "It is not a number; try again\n";
        skip_to_int();
    }
}

int get_int(int low, int high, const string &greeting, const string &sorry)
{
    cout << greeting << ": [" << low << ":" << high << "]" << endl;
    while (true)
    {
        int n = get_int();
        if (low <= n && n <= high)
            return n;
        cout << sorry << ": [" << low << ":" << high << "]" << endl;
    }
}

int main()
{
    int strength = get_int(1, 10, "Input strength", "Out of range, try again");
    cout << "Strength: " << strength << endl;
}