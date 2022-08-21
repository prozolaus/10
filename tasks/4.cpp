#include "std_lib_facilities.h"

int main()
{
    string oname = "test";
    ofstream ost{oname};
    if (!ost)
        error("Imposible opening output file ", oname);
    ost << "hello\n";

    string iname = oname;
    ifstream ist{iname};
    if (!ist)
        error("Imposible opening input file ", iname);
    string i;
    ist >> i;
    cout << i << endl;
}