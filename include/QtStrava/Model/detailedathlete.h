#pragma once

#include <QtStrava/global.h>

#include <QtCore/qstring.h>

class QDebug;

namespace QtStrava::Model {
class QTSTRAVA_EXPORT DetailedAthlete
{
public:
    static constexpr auto JsonSchema{":/schemas/DetailedAthlete.schema.json"};

    [[nodiscard]] long id() const { return m_id; }
    void setId(long id) { m_id = id; }

    [[nodiscard]] QString firstName() const { return m_firstName; }
    void setFirstName(const QString &firstName) { m_firstName = firstName; }

    [[nodiscard]] QString lastName() const { return m_lastName; }
    void setLastName(const QString &lastName) { m_lastName = lastName; }

private:
    long m_id{-1};
    QString m_firstName;
    QString m_lastName;
};

extern QDebug QTSTRAVA_EXPORT operator<<(QDebug dbg, const DetailedAthlete &athlete);
} // namespace QtStrava::Model
