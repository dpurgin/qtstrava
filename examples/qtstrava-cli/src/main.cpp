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

#include <QtStrava/Model/detailedactivity.h>
#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/Model/updatableactivity.h>
#include <QtStrava/Model/upload.h>
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

static void createActivity(QtStrava::Client &stravaClient)
{
    qInfo() << "\ncreateActivity()";
    qInfo() << "================";

    std::string nameStr;
    std::string activityTypeStr;
    std::string startDateLocalStr;
    std::string elapsedTimeStr;
    std::string descriptionStr;
    std::string distanceStr;
    std::string trainerStr;
    std::string commuteStr;

    // https://en.cppreference.com/w/cpp/io/basic_istream/ignore
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nName: ";
    std::getline(std::cin, nameStr);

    std::cout << "\nActivity type (default: Ride): ";
    std::getline(std::cin, activityTypeStr);

    std::cout << "\nStart date (ISO date, default: current time stamp): ";
    std::getline(std::cin, startDateLocalStr);

    std::cout << "\nElapsed time (seconds): ";
    std::getline(std::cin, elapsedTimeStr);

    std::cout << "\nDescription (optional): ";
    std::getline(std::cin, descriptionStr);

    std::cout << "\nDistance (meters, optional): ";
    std::getline(std::cin, distanceStr);

    std::cout << "\nTrainer (true/false, default: false): ";
    std::getline(std::cin, trainerStr);

    std::cout << "\nCommute (true/false, default: false): ";
    std::getline(std::cin, commuteStr);

    QString name = QString::fromStdString(nameStr);
    auto type = QtStrava::toActivityType(QString::fromStdString(activityTypeStr));

    QDateTime startDateLocal = QDateTime::currentDateTime();
    if (!startDateLocalStr.empty()) {
        startDateLocal = QDateTime::fromString(QString::fromStdString(startDateLocalStr),
                                               Qt::ISODate);
        if (!startDateLocal.isValid()) {
            std::cerr << "\nUnable to convert to date: " << startDateLocalStr;
            startDateLocal = QDateTime::currentDateTime();
        }
    }

    if (!type.has_value()) {
        std::cerr << "\nUnknown activity type: " << activityTypeStr;
        return;
    }

    std::chrono::seconds elapsedTime{std::stoi(elapsedTimeStr)};

    std::optional<QString> description = descriptionStr.empty()
                                             ? std::nullopt
                                             : std::make_optional(
                                                 QString::fromStdString(descriptionStr));
    std::optional<qreal> distance = distanceStr.empty()
                                        ? std::nullopt
                                        : std::make_optional(std::stod(distanceStr));
    std::optional<bool> trainer = trainerStr.empty() ? std::make_optional(false)
                                                     : std::make_optional(trainerStr == "t"
                                                                          || trainerStr == "true");
    std::optional<bool> commute = commuteStr.empty() ? std::make_optional(false)
                                                     : std::make_optional(commuteStr == "t"
                                                                          || commuteStr == "true");

    stravaClient
        .createActivity(name,
                        *type,
                        startDateLocal,
                        elapsedTime,
                        description,
                        distance,
                        trainer,
                        commute)
        .then([](const QtStrava::Model::DetailedActivity &activity) { qDebug() << activity; })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; })
        .wait();
}

static void updateActivityById(QtStrava::Client &stravaClient)
{
    qInfo() << "\nupdateActivityById()";
    qInfo() << "====================";

    std::string idStr;
    std::string nameStr;
    std::string trainerStr;
    std::string commuteStr;
    std::string activityTypeStr;

    // https://en.cppreference.com/w/cpp/io/basic_istream/ignore
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nID: ";
    std::getline(std::cin, idStr);

    std::cout << "\nName: ";
    std::getline(std::cin, nameStr);

    std::cout << "\nActivity type (default: Ride): ";
    std::getline(std::cin, activityTypeStr);

    std::cout << "\nTrainer (true/false, default: false): ";
    std::getline(std::cin, trainerStr);

    std::cout << "\nCommute (true/false, default: false): ";
    std::getline(std::cin, commuteStr);

    auto type = QtStrava::toActivityType(QString::fromStdString(activityTypeStr));

    bool trainer = !trainerStr.empty() && (trainerStr == "t" || trainerStr == "true");
    bool commute = !commuteStr.empty() && (commuteStr == "t" || commuteStr == "true");

    QtStrava::Model::UpdatableActivity updatableActivity;
    updatableActivity.setName(QString::fromStdString(nameStr));
    updatableActivity.setCommute(commute);
    updatableActivity.setTrainer(trainer);
    updatableActivity.setType(type.value_or(QtStrava::ActivityType::Other));

    stravaClient.updateActivityById(std::stoull(idStr), updatableActivity)
        .then([](const QtStrava::Model::DetailedActivity &activity) { qDebug() << activity; })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; })
        .wait();
}

static void createUpload(QtStrava::Client &stravaClient)
{
    qInfo() << "\ncreateUpload()";
    qInfo() << "==============";

    std::string fileStr;
    std::string nameStr;
    std::string descriptionStr;
    std::string trainerStr;
    std::string commuteStr;
    std::string dataTypeStr;
    std::string externalIdStr;

    // https://en.cppreference.com/w/cpp/io/basic_istream/ignore
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nFile path: ";
    std::getline(std::cin, fileStr);

    std::cout << "\nActivity name: ";
    std::getline(std::cin, nameStr);

    std::cout << "\nDescription: ";
    std::getline(std::cin, descriptionStr);

    std::cout << "\nTrainer (true/false, default: false): ";
    std::getline(std::cin, trainerStr);

    std::cout << "\nCommute (true/false, default: false): ";
    std::getline(std::cin, commuteStr);

    std::cout << "\nData type (fit, fit.gz, tcx, tcx.gz, gpx, gpx.gz): ";
    std::getline(std::cin, dataTypeStr);

    std::cout << "\nExternal ID: ";
    std::getline(std::cin, externalIdStr);

    auto file = new QFile{QString::fromStdString(fileStr)};
    if (!file->open(QIODevice::ReadOnly)) {
        qCritical() << "Unable to open:" << file->errorString();
        return;
    }

    bool trainer = !trainerStr.empty() && (trainerStr == "t" || trainerStr == "true");
    bool commute = !commuteStr.empty() && (commuteStr == "t" || commuteStr == "true");

    auto dataType = QtStrava::toDataType(QString::fromStdString(dataTypeStr));

    if (!dataType.has_value()) {
        qCritical() << "Unknown data type:" << QString::fromStdString(dataTypeStr);
        return;
    }

    stravaClient
        .createUpload(file,
                      QString::fromStdString(nameStr),
                      QString::fromStdString(descriptionStr),
                      trainer,
                      commute,
                      *dataType,
                      QString::fromStdString(externalIdStr))
        .then([](const QtStrava::Model::Upload &upload) { qDebug() << upload; })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; })
        .finally([file]() { delete file; })
        .wait();
}

static void getUploadById(QtStrava::Client &stravaClient)
{
    qInfo() << "\ngetUploadById()";
    qInfo() << "==============";

    std::string idStr;

    // https://en.cppreference.com/w/cpp/io/basic_istream/ignore
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nID: ";
    std::getline(std::cin, idStr);

    stravaClient.getUploadById(std::stoull(idStr))
        .then([](const QtStrava::Model::Upload &upload) { qDebug() << upload; })
        .fail([](const QtStrava::Model::Fault &fault) { qWarning() << fault; })
        .fail([](const QtStrava::DeserializerError &error) { qWarning() << error; })
        .fail([](const QtStrava::NetworkError &error) { qWarning() << error; })
        .wait();
}

int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    std::cout << "\nqtstrava-cli  Copyright (C) 2020  Dmitriy Purgin <dpurgin@gmail.com>";
    std::cout
        << "\n\nThis program comes with ABSOLUTELY NO WARRANTY. This is free software, and you are "
           "\nwelcome to redistribute it under certain conditions; See GNU General Public "
           "\nLicense v3 at https://www.gnu.org/licenses/ for details.";
    std::cout << "\n\nEnable qtstrava.network logging category for verbose output. See "
                 "\nhttps://doc.qt.io/qt-5/qloggingcategory.html#configuring-categories";

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
                    std::cout << "\n [3] createActivity";
                    std::cout << "\n [4] updateActivityById";
                    std::cout << "\n [5] createUpload";
                    std::cout << "\n [6] getUploadById";
                    std::cout << "\n\nEnter 0-6: ";
                    std::cin >> choice;
                } while (choice < 0 || choice > 6);

                static QVector<std::function<void(QtStrava::Client &)>>
                    functions{&getLoggedInAthlete,
                              &getLoggedInAthleteActivities,
                              &createActivity,
                              &updateActivityById,
                              &createUpload,
                              &getUploadById};

                if (choice > 0) {
                    functions[choice - 1](stravaClient);
                }
            } while (choice != 0);

            QTimer::singleShot(0, qApp, &QCoreApplication::quit);
        })
        .fail([]() { std::cerr << "\nUnable to obtain Strava authorization!"; });

    return app.exec();
}
