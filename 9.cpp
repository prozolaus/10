#include "std_lib_facilities.h"

int main()
{
    string name1 = "9_input1.txt";
    ifstream ist1{name1};
    if (!ist1)
        error("Unable to open input file ", name1);

    string name2 = "9_input2.txt";
    ifstream ist2{name2};
    if (!ist2)
        error("Unable to open input file ", name2);

    string oname = "9_output.txt";
    ofstream ost{oname};
    if (!ost)
        error("Unable to open outnput file ", oname);

    string s1, s2;
    bool b1 = false, b2 = false;
    ist1 >> s1;
    ist2 >> s2;
    if (s1 == "" && s2 == "")
        error("At least one of files is empty!");

    while (true)
    {
        if (s1 <= s2)
        {
            ost << s1 << endl;
            if (ist1.eof())
            {
                b1 = true;
                break;
            }
            else
                ist1 >> s1;
        }
        else
        {
            ost << s2 << endl;
            if (ist2.eof())
            {
                b2 = true;
                break;
            }
            else
                ist2 >> s2;
        }
    }
    if (b1)
    {
        ost << s2 << endl;
        while (ist2 >> s2)
            ost << s2 << endl;
    }
    if (b2)
    {
        ost << s1 << endl;
        while (ist1 >> s1)
            ost << s1 << endl;
    }
}