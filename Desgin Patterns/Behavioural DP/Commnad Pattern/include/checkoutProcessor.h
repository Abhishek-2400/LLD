#pragma once
#include <bits/stdc++.h>
#include "command.h"
using namespace std;

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
