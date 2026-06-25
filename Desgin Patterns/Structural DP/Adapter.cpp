#include <bits/stdc++.h>
using namespace std;

class PaymentProcessor
{
public:
    virtual void pay() = 0;
    virtual ~PaymentProcessor() = default;
};
class RazorPay
{
public:
    void makePayment()
    {
        cout << "Payming via Razorpay" << endl;
    }
};

class RazorPayAdapter : public PaymentProcessor
{
    RazorPay razorpay;

public:
    void pay()
    {
        razorpay.makePayment();
    }
};

int main()

{
    PaymentProcessor *paymentProcessor = new RazorPayAdapter();
    paymentProcessor->pay();

    delete paymentProcessor;
    return 0;
}