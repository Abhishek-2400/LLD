#pragma once
#include <bits/stdc++.h>
#include "command.h"
using namespace std;

class Command
{
public:
    virtual bool execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};
