// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/Model/summaryclub.h>
#include <QtStrava/Model/summarygear.h>
#include <QtStrava/global.h>

#include <QtCore/qdatetime.h>
#include <QtCore/qstring.h>
#include <QtCore/qurl.h>
#include <QtCore/qvector.h>

class QDebug;

namespace QtStrava::Model {

// See https://developers.strava.com/docs/reference/#api-models-DetailedAthlete
class QTSTRAVA_EXPORT DetailedAthlete
{
public:
    static constexpr auto JsonSchema{":/schemas/DetailedAthlete.schema.json"};

    [[nodiscard]] long id() const { return m_id; }
    void setId(long id) { m_id = id; }

    [[nodiscard]] QString firstName() const { return m_firstName; }
    void setFirstName(const QString &firstName) { m_firstName = firstName; }

    [[nodiscard]] QString lastName() const { return m_lastName; }
    void setLastName(const QString &lastName) { m_lastName = lastName; }

    [[nodiscard]] ResourceState resourceState() const { return m_resourceState; }
    void setResourceState(ResourceState resourceState) { m_resourceState = resourceState; }

    [[nodiscard]] QUrl profileMedium() const { return m_profileMedium; }
    void setProfileMedium(const QUrl &profileMedium) { m_profileMedium = profileMedium; }

    [[nodiscard]] QUrl profile() const { return m_profile; }
    void setProfile(const QUrl &profile) { m_profile = profile; }

    [[nodiscard]] QString city() const { return m_city; }
    void setCity(const QString &city) { m_city = city; }

    [[nodiscard]] QString state() const { return m_state; }
    void setState(const QString &state) { m_state = state; }

    [[nodiscard]] QString country() const { return m_country; }
    void setCountry(const QString &country) { m_country = country; }

    [[nodiscard]] QString sex() const { return m_sex; }
    void setSex(const QString &sex) { m_sex = sex; }

    [[nodiscard]] bool summit() const { return m_summit; }
    void setSummit(bool summit) { m_summit = summit; }

    [[nodiscard]] QDateTime createdAt() const { return m_createdAt; }
    void setCreatedAt(const QDateTime &createdAt) { m_createdAt = createdAt; }

    [[nodiscard]] QDateTime updatedAt() const { return m_updatedAt; }
    void setUpdatedAt(const QDateTime &updatedAt) { m_updatedAt = updatedAt; }

    [[nodiscard]] int followerCount() const { return m_followerCount; }
    void setFollowerCount(int followerCount) { m_followerCount = followerCount; }

    [[nodiscard]] int friendCount() const { return m_friendCount; }
    void setFriendCount(int friendCount) { m_friendCount = friendCount; }

    [[nodiscard]] QString measurementPreference() const { return m_measurementPreference; }
    void setMeasurementPreference(const QString &measurementPreference)
    {
        m_measurementPreference = measurementPreference;
    }

    [[nodiscard]] int ftp() const { return m_ftp; }
    void setFtp(int ftp) { m_ftp = ftp; }

    [[nodiscard]] qreal weight() const { return m_weight; }
    void setWeight(const qreal &weight) { m_weight = weight; }

    [[nodiscard]] const QVector<SummaryClub> &clubs() const { return m_clubs; }
    void setClubs(const QVector<SummaryClub> &clubs) { m_clubs = clubs; }

    [[nodiscard]] const QVector<SummaryGear> &bikes() const { return m_bikes; }
    void setBikes(const QVector<SummaryGear> &bikes) { m_bikes = bikes; }

    [[nodiscard]] const QVector<SummaryGear> &shoes() const { return m_shoes; }
    void setShoes(const QVector<SummaryGear> &shoes) { m_shoes = shoes; }

private:
    long m_id{-1};
    ResourceState m_resourceState;
    QString m_firstName;
    QString m_lastName;
    QUrl m_profileMedium;
    QUrl m_profile;
    QString m_city;
    QString m_state;
    QString m_country;
    QString m_sex;
    bool m_summit{false};
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
    int m_followerCount{0};
    int m_friendCount{0};
    QString m_measurementPreference;
    int m_ftp{0};
    qreal m_weight{0};
    QVector<SummaryClub> m_clubs;
    QVector<SummaryGear> m_bikes;
    QVector<SummaryGear> m_shoes;
};

extern QDebug QTSTRAVA_EXPORT operator<<(QDebug dbg, const DetailedAthlete &athlete);
} // namespace QtStrava::Model
