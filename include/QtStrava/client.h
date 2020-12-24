// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtPromise>

#include <chrono>
#include <optional>

class QFile;

namespace QtStrava {

namespace Model {
class DetailedActivity;
class DetailedAthlete;
class ClientPrivate;
class SummaryActivity;
class UpdatableActivity;
class Upload;
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

    /*!
     * Possible rejection reasons:
     *   - QtStrava::NetworkError
     *   - QtStrava::DeserializerError
     *   - QtStrava::Model::Fault     
     *   
     * Strava API Source: https://developers.strava.com/docs/reference/#api-Activities-createActivity
     */
    [[nodiscard]] QtPromise::QPromise<Model::DetailedActivity> createActivity(
        const QString &name,
        ActivityType type,
        const QDateTime &startDateLocal,
        std::chrono::seconds elapsedTime,
        std::optional<QString> description,
        std::optional<qreal> distance,
        std::optional<bool> trainer,
        std::optional<bool> commute);

    /*!
     * Possible rejection reasons:
     *   - QtStrava::NetworkError
     *   - QtStrava::DeserializerError
     *   - QtStrava::Model::Fault     
     *   
     * Strava API Source: https://developers.strava.com/docs/reference/#api-Activities-updateActivityById
     */
    [[nodiscard]] QtPromise::QPromise<Model::DetailedActivity> updateActivityById(
        quint64 id, const Model::UpdatableActivity &updatableActivity);

    /*!
     * Possible rejection reasons:
     *   - QtStrava::NetworkError
     *   - QtStrava::DeserializerError
     *   - QtStrava::Model::Fault     
     *   
     * Strava API Source: https://developers.strava.com/docs/reference/#api-Uploads-createUpload
     */
    [[nodiscard]] QtPromise::QPromise<Model::Upload> createUpload(QFile *file,
                                                                  const QString &name,
                                                                  const QString &description,
                                                                  bool trainer,
                                                                  bool commute,
                                                                  DataType dataType,
                                                                  const QString &externalId);

Q_SIGNALS:
    void accessTokenChanged();

private:
    ClientPrivate *d_ptr{nullptr};
    Q_DECLARE_PRIVATE(Client)
};
} // namespace QtStrava
