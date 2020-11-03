#include <QtStrava/Model/fault.h>

#include <QtCore/qdebug.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const Fault &fault)
{
    QDebugStateSaver saver{dbg};

    dbg.nospace() << "StravaFault[message=" << fault.message() << ", errors=[";

    if (fault.errors().isEmpty()) {
        dbg << "no items";
    } else {
        dbg << fault.errors().first();

        if (fault.errors().size() > 1) {
            dbg << " and " << fault.errors().size() - 1 << " other";
        }
    }

    dbg << "]";

    return dbg;
}
} // namespace QtStrava::Model
