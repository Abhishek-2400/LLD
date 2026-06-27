#include <bits/stdc++.h>
#include "../include/invenotryService.h"
#include "../include/emailService.h"
#include "../include/paymentService.h"
#include "../include/verifyStock.h"
#include "../include/chargeCard.h"
#include "../include/sendReceipt.h"
#include "../include/checkoutProcessor.h"

using namespace std;

int main()
{
    InventoryService inventory;
    PaymentService payment;
    EmailService email;

    auto verify = make_shared<VerifyStock>(&inventory);
    auto charge = make_shared<ChargeCard>(&payment);
    auto receipt = make_shared<SendReceipt>(&email);

    CheckoutProcessor processor;

    processor.addCommand(verify);
    processor.addCommand(charge);
    processor.addCommand(receipt);

    processor.placeOrder();
}
