// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#include <QtStrava/global.h>

namespace QtStrava {
namespace Private {
Q_LOGGING_CATEGORY(network, "qtstrava.network", QtWarningMsg);
}

QString toString(ActivityType activity)
{
    switch (activity) {
    case ActivityType::AlpineSki:
        return "AlpineSki";
    case ActivityType::BackcountrySki:
        return "BackcountrySki";
    case ActivityType::Canoeing:
        return "Canoeing";
    case ActivityType::Crossfit:
        return "Crossfit";
    case ActivityType::EBikeRide:
        return "EBikeRide";
    case ActivityType::Elliptical:
        return "Elliptical";
    case ActivityType::Golf:
        return "Golf";
    case ActivityType::Handcycle:
        return "Handcycle";
    case ActivityType::Hike:
        return "Hike";
    case ActivityType::IceSkate:
        return "IceSkate";
    case ActivityType::InlineSkate:
        return "InlineSkate";
    case ActivityType::Kayaking:
        return "Kayaking";
    case ActivityType::Kitesurf:
        return "Kitesurf";
    case ActivityType::NordicSki:
        return "NordicSki";
    case ActivityType::Ride:
        return "Ride";
    case ActivityType::RockClimbing:
        return "RockClimbing";
    case ActivityType::RollerSki:
        return "RollerSki";
    case ActivityType::Rowing:
        return "Rowing";
    case ActivityType::Run:
        return "Run";
    case ActivityType::Sail:
        return "Sail";
    case ActivityType::Skateboard:
        return "Skateboard";
    case ActivityType::Snowboard:
        return "Snowboard";
    case ActivityType::Snowshoe:
        return "Snowshoe";
    case ActivityType::Soccer:
        return "Soccer";
    case ActivityType::StairStepper:
        return "StairStepper";
    case ActivityType::StandUpPaddling:
        return "StandUpPaddling";
    case ActivityType::Surfing:
        return "Surfing";
    case ActivityType::Swim:
        return "Swim";
    case ActivityType::Velomobile:
        return "Velomobile";
    case ActivityType::VirtualRide:
        return "VirtualRide";
    case ActivityType::VirtualRun:
        return "VirtualRun";
    case ActivityType::Walk:
        return "Walk";
    case ActivityType::WeightTraining:
        return "WeightTraining";
    case ActivityType::Wheelchair:
        return "Wheelchair";
    case ActivityType::Windsurf:
        return "Windsurf";
    case ActivityType::Workout:
        return "Workout";
    case ActivityType::Yoga:
        return "Yoga";

    case ActivityType::Other:
        return "Other";
    }
}

std::optional<ActivityType> toActivityType(const QString &str)
{
    static QHash<QString, ActivityType> activityTypes = {{
                                                             "AlpineSki",
                                                             ActivityType::AlpineSki,
                                                         },
                                                         {
                                                             "BackcountrySki",
                                                             ActivityType::BackcountrySki,
                                                         },
                                                         {
                                                             "Canoeing",
                                                             ActivityType::Canoeing,
                                                         },
                                                         {
                                                             "Crossfit",
                                                             ActivityType::Crossfit,
                                                         },
                                                         {
                                                             "EBikeRide",
                                                             ActivityType::EBikeRide,
                                                         },
                                                         {
                                                             "Elliptical",
                                                             ActivityType::Elliptical,
                                                         },
                                                         {
                                                             "Golf",
                                                             ActivityType::Golf,
                                                         },
                                                         {
                                                             "Handcycle",
                                                             ActivityType::Handcycle,
                                                         },
                                                         {
                                                             "Hike",
                                                             ActivityType::Hike,
                                                         },
                                                         {
                                                             "IceSkate",
                                                             ActivityType::IceSkate,
                                                         },
                                                         {
                                                             "InlineSkate",
                                                             ActivityType::InlineSkate,
                                                         },
                                                         {
                                                             "Kayaking",
                                                             ActivityType::Kayaking,
                                                         },
                                                         {
                                                             "Kitesurf",
                                                             ActivityType::Kitesurf,
                                                         },
                                                         {
                                                             "NordicSki",
                                                             ActivityType::NordicSki,
                                                         },
                                                         {
                                                             "Ride",
                                                             ActivityType::Ride,
                                                         },
                                                         {
                                                             "RockClimbing",
                                                             ActivityType::RockClimbing,
                                                         },
                                                         {
                                                             "RollerSki",
                                                             ActivityType::RollerSki,
                                                         },
                                                         {
                                                             "Rowing",
                                                             ActivityType::Rowing,
                                                         },
                                                         {
                                                             "Run",
                                                             ActivityType::Run,
                                                         },
                                                         {
                                                             "Sail",
                                                             ActivityType::Sail,
                                                         },
                                                         {
                                                             "Skateboard",
                                                             ActivityType::Skateboard,
                                                         },
                                                         {
                                                             "Snowboard",
                                                             ActivityType::Snowboard,
                                                         },
                                                         {
                                                             "Snowshoe",
                                                             ActivityType::Snowshoe,
                                                         },
                                                         {
                                                             "Soccer",
                                                             ActivityType::Soccer,
                                                         },
                                                         {
                                                             "StairStepper",
                                                             ActivityType::StairStepper,
                                                         },
                                                         {
                                                             "StandUpPaddling",
                                                             ActivityType::StandUpPaddling,
                                                         },
                                                         {
                                                             "Surfing",
                                                             ActivityType::Surfing,
                                                         },
                                                         {
                                                             "Swim",
                                                             ActivityType::Swim,
                                                         },
                                                         {
                                                             "Velomobile",
                                                             ActivityType::Velomobile,
                                                         },
                                                         {
                                                             "VirtualRide",
                                                             ActivityType::VirtualRide,
                                                         },
                                                         {
                                                             "VirtualRun",
                                                             ActivityType::VirtualRun,
                                                         },
                                                         {
                                                             "Walk",
                                                             ActivityType::Walk,
                                                         },
                                                         {
                                                             "WeightTraining",
                                                             ActivityType::WeightTraining,
                                                         },
                                                         {
                                                             "Wheelchair",
                                                             ActivityType::Wheelchair,
                                                         },
                                                         {
                                                             "Windsurf",
                                                             ActivityType::Windsurf,
                                                         },
                                                         {
                                                             "Workout",
                                                             ActivityType::Workout,
                                                         },
                                                         {
                                                             "Yoga",
                                                             ActivityType::Yoga,
                                                         }};
    return activityTypes.contains(str) ? std::make_optional(activityTypes.value(str))
                                       : std::nullopt;
}

QString toString(DataType dataType)
{
    switch (dataType) {
    case DataType::Fit:
        return "fit";
    case DataType::FitGz:
        return "fit.gz";
    case DataType::Gpx:
        return "gpx";
    case DataType::GpxGz:
        return "gpx.gz";
    case DataType::Tcx:
        return "tcx";
    case DataType::TcxGz:
        return "tcx.gz";
    }
}

std::optional<DataType> toDataType(const QString &str)
{
    static QHash<QString, DataType> dataTypes = {{"fit", DataType::Fit},
                                                 {"fit.gz", DataType::FitGz},
                                                 {"gpx", DataType::Gpx},
                                                 {"gpx.gz", DataType::GpxGz},
                                                 {"tcx", DataType::Tcx},
                                                 {"tcx.gz", DataType::TcxGz}};
    return dataTypes.contains(str) ? std::make_optional(dataTypes.value(str)) : std::nullopt;
}

} // namespace QtStrava
