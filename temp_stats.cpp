#include "std_lib_facilities.h"

struct Reading
{
    int hour;
    double temperature;
};

istream &operator>>(istream &is, Reading &r)
{
    is.exceptions(is.exceptions() | ios_base::badbit);
    char ch1, ch2, ch3, ch4;
    int x;
    double y;
    is >> ch1 >> x >> ch2 >> y >> ch3 >> ch4;
    if (is.eof())
        return is;
    if (is.fail() || ch1 != '(' || ch2 != ',' || !(ch3 == 'f' || ch3 == 'c') || ch4 != ')')
        error("Input was wrong!");
    r.hour = x;
    if (ch3 == 'c')
        r.temperature = y * 1.8 + 32;
    else 
        r.temperature = y;
    return is;
}

double average_temp(const vector<Reading> &temps)
{
    double av;
    for (Reading r : temps)
        av += r.temperature;
    av /= temps.size();
    return av;
}

double mediana(const vector<Reading> &temps)
{
    vector<double> v;

    for (Reading r : temps)
        v.push_back(r.temperature);

    sort(v.begin(), v.end());
    return v[v.size()/2];
}

double rounding(double &d, int signs)
{
    long s = pow(10, signs), temp, i;
    temp = d * s * 10;
    d *= s;
    i = (temp % 10 >= 5) ? d + 1 : d;
    d = (double)i / s;
    return d;
}

int main()
{
    string iname = "raw_temps.txt";
    ifstream ist{iname};
    if (!ist)
        error("Imposible opening output file ", iname);

    vector<Reading> temps;
    for (Reading r; ist >> r;)
        temps.push_back(r);
    
    double av = average_temp(temps);
    cout << "Average temp = " << rounding(av, 1) << endl;

    double median = mediana(temps);
    cout << "Median temp = " << rounding(median,1) << endl;
}