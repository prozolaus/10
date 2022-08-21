#include "std_lib_facilities.h"

void fill_vector(istream &ist, vector<int> &v, char terminator)
{
    for (int i; ist >> i;)
        v.push_back(i);

    if (ist.eof())
        return;

    ist.exceptions(ist.exceptions() | ios::badbit);

    ist.clear();

    char c;
    ist >> c;

    if (c != terminator)
    {
        ist.unget();
        ist.clear(ios_base::failbit);
    }
}

int main()
{
    string iname = "input2";
    ifstream ist{iname};
    if (!ist)
        error("Imposible opening input file ", iname);

    vector<int> v;
    char c = '*';
    fill_vector(ist, v, c);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ' ';
    }
    cout << endl;
    cout << ist.eof() << endl;
    cout << ist.fail() << endl;
    cout << ist.good() << endl;
}