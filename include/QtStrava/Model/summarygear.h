// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {

// See https://developers.strava.com/docs/reference/#api-models-SummaryGear
class QTSTRAVA_EXPORT SummaryGear
{
public:
    [[nodiscard]] QString id() const { return m_id; }
    void setId(const QString &id) { m_id = id; }

    [[nodiscard]] ResourceState resourceState() const { return m_resourceState; }
    void setResourceState(const ResourceState &resourceState) { m_resourceState = resourceState; }

    [[nodiscard]] bool primary() const { return m_primary; }
    void setPrimary(bool primary) { m_primary = primary; }

    [[nodiscard]] QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    [[nodiscard]] qreal distance() const { return m_distance; }
    void setDistance(qreal distance) { m_distance = distance; }

private:
    QString m_id;
    ResourceState m_resourceState{ResourceState::Unknown};
    bool m_primary{false};
    QString m_name;
    qreal m_distance{0.0};
};

extern QTSTRAVA_EXPORT QDebug operator<<(QDebug dbg, const SummaryGear &summaryGear);
} // namespace QtStrava::Model
