#include <bits/stdc++.h>
using namespace std;

enum Category
{
    TWO_WHEELER,
    FOUR_WHEELER,
    OTHERS
};

class Vehicle
{
    string name;
    string number;
    Category category;

public:
    Vehicle() {} // default constructor
    Vehicle(string n, string num, Category cat)
    {
        name = n;
        number = num;
        category = cat;
    }

    Category getCategory()
    {
        return category;
    }

    string getNumber()
    {
        return number;
    }
};

class Slot
{
    int id;
    Category category;
    Vehicle *vehicle;
    bool isOccupied;

public:
    Slot() {} // default constructor
    Slot(int id, Category cat) : vehicle()
    {
        this->id = id;
        category = cat;
        isOccupied = false;
    }

    bool isAvailable()
    {
        return !isOccupied;
    }

    Category getCategory()
    {
        return category;
    }

    void parkVehicle(Vehicle &v)
    {
        if (isOccupied)
        {
            cout << "Slot is already occupied" << endl;
            return;
        }
        if (v.getCategory() != category)
        {
            cout << "Vehicle category does not match slot category" << endl;
            return;
        }

        vehicle = &v;
        isOccupied = true;
    }

    void unparkVehicle()
    {
        if (!isOccupied)
        {
            cout << "Slot is already empty" << endl;
            return;
        }

        vehicle = nullptr; // reset the vehicle
        isOccupied = false;
    }
};

// payment method abstraction
class PaymentMethod
{

public:
    virtual void pay(double) = 0;
    virtual ~PaymentMethod() = default;
};

class CashPayment : public PaymentMethod
{
    void pay(double amount) override
    {
        cout << "Paying with cash" << endl;
    }
};

class UPIPayment : public PaymentMethod
{
    void pay(double amount) override
    {
        cout << "Paying with UPI" << endl;
    }
};

class RazorPay : public PaymentMethod
{
public:
    void pay(double amount) override
    {
        cout << "Paying with RazorPay" << endl;
    }
};

// pricing strategy abstraction
class PricingStrategy
{
public:
    virtual double calculatePrice(Vehicle) = 0;
    virtual ~PricingStrategy() = default;
};

class TwoWheelerPricingStrategy : public PricingStrategy
{
public:
    double calculatePrice(Vehicle v) override
    {
        cout << "Calculating price for two wheeler" << endl;
    }
};

class FourWheelerPricingStrategy : public PricingStrategy
{
public:
    double calculatePrice(Vehicle v) override
    {
        cout << "Calculating price for four wheeler" << endl;
    }
};

class OthersPricingStrategy : public PricingStrategy
{
public:
    double calculatePrice(Vehicle v) override
    {
        cout << "Calculating price for other category vehicle" << endl;
    }
};

class PricingStrategyFactory
{
    using creator = function<unique_ptr<PricingStrategy>()>;
    static unordered_map<Category, creator> registry;

public:
    static void registery(Category type, creator fn)
    {
        registry[type] = fn;
    }

    static unique_ptr<PricingStrategy> getPricingStrategy(Category category)
    {
        if (registry.find(category) == registry.end())
        {
            throw invalid_argument("Undefined catoegry not in registry unavle to make object");
        }

        return registry[category]();
    }
};

class PaymentFactory
{

    using creator = function<unique_ptr<PaymentMethod>()>;
    static unordered_map<string, creator> registry;

public:
    static void registery(string type, creator fn)
    {
        registry[type] = fn;
    }
    static unique_ptr<PaymentMethod> getPayemntMetho(string &type)
    {
        if (registry.find(type) == registry.end())
            throw invalid_argument("invaid payment type");
        return registry[type]();
    }
};

class CheckOutCounter
{
    unordered_map<string, Slot *> vehicleToSlot; // map to vehicle->slot for easy lookup when unparking

public:
    void regisTerVehicleToSlot(Vehicle &v, Slot *s)
    {
        vehicleToSlot[v.getNumber()] = s;
    }
    void unParkVehicle(Vehicle &v)
    {
        if (vehicleToSlot.find(v.getNumber()) == vehicleToSlot.end())
        {
            cout << "Vehicle not found in the parking lot" << endl;
            return;
        }

        vehicleToSlot[v.getNumber()]->unparkVehicle();
        vehicleToSlot.erase(v.getNumber());
    }
    double calculatePrice(Vehicle &v)
    {
        unique_ptr<PricingStrategy> pricingStrategy = PricingStrategyFactory::getPricingStrategy(v.getCategory());
        double price = pricingStrategy.get()->calculatePrice(v);
        cout << "Price for vehicle " << v.getNumber() << " is " << price << endl;
        return price;
    }

    void Pay(double amt)
    {
        string mode;
        cin >> mode;

        unique_ptr<PaymentMethod> paymentMethod = PaymentFactory::getPayemntMetho(mode);

        paymentMethod.get()->pay(amt);

        // clean payment method after payment
        paymentMethod = nullptr;
    }
};

class ParkingLot
{
    vector<Slot *> slots;
    CheckOutCounter checkOutCounter;

public:
    void addSlot(Slot *s)
    {
        slots.push_back(s);
    }

    void ParkVehicle(Vehicle &v)
    {
        int n = slots.size();
        bool parked = false;
        for (auto &slot : slots)
        {
            if (slot->isAvailable() && slot->getCategory() == v.getCategory())
            {
                slot->parkVehicle(v);
                checkOutCounter.regisTerVehicleToSlot(v, slot);
                cout << "Vehicle parked successfully" << endl;
                parked = true;
                break;
            }
        }
        if (!parked)
        {
            cout << "No available slot for this vehicle" << endl;
        }
    }

    void checkoutVehicle(Vehicle &v)
    {
        checkOutCounter.unParkVehicle(v);
        double amt = checkOutCounter.calculatePrice(v);
        checkOutCounter.Pay(amt);
    }
};

int main()
{

    Slot s1(1, TWO_WHEELER);
    Slot s2(2, FOUR_WHEELER);
    Slot s3(3, FOUR_WHEELER);
    Slot s4(4, OTHERS);
    Slot s5(5, TWO_WHEELER);

    PricingStrategyFactory::registery(TWO_WHEELER, []()
                                      { return make_unique<TwoWheelerPricingStrategy>(); });
    PricingStrategyFactory::registery(FOUR_WHEELER, []()
                                      { return make_unique<FourWheelerPricingStrategy>(); });
    PricingStrategyFactory::registery(OTHERS, []()
                                      { return make_unique<OthersPricingStrategy>(); });

    PaymentFactory::registery("cash", []()
                              { return make_unique<CashPayment>(); });
    PaymentFactory::registery("upi", []()
                              { return make_unique<UPIPayment>(); });

    ParkingLot parkingLot;

    parkingLot.addSlot(&s1);
    parkingLot.addSlot(&s2);
    parkingLot.addSlot(&s3);
    parkingLot.addSlot(&s4);
    parkingLot.addSlot(&s5);

    Vehicle v1("Bike1", "123454", TWO_WHEELER);
    parkingLot.ParkVehicle(v1);

    Vehicle v2("Bike2", "123443", TWO_WHEELER);
    parkingLot.ParkVehicle(v2);

    Vehicle v3("Car", "5678", FOUR_WHEELER);
    parkingLot.ParkVehicle(v3);

    // checkout
    parkingLot.checkoutVehicle(v1);

    return 0;
}