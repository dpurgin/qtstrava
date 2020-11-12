// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

#include <QtCore/qdatetime.h>
#include <QtCore/qstring.h>

class QDebug;

namespace QtStrava::Model {
class QTSTRAVA_EXPORT SummaryActivity
{
public:
    static constexpr auto JsonSchema{":/schemas/SummaryActivity.schema.json"};

    long id() const;
    void setId(long id);

    QString name() const;
    void setName(const QString &name);

    qreal distance() const;
    void setDistance(qreal distance);

    int movingTime() const;
    void setMovingTime(int movingTime);

    ActivityType activityType() const;
    void setActivityType(ActivityType activityType);

    QDateTime startDate() const;
    void setStartDate(const QDateTime &startDate);

    QDateTime startDateLocal() const;
    void setStartDateLocal(const QDateTime &startDateLocal);

    QString gearId() const;
    void setGearId(const QString &gearId);

private:
    long m_id{-1};
    QString m_name;
    qreal m_distance{0};
    int m_movingTime{0};
    ActivityType m_activityType;
    QDateTime m_startDate;
    QDateTime m_startDateLocal;
    QString m_gearId;
};

extern QTSTRAVA_EXPORT QDebug operator<<(QDebug dbg, const SummaryActivity &summaryActivity);
} // namespace QtStrava::Model
