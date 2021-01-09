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

#include "authorizationhandler.h"

#include <QDesktopServices>
#include <QSettings>

using namespace std::chrono_literals;

AuthorizationHandler::AuthorizationHandler(QObject *parent)
    : QObject{parent}, m_oauth2(&m_nam), m_clientId(restore("strava/clientId").toString()),
      m_clientSecret{restore("strava/clientSecret").toString()},
      m_accessToken{restore("strava/accessToken").toString()},
      m_refreshToken{restore("strava/refreshToken").toString()},
      m_expirationAt{restore("strava/expirationAt").toDateTime()}

{
    if (m_clientId.isEmpty()) {
        qFatal("Unable to restore strava/clientId from settings");
    }

    if (m_clientSecret.isEmpty()) {
        qFatal("Unable to restore strava/clientSecret from settings");
    }

    m_oauth2.setReplyHandler(new QOAuthHttpServerReplyHandler{61337, this});
    m_oauth2.setAuthorizationUrl(QUrl{"https://www.strava.com/oauth/authorize"});
    m_oauth2.setAccessTokenUrl(QUrl{"https://www.strava.com/api/v3/oauth/token"});
    m_oauth2.setClientIdentifier(m_clientId);
    m_oauth2.setScope("profile:read_all,activity:read_all,activity:write");
    m_oauth2.setRefreshToken(m_refreshToken);

    m_oauth2.setModifyParametersFunction(
        [this](QAbstractOAuth::Stage stage, QVariantMap *parameters) {
            if (stage == QAbstractOAuth::Stage::RequestingAccessToken
                || stage == QAbstractOAuth::Stage::RefreshingAccessToken) {
                parameters->insert("client_id", m_clientId);
                parameters->insert("client_secret", m_clientSecret);
            }

            qDebug() << "Stage:" << static_cast<int>(stage) << *parameters;
        });

    connect(&m_oauth2,
            &QOAuth2AuthorizationCodeFlow::error,
            [](const QString &error, const QString &errorDescription, const QUrl &uri) {
                qDebug() << "Error:" << error << errorDescription << uri;
            });

    connect(&m_oauth2,
            &QOAuth2AuthorizationCodeFlow::expirationAtChanged,
            [](const QDateTime &expiration) {
                qDebug() << "Expiration at:" << expiration;
                save("strava/expirationAt", expiration);
            });

    connect(&m_oauth2,
            &QOAuth2AuthorizationCodeFlow::refreshTokenChanged,
            [this](const QString &refreshToken) {
                qDebug() << "Refresh token:" << refreshToken;
                setRefreshToken(refreshToken);
                save("strava/refreshToken", refreshToken);
            });

    connect(&m_oauth2, &QOAuth2AuthorizationCodeFlow::tokenChanged, [this](const QString &token) {
        qDebug() << "Access token:" << token;
        setAccessToken(token);
        save("strava/accessToken", token);
    });

    connect(&m_oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, [](const QUrl &url) {
        qDebug() << "Authorize with browser: " << url;
        QDesktopServices::openUrl(url);
    });

    connect(&m_oauth2, &QOAuth2AuthorizationCodeFlow::granted, []() { qDebug() << "Granted"; });
    connect(&m_oauth2, &QOAuth2AuthorizationCodeFlow::granted, this, &AuthorizationHandler::granted);
}

QtPromise::QPromise<void> AuthorizationHandler::grant()
{
    auto grantPromise = QtPromise::connect(this, &AuthorizationHandler::granted).timeout(10s);

    if (m_expirationAt.isValid() && m_expirationAt <= QDateTime::currentDateTime()
        && !m_refreshToken.isEmpty()) {
        qDebug() << "Current access token expired, refreshing...";
        m_oauth2.refreshAccessToken();
    } else if (QDateTime::currentDateTime() < m_expirationAt && !m_accessToken.isEmpty()) {
        qDebug() << "Reusing current access token...";
        emit granted();
    } else {
        qDebug() << "Requesting new authorization...";
        m_oauth2.grant();
    }

    return grantPromise;
}

void AuthorizationHandler::setAccessToken(const QString &accessToken)
{
    if (m_accessToken != accessToken) {
        m_accessToken = accessToken;
        emit accessTokenChanged();
    }
}

void AuthorizationHandler::setRefreshToken(const QString &refreshToken)
{
    if (m_refreshToken != refreshToken) {
        m_refreshToken = refreshToken;
        emit refreshTokenChanged();
    }
}

void AuthorizationHandler::save(const QString &key, const QVariant &value)
{
    QSettings settings{"org.dpurgin", "qtstrava-cli"};
    settings.setValue(key, value);
}

QVariant AuthorizationHandler::restore(const QString &key)
{
    QSettings settings{"org.dpurgin", "qtstrava-cli"};
    return settings.value(key);
}
