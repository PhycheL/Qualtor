#include <gtest/gtest.h>
#include "mustache.h"
#include <QFile>
#include <QTemporaryDir>
#include <QVariantMap>

struct BothMaps {};
Q_DECLARE_METATYPE(BothMaps)
static QVariantHash asHash(const BothMaps&) { return {{"x", "hash"}}; }
static QVariantMap asMap(const BothMaps&) { return {{"x", "map"}}; }
static const bool registeredHash = QMetaType::registerConverter<BothMaps, QVariantHash>(asHash);
static const bool registeredMap = QMetaType::registerConverter<BothMaps, QVariantMap>(asMap);
QVariant variantMapValue(const QVariant&, const QString&);
QVariant variantMapValueForKeyPath(const QVariant&, const QStringList);

TEST(Review, CustomVariantConversionAndEmptyPath) {
  EXPECT_TRUE(registeredHash); EXPECT_TRUE(registeredMap);
  EXPECT_EQ(QString("hash"), variantMapValue(QVariant::fromValue(BothMaps{}), "x").toString());
  EXPECT_FALSE(variantMapValueForKeyPath(QVariantMap{{"x", 1}}, {}).isValid());
}

TEST(Review, ErrorStateClearsBetweenRenders) {
  Mustache::PartialMap partials({{"broken", "{{/x}}"}});
  Mustache::QtVariantContext context(QVariantHash{}, &partials);
  Mustache::Renderer renderer;
  renderer.render("{{>broken}}", &context);
  EXPECT_FALSE(renderer.error().isEmpty());
  EXPECT_EQ(QString("broken"), renderer.errorPartial());
  EXPECT_EQ(QString("ok"), renderer.render("ok", &context));
  EXPECT_TRUE(renderer.error().isEmpty());
  EXPECT_TRUE(renderer.errorPartial().isEmpty());
  EXPECT_EQ(-1, renderer.errorPos());
}

TEST(Review, PartialCacheAndLeadingNewline) {
  QTemporaryDir dir;
  ASSERT_TRUE(dir.isValid());
  QFile file(dir.filePath("cached.mustache"));
  ASSERT_TRUE(file.open(QIODevice::WriteOnly));
  file.write("old"); file.close();
  Mustache::PartialFileLoader loader(dir.path());
  EXPECT_EQ(QString("old"), loader.getPartial("cached"));
  ASSERT_TRUE(file.open(QIODevice::WriteOnly | QIODevice::Truncate));
  file.write("new"); file.close();
  EXPECT_EQ(QString("old"), loader.getPartial("cached"));
  Mustache::PartialMap partials({{"p", "\nA\n"}});
  Mustache::QtVariantContext context(QVariantHash{}, &partials);
  Mustache::Renderer renderer;
  EXPECT_EQ(QString("  \nA\n"), renderer.render("  {{>p}}\n", &context));
}

TEST(Review, CustomDelimiterErrors) {
  Mustache::QtVariantContext context(QVariantHash{});
  for (const QString& input : {QString("{{=a= b=}}"), QString("{{=a b=c=}}")}) {
    Mustache::Renderer renderer;
    renderer.render(input, &context);
    EXPECT_EQ(QString("Custom delimiters may not contain '='."), renderer.error());
  }
}

TEST(Review, RawNameBoundaryAndClosingMarker) {
  Mustache::QtVariantContext context(QVariantHash{{"x", "raw"}, {"x}", "wrong"}});
  Mustache::Renderer renderer;
  EXPECT_EQ(QString("raw"), renderer.render("{{{x} y}}", &context));
  EXPECT_TRUE(renderer.error().isEmpty());
  renderer.setTagMarkers("<", "=>");
  EXPECT_EQ(QString("X"), renderer.render("<=abc=>X", &context));
  EXPECT_TRUE(renderer.error().isEmpty());
}
