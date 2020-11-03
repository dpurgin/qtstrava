#include <QCoreApplication>
#include <QUrl>

#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/client.h>
#include <QtStrava/deserializererror.h>
#include <QtStrava/networkerror.h>

int main(int argc, char *argv[])
{
    QCoreApplication app{argc, argv};

    QtStrava::Client client{QUrl{"https://www.strava.com/api/v3"},
                            "fc6888d4578d84bf6a48d95ae5791d447c2508a7"};

    client.getLoggedInAthlete()
        .then([](const QtStrava::Model::DetailedAthlete &athlete) { qDebug() << athlete; })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; });

    client.getLoggedInAthleteActivities(std::nullopt, std::nullopt)
        .then([](const QVector<QtStrava::Model::SummaryActivity> &activities) {
            qDebug() << activities;
        })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; });

    return app.exec();
}
