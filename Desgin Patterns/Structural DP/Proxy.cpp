#include <bits/stdc++.h>
using namespace std;

class File
{
public:
    virtual void read() = 0;
    virtual ~File() = default;
};

class RealFile : public File
{
public:
    void read()
    {
        cout << "Reading the file" << endl;
    }
};

class ProxyFile : public File
{
    unique_ptr<RealFile> rf;
    string role;

public:
    ProxyFile(string role)
    {
        this->role = role;
    }
    void read()
    {
        if (role != "Admin")
        {
            cout << "opr bloclked" << endl;
            return;
        }

        if (rf == nullptr)
            rf = make_unique<RealFile>();

        rf->read();
    }
};

int main()
{
    unique_ptr<File> file = make_unique<ProxyFile>("Admin");
    file->read();

    return 0;
}