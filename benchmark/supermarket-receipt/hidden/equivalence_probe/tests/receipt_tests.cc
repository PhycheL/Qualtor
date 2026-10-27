// 参考强测试集：SupermarketReceipt 购物车、优惠与小票。隐藏材料，不提供给被评测的生成 Agent。
// 断言以现有代码的实际运行结果为准（D001），包括优惠描述里 std::to_string 的六位小数格式。
#include "FakeCatalog.h"
#include "Product.h"
#include "Receipt.h"
#include "ReceiptPrinter.h"
#include "ShoppingCart.h"
#include "Teller.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

const double kTolerance = 1e-9;

class SupermarketTest : public ::testing::Test {
protected:
    SupermarketTest()
        : toothbrush("toothbrush", ProductUnit::Each),
          apples("apples", ProductUnit::Kilo),
          tomatoes("cherry tomatoes", ProductUnit::Each),
          toothpaste("toothpaste", ProductUnit::Each),
          teller(&catalog) {
        catalog.addProduct(toothbrush, 0.99);
        catalog.addProduct(apples, 1.99);
        catalog.addProduct(tomatoes, 0.69);
        catalog.addProduct(toothpaste, 1.79);
    }

    Receipt checkout(const Product& product, double quantity) {
        ShoppingCart cart;
        cart.addItemQuantity(product, quantity);
        return teller.checksOutArticlesFrom(cart);
    }

    FakeCatalog catalog;
    Product toothbrush;
    Product apples;
    Product tomatoes;
    Product toothpaste;
    Teller teller;
};

TEST_F(SupermarketTest, ItemWithoutOfferIsChargedAtUnitPriceTimesQuantity) {
    Receipt receipt = checkout(apples, 2.5);
    ASSERT_EQ(1u, receipt.getItems().size());
    ReceiptItem item = receipt.getItems()[0];
    EXPECT_EQ(apples, item.getProduct());
    EXPECT_NEAR(1.99, item.getPrice(), kTolerance);
    EXPECT_NEAR(2.5 * 1.99, item.getTotalPrice(), kTolerance);
    EXPECT_NEAR(2.5, item.getQuantity(), kTolerance);
    EXPECT_TRUE(receipt.getDiscounts().empty());
    EXPECT_NEAR(4.975, receipt.getTotalPrice(), kTolerance);
}

TEST_F(SupermarketTest, OfferOnOtherProductDoesNotApply) {
    teller.addSpecialOffer(SpecialOfferType::TenPercentDiscount, toothbrush, 10.0);
    Receipt receipt = checkout(apples, 2.5);
    EXPECT_TRUE(receipt.getDiscounts().empty());
    EXPECT_NEAR(4.975, receipt.getTotalPrice(), kTolerance);
}

TEST_F(SupermarketTest, TenPercentDiscountUsesArgumentAsPercentage) {
    teller.addSpecialOffer(SpecialOfferType::TenPercentDiscount, apples, 20.0);
    Receipt receipt = checkout(apples, 2.5);
    ASSERT_EQ(1u, receipt.getDiscounts().size());
    Discount discount = receipt.getDiscounts()[0];
    EXPECT_EQ("20.000000% off", discount.getDescription());
    EXPECT_NEAR(-2.5 * 1.99 * 0.2, discount.getDiscountAmount(), kTolerance);
    EXPECT_EQ(apples, discount.getProduct());
    EXPECT_NEAR(2.5 * 1.99 * 0.8, receipt.getTotalPrice(), kTolerance);
}

TEST_F(SupermarketTest, ThreeForTwoNeedsAtLeastThreeItems) {
    teller.addSpecialOffer(SpecialOfferType::ThreeForTwo, toothbrush, 0.0);
    EXPECT_TRUE(checkout(toothbrush, 2).getDiscounts().empty());

    Receipt three = checkout(toothbrush, 3);
    ASSERT_EQ(1u, three.getDiscounts().size());
    EXPECT_EQ("3 for 2", three.getDiscounts()[0].getDescription());
    EXPECT_NEAR(-0.99, three.getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(1.98, three.getTotalPrice(), kTolerance);
}

TEST_F(SupermarketTest, ThreeForTwoChargesRemainderAtUnitPrice) {
    teller.addSpecialOffer(SpecialOfferType::ThreeForTwo, toothbrush, 0.0);
    EXPECT_NEAR(-0.99, checkout(toothbrush, 4).getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(-0.99, checkout(toothbrush, 5).getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(-1.98, checkout(toothbrush, 6).getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(7 * 0.99 - 1.98, checkout(toothbrush, 7).getTotalPrice(), kTolerance);
}

TEST_F(SupermarketTest, TwoForAmountAppliesFromTwoItems) {
    teller.addSpecialOffer(SpecialOfferType::TwoForAmount, tomatoes, 0.99);
    EXPECT_TRUE(checkout(tomatoes, 1).getDiscounts().empty());

    Receipt two = checkout(tomatoes, 2);
    ASSERT_EQ(1u, two.getDiscounts().size());
    EXPECT_EQ("2 for 0.990000", two.getDiscounts()[0].getDescription());
    EXPECT_NEAR(-(2 * 0.69 - 0.99), two.getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(0.99, two.getTotalPrice(), kTolerance);

    EXPECT_NEAR(-(3 * 0.69 - (0.99 + 0.69)), checkout(tomatoes, 3).getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(-(4 * 0.69 - 2 * 0.99), checkout(tomatoes, 4).getDiscounts()[0].getDiscountAmount(), kTolerance);
}

TEST_F(SupermarketTest, FiveForAmountAppliesFromFiveItems) {
    teller.addSpecialOffer(SpecialOfferType::FiveForAmount, toothpaste, 7.49);
    EXPECT_TRUE(checkout(toothpaste, 4).getDiscounts().empty());

    Receipt five = checkout(toothpaste, 5);
    ASSERT_EQ(1u, five.getDiscounts().size());
    EXPECT_EQ("5 for 7.490000", five.getDiscounts()[0].getDescription());
    EXPECT_NEAR(-(5 * 1.79 - 7.49), five.getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(7.49, five.getTotalPrice(), kTolerance);

    EXPECT_NEAR(-(6 * 1.79 - (7.49 + 1.79)), checkout(toothpaste, 6).getDiscounts()[0].getDiscountAmount(), kTolerance);
    EXPECT_NEAR(-(11 * 1.79 - (2 * 7.49 + 1.79)), checkout(toothpaste, 11).getDiscounts()[0].getDiscountAmount(), kTolerance);
}

TEST_F(SupermarketTest, FractionalQuantitiesAreTruncatedForCountBasedOffers) {
    teller.addSpecialOffer(SpecialOfferType::ThreeForTwo, apples, 0.0);
    EXPECT_TRUE(checkout(apples, 2.9).getDiscounts().empty());
    Receipt receipt = checkout(apples, 3.5);
    ASSERT_EQ(1u, receipt.getDiscounts().size());
    EXPECT_NEAR(-(3.5 * 1.99 - (2 * 1.99 + 0 * 1.99)), receipt.getDiscounts()[0].getDiscountAmount(), kTolerance);
}

TEST_F(SupermarketTest, CartKeepsEveryAdditionAndAggregatesQuantities) {
    ShoppingCart cart;
    cart.addItem(toothbrush);
    cart.addItemQuantity(apples, 1.5);
    cart.addItem(toothbrush);
    EXPECT_EQ(3u, cart.getItems().size());
    std::map<Product, double> quantities = cart.getProductQuantities();
    EXPECT_EQ(2u, quantities.size());
    EXPECT_NEAR(2.0, quantities[toothbrush], kTolerance);
    EXPECT_NEAR(1.5, quantities[apples], kTolerance);

    teller.addSpecialOffer(SpecialOfferType::ThreeForTwo, toothbrush, 0.0);
    cart.addItem(toothbrush);
    Receipt receipt = teller.checksOutArticlesFrom(cart);
    EXPECT_EQ(4u, receipt.getItems().size());
    ASSERT_EQ(1u, receipt.getDiscounts().size());
    EXPECT_NEAR(3 * 0.99 + 1.5 * 1.99 - 0.99, receipt.getTotalPrice(), kTolerance);
}

TEST_F(SupermarketTest, LaterOfferForSameProductReplacesEarlierOne) {
    teller.addSpecialOffer(SpecialOfferType::ThreeForTwo, toothbrush, 0.0);
    teller.addSpecialOffer(SpecialOfferType::TenPercentDiscount, toothbrush, 50.0);
    Receipt receipt = checkout(toothbrush, 3);
    ASSERT_EQ(1u, receipt.getDiscounts().size());
    EXPECT_EQ("50.000000% off", receipt.getDiscounts()[0].getDescription());
    EXPECT_NEAR(-1.485, receipt.getDiscounts()[0].getDiscountAmount(), kTolerance);
}

TEST(ReceiptTest, TotalAddsItemsAndDiscounts) {
    Product milk("milk", ProductUnit::Each);
    Receipt receipt;
    EXPECT_NEAR(0.0, receipt.getTotalPrice(), kTolerance);
    receipt.addProduct(milk, 2, 1.25, 2.5);
    receipt.addProduct(milk, 1, 1.25, 1.25);
    receipt.addDiscount(Discount("promo", -0.75, milk));
    EXPECT_NEAR(3.0, receipt.getTotalPrice(), kTolerance);
    ASSERT_EQ(2u, receipt.getItems().size());
    EXPECT_NEAR(2.0, receipt.getItems()[0].getQuantity(), kTolerance);
    EXPECT_NEAR(1.25, receipt.getItems()[1].getTotalPrice(), kTolerance);
    ASSERT_EQ(1u, receipt.getDiscounts().size());
    EXPECT_EQ("promo", receipt.getDiscounts()[0].getDescription());
}

TEST(ProductTest, ComparesByNameThenUnit) {
    Product a("apple", ProductUnit::Kilo);
    Product a2("apple", ProductUnit::Kilo);
    Product aEach("apple", ProductUnit::Each);
    Product b("banana", ProductUnit::Kilo);
    EXPECT_TRUE(a == a2);
    EXPECT_FALSE(a != a2);
    EXPECT_FALSE(a == aEach);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a <= a2);
    EXPECT_TRUE(a >= a2);
    EXPECT_FALSE(a > a2);
    EXPECT_TRUE(a < aEach);  // ProductUnit::Kilo 排在 Each 前面
    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(a >= b);
    EXPECT_EQ("apple", a.getName());
    EXPECT_TRUE(ProductUnit::Kilo == a.getUnit());
}

TEST(ReceiptItemTest, EqualityUsesAllFields) {
    Product p("pen", ProductUnit::Each);
    ReceiptItem item(p, 2, 1.5, 3.0);
    EXPECT_TRUE(item == ReceiptItem(p, 2, 1.5, 3.0));
    EXPECT_FALSE(item != ReceiptItem(p, 2, 1.5, 3.0));
    EXPECT_TRUE(item != ReceiptItem(p, 3, 1.5, 3.0));
    EXPECT_TRUE(item != ReceiptItem(p, 2, 1.0, 3.0));
    EXPECT_TRUE(item != ReceiptItem(p, 2, 1.5, 2.0));
    EXPECT_TRUE(item != ReceiptItem(Product("pencil", ProductUnit::Each), 2, 1.5, 3.0));
}

TEST(OfferTest, KeepsTypeProductAndArgument) {
    Product p("pen", ProductUnit::Each);
    Offer offer(SpecialOfferType::FiveForAmount, p, 4.5);
    EXPECT_TRUE(SpecialOfferType::FiveForAmount == offer.getOfferType());
    EXPECT_EQ(p, offer.getProduct());
    EXPECT_NEAR(4.5, offer.getArgument(), kTolerance);
}

TEST(CatalogTest, ReturnsPriceByProductName) {
    FakeCatalog catalog;
    catalog.addProduct(Product("pen", ProductUnit::Each), 1.25);
    catalog.addProduct(Product("pen", ProductUnit::Each), 1.5);
    EXPECT_NEAR(1.5, catalog.getUnitPrice(Product("pen", ProductUnit::Each)), kTolerance);
}

TEST(ReceiptPrinterTest, PrintsItemsDiscountsAndTotal) {
    Product toothbrush("toothbrush", ProductUnit::Each);
    Product apples("apples", ProductUnit::Kilo);
    Receipt receipt;
    receipt.addProduct(toothbrush, 1, 0.99, 0.99);
    receipt.addProduct(apples, 2.5, 1.99, 4.975);
    receipt.addDiscount(Discount("3 for 2", -0.99, toothbrush));
    std::string expected =
        "toothbrush                          0.99\n"
        "apples                              4.97\n"
        "  1.99 * 2.500\n"
        "3 for 2(toothbrush)                -0.99\n"
        "\n"
        "Total:                              4.97\n";
    EXPECT_EQ(expected, ReceiptPrinter().printReceipt(receipt));
    EXPECT_EQ("x     1.00\n", ReceiptPrinter(10).formatLineWithWhitespace("x", "1.00"));
}

}  // namespace
