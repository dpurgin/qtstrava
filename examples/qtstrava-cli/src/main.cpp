#include <QGuiApplication>

#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/client.h>
#include <QtStrava/deserializererror.h>
#include <QtStrava/networkerror.h>

#include "authorizationhandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    AuthorizationHandler authorizationHandler;

    QtStrava::Client client;
    client.setAccessToken(authorizationHandler.accessToken());

    QObject::connect(&authorizationHandler, &AuthorizationHandler::accessTokenChanged, [&]() {
        client.setAccessToken(authorizationHandler.accessToken());
    });

    client.getLoggedInAthlete()
        .then([](const QtStrava::Model::DetailedAthlete &athlete) { qDebug() << athlete; })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; });

    //    client.getLoggedInAthleteActivities(std::nullopt, std::nullopt)
    //        .then([](const QVector<QtStrava::Model::SummaryActivity> &activities) {
    //            qDebug() << activities;
    //        })
    //        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
    //        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
    //        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; });

    return app.exec();
}
