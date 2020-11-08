// qtstrava-cli - An example usage of QtStrava, a Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin  <dpurgin@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

    qInfo() << "qtstrava-cli  Copyright (C) 2020  Dmitriy Purgin <dpurgin@gmail.com>";
    qInfo() << "This program comes with ABSOLUTELY NO WARRANTY. This is free software, and you are "
               "welcome to redistribute it under certain conditions; See GNU General Public "
               "License v3 at https://www.gnu.org/licenses/ for details.";

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
