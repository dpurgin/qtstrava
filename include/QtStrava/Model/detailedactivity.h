// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

#include <QtStrava/Model/metaathlete.h>

class QDebug;

namespace QtStrava::Model {

/*! 
 * https://developers.strava.com/docs/reference/#api-models-DetailedActivity
 */
class QTSTRAVA_EXPORT DetailedActivity
{
public:
    static constexpr auto JsonSchema{":/schemas/DetailedActivity.schema.json"};

    [[nodiscard]] quint64 id() const { return m_id; }
    void setId(quint64 id) { m_id = id; }

    [[nodiscard]] ResourceState resourceState() const { return m_resourceState; }
    void setResourceState(ResourceState resourceState) { m_resourceState = resourceState; }

    [[nodiscard]] QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    [[nodiscard]] MetaAthlete athlete() const { return m_athlete; }
    void setAthlete(const MetaAthlete &athlete) { m_athlete = athlete; }

    [[nodiscard]] ActivityType type() const { return m_type; }
    void setType(ActivityType type) { m_type = type; }

    [[nodiscard]] qreal distance() const { return m_distance; }
    void setDistance(qreal distance) { m_distance = distance; }

    [[nodiscard]] std::chrono::seconds movingTime() const { return m_movingTime; }
    void setMovingTime(std::chrono::seconds movingTime) { m_movingTime = movingTime; }

    [[nodiscard]] std::chrono::seconds elapsedTime() const { return m_elapsedTime; }
    void setElapsedTime(std::chrono::seconds elapsedTime) { m_elapsedTime = elapsedTime; }

    [[nodiscard]] bool trainer() const { return m_trainer; }
    void setTrainer(bool trainer) { m_trainer = trainer; }

    [[nodiscard]] bool commute() const { return m_commute; }
    void setCommute(bool commute) { m_commute = commute; }

    [[nodiscard]] bool operator==(const DetailedActivity &other) const
    {
        return id() == other.id() &&                       //
               resourceState() == other.resourceState() && //
               name() == other.name() &&                   //
               athlete() == other.athlete() &&             //
               type() == other.type() &&                   //
               distance() == other.distance() &&           //
               movingTime() == other.movingTime() &&       //
               elapsedTime() == other.elapsedTime() &&     //
               trainer() == other.trainer() &&             //
               commute() == other.commute();
    }

private:
    quint64 m_id{0};
    ResourceState m_resourceState{ResourceState::Unknown};
    QString m_name;
    qreal m_distance{0.0};
    std::chrono::seconds m_movingTime{0};
    std::chrono::seconds m_elapsedTime{0};
    MetaAthlete m_athlete;
    ActivityType m_type{ActivityType::Other};
    bool m_trainer{false};
    bool m_commute{false};
};

QTSTRAVA_EXPORT QDebug operator<<(QDebug dbg, const DetailedActivity &activity);

} // namespace QtStrava::Model
