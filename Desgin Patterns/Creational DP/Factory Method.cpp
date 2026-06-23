#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
public:
    virtual void start() = 0;
    virtual ~Vehicle() = default;
};

class HondaCreta : public Vehicle
{
public:
    void start()
    {
        cout << "Running Honda Ceta" << endl;
    }
};

class HondaCity : public Vehicle
{
public:
    void start()
    {
        cout << "Running Honda City" << endl;
    }
};

class ToyotaCrema : public Vehicle
{
public:
    void start()
    {
        cout << "Running Toyotacrema" << endl;
    }
};

class VehicleFactory
{
public:
    virtual Vehicle *createVehicle(string) = 0;
    virtual ~VehicleFactory() = default;
};

class HondaFactory : public VehicleFactory
{

public:
    Vehicle *createVehicle(string type)
    {
        if (type == "hondaCity")
            return new HondaCity();
        else if (type == "hondaCreta")
            return new HondaCreta();
        else
            return nullptr;
    }
};

class ToyotaFactory : public VehicleFactory
{

public:
    Vehicle *createVehicle(string type)
    {

        if (type == "toyotaCrema")
            return new ToyotaCrema();
        else
            return nullptr;
    }
};

int main()
{
    VehicleFactory *vehicleFactory = new HondaFactory();
    Vehicle *v = vehicleFactory->createVehicle("hondaCreta");
    v->start();

    return 0;
}
