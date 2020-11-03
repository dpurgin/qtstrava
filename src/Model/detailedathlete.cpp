#include <QtStrava/Model/detailedathlete.h>

#include <QtCore/qdebug.h>

namespace QtStrava::Model {
QDebug operator<<(QDebug dbg, const DetailedAthlete &athlete)
{
    QDebugStateSaver saver{dbg};
    dbg.nospace() << "StravaDetailedAthlete[id=" << athlete.id()
                  << ", firstName=" << athlete.firstName() << ", lastName=" << athlete.lastName()
                  << "]";
    return dbg;
}
} // namespace QtStrava::Model
