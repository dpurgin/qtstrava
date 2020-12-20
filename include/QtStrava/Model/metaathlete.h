// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

class QDebug;

namespace QtStrava::Model {

class QTSTRAVA_EXPORT MetaAthlete
{
public:
    [[nodiscard]] quint64 id() const { return m_id; }
    void setId(quint64 id) { m_id = id; }

    [[nodiscard]] ResourceState resourceState() const { return m_resourceState; }
    void setResourceState(ResourceState resourceState) { m_resourceState = resourceState; }

    [[nodiscard]] bool operator==(const MetaAthlete &other) const
    {
        return id() == other.id() && resourceState() == other.resourceState();
    }

private:
    quint64 m_id{0};
    ResourceState m_resourceState{ResourceState::Unknown};
};

extern QTSTRAVA_EXPORT QDebug operator<<(QDebug dbg, const MetaAthlete &metaAthlete);

} // namespace QtStrava::Model
