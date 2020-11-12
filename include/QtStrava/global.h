#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/qloggingcategory.h>

#if defined(QTSTRAVA_LIBRARY)
#define QTSTRAVA_EXPORT Q_DECL_EXPORT
#else
#define QTSTRAVA_EXPORT Q_DECL_IMPORT
#endif

namespace QtStrava::Private {
Q_DECLARE_LOGGING_CATEGORY(network);
}

namespace QtStrava {

enum class ActivityType {
    Ride,
    VirtualRide,
    EBikeRide,

    Other
};

// See "resource_state" in https://developers.strava.com/docs/reference/#api-models-DetailedAthlete
enum class ResourceState {
    Unknown,

    Meta,
    Summary,
    Detail
};
}
