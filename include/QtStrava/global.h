#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/qloggingcategory.h>

#include <optional>

#if defined(QTSTRAVA_LIBRARY) && defined(QTSTRAVA_LIBRARY_SHARED)
#define QTSTRAVA_EXPORT Q_DECL_EXPORT
#elif defined(QTSTRAVA_LIBRARY_SHARED)
#define QTSTRAVA_EXPORT Q_DECL_IMPORT
#else
#define QTSTRAVA_EXPORT
#endif

namespace QtStrava::Private {
Q_DECLARE_LOGGING_CATEGORY(network);
}

namespace QtStrava {

/*!
 * https://developers.strava.com/docs/reference/#api-models-ActivityType
 */
enum class ActivityType {
    AlpineSki,
    BackcountrySki,
    Canoeing,
    Crossfit,
    EBikeRide,
    Elliptical,
    Golf,
    Handcycle,
    Hike,
    IceSkate,
    InlineSkate,
    Kayaking,
    Kitesurf,
    NordicSki,
    Ride,
    RockClimbing,
    RollerSki,
    Rowing,
    Run,
    Sail,
    Skateboard,
    Snowboard,
    Snowshoe,
    Soccer,
    StairStepper,
    StandUpPaddling,
    Surfing,
    Swim,
    Velomobile,
    VirtualRide,
    VirtualRun,
    Walk,
    WeightTraining,
    Wheelchair,
    Windsurf,
    Workout,
    Yoga,

    Other
};

// See "resource_state" in https://developers.strava.com/docs/reference/#api-models-DetailedAthlete
enum class ResourceState {
    Unknown,

    Meta,
    Summary,
    Detail
};

// Upload data type in https://developers.strava.com/docs/reference/#api-Uploads-createUpload
enum class DataType { Fit, FitGz, Tcx, TcxGz, Gpx, GpxGz };

[[nodiscard]] extern QTSTRAVA_EXPORT QString toString(ActivityType activity);
[[nodiscard]] extern QTSTRAVA_EXPORT std::optional<ActivityType> toActivityType(const QString &str);

[[nodiscard]] extern QTSTRAVA_EXPORT QString toString(DataType dataType);
[[nodiscard]] extern QTSTRAVA_EXPORT std::optional<DataType> toDataType(const QString &str);
}
