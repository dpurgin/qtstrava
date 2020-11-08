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

#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <QtNetworkAuth>

class AuthorizationHandler : public QObject
{
    Q_OBJECT

public:
    AuthorizationHandler(QObject *parent = nullptr);

    [[nodiscard]] QString accessToken() const { return m_accessToken; }
    [[nodiscard]] QString refreshToken() const { return m_refreshToken; }

    void grant();

signals:
    void accessTokenChanged();
    void refreshTokenChanged();
    void granted();

private slots:
    void setAccessToken(const QString &accessToken);
    void setRefreshToken(const QString &refershToken);

private:
    static void save(const QString &key, const QVariant &value);
    [[nodiscard]] static QVariant restore(const QString &key);

private:
    QNetworkAccessManager m_nam;
    QOAuth2AuthorizationCodeFlow m_oauth2;

    QString m_clientId;
    QString m_clientSecret;
    QString m_accessToken;
    QString m_refreshToken;
    QDateTime m_expirationAt;
};
