#include <bits/stdc++.h>
#include "../include/invenotryService.h"
#include "../include/verifyStock.h"
using namespace std;

void test_should_reserve_stock()
{
    InventoryService inventory;
    VerifyStock cmd(&inventory);

    assert(cmd.execute() == true);
}

int main()
{

    test_should_reserve_stock();
    return 0;
}
// test cases
