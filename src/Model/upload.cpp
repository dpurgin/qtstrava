// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/Model/upload.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const Upload &upload)
{
    QDebugStateSaver saver{dbg};
    dbg.nospace() << "Upload[id=" << upload.id() << ", status=" << upload.status()
                  << ", error=" << upload.error() << "]";
    return dbg;
}
} // namespace QtStrava::Model
