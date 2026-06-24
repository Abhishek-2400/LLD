#include <bits/stdc++.h>
using namespace std;

class Car
{
public:
    string name;
    string engine;
    void show()
    {
        cout << name << " " << engine << endl;
    }
};

class CarBuilder
{
    Car c;

public:
    CarBuilder &setName(string name)
    {
        c.name = name;
        return *this;
    }

    CarBuilder &setEngine(string engine)
    {
        c.engine = engine;
        return *this;
    }

    Car Build()
    {
        return c;
    }
};

int main()
{
    CarBuilder carbuilder;
    Car c = carbuilder.setName("honda").setEngine("125cc").Build();
    c.show();
    return 0;
}