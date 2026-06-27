#pragma once
#include <bits/stdc++.h>
#include "command.h"
#include "emailService.h"
using namespace std;

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