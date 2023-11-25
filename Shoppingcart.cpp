#include <bits/stdc++.h>
using namespace std;

class Basket {
private:
    char productName[40];
    double price, gstPercent;
    int quantity;

public:
    Basket(const char* n, double c, double g, int qty)
        : price(c), gstPercent(g), quantity(qty) {
        strncpy(productName, n, sizeof(productName));
        productName[sizeof(productName) - 1] = '\0';
    }

    const char* getproductName() const {
        return productName;
    }

    double calculateTotalCost() const {
        return price * quantity * (1 + gstPercent / 100);
    }

    double calculateGstAmount() const {
        return price * quantity * (gstPercent / 100);
    }

    double calculateDiscountedTotalCost() const {
        return (price >= 500) ? calculateTotalCost() * 0.95 : calculateTotalCost();
    }
};

Basket findProductWithMaxGst(const Basket* basketList, size_t size) {
    Basket maxGstProduct = basketList[0];
    double maxGstAmount = maxGstProduct.calculateGstAmount();

    for (size_t i = 1; i < size; ++i) {
        double currentGstAmount = basketList[i].calculateGstAmount();
        maxGstProduct = (currentGstAmount > maxGstAmount) ? basketList[i] : maxGstProduct;
        maxGstAmount = (currentGstAmount > maxGstAmount) ? currentGstAmount : maxGstAmount;
    }

    return maxGstProduct;
}

int main() {
    Basket basket[] = {
        Basket("Leather Wallet", 1100, 18, 1),
        Basket("Umbrella", 900, 12, 4),
        Basket("Cigarette", 200, 28, 3),
        Basket("Honey", 100, 0, 2)
    };

    Basket maxGstProduct = findProductWithMaxGst(basket, sizeof(basket) / sizeof(basket[0]));

    double totalAmountToBePaid = 0.0;
    for (const auto& item : basket) {
        totalAmountToBePaid += item.calculateDiscountedTotalCost();
    }

    cout << "Product with maximum GST amount: " << maxGstProduct.getproductName() << endl;
    cout << "Total amount to be paid: Rs. " << totalAmountToBePaid << endl;

    return 0;
}
