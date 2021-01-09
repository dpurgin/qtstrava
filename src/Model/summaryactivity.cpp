// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/summaryactivity.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {

quint64 SummaryActivity::id() const
{
    return m_id;
}

void SummaryActivity::setId(quint64 id)
{
    m_id = id;
}

QString SummaryActivity::name() const
{
    return m_name;
}

void SummaryActivity::setName(const QString &name)
{
    m_name = name;
}

qreal SummaryActivity::distance() const
{
    return m_distance;
}

void SummaryActivity::setDistance(qreal distance)
{
    m_distance = distance;
}

int SummaryActivity::movingTime() const
{
    return m_movingTime;
}

void SummaryActivity::setMovingTime(int movingTime)
{
    m_movingTime = movingTime;
}

ActivityType SummaryActivity::activityType() const
{
    return m_activityType;
}

void SummaryActivity::setActivityType(ActivityType activityType)
{
    m_activityType = activityType;
}

QDateTime SummaryActivity::startDate() const
{
    return m_startDate;
}

void SummaryActivity::setStartDate(const QDateTime &startDate)
{
    m_startDate = startDate;
}

QDateTime SummaryActivity::startDateLocal() const
{
    return m_startDateLocal;
}

void SummaryActivity::setStartDateLocal(const QDateTime &startDateLocal)
{
    m_startDateLocal = startDateLocal;
}

QString SummaryActivity::gearId() const
{
    return m_gearId;
}

void SummaryActivity::setGearId(const QString &gearId)
{
    m_gearId = gearId;
}

QDebug operator<<(QDebug dbg, const SummaryActivity &summaryActivity)
{
    QDebugStateSaver saver{dbg};
    dbg.nospace() << "SummaryActivity[id=" << summaryActivity.id()
                  << ", name=" << summaryActivity.name() << "]";
    return dbg;
}
} // namespace QtStrava::Model
