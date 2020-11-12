// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/summarygear.h>

namespace QtStrava::Model {

QDebug operator<<(QDebug dbg, const QtStrava::Model::SummaryGear &summaryGear)
{
    QDebugStateSaver saver{dbg};
    dbg.nospace() << "SummaryGear[id=" << summaryGear.id() << ", name=" << summaryGear.name()
                  << "]";
    return dbg;
}
} // namespace QtStrava::Model
