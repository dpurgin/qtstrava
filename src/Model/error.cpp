#include <QtStrava/Model/error.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const Error &stravaError)
{
    QDebugStateSaver saver{dbg};

    dbg.nospace() << "StravaError[code=" << stravaError.code() << ", field=" << stravaError.field()
                  << ", resource=" << stravaError.resource() << "]";

    return dbg;
}
} // namespace QtStrava::Model
