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
    // raw pointer is not automatically nulled when memory is freed. It still holds the old address, it doesn't know the memory is gone.

    // cpp
    // Team* raw = new Team();
    // delete raw;  // memory freed

    // if (raw == nullptr)  // FALSE — raw still has the old address
    //     cout << "gone";

    // raw->getEmpCount();  // UB — crash or garbage, no warning
    // Only if you manually do raw = nullptr after delete does the null check work. But in complex code with multiple raw observers pointing to same object — you'd have to null every single one manually. That's error prone.

    // weak_ptr does this automatically. When the shared_ptr owner dies, all weak_ptrs to that object know it's gone via lock() returning null. No manual tracking needed.

    // A weak_ptr can be constructed from a shared_ptr, but to get a shared_ptr back you must use lock().

    // weak_ptr needs a shared_ptr owner — you can't create weak_ptr from unique_ptr.
    // weak_ptr must be locked before use — you're calling v->update(data) directly on weak_ptr, that won't compile. Need to lock() first:

    //     wp.lock() tries to get a shared_ptr from the weak_ptr.

    // If object is alive → returns a valid shared_ptr, assigns to sp, condition is true, calls update
    // If object is destroyed → returns nullptr, condition is false, skips
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