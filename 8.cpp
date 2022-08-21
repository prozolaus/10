#include "std_lib_facilities.h"

int main()
{
    string name1 = "input.txt";
    ifstream ist1{name1};
    if (!ist1)
        error("Unable to open input file ", name1);

    string name2 = "output.txt";
    ifstream ist2{name2};
    if (!ist2)
        error("Unable to open input file ", name2);

    string oname = "8_output.txt";
    ofstream ost{oname};
    if (!ost)
        error("Unable to open outnput file ", oname);

    char ch;
    while (ist1.get(ch))
        ost << ch;
    ost << endl;
    while (ist2.get(ch))
        ost << ch;
}