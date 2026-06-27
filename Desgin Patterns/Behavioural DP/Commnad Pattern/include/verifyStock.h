#pragma once
#include <bits/stdc++.h>
#include "invenotryService.h"
#include "command.h"
using namespace std;

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
