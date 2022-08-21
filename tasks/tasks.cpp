#include "std_lib_facilities.h"

struct Point
{
    int x;
    int y;
};

istream &operator>>(istream &is, Point &p)
{
    char ch1, ch2, ch3;
    int x, y;
    is >> ch1 >> x >> ch2 >> y >> ch3;
    if (!is || ch1 != '(' || ch2 != ',' || ch3 != ')')
        error("Input was wrong!");
    p.x = x;
    p.y = y;
    return is;
}

ostream &operator<<(ostream &os, Point &p)
{
    return os << '(' << p.x << ',' << p.y << ')' << endl;
}

int main()
{
    const int count = 3;
    vector<Point> original_points;
    cout << "Input " << count << " pairs of coordinates in the format (x,y), where x and y are integers:\n";
    for (int i = 0; i < count; i++)
    {
        Point p;
        cin >> p;
        original_points.push_back(p);
    }

    string filename = "mydata.txt";
    ofstream ost{filename};
    if (!ost)
        error("Unable to open output file", filename);
    for (Point p : original_points)
        ost << p;
    ost.close();

    ifstream ist{filename};
    if (!ist)
        error("Unable to open input file", filename);

    vector<Point> processed_points;
    for (int i = 0; i < count; i++)
    {
        Point p;
        ist >> p;
        processed_points.push_back(p);
    }

    cout << "original_points:\n";
    for (Point p : original_points)
        cout << p;
    cout << "processed_points:\n";
    for (Point p : processed_points)
        cout << p;

    for (int i = 0; i < count; i++)
        if (original_points[i].x != processed_points[i].x || original_points[i].y != processed_points[i].y)
            error("Something went wrong!");
}