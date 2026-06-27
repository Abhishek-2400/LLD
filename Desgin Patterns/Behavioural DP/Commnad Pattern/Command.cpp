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
    // checkout processor also owns thse cmds as it might excute them in bckg even after main is gone
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

// Does the class have only declarations (pure virtual / interface)?
// → .h only, goes in include/

// Does the class have implementation?
// → .h (declaration) in include/ + .cpp (definition) in src/

// What goes in .h vs .cpp:

// VerifyStock.h:

// cpp
// #pragma once
// #include "Command.h"
// #include "InventoryService.h"

// class VerifyStock : public Command {
//     InventoryService* inventory;
// public:
//     VerifyStock(InventoryService* i);
//     bool execute() override;
//     void undo() override;
// };
// VerifyStock.cpp:

// cpp
// #include "VerifyStock.h"

// VerifyStock::VerifyStock(InventoryService* i) : inventory(i) {}

// bool VerifyStock::execute() {
//     inventory->reserveStock();
//     return true;
// }

// void VerifyStock::undo() {
//     inventory->releaseStock();
// }
// test_VerifyStock.cpp:

// cpp
// #include "VerifyStock.h"
// #include <cassert>

// void test_should_reserve_stock() {
//     InventoryService inventory;
//     VerifyStock cmd(&inventory);
//     assert(cmd.execute() == true);
// }

// int main() {
//     test_should_reserve_stock();
// }
// Simple decision rule to remember:

// Header (.h) = what the class does
// Source (.cpp) = how it does it
// Test (.cpp in test/) = proof it does it correctly
