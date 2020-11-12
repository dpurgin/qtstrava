// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/client.h>

#include "jsondeserializer_p.h"

#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/deserializererror.h>
#include <QtStrava/networkerror.h>

#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkrequest.h>

static void initResources()
{
    Q_INIT_RESOURCE(qtstrava);
}
Q_CONSTRUCTOR_FUNCTION(initResources)

namespace QtStrava {

template<typename Reject>
inline void handleNetworkError(QNetworkReply *reply, const Reject &reject)
{
    Q_ASSERT(reply->error() != QNetworkReply::NoError);

    QByteArray data = reply->readAll();
    qCDebug(Private::network) << "Network error received:" << reply->errorString() << data;

    if (data.isEmpty()) {
        reject(NetworkError{reply->errorString()});
    } else {
        auto fault = Private::deserialize<Model::Fault>(data);

        if (fault.has_value()) {
            reject(*fault);
        } else {
            reject(fault.error());
        }
    }
}

template<typename ExpectedModel, typename Resolve, typename Reject>
inline void handleNetworkSuccess(QNetworkReply *reply, const Resolve &resolve, const Reject &reject)
{
    Q_ASSERT(reply->error() == QNetworkReply::NoError);

    QByteArray data = reply->readAll();

    qCDebug(Private::network).noquote() << "Reply received:" << data;

    auto model = Private::deserialize<ExpectedModel>(data);

    if (model.has_value()) {
        resolve(*model);
    } else {
        reject(model.error());
    }
}

template<typename ExpectedModel, typename Resolve, typename Reject>
inline auto networkReplyHandler(QNetworkReply *reply, const Resolve &resolve, const Reject &reject)
{
    return [reply, resolve, reject]() {
        if (reply->error() != QNetworkReply::NoError) {
            handleNetworkError(reply, reject);
        } else {
            handleNetworkSuccess<ExpectedModel>(reply, resolve, reject);
        }

        reply->deleteLater();
    };
}

class ClientPrivate
{
    friend class Client;

    ClientPrivate(const QUrl &server) : m_server{server} {}

    [[nodiscard]] QNetworkRequest createRequest(const QString &endPoint,
                                                const QVariantMap &parameters);

    template<typename ExpectedModel, typename Resolve, typename Reject>
    void get(const QString &endPoint,
             const QVariantMap &parameters,
             const Resolve &resolve,
             const Reject &reject);

    QNetworkAccessManager m_nam;
    QUrl m_server;
    QString m_accessToken;
    QByteArray m_authorizationHeaderValue;
};

QNetworkRequest ClientPrivate::createRequest(const QString &endPoint, const QVariantMap &parameters)
{
    QUrl url{m_server};
    url.setPath(m_server.path() + endPoint);

    QStringList queryItems;

    for (auto cit = std::cbegin(parameters); cit != std::cend(parameters); ++cit) {
        if (cit.value().isNull()) {
            continue;
        }

        queryItems << QString{"%1=%2"}.arg(cit.key()).arg(cit.value().toString());
    }

    url.setQuery(queryItems.join('&'));

    QNetworkRequest request{url};
    request.setRawHeader("Authorization", m_authorizationHeaderValue);

    return request;
}

template<typename ExpectedModel, typename Resolve, typename Reject>
void ClientPrivate::get(const QString &endPoint,
                        const QVariantMap &parameters,
                        const Resolve &resolve,
                        const Reject &reject)
{
    QNetworkRequest request = createRequest(endPoint, parameters);

    qCDebug(Private::network) << "Requesting:" << request.url();

    QNetworkReply *reply = m_nam.get(request);

    QObject::connect(reply,
                     &QNetworkReply::finished,
                     networkReplyHandler<ExpectedModel>(reply, resolve, reject));
}

Client::Client(const QUrl &server, QObject *parent)
    : QObject{parent}, d_ptr{new ClientPrivate{server}}
{}

Client::~Client()
{
    delete d_ptr;
}

QString Client::accessToken() const
{
    Q_D(const Client);
    return d->m_accessToken;
}

void Client::setAccessToken(const QString &accessToken)
{
    Q_D(Client);

    if (d->m_accessToken != accessToken) {
        d->m_accessToken = accessToken;
        d->m_authorizationHeaderValue = QString{"Bearer %1"}.arg(accessToken).toLatin1();

        emit accessTokenChanged();
    }
}

QtPromise::QPromise<Model::DetailedAthlete> Client::getLoggedInAthlete()
{
    Q_D(Client);

    return QtPromise::QPromise<Model::DetailedAthlete>{[d](const auto &resolve, const auto &reject) {
        d->get<Model::DetailedAthlete>("/athlete", {}, resolve, reject);
    }};
}

QtPromise::QPromise<QVector<Model::SummaryActivity>> Client::getLoggedInAthleteActivities(
    std::optional<QDateTime> before, std::optional<QDateTime> after, int page, int perPage)
{
    Q_D(Client);

    return QtPromise::QPromise<QVector<Model::SummaryActivity>>{[=](const auto &resolve,
                                                                    const auto &reject) {
        QVariantMap parameters{{"before", before ? QVariant{*before} : QVariant{}},
                               {"after", after ? QVariant{*after} : QVariant{}},
                               {"page", page},
                               {"per_page", perPage}};

        d->get<QVector<Model::SummaryActivity>>("/athlete/activities", parameters, resolve, reject);
    }};
}
} // namespace QtStrava
