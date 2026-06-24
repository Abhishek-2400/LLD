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
    virtual unique_ptr<MainDish> prepareMainCourse() = 0;
    virtual unique_ptr<SideDish> prepareSideCourse() = 0;
    virtual unique_ptr<Drinks> prepareDrinks() = 0;
    virtual ~FoodFactory() = default;
};

class VegFoodFactory : public FoodFactory
{
public:
    unique_ptr<MainDish> prepareMainCourse() override
    {
        return make_unique<VegBurger>();
    }

    unique_ptr<SideDish> prepareSideCourse() override
    {
        return make_unique<VegPuff>();
    }

    unique_ptr<Drinks> prepareDrinks() override
    {
        return make_unique<OatsMilk>();
    }
};

class NonVegFoodFactory : public FoodFactory
{
public:
    unique_ptr<MainDish> prepareMainCourse() override
    {
        return make_unique<ChickenBurger>();
    }

    unique_ptr<SideDish> prepareSideCourse() override
    {
        return make_unique<FrenchFries>();
    }

    unique_ptr<Drinks> prepareDrinks() override
    {
        return make_unique<ColdDrink>();
    }
};

int main()
{
    unique_ptr<FoodFactory> foodFactory = make_unique<VegFoodFactory>();
    foodFactory->prepareMainCourse()->prepare();
    foodFactory->prepareSideCourse()->prepare();
    foodFactory->prepareDrinks()->prepare();

    return 0;
}