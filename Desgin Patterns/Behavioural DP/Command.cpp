#include <bits/stdc++.h>
using namespace std;

class InventoryService
{
public:
    void reserveStock() { cout << "Reserving stock\n"; }
    void releaseStock() { cout << "Releasing stock\n"; }
};

class PaymentService
{
public:
    void charge() { cout << "Charging card\n"; }
    void refund() { cout << "Refunding payment\n"; }
};

class EmailService
{
public:
    void sendReceipt() { cout << "Sending receipt\n"; }
};

class Command
{
public:
    virtual bool execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class VerifyStock : public Command
{
    InventoryService *inventory;

public:
    VerifyStock(InventoryService *i) : inventory(i) {}

    bool execute() override
    {
        inventory->reserveStock();
        return true;
    }

    void undo() override
    {
        inventory->releaseStock();
    }
};

class ChargeCard : public Command
{
    PaymentService *payment;

public:
    ChargeCard(PaymentService *p) : payment(p) {}

    bool execute() override
    {
        payment->charge();

        // simulate failure if needed
        // return false;

        return true;
    }

    void undo() override
    {
        payment->refund();
    }
};

class SendReceipt : public Command
{
    EmailService *email;

public:
    SendReceipt(EmailService *e) : email(e) {}

    bool execute() override
    {
        email->sendReceipt();
        return true;
    }

    void undo() override
    {
        cout << "Receipt cannot be undone\n";
    }
};

class CheckoutProcessor
{
    vector<shared_ptr<Command>> commands;
    stack<shared_ptr<Command>> executed;

    void undoAll()
    {
        while (!executed.empty())
        {
            executed.top()->undo();
            executed.pop();
        }
    }

public:
    void addCommand(shared_ptr<Command> cmd)
    {
        commands.push_back(cmd);
    }

    void placeOrder()
    {
        for (auto &cmd : commands)
        {
            if (!cmd->execute())
            {
                undoAll();
                return;
            }

            executed.push(cmd);
        }

        while (!executed.empty())
            executed.pop();

        cout << "Order Successful\n";
    }
};

int main()
{
    InventoryService inventory;
    PaymentService payment;
    EmailService email;

    auto verify = make_shared<VerifyStock>(&inventory);
    auto charge = make_shared<ChargeCard>(&payment);
    auto receipt = make_shared<SendReceipt>(&email);

    CheckoutProcessor processor;

    processor.addCommand(verify);
    processor.addCommand(charge);
    processor.addCommand(receipt);

    processor.placeOrder();
}