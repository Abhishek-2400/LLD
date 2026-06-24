#include <bits/stdc++.h>
using namespace std;

class Shape
{
public:
    virtual void draw() = 0;
    virtual Shape *clone() = 0;
    virtual void show() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
    string name;
    string *nikname;

public:
    Circle(string name, string nikname)
    {
        this->name = name;
        this->nikname = new string(nikname);
    }

    void draw()
    {
        cout << "drawing curcle" << endl;
    }

    Circle(const Circle &other)
    {
        name = other.name;
        nikname = new string(*other.nikname);
    }

    void show()
    {
        cout << name << " " << &name << endl;
        cout << *nikname << " " << nikname << endl;
    }

    Shape *clone()
    {
        return new Circle(*this);
    }
};

int main()
{
    Shape *shape = new Circle("ram", "abhishek");
    Shape *s1 = shape->clone();
    shape->show();
    s1->show();
    return 0;
}