#include <gtest/gtest.h>
#include "mustache.h"
#include <QTemporaryDir>
#include <QFile>

TEST(MustacheFiles, UpstreamPartialInTemporaryDirectory) {
  QTemporaryDir directory;
  ASSERT_TRUE(directory.isValid());
  QFile file(directory.filePath("partial.mustache"));
  ASSERT_TRUE(file.open(QIODevice::WriteOnly));
  ASSERT_EQ(22, file.write("{{name}} -- {{email}}\n"));
  file.close();
  QVariantHash data;
  data["name"] = "Jim Smith";
  data["email"] = "jim.smith@gmail.com";
  Mustache::Renderer renderer;
  Mustache::PartialFileLoader loader(directory.path());
  Mustache::QtVariantContext context(data, &loader);
  EXPECT_EQ(QString("Jim Smith -- jim.smith@gmail.com\n"), renderer.render("{{>partial}}", &context));
}
