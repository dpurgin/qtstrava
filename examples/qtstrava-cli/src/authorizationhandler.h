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
