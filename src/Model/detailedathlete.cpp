// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/detailedathlete.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const DetailedAthlete &athlete)
{
    QDebugStateSaver saver{dbg};
    dbg.nospace() << "DetailedAthlete[id=" << athlete.id() << ", firstName=" << athlete.firstName()
                  << ", lastName=" << athlete.lastName() << "]";
    return dbg;
}

} // namespace QtStrava::Model
