// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

namespace QtStrava::Model {

/*!
 * https://developers.strava.com/docs/reference/#api-models-Upload
 */
class QTSTRAVA_EXPORT Upload
{
public:
    static constexpr auto JsonSchema{":/schemas/Upload.schema.json"};

    quint64 id() const { return m_id; }
    void setId(quint64 id) { m_id = id; }

    QString idStr() const { return m_idStr; }
    void setIdStr(const QString &idStr) { m_idStr = idStr; }

    QString externalId() const { return m_externalId; }
    void setExternalId(const QString &externalId) { m_externalId = externalId; }

    QString error() const { return m_error; }
    void setError(const QString &error) { m_error = error; }

    QString status() const { return m_status; }
    void setStatus(const QString &status) { m_status = status; }

    quint64 activityId() const { return m_activityId; }
    void setActivityId(const quint64 &activityId) { m_activityId = activityId; }

private:
    quint64 m_id{0};
    QString m_idStr;
    QString m_externalId;
    QString m_error;
    QString m_status;
    quint64 m_activityId{0};
};
} // namespace QtStrava::Model
