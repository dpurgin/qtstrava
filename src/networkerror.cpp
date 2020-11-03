#include <QtStrava/networkerror.h>

#include <QtCore/qdebug.h>

namespace QtStrava {
QDebug operator<<(QDebug dbg, const NetworkError &networkError)
{
    return dbg.nospace() << "NetworkError[" << networkError.errorText() << "]";
}
} // namespace QtStrava
