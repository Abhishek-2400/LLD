#include <bits/stdc++.h>
using namespace std;

class ATM;

class ATMState
{
protected:
    ATM *a;

public:
    virtual void insert() = 0;
    virtual void enterPin() = 0;
    virtual void withdraw() = 0;
    virtual ~ATMState() = default;
};

class IdleState : public ATMState
{
public:
    IdleState(ATM *);
    void insert() override;
    void enterPin() override;
    void withdraw() override;
};

class CardInsertedState : public ATMState
{
public:
    CardInsertedState(ATM *);
    void insert() override;
    void enterPin() override;
    void withdraw() override;
};

class PinVerifiedState : public ATMState
{
public:
    PinVerifiedState(ATM *);
    void insert() override;
    void enterPin() override;
    void withdraw() override;
};

class ATM
{
    unique_ptr<ATMState> atmState = make_unique<IdleState>(this);

public:
    void setState(unique_ptr<ATMState> a)
    {
        atmState = move(a);
    }

    void insertCard()
    {
        atmState->insert();
    }
    void enterPin()
    {
        atmState->enterPin();
    }

    void withdraw()
    {
        atmState->withdraw();
    }
};

IdleState::IdleState(ATM *atm)
{
    a = atm;
}
void IdleState::insert()
{
    cout << "Card Inserted" << endl;
    // direct to CARD inserted state
    a->setState(make_unique<CardInsertedState>(a));
}
void IdleState::enterPin()
{
    cout << "Not Allowed" << endl;
}

void IdleState::withdraw()
{
    cout << "Not allowed" << endl;
}

CardInsertedState::CardInsertedState(ATM *a)
{
    this->a = a;
}
void CardInsertedState::insert()
{
    cout << "Card already Inserted" << endl;
}
void CardInsertedState::enterPin()
{
    cout << "Please enter the pin" << endl;
    // direct to next state
    a->setState(make_unique<PinVerifiedState>(a));
}

void CardInsertedState::withdraw()
{
    cout << "Not allowed" << endl;
}

PinVerifiedState::PinVerifiedState(ATM *a)
{
    this->a = a;
}
void PinVerifiedState::insert()
{
    cout << "Card already Inserted" << endl;
}
void PinVerifiedState::enterPin()
{
    cout << "Pin already entered" << endl;
}

void PinVerifiedState::withdraw()
{
    cout << "Withrawl in process" << endl;
    // next state
    a->setState(make_unique<IdleState>(a));
}

int main()
{
    ATM a;
    a.withdraw();   // no
    a.insertCard(); // card entered
    a.withdraw();   // no
    a.enterPin();   // pin verified
    a.withdraw();   // idle state

    return 0;
}