/*
  Copyright 2012, Robert Knight

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
*/

#include <gtest/gtest.h>
#define QCOMPARE(actual, expected) ASSERT_EQ((expected), (actual))
#define QVERIFY(value) ASSERT_TRUE(value)
#define QVERIFY2(value, message) ASSERT_TRUE(value) << message
#define QFAIL(message) FAIL() << message
#include "mustache.h"

#include <QDir>
#include <QList>
#include <QFile>
#include <QHash>
#include <QString>

#if QT_VERSION >= 0x050000
    #include <QJsonDocument>
    #include <QJsonObject>
    #include <QJsonArray>
#endif // QT_VERSION >= 0x050000

// To be able to use QHash<QString, QString> in QFETCH(..).
typedef QHash<QString, QString> PartialsHash;
Q_DECLARE_METATYPE(PartialsHash)

TEST(Mustache, testValues)
{
	QVariantHash map;
	map["name"] = "John Smith";
	map["age"] = 42;
	map["sex"] = "Male";
	map["company"] = "Smith & Co";
	map["signature"] = "John Smith of <b>Smith & Co</b>";
	map["alive"] = false;

	QString _template = "Name: {{name}}, Age: {{age}}, Sex: {{sex}}, Alive: {{alive}}\n"
	                    "Company: {{company}}\n"
	                    "  {{{signature}}}"
	                    "{{missing-key}}";
	QString expectedOutput = "Name: John Smith, Age: 42, Sex: Male, Alive: false\n"
	                         "Company: Smith &amp; Co\n"
	                         "  John Smith of <b>Smith & Co</b>";

	Mustache::Renderer renderer;
	Mustache::QtVariantContext context(map);
	QString output = renderer.render(_template, &context);

	QCOMPARE(output, expectedOutput);
}

TEST(Mustache, testFloatValues)
{
  QList<float> values = {-3., -0.5, 0., 0.5, 1., 1.5, 3.};

  for (auto value : values) {
    QVariantHash map;
    map["val"] = value;
    QString _template = "Value: {{val}}";
    QString expectedOutput = "Value: " + QString::number(value);

    Mustache::Renderer renderer;
    Mustache::QtVariantContext context(map);
    QString output = renderer.render(_template, &context);

    QCOMPARE(output, expectedOutput);
  }
}

QVariantHash contactInfo(const QString& name, const QString& email)
{
	QVariantHash map;
	map["name"] = name;
	map["email"] = email;
	return map;
}

TEST(Mustache, testSections)
{
	QVariantHash map = contactInfo("John Smith", "john.smith@gmail.com");
	QVariantList contacts;
	contacts << contactInfo("James Dee", "james@dee.org");
	contacts << contactInfo("Jim Jones", "jim-jones@yahoo.com");
	map["contacts"] = contacts;

	QString _template = "Name: {{name}}, Email: {{email}}\n"
	                    "{{#contacts}}  {{name}} - {{email}}\n{{/contacts}}"
	                    "{{^contacts}}  No contacts{{/contacts}}";

	QString expectedOutput = "Name: John Smith, Email: john.smith@gmail.com\n"
	                         "  James Dee - james@dee.org\n"
	                         "  Jim Jones - jim-jones@yahoo.com\n";

	Mustache::Renderer renderer;
	Mustache::QtVariantContext context(map);
	QString output = renderer.render(_template, &context);

	QCOMPARE(output, expectedOutput);

	// test inverted sections
	map.remove("contacts");
	context = Mustache::QtVariantContext(map);
	output = renderer.render(_template, &context);

	expectedOutput = "Name: John Smith, Email: john.smith@gmail.com\n"
	                 "  No contacts";
	QCOMPARE(output, expectedOutput);

	// test with an empty list instead of an empty key
	map["contacts"] = QVariantHash();
	context = Mustache::QtVariantContext(map);
	output = renderer.render(_template, &context);
	QCOMPARE(output, expectedOutput);
}

TEST(Mustache, testSectionQString)
{
	QVariantHash data;
	data["text"] = "test";
	QString output = Mustache::renderTemplate("{{#text}}{{text}}{{/text}}", data);
	QCOMPARE(output, QString("test"));
}

TEST(Mustache, testFalsiness)
{
	Mustache::Renderer renderer;
	QVariantHash data;
	QString _template = "{{#bool}}This should not be shown{{/bool}}";

	// test falsiness of 0
	data["bool"] = 0;
	Mustache::QtVariantContext context = Mustache::QtVariantContext(data);
	QString output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "0 evaluated as truthy");

	// test falsiness of 0u
	data["bool"] = 0u;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "0u evaluated as truthy");

	// test falsiness of 0ll
	data["bool"] = 0ll;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "0ll evaluated as truthy");

	// test falsiness of 0ull
	data["bool"] = 0ull;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "0ull evaluated as truthy");

	// test falsiness of 0.0
	data["bool"] = 0.0;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "0.0 evaluated as truthy");

	// test falsiness of 0.4
	data["bool"] = 0.4f;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(!output.isEmpty(), "0.4 evaluated as falsey");

	// test falsiness of 0.5
	data["bool"] = 0.5f;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(!output.isEmpty(), "0.5f evaluated as falsey");

	// test falsiness of 0.0f
	data["bool"] = 0.0f;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "0.0f evaluated as truthy");

	// test falsiness of '\0'
	data["bool"] = '\0';
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "'\0' evaluated as truthy");

	// test falsiness of 'false'
	data["bool"] = false;
	context = Mustache::QtVariantContext(data);
	output = renderer.render(_template, &context);
	QVERIFY2(output.isEmpty(), "'\0' evaluated as truthy");
}

TEST(Mustache, testContextLookup)
{
	QVariantHash fileMap;
	fileMap["dir"] = "/home/robert";
	fileMap["name"] = "robert";

	QVariantList files;
	QVariantHash file;
	file["name"] = "test.pdf";
	files << file;

	fileMap["files"] = files;

	QString _template = "{{#files}}{{dir}}/{{name}}{{/files}}";

	Mustache::Renderer renderer;
	Mustache::QtVariantContext context(fileMap);
	QString output = renderer.render(_template, &context);

	QCOMPARE(output, QString("/home/robert/test.pdf"));
}

TEST(Mustache, testPartials)
{
	QHash<QString, QString> partials;
	partials["file-info"] = "{{name}} {{size}} {{type}}\n";

	QString _template = "{{#files}}{{>file-info}}{{/files}}";

	QVariantHash map;
	QVariantList fileList;

	QVariantHash file1;
	file1["name"] = "mustache.pdf";
	file1["size"] = "200KB";
	file1["type"] = "PDF Document";

	QVariantHash file2;
	file2["name"] = "cv.doc";
	file2["size"] = "300KB";
	file2["type"] = "Microsoft Word Document";

	fileList << file1 << file2;
	map["files"] = fileList;

	Mustache::Renderer renderer;
	Mustache::PartialMap partialMap(partials);
	Mustache::QtVariantContext context(map, &partialMap);
	QString output = renderer.render(_template, &context);

	QCOMPARE(output,
	         QString("mustache.pdf 200KB PDF Document\n"
	                 "cv.doc 300KB Microsoft Word Document\n"));
}

TEST(Mustache, testSetDelimiters)
{
	// test changing the markers within a template
	QVariantHash map;
	map["name"] = "John Smith";
	map["phone"] = "01234 567890";

	QString _template =
	    "{{=<% %>=}}"
	    "<%name%>{{ }}<%phone%>"
	    "<%={{ }}=%>"
	    " {{name}}<% %>{{phone}}";

	QString expectedOutput = "John Smith{{ }}01234 567890 John Smith<% %>01234 567890";

	Mustache::Renderer renderer;
	Mustache::QtVariantContext context(map);
	QString output = renderer.render(_template, &context);

	QCOMPARE(output, expectedOutput);

	// test changing the default markers
	renderer.setTagMarkers("%", "%");
	output = renderer.render("%name%'s phone number is %phone%", &context);
	QCOMPARE(output, QString("John Smith's phone number is 01234 567890"));

	renderer.setTagMarkers("{{", "}}");
	output = renderer.render("{{== ==}}", &context);
	QCOMPARE(renderer.error(), QString("Custom delimiters may not contain '='."));
}

TEST(Mustache, testErrors)
{
	QVariantHash map;
	map["name"] = "Jim Jones";

	QHash<QString, QString> partials;
	partials["buggy-partial"] = "--{{/one}}--";

	QString _template = "{{name}}";

	Mustache::Renderer renderer;
	Mustache::PartialMap partialMap(partials);
	Mustache::QtVariantContext context(map, &partialMap);
	QString output = renderer.render(_template, &context);

	QCOMPARE(output, QString("Jim Jones"));
	QCOMPARE(renderer.error(), QString());
	QCOMPARE(renderer.errorPos(), -1);

	_template = "{{#one}} {{/two}}";
	output = renderer.render(_template, &context);
	QCOMPARE(renderer.error(), QString("Tag start/end key mismatch"));
	QCOMPARE(renderer.errorPos(), 9);
	QCOMPARE(renderer.errorPartial(), QString());

	_template = "Hello {{>buggy-partial}}";
	output = renderer.render(_template, &context);
	QCOMPARE(renderer.error(), QString("Unexpected end tag"));
	QCOMPARE(renderer.errorPos(), 2);
	QCOMPARE(renderer.errorPartial(), QString("buggy-partial"));
}



TEST(Mustache, testEscaping)
{
	QVariantHash map;
	map["escape"] = "<b>foo</b>";
	map["unescape"] = "One &amp; Two &quot;quoted&quot;";
	map["raw"] = "<b>foo</b>";

	QString _template = "{{escape}} {{&unescape}} {{{raw}}}";

	Mustache::Renderer renderer;
	Mustache::QtVariantContext context(map);
	QString output = renderer.render(_template, &context);

	QCOMPARE(output, QString("&lt;b&gt;foo&lt;/b&gt; One & Two \"quoted\" <b>foo</b>"));
}

class CounterContext : public Mustache::QtVariantContext
{
public:
	int counter;

	CounterContext(const QVariantHash& map)
		: Mustache::QtVariantContext(map)
		, counter(0)
	{}

	virtual bool canEval(const QString& key) const {
		return key == "counter";
	}

	virtual QString eval(const QString& key, const QString& _template, Mustache::Renderer* renderer) {
		if (key == "counter") {
			++counter;
		}
		return renderer->render(_template, this);
	}

	virtual QString stringValue(const QString& key) const {
		if (key == "count") {
			return QString::number(counter);
		} else {
			return Mustache::QtVariantContext::stringValue(key);
		}
	}
};

TEST(Mustache, testEval)
{
	QVariantHash map;
	QVariantList list;
	list << contactInfo("Rob Knight", "robertknight@gmail.com");
	list << contactInfo("Jim Smith", "jim.smith@smith.org");
	map["list"] = list;

	QString _template = "{{#list}}{{#counter}}#{{count}} {{name}} {{email}}{{/counter}}\n{{/list}}";

	Mustache::Renderer renderer;
	CounterContext context(map);
	QString output = renderer.render(_template, &context);
	QCOMPARE(output, QString("#1 Rob Knight robertknight@gmail.com\n"
	                         "#2 Jim Smith jim.smith@smith.org\n"));
}

TEST(Mustache, testHelpers)
{
	QVariantHash args;
	args.insert("name", "Jim Smith");
	args.insert("age", 42);

	QString output = Mustache::renderTemplate("Hello {{name}}, you are {{age}}", args);
	QCOMPARE(output, QString("Hello Jim Smith, you are 42"));
}

TEST(Mustache, testIncompleteTag)
{
	QVariantHash args;
	args.insert("name", "Jim Smith");

	QString output = Mustache::renderTemplate("Hello {{name}}, you are {", args);
	QCOMPARE(output, QString("Hello Jim Smith, you are {"));

	output = Mustache::renderTemplate("Hello {{name}}, you are {{", args);
	QCOMPARE(output, QString("Hello Jim Smith, you are {{"));

	output = Mustache::renderTemplate("Hello {{name}}, you are {{}", args);
	QCOMPARE(output, QString("Hello Jim Smith, you are {{}"));
}

TEST(Mustache, testIncompleteSection)
{
	QVariantHash args;
	args.insert("list", QVariantList() << QVariantHash());

	Mustache::Renderer renderer;
	Mustache::QtVariantContext context(args);
	QString output = renderer.render("{{#list}}", &context);
	QCOMPARE(output, QString());
	QCOMPARE(renderer.error(), QString("No matching end tag found for section"));

	output = renderer.render("{{^list}}", &context);
	QCOMPARE(output, QString());
	QCOMPARE(renderer.error(), QString("No matching end tag found for inverted section"));

	output = renderer.render("{{/list}}", &context);
	QCOMPARE(output, QString());
	QCOMPARE(renderer.error(), QString("Unexpected end tag"));

	output = renderer.render("{{#list}}{{/foo}}", &context);
	QCOMPARE(output, QString());
	QCOMPARE(renderer.error(), QString("Tag start/end key mismatch"));
}

static QString decorate(const QString& text, Mustache::Renderer* r, Mustache::Context* ctx)
{
	return "~" + r->render(text, ctx) + "~";
}

TEST(Mustache, testLambda)
{
	QVariantHash args;
	args["text"] = "test";
	args["fn"] = QVariant::fromValue(Mustache::QtVariantContext::fn_t(decorate));
	QString output = Mustache::renderTemplate("{{#fn}}{{text}}{{/fn}}", args);
	QCOMPARE(output, QString("~test~"));
}

TEST(Mustache, testQStringListIteration)
{
	QStringList list;
	list << "str1" << "str2" << "str3";
	QVariantHash args;
	args["list"] = list;
	QString output = Mustache::renderTemplate("{{#list}}{{.}}{{/list}}", args);
	QCOMPARE(output, QString("str1str2str3"));
}

TEST(Mustache, testUnescapeHtml)
{
	QVariantHash args;
	args["s"] = "&lt;&gt;&amp;&quot;&amp;quot;";
	QString output = Mustache::renderTemplate("{{&s}}", args);
	QCOMPARE(output, QString("<>&\"&quot;"));
}

#if QT_VERSION >= 0x050000 // JSON classes only in Qt 5+.



/*
 * This test will run once for each test case defined in version 1.1.2 of the
 * Mustache specification [1].
 *
 * [1] https://github.com/mustache/spec/tree/v1.1.2/specs
 */


#endif // QT_VERSION >= 0x050000

