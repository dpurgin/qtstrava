// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/metaathlete.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const MetaAthlete &metaAthlete)
{
    QDebugStateSaver stateSaver{dbg};
    dbg.nospace() << "MetaAthlete[id=" << metaAthlete.id() << "]";
    return dbg;
}
} // namespace QtStrava::Model
