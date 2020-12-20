#include <QtTest>

#include <nlohmann/json-schema.hpp>

#include <QtStrava/Model/detailedactivity.h>
#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/client.h>

class SchemataTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void validateModelSchema_data();
    void validateModelSchema();
};

void SchemataTest::initTestCase()
{
    // Call something in the library to initialize the resources
    QtStrava::Client client;
    Q_UNUSED(client.accessToken());
}

void SchemataTest::validateModelSchema_data()
{
    using namespace QtStrava::Model;

    QTest::addColumn<QString>("fileName");

    QTest::addRow("DetailedActivity") << DetailedActivity::JsonSchema;
    QTest::addRow("DetailedAthlete") << DetailedAthlete::JsonSchema;
    QTest::addRow("Fault") << Fault::JsonSchema;
    QTest::addRow("SummaryActivity") << SummaryActivity::JsonSchema;    
}

void SchemataTest::validateModelSchema()
{
    QFETCH(QString, fileName);

    QFile file{fileName};
    QVERIFY(file.open(QFile::ReadOnly));

    try {
        auto data = file.readAll();
        auto doc = nlohmann::json::parse(std::cbegin(data), std::cend(data));

        nlohmann::json_schema::json_validator validator{nlohmann::json_schema::draft7_schema_builtin,
                                                        nullptr,
                                                        [](const std::string &,
                                                           const std::string &) {}};
        validator.validate(doc);

        validator.validate(doc);
    } catch (const std::exception &e) {
        QFAIL(e.what());
    }
}

QTEST_APPLESS_MAIN(SchemataTest)

#include "tst_schemata.moc"
