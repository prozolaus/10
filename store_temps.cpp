#include "std_lib_facilities.h"

struct Reading
{
    int hour;
    double temperature;
    char grad;
};

double random(double min, double max)
{
    double d = (double)(rand())/RAND_MAX*(max - min) + min;
    int i = d*10;
    return (double)i/10;
}

int main()
{
    const int count = 24;
    vector<Reading> temps;
    srand(1000);
    char gr;
    for (int i = 0, sym, min, max; i < count; i++)
    {
        sym = randint(1,2);
        min = (sym==1) ? 50 : 10;
        max = (sym==1) ? 72 : 22;
        gr = (sym==1) ? 'f' : 'c';
        temps.push_back(Reading{i+1, random(min,max), gr});
    }
        
    string oname = "raw_temps.txt";
    ofstream ost{oname};
    if (!ost)
        error("Imposible opening output file ", oname);

    for (int i = 0; i < temps.size(); i++)
    {
        ost << '(' << temps[i].hour << ',' << temps[i].temperature << temps[i].grad << ")\n";
    }
    
}