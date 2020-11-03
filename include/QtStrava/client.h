#pragma once

#include <QtStrava/global.h>

#include <QtCore/qobject.h>
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
    explicit Client(const QUrl &url, const QString &authorizationToken, QObject *parent = nullptr);
    ~Client();

    [[nodiscard]] QtPromise::QPromise<Model::DetailedAthlete> getLoggedInAthlete();
    [[nodiscard]] QtPromise::QPromise<QVector<Model::SummaryActivity>> getLoggedInAthleteActivities(
        std::optional<QDateTime> before,
        std::optional<QDateTime> after,
        int page = 1,
        int perPage = 30);

private:
    ClientPrivate *d_ptr{nullptr};
    Q_DECLARE_PRIVATE(Client)
};
} // namespace QtStrava
