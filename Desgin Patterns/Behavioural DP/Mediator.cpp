#include <bits/stdc++.h>
using namespace std;

class Member;

// start from interface declaration first to avoid unnecesaary frwd declarations
class Mediator
{
public:
    virtual void Register(Member *) = 0;
    virtual void SendMessage(Member *, string) = 0;
    virtual ~Mediator() = default;
};

class Member
{
    string name;
    weak_ptr<Mediator> mediator;

public:
    Member(string name, shared_ptr<Mediator> m)
    {
        this->name = name;
        mediator = m;
    }
    void sendMessage(string data)
    {
        if (auto sp = mediator.lock())
            sp->SendMessage(this, data);
    }

    void receiveMessage(string data)
    {
        cout << name << " " << "Received " << data << endl;
    }
};

class AuctionHouse : public Mediator
{
    vector<Member *> v;

protected:
    void SendMessage(Member *m, string data)
    {
        for (auto &it : v)
        {
            if (m != it)
                it->receiveMessage(data);
        }
    }

public:
    void Register(Member *m)
    {
        v.push_back(m);
    }
};

class ExtendedAuction : public AuctionHouse
{
    int timer;

protected:
    // this is overrirding only Since the function was originally virtual in Mediator, it remains virtual all the way down
    // and virtual in parent + same name+parsms in child is overriding
    void SendMessage(Member *m, string data)
    {
        if (time(nullptr) > timer)
        {
            cout << "Bid time over" << endl;
            return;
        }

        AuctionHouse::SendMessage(m, data);
    }

public:
    ExtendedAuction(int time)
    {
        timer = time;
    }
};

int main()
{
    shared_ptr<Mediator> mediator = make_shared<ExtendedAuction>(time(nullptr) + 5);

    Member m1("Ram", mediator);
    Member m2("Sham", mediator);
    Member m3("Palm", mediator);

    mediator->Register(&m1);
    mediator->Register(&m2);
    mediator->Register(&m3);

    m1.sendMessage("Hi all");

    this_thread::sleep_for(chrono::seconds(6));

    m2.sendMessage("HI");

    return 0;
}