#pragma once

#include <QtStrava/global.h>

#include <QtCore/qstring.h>

class QDebug;

namespace QtStrava::Model {
class QTSTRAVA_EXPORT Error
{
public:
    [[nodiscard]] QString code() const { return m_code; }
    void setCode(const QString &code) { m_code = code; }

    [[nodiscard]] QString field() const { return m_field; }
    void setField(const QString &field) { m_field = field; }

    [[nodiscard]] QString resource() const { return m_resource; }
    void setResource(const QString &resource) { m_resource = resource; }

private:
    QString m_code;
    QString m_field;
    QString m_resource;
};

QDebug QTSTRAVA_EXPORT operator<<(QDebug dbg, const Error &stravaError);
} // namespace QtStrava::Model
