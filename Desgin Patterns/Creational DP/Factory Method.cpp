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
    virtual unique_ptr<Vehicle> createVehicle(string) = 0;
    virtual ~VehicleFactory() = default;
};

class HondaFactory : public VehicleFactory
{

public:
    unique_ptr<Vehicle> createVehicle(string type)
    {
        if (type == "hondaCity")
            return make_unique<HondaCity>();
        else if (type == "hondaCreta")
            return make_unique<HondaCreta>();
        else
            return nullptr;
    }
};

class ToyotaFactory : public VehicleFactory
{

public:
    unique_ptr<Vehicle> createVehicle(string type)
    {

        if (type == "toyotaCrema")
            return make_unique<ToyotaCrema>();
        else
            return nullptr;
    }
};

int main()
{
    unique_ptr<VehicleFactory> vehicleFactory = make_unique<HondaFactory>();
    unique_ptr<Vehicle> v = vehicleFactory->createVehicle("hondaCreta");
    v->start();

    return 0;
}
