// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/networkerror.h>

#include <QtCore/qdebug.h>

namespace QtStrava {
QDebug operator<<(QDebug dbg, const NetworkError &networkError)
{
    return dbg.nospace() << "NetworkError[" << networkError.errorText() << "]";
}
} // namespace QtStrava
