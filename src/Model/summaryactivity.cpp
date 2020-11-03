#include <QtStrava/Model/summaryactivity.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {

long SummaryActivity::id() const
{
    return m_id;
}

void SummaryActivity::setId(long id)
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

bool SummaryActivity::trainer() const
{
    return m_trainer;
}

void SummaryActivity::setTrainer(bool trainer)
{
    m_trainer = trainer;
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
    dbg.nospace() << "StravaSummaryActivity[id=" << summaryActivity.id()
                  << ", name=" << summaryActivity.name() << "]";
    return dbg;
}
} // namespace QtStrava::Model
