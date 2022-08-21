#include "std_lib_facilities.h"

int main()
try
{
    string iname = "x";
    ifstream ifs{iname};
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    if (!ifs)
        error("Unable to open input file ", iname);
    int sum = 0, i;
    bool flag, minus_flag;
    string s;
    while (ifs)
    {
        flag = false;
        minus_flag = false;

        ifs >> s;

        if (s[0] == '-')
            minus_flag = true;

        for (int i = (minus_flag ? 1 : 0); i < s.length(); i++)
            if (!isdigit(s[i]))
            {
                flag = true;
                break;
            }

        if (!flag)
            sum += stoi(s);
    }
    cout << sum << endl;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
}
