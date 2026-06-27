#pragma once
#include <bits/stdc++.h>
#include "command.h"
#include "paymentService.h"

using namespace std;

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