// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtStrava/global.h>

namespace QtStrava::Model {

/*! 
 * https://developers.strava.com/docs/reference/#api-models-UpdatableActivity
 */
class QTSTRAVA_EXPORT UpdatableActivity
{
public:
    [[nodiscard]] bool commute() const { return m_commute; }
    void setCommute(bool commute) { m_commute = commute; }

    [[nodiscard]] bool trainer() const { return m_trainer; }
    void setTrainer(bool trainer) { m_trainer = trainer; }

    [[nodiscard]] QString description() const { return m_description; }
    void setDescription(const QString &description) { m_description = description; }

    [[nodiscard]] QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    [[nodiscard]] ActivityType type() const { return m_type; }
    void setType(ActivityType type) { m_type = type; }

    [[nodiscard]] QString gearId() const { return m_gearId; }
    void setGearId(const QString &gearId) { m_gearId = gearId; }
    // Quote from https://developers.strava.com/docs/reference/#api-models-UpdatableActivity:
    //  ‘none’ clears gear from activity
    void clearGearId() { m_gearId = "none"; }

private:
    bool m_commute{false};
    bool m_trainer{false};
    QString m_description;
    QString m_name;
    ActivityType m_type{ActivityType::Other};
    QString m_gearId{"none"};
};

} // namespace QtStrava::Model
