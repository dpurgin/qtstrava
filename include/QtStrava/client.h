// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtPromise>

#include <optional>

namespace QtStrava {

namespace Model {
class DetailedAthlete;
class ClientPrivate;
class SummaryActivity;
} // namespace Model

class ClientPrivate;

class QTSTRAVA_EXPORT Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(const QUrl &url = QUrl{"https://www.strava.com/api/v3"},
                    QObject *parent = nullptr);
    ~Client() override;

    [[nodiscard]] QString accessToken() const;
    void setAccessToken(const QString &accessToken);

    // https://developers.strava.com/docs/reference/#api-Athletes-getLoggedInAthlete
    [[nodiscard]] QtPromise::QPromise<Model::DetailedAthlete> getLoggedInAthlete();

    /*!
     * Possible rejection reasons:
     *   - QtStrava::NetworkError
     *   - QtStrava::DeserializerError
     *   - QtStrava::Model::Fault     
     *
     * Strava API Source: https://developers.strava.com/docs/reference/#api-Activities-getLoggedInAthleteActivities
     */
    [[nodiscard]] QtPromise::QPromise<QVector<Model::SummaryActivity>> getLoggedInAthleteActivities(
        std::optional<QDateTime> before,
        std::optional<QDateTime> after,
        int page = 1,
        int perPage = 30);

Q_SIGNALS:
    void accessTokenChanged();

private:
    ClientPrivate *d_ptr{nullptr};
    Q_DECLARE_PRIVATE(Client)
};
} // namespace QtStrava
