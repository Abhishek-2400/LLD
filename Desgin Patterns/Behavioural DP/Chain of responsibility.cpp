#include <bits/stdc++.h>
using namespace std;

class Handler
{
protected:
    Handler *next = nullptr;

public:
    void setNext(Handler *handler)
    {
        next = handler;
    }
    virtual void handle() = 0;
};

class AuthHandler : public Handler
{
public:
    void handle()
    {
        cout << "AuthHandler" << endl;
        if (next)
            next->handle();
        cout << "AuthHandler Terminated" << endl;
    }
};

class LogHandler : public Handler
{
public:
    void handle()
    {
        cout << "LogHandler" << endl;
        if (next)
            next->handle();
        cout << "LogHandler Terminated" << endl;
    }
};

int main()
{
    LogHandler logHandler;
    AuthHandler authHandler;
    authHandler.setNext(&logHandler);

    authHandler.handle();
    return 0;
}