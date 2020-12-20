#include <QtTest>

#include "../../src/jsondeserializer_p.h"

#include <QtStrava/Model/detailedactivity.h>
#include <QtStrava/client.h>

Q_DECLARE_METATYPE(QtStrava::Model::DetailedActivity)

using namespace std::chrono_literals;

class DetailedActivityTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void testDeserializer_data();
    void testDeserializer();
};

void DetailedActivityTest::initTestCase()
{
    // Call something in the library to initialize the resources
    QtStrava::Client client;
    Q_UNUSED(client.accessToken());
}

void DetailedActivityTest::testDeserializer_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QtStrava::Model::DetailedActivity>("expected");

    QtStrava::Model::MetaAthlete athlete;
    athlete.setId(12345677);
    athlete.setResourceState(QtStrava::ResourceState::Meta);

    {
        QtStrava::Model::DetailedActivity detailedActivity;
        detailedActivity.setAthlete(athlete);
        detailedActivity.setCommute(true);
        detailedActivity.setDistance(1000.0);
        detailedActivity.setElapsedTime(60s);
        detailedActivity.setId(9876543210);
        detailedActivity.setMovingTime(60s);
        detailedActivity.setName("Test upload");
        detailedActivity.setResourceState(QtStrava::ResourceState::Detail);
        detailedActivity.setTrainer(true);
        detailedActivity.setType(QtStrava::ActivityType::Ride);
        QTest::addRow("DetailedActivity1.json") << ":/DetailedActivity1.json" << detailedActivity;
    }

    {
        QtStrava::Model::DetailedActivity detailedActivity;
        detailedActivity.setAthlete(athlete);
        detailedActivity.setCommute(false);
        detailedActivity.setDistance(0.0);
        detailedActivity.setElapsedTime(60min);
        detailedActivity.setId(9876543210);
        detailedActivity.setMovingTime(60min);
        detailedActivity.setName("Test activity");
        detailedActivity.setResourceState(QtStrava::ResourceState::Detail);
        detailedActivity.setTrainer(false);
        detailedActivity.setType(QtStrava::ActivityType::Walk);
        QTest::addRow("DetailedActivity2.json") << ":/DetailedActivity2.json" << detailedActivity;
    }
}

void DetailedActivityTest::testDeserializer()
{
    QFETCH(QString, fileName);
    QFETCH(QtStrava::Model::DetailedActivity, expected);

    QFile jsonFile{fileName};
    QVERIFY(jsonFile.open(QIODevice::ReadOnly));
    QByteArray jsonData = jsonFile.readAll();

    auto doc = nlohmann::json::parse(std::cbegin(jsonData), std::cend(jsonData));

    QFile schemaFile{QtStrava::Model::DetailedActivity::JsonSchema};
    QVERIFY(schemaFile.open(QIODevice::ReadOnly));
    QByteArray schemaData = schemaFile.readAll();
    auto schema = nlohmann::json::parse(std::cbegin(schemaData), std::cend(schemaData));

    nlohmann::json_schema::json_validator validator{schema};
    validator.validate(doc);

    auto actual = doc.get<QtStrava::Model::DetailedActivity>();
    QCOMPARE(expected, actual);
}

QTEST_APPLESS_MAIN(DetailedActivityTest)

#include "tst_detailedactivity.moc"
