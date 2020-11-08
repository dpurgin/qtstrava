// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/deserializererror.h>

#include <QtCore/qdebug.h>

namespace QtStrava {
QDebug operator<<(QDebug dbg, const DeserializerError &deserializerError)
{
    return dbg.nospace() << "DeserializerError[" << deserializerError.errorText() << "]";
}
} // namespace QtStrava
