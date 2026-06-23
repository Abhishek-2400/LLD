#include <bits/stdc++.h>
using namespace std;

class PaymentMethod
{
public:
    virtual void pay() = 0;
};

class UPI : public PaymentMethod
{
public:
    void pay()
    {
        cout << "Paying via upi" << endl;
    }
};

class PaymentFactory
{
    // using creates an alias (nickname) for a type.
    //  same as typedef , using ll = long long;

    // function is a wrapper that can store:
    //  Normal functions
    //  Lambdas

    using creator = function<PaymentMethod *()>;
    // inline static variables (introduced in C++17) allow a static data member to be defined directly inside the class.

    // Earlier : static int x;
    // was only a declaration, so we had to separately define it to allocate memory.

    //                         Now : inline static int x = 0;
    // is both declaration and definition, so memory is allocated right there and no separate definition is required.

    inline static unordered_map<string, creator> m;

public:
    static void registry(string type, creator c)
    {
        m[type] = c;
    }
    static PaymentMethod *getPaymentMethod(string type)
    {
        if (m.find(type) == m.end())
        {
            cout << "invalid payment method" << endl;
            return nullptr;
        }
        return m[type]();
    }
};

int main()
{
    // register all the payment methods
    PaymentFactory::registry("upi", []()
                             { return new UPI(); });

    PaymentMethod *paymentMethod = PaymentFactory::getPaymentMethod("upi");
    if (!paymentMethod)
        return -1;
    paymentMethod->pay();
    return 0;
}
