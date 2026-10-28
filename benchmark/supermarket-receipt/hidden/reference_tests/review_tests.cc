// 复核补充测试：2026-10-27 变异复核中用来区分等价候选的反例（runs/bank-review-20261027-03），
// 由 benchmark/tools/bankutil.py 在建题时并入参考测试与探针。隐藏材料，不提供给被评测的生成 Agent。
// 断言为原代码的实际运行结果（D001），与其他测试的执行顺序无关。
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "Product.h"
#include "ShoppingCart.h"
#include "FakeCatalog.h"
#include "Teller.h"

TEST(ReviewExtra, ProductOrderingAndNoOffer) {
 Product a("z",ProductUnit::Kilo),b("a",ProductUnit::Each);
 EXPECT_FALSE(a<b);EXPECT_FALSE(a<=b);
 Product p("p",ProductUnit::Each);ShoppingCart cart;FakeCatalog catalog;catalog.addProduct(p,10);
 cart.addItemQuantity(p,3);Teller teller(&catalog);auto r=teller.checksOutArticlesFrom(cart);
 EXPECT_TRUE(r.getDiscounts().empty());EXPECT_DOUBLE_EQ(30,r.getTotalPrice());
 ShoppingCart zero;zero.addItemQuantity(p,-0.0);EXPECT_TRUE(std::signbit(zero.getProductQuantities().at(p)));
}
