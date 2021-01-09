// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/detailedactivity.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const DetailedActivity &activity)
{
    QDebugStateSaver saver{dbg};
    dbg.nospace() << "DetailedActivity[id=" << activity.id() << ", name=" << activity.name() << "]";
    return dbg;
}
} // namespace QtStrava::Model
