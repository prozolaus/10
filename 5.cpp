#include "std_lib_facilities.h"

struct Reading
{
    int day;
    int hour;
    double temperature;
};

const int not_a_reading = -7777;
const int not_a_month = -1;
constexpr int min_temp = -200;
constexpr int max_temp = 200;

struct Day
{
    vector<double> hour{vector<double>(24, not_a_reading)};
};

struct Month
{
    int month{not_a_month};
    vector<Day> day{32};
};

struct Year
{
    int year;
    vector<Month> month{12};
};

void end_of_loop(istream &is, char term, const string &message)
{
    if (is.fail())
    {
        is.clear();
        char ch;
        if (is >> ch && ch == term)
            return;
        error(message);
    }
}

bool is_valid(Reading &r)
{
    if (r.day < 1 || r.day > 31)
        return false;
    if (r.hour < 0 || r.hour > 23)
        return false;
    if (r.temperature < min_temp || r.temperature > max_temp)
        return false;
    return true;
}

int month_to_int(string mm)
{
    vector<string> months{"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
    for (int i = 0; i < months.size(); i++)
        if (mm == months[i])
            return i;
    return not_a_month;
}

string int_to_month(int mm)
{
    if (mm < 0 && mm > 11)
        error("Wrong month!");
    vector<string> months{"January", "February", "March", "April", "May", "June", "July",
                          "August", "September", "October", "November", "December"};
    return months[mm];
}

istream &operator>>(istream &is, Reading &r)
{
    char ch1;
    if (is >> ch1 && ch1 != '(')
    {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    char ch2;
    int d;
    int h;
    double t;
    is >> d >> h >> t >> ch2;
    if (!is || ch2 != ')')
        error("Bad record!");
    r.day = d;
    r.hour = h;
    r.temperature = t;
    return is;
}

istream &operator>>(istream &is, Month &m)
{
    char ch = 0;
    if (is >> ch && ch != '{')
    {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }
    string month_marker;
    string mm;
    is >> month_marker >> mm;
    if (!is || month_marker != "month")
        error("Wrong begin of month!");
    m.month = month_to_int(mm);

    Reading r;
    int duplicates = 0;
    int invalids = 0;
    for (Reading r; is >> r;)
    {
        if (is_valid(r))
        {
            if (m.day[r.day].hour[r.hour] != not_a_reading)
                duplicates++;
            m.day[r.day].hour[r.hour] = r.temperature;
        }
        else
            invalids++;
    }
    if (invalids)
        error("Wrong data in Month, in total: ", invalids);
    if (duplicates)
        error("Repeated readings, in total: ", duplicates);
    end_of_loop(is, '}', "Wrong end of Month!");
    return is;
}

istream &operator>>(istream &is, Year &y)
{
    char ch = 0;
    is >> ch;
    if (ch != '{')
    {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string year_marker;
    int yy;
    is >> year_marker >> yy;
    if (!is || year_marker != "year")
        error("Wrong begin of year!");
    y.year = yy;

    while (true)
    {
        Month m;
        if (!(is >> m))
            break;
        y.month[m.month] = m;
    }

    end_of_loop(is, '}', "Wrong end of Year!");
    return is;
}

void print_year(ostream &os, const Year &y)
{
    string year_marker;
    os << "Year " << y.year << ":\n";
    for (int i = 0; i < y.month.size(); i++)
    {
        Month m = y.month[i];
        if (m.month != not_a_month)
        {
            os << "\t" << int_to_month(m.month) << ":";
            vector<Day> d = m.day;
            bool flag;
            for (int i = 1; i < d.size(); i++)
            {
                flag = false;
                for (int j = 0; j < 24; j++)
                    if (d[i].hour[j] != not_a_reading)
                    {
                        if (!flag)
                        {
                            os << "\n\t\tDay " << i << ":";
                            flag = true;
                        }
                        os << "\n\t\t\thour: " << j << ", temperature: " << d[i].hour[j];
                    }
            }
            os << endl;
        }
    }
    os << endl;
}

int main()
{
    string iname = "input.txt";
    ifstream ifs{iname};
    if (!ifs)
        error("Unable to open input file ", iname);

    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    string oname = "output.txt";
    ofstream ofs{oname};
    if (!ofs)
        error("Unable to open output file ", oname);

    vector<Year> ys;
    while (true)
    {
        Year y;
        if (!(ifs >> y))
            break;
        ys.push_back(y);
    }
    cout << "Read " << ys.size() << " year records\n";

    for (Year &y : ys)
        print_year(ofs, y);
}