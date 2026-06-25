#include <bits/stdc++.h>
using namespace std;

class Observer
{
public:
    virtual void update(string) = 0;
    virtual ~Observer() = default;
};

class Subscriber : public Observer
{
    string name;

public:
    Subscriber(string name)
    {
        this->name = name;
    }
    void update(string data)
    {
        cout << name << " " << "received" << " " << data << endl;
    }
};

class Youtube
{
    vector<weak_ptr<Observer>> v;
    void notifyAll(string data)
    {
        for (auto &wp : v)
        {
            if (auto sp = wp.lock())
                sp->update(data);
        }
    }

public:
    // A weak_ptr can be constructed from a shared_ptr, but to get a shared_ptr back you must use lock().
    void add(shared_ptr<Observer> &s)
    {
        v.push_back(s);
    }
    void upload(string data)
    {
        cout << "data uploaded successfullly" << endl;
        notifyAll(data);
    }
};

int main()
{
    shared_ptr<Observer> ob1 = make_shared<Subscriber>("ram");
    shared_ptr<Observer> ob2 = make_shared<Subscriber>("shyam");

    Youtube yt;
    yt.add(ob1);
    yt.add(ob2);

    yt.upload("Design Patterns Video");

    return 0;
}

// Typical Observer:

// vector<Observer*> observers;

// or

// vector<weak_ptr<Observer>>

// because:

// Subscriber subscribes to Youtube
// Subscriber is not owned by Youtube

// Subscribers exist independently
// Youtube just keeps references to them