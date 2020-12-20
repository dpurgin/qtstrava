// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/error.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const Error &stravaError)
{
    QDebugStateSaver saver{dbg};

    dbg.nospace() << "Error[code=" << stravaError.code() << ", field=" << stravaError.field()
                  << ", resource=" << stravaError.resource() << "]";

    return dbg;
}
} // namespace QtStrava::Model
