#include <bits/stdc++.h>
using namespace std;

class InventoryService
{
public:
    void reserveInventory()
    {
        cout << "Reserving inventory";
    }
};

class PaymentService
{
public:
    void makePayment()
    {
        cout << "Doing Payment";
    }
};

class OrderFacade
{
    InventoryService *inventoryService;
    PaymentService *paymentService;

public:
    OrderFacade(InventoryService *i, PaymentService *p)
    {
        inventoryService = i;
        paymentService = p;
    }

    void placeOrder()
    {
        inventoryService->reserveInventory();
        paymentService->makePayment();
    }
};

int main()
{
    InventoryService inventoryService;
    PaymentService PaymentService;

    OrderFacade order(&inventoryService, &PaymentService);
    order.placeOrder();

    return 0;
}