// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/summaryclub.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {

quint64 SummaryClub::id() const
{
    return m_id;
}

void SummaryClub::setId(quint64 id)
{
    m_id = id;
}

QString SummaryClub::name() const
{
    return m_name;
}

void SummaryClub::setName(const QString &name)
{
    m_name = name;
}

QDebug operator<<(QDebug dbg, const SummaryClub &summaryClub)
{
    QDebugStateSaver saver{dbg};
    dbg.nospace() << "SummaryClub[id=" << summaryClub.id() << ", name=" << summaryClub.name()
                  << "]";
    return dbg;
}

} // namespace QtStrava::Model
