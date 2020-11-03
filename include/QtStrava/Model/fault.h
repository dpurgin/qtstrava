#pragma once

#include <QtStrava/Model/error.h>
#include <QtStrava/global.h>

#include <QtCore/qstring.h>
#include <QtCore/qvector.h>

class QDebug;

namespace QtStrava::Model {
class QTSTRAVA_EXPORT Fault
{
public:
    static constexpr auto JsonSchema = ":/schemas/Fault.schema.json";

    [[nodiscard]] QString message() const { return m_message; }
    void setMessage(const QString &message) { m_message = message; }

    [[nodiscard]] const QVector<Error> &errors() const { return m_errors; }
    void setErrors(const QVector<Error> &errors) { m_errors = errors; }

public:
    QString m_message;
    QVector<Error> m_errors;
};

extern QTSTRAVA_EXPORT QDebug operator<<(QDebug dbg, const Fault &fault);
} // namespace QtStrava::Model
