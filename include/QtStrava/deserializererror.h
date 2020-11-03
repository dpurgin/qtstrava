#pragma once

#include <QtStrava/global.h>

#include <QtCore/qstring.h>

class QDebug;

namespace QtStrava {
class QTSTRAVA_EXPORT DeserializerError
{
public:
    DeserializerError(QString errorText) : m_errorText{errorText} {}

    QString errorText() const { return m_errorText; }

private:
    QString m_errorText;
};

extern QTSTRAVA_EXPORT QDebug operator<<(QDebug dbg, const DeserializerError &error);
} // namespace QtStrava
