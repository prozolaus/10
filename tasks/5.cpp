#include "std_lib_facilities.h"

struct Reading
{
    int hour;
    double temperature;
};

int main()
{
    string iname = "input";
    ifstream ist{iname};
    if (!ist)
        error("Imposible opening input file ", iname);

    string oname = "output";
    ofstream ost{oname};
    if (!ost)
        error("Imposible opening output file ", oname);

    vector<Reading> temps;
    int hour;
    double temperature;
    while (ist >> hour >> temperature)
    {
        if (hour < 0 || hour > 23)
            error("Incorrect time!");
        temps.push_back(Reading{hour, temperature});
    }
    for (int i = 0; i < temps.size(); i++)
    {
        ost << '(' << temps[i].hour << ',' << temps[i].temperature << ")\n";
    }
    
}