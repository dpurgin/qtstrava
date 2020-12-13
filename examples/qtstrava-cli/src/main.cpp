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

#include <iostream>

#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/client.h>
#include <QtStrava/deserializererror.h>
#include <QtStrava/networkerror.h>

#include "authorizationhandler.h"

template<typename T>
QDebug operator<<(QDebug dbg, const std::optional<T> &val)
{
    return val.has_value() ? dbg << *val : dbg << "std::nullopt";
}

static void getLoggedInAthlete(QtStrava::Client &stravaClient)
{
    qInfo() << "\ngetLoggedInAthlete()";
    qInfo() << "====================";

    stravaClient.getLoggedInAthlete()
        .then([](const QtStrava::Model::DetailedAthlete &athlete) {
            qInfo() << athlete;
            qInfo() << "Bikes:" << athlete.bikes();
        })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; })
        .wait();
}

static void getLoggedInAthleteActivities(QtStrava::Client &stravaClient)
{
    qInfo() << "\ngetLoggedInAthleteActivities()";
    qInfo() << "==============================";

    std::string beforeStr;
    std::string afterStr;
    std::string pageStr;
    std::string perPageStr;

    // https://en.cppreference.com/w/cpp/io/basic_istream/ignore
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nBefore (ISO date, optional): ";
    std::getline(std::cin, beforeStr);

    std::cout << "After (ISO date, optional): ";
    std::getline(std::cin, afterStr);

    std::cout << "Page (number, default: 1): ";
    std::getline(std::cin, pageStr);

    std::cout << "Per page (number, default: 10): ";
    std::getline(std::cin, perPageStr);

    std::optional<QDateTime> before;
    std::optional<QDateTime> after;
    int page = 1;
    int perPage = 10;

    if (!beforeStr.empty()) {
        before = QDateTime::fromString(QString::fromStdString(beforeStr), Qt::ISODate);
        if (!before->isValid()) {
            std::cerr << "\nUnable to convert to date: " << beforeStr;
            before = std::nullopt;
        }
    }

    if (!afterStr.empty()) {
        after = QDateTime::fromString(QString::fromStdString(afterStr), Qt::ISODate);
        if (!after->isValid()) {
            std::cerr << "\nUnable to convert to date: " << afterStr;
            after = std::nullopt;
        }
    }

    if (!pageStr.empty()) {
        page = std::stoi(pageStr);
    }

    if (!perPageStr.empty()) {
        perPage = std::stoi(perPageStr);
    }

    qInfo() << "getLoggedInAthleteActivities(" << before << "," << after << "," << page << ","
            << perPage << ")";

    stravaClient.getLoggedInAthleteActivities(before, after, page, perPage)
        .then([](const QVector<QtStrava::Model::SummaryActivity> &activities) {
            qDebug() << activities;
        })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; })
        .wait();
}

int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    std::cout << "qtstrava-cli  Copyright (C) 2020  Dmitriy Purgin <dpurgin@gmail.com>";
    std::cout
        << "\nThis program comes with ABSOLUTELY NO WARRANTY. This is free software, and you are "
           "welcome to redistribute it under certain conditions; See GNU General Public "
           "License v3 at https://www.gnu.org/licenses/ for details.";
    std::cout << "\nEnable qtstrava.network logging category for verbose output. See "
                 "https://doc.qt.io/qt-5/qloggingcategory.html#configuring-categories";

    QtStrava::Client stravaClient;
    AuthorizationHandler authorizationHandler;

    stravaClient.setAccessToken(authorizationHandler.accessToken());

    QObject::connect(&authorizationHandler, &AuthorizationHandler::accessTokenChanged, [&]() {
        stravaClient.setAccessToken(authorizationHandler.accessToken());
    });

    authorizationHandler.grant()
        .then([&]() {
            int choice = 0;

            do {
                do {
                    std::cout << "\nqtstrava-cli";
                    std::cout << "\n============";
                    std::cout << "\n [0] Quit";
                    std::cout << "\n [1] getLoggedInAthlete";
                    std::cout << "\n [2] getLoggedInAthleteActivities";
                    std::cout << "\n\nEnter 0, 1, or 2:";
                    std::cin >> choice;
                } while (choice < 0 || choice > 2);

                static QVector<std::function<void(QtStrava::Client &)>>
                    functions{&getLoggedInAthlete, &getLoggedInAthleteActivities};

                if (choice > 0) {
                    functions[choice - 1](stravaClient);
                }
            } while (choice != 0);

            QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        })
        .fail([]() { std::cerr << "\nUnable to obtain Strava authorization!"; });

    return app.exec();
}
