#include <QtStrava/deserializererror.h>

#include <QtCore/qdebug.h>

namespace QtStrava {
QDebug operator<<(QDebug dbg, const DeserializerError &deserializerError)
{
    return dbg.nospace() << "DeserializerError[" << deserializerError.errorText() << "]";
}
} // namespace QtStrava
