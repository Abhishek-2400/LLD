// #include <bits/stdc++.h>
// using namespace std;

// class Coffee
// {
// public:
//     virtual float cost() = 0;
//     virtual ~Coffee()
//     {
//         cout << "~Coffee" << endl;
//     }
// };

// class SimpleCoffee : public Coffee
// {
// public:
//     float cost() { return 100.00; }
//     ~SimpleCoffee() { cout << "~SimpleCoffee" << endl; }
// };

// class CoffeeDecorator : public Coffee
// {
// protected:
//     Coffee *coffee;

// public:
//     CoffeeDecorator(Coffee *c) { coffee = c; }
//     virtual ~CoffeeDecorator()
//     {
//         cout << "~CoffeeDecorator" << endl;
//         delete coffee;
//     }
// };

// class MilkDecorator : public CoffeeDecorator
// {
// public:
//     MilkDecorator(Coffee *c) : CoffeeDecorator(c) {}
//     ~MilkDecorator() { cout << "~MilkDecorator" << endl; }
//     float cost() { return 20.00 + coffee->cost(); }
// };

// class SugarDecorator : public CoffeeDecorator
// {
// public:
//     SugarDecorator(Coffee *c) : CoffeeDecorator(c) {}
//     ~SugarDecorator() { cout << "~SugarDecorator" << endl; }
//     float cost() { return 30.00 + coffee->cost(); }
// };

// class CreamDecorator : public CoffeeDecorator
// {
// public:
//     CreamDecorator(Coffee *c) : CoffeeDecorator(c) {}
//     ~CreamDecorator() { cout << "~CreamDecorator" << endl; }
//     float cost() { return 40.00 + coffee->cost(); }
// };

// int main()
// {
//     Coffee *coffee = new SimpleCoffee();
//     coffee = new CreamDecorator(coffee);
//     coffee = new SugarDecorator(coffee);
//     coffee = new MilkDecorator(coffee);

//     cout << coffee->cost() << endl;
//     delete coffee;
// }

output of destrucotr call :

    ~MilkDecorator ~CoffeeDecorator        ← delete coffee triggers sugar chain... ~SugarDecorator ~CoffeeDecorator      ← delete coffee triggers cream chain... ~CreamDecorator ~CoffeeDecorator    ← delete coffee triggers simple chain... ~SimpleCoffee ~Coffee           ← simple's base ~Coffee             ← cream's base ~Coffee               ← sugar's base ~Coffee                 ← milk's base

    // #include <bits/stdc++.h>
    // using namespace std;

    // class Coffee
    // {
    // public:
    //     virtual float cost() = 0;
    //     virtual ~Coffee() = default;
    // };

    // class SimpleCoffee : public Coffee
    // {
    // public:
    //     float cost() override
    //     {
    //         return 100.0;
    //     }
    // };

    // class CoffeeDecorator : public Coffee
    // {
    // protected:
    //     unique_ptr<Coffee> coffee;

    // public:
    //     CoffeeDecorator(unique_ptr<Coffee> c)
    //         : coffee(move(c))
    //     {
    //     }

    //     virtual ~CoffeeDecorator() = default;
    // };

    // class MilkDecorator : public CoffeeDecorator
    // {
    // public:
    //     MilkDecorator(unique_ptr<Coffee> c)
    //         : CoffeeDecorator(move(c))
    //     {
    //     }

    //     float cost() override
    //     {
    //         return 20.0 + coffee->cost();
    //     }
    // };

    // class SugarDecorator : public CoffeeDecorator
    // {
    // public:
    //     SugarDecorator(unique_ptr<Coffee> c)
    //         : CoffeeDecorator(move(c))
    //     {
    //     }

    //     float cost() override
    //     {
    //         return 30.0 + coffee->cost();
    //     }
    // };

    // class CreamDecorator : public CoffeeDecorator
    // {
    // public:
    //     CreamDecorator(unique_ptr<Coffee> c)
    //         : CoffeeDecorator(move(c))
    //     {
    //     }

    //     float cost() override
    //     {
    //         return 40.0 + coffee->cost();
    //     }
    // };

    // int main()
    // {
    //     unique_ptr<Coffee> coffee = make_unique<SimpleCoffee>();

    //     coffee = make_unique<CreamDecorator>(move(coffee));
    //     coffee = make_unique<SugarDecorator>(move(coffee));
    //     coffee = make_unique<MilkDecorator>(move(coffee));

    //     cout << "Cost = " << coffee->cost() << endl;

    //     return 0;
    // }