// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

class QDebug;

namespace QtStrava::Model {

// See https://developers.strava.com/docs/reference/#api-models-SummaryClub
class QTSTRAVA_EXPORT SummaryClub
{
public:
    [[nodiscard]] quint64 id() const;
    void setId(quint64 id);

    [[nodiscard]] QString name() const;
    void setName(const QString &name);

private:
    quint64 m_id{0};
    QString m_name;
};

extern QTSTRAVA_EXPORT QDebug operator<<(QDebug dbg, const SummaryClub &summaryClub);
} // namespace QtStrava::Model
