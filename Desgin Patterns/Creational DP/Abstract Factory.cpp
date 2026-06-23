#include <bits/stdc++.h>
using namespace std;

class MainDish
{
public:
    virtual void prepare() = 0;
    virtual ~MainDish() = default;
};

class SideDish
{
public:
    virtual void prepare() = 0;
    virtual ~SideDish() = default;
};

class Drinks
{
public:
    virtual void prepare() = 0;
    virtual ~Drinks() = default;
};

class ChickenBurger : public MainDish
{
public:
    void prepare() override
    {
        cout << "Preparing Chicken  Burger" << endl;
    }
};

class VegBurger : public MainDish
{
public:
    void prepare() override
    {
        cout << "Preparing Veg Burger" << endl;
    }
};

class FrenchFries : public SideDish
{
public:
    void prepare() override
    {
        cout << "Preparing French Fries" << endl;
    }
};

class VegPuff : public SideDish
{
public:
    void prepare() override
    {
        cout << "Preparing Veg Puff" << endl;
    }
};

class ColdDrink : public Drinks
{
public:
    void prepare() override
    {
        cout << "Preparing Cold Drink" << endl;
    }
};

class OatsMilk : public Drinks
{
public:
    void prepare() override
    {
        cout << "Preparing Oats Milk" << endl;
    }
};

class FoodFactory
{
public:
    virtual MainDish *prepareMainCourse() = 0;
    virtual SideDish *prepareSideCourse() = 0;
    virtual Drinks *prepareDrinks() = 0;
    virtual ~FoodFactory() = default;
};

class VegFoodFactory : public FoodFactory
{
public:
    MainDish *prepareMainCourse() override
    {
        return new VegBurger();
    }

    SideDish *prepareSideCourse() override
    {
        return new VegPuff();
    }

    Drinks *prepareDrinks() override
    {
        return new OatsMilk();
    }
};

class NonVegFoodFactory : public FoodFactory
{
public:
    MainDish *prepareMainCourse() override
    {
        return new ChickenBurger();
    }

    SideDish *prepareSideCourse() override
    {
        return new FrenchFries();
    }

    Drinks *prepareDrinks() override
    {
        return new ColdDrink();
    }
};

int main()
{
    FoodFactory *foodFactory = new VegFoodFactory();
    foodFactory->prepareMainCourse()->prepare();
    foodFactory->prepareSideCourse()->prepare();
    foodFactory->prepareDrinks()->prepare();

    return 0;
}