#include <bits/stdc++.h>
using namespace std;

class ConfigurationManager
{
    ConfigurationManager()
    {
        cout << "Initalising cm" << endl;
        m["wms"] = "https://wms.com";
    }
    inline static unordered_map<string, string> m;

public:
    static ConfigurationManager *getInstance()
    {
        static ConfigurationManager instance;
        return &instance;
    }
    static string GetServiceApi(string service)
    {
        return m[service];
    }

    // ConfigurationManager c2 = *c1; // copy ctor
    ConfigurationManager(const ConfigurationManager &) = delete;

    //     ConfigurationManager c3;
    // c3 = *c1; // assignment operator
    ConfigurationManager &operator=(const ConfigurationManager &) = delete;

    // we mark above constant as you don't want to accidentally modify the source object (b) while copying from it.
    // other is just the thing you're reading from — marking it const enforces that you only read its fields, never modify them.
};

int main()
{

    ConfigurationManager *config = ConfigurationManager::getInstance();

    cout << config->GetServiceApi("wms") << endl;

    return 0;
}