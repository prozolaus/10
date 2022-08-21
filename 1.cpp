#include "std_lib_facilities.h"

void skip_to_int(istream &ist)
{
    ist.exceptions(ist.exceptions() | ios_base::badbit);
    
    if (ist.fail())
    {
        ist.clear();
        for (char ch; ist >> ch;)
        {
            if (isdigit(ch) || ch == '-')
            {
                ist.unget();
                return;
            }
            else
                cout << "'" <<  ch << "'" << " is not a number\n";
        }
    }
}

int get_int(istream &ist)
{
    int n = 0;
    while (true)
    {
        if (ist >> n)
            return n;
        skip_to_int(ist);
        if (ist.eof())
            return 0;
    }
}

int main()
{
    string fname = "1.txt";
    ifstream ist{fname};
    if (!ist)
        error("Unable to open input file", fname);
    int sum = 0;
    while (!ist.eof())
    {
        sum += get_int(ist);
    }
    cout << "The sum of input numbers is " << sum << endl;
}