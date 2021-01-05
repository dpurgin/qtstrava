// QtStrava - A Qt wrapper for Strava API
// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.

#pragma once

#include <QtCore/qbytearray.h>
#include <QtCore/qexception.h>
#include <QtCore/qfile.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

#include <nonstd/expected.hpp>

#include <QtStrava/Model/detailedactivity.h>
#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/error.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/Model/upload.h>
#include <QtStrava/deserializererror.h>

#include <nlohmann/json-qt.hpp>
#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>

namespace QtStrava {
inline void from_json(const nlohmann::json &j, ResourceState &resourceState)
{
    resourceState = static_cast<ResourceState>(j.get<int>());
}

inline void from_json(const nlohmann::json &j, ActivityType &activityType)
{
    activityType = toActivityType(j.get<QString>()).value_or(ActivityType::Other);
}
} // namespace QtStrava

namespace QtStrava::Model {

inline void from_json(const nlohmann::json &j, MetaAthlete &athlete)
{
    athlete.setId(j["id"].get<quint64>());
    athlete.setResourceState(j["resource_state"].get<ResourceState>());
}

inline void from_json(const nlohmann::json &j, Error &error)
{
    error.setCode(j["code"].get<QString>());
    error.setField(j["field"].get<QString>());
    error.setResource(j["resource"].get<QString>());
}

inline void from_json(const nlohmann::json &j, Fault &fault)
{
    fault.setMessage(j.at("message").get<QString>());
    fault.setErrors(j.at("errors").get<QVector<Error>>());
}

inline void from_json(const nlohmann::json &j, SummaryActivity &activity)
{
    activity.setId(j["id"].get<quint64>());
    activity.setName(j["name"].get<QString>());
    activity.setDistance(j["distance"].get<qreal>());
    activity.setMovingTime(j["moving_time"].get<int>());
    activity.setActivityType(j["type"].get<ActivityType>());
    activity.setStartDate(j["start_date"].get<QDateTime>());
    activity.setStartDateLocal(j["start_date_local"].get<QDateTime>());
    activity.setGearId(j["gear_id"].is_null() ? QString{} : j["gear_id"].get<QString>());
}

inline void from_json(const nlohmann::json &j, SummaryClub &club) {}

inline void from_json(const nlohmann::json &j, SummaryGear &gear)
{
    gear.setId(j["id"].get<QString>());
    gear.setName(j["name"].get<QString>());
    gear.setPrimary(j["primary"].get<bool>());
    gear.setResourceState(j["resource_state"].get<ResourceState>());
    gear.setDistance(j["distance"].get<qreal>());
}

inline void from_json(const nlohmann::json &j, DetailedAthlete &detailedAthlete)
{
    detailedAthlete.setId(j["id"].get<quint64>());
    detailedAthlete.setFirstName(j["firstname"].get<QString>());
    detailedAthlete.setLastName(j["lastname"].get<QString>());
    detailedAthlete.setResourceState(j["resource_state"].get<ResourceState>());
    detailedAthlete.setProfileMedium(j["profile_medium"].get<QUrl>());
    detailedAthlete.setProfile(j["profile"].get<QUrl>());
    detailedAthlete.setCity(j["city"].get<QString>());
    detailedAthlete.setState(j["state"].get<QString>());
    detailedAthlete.setCountry(j["country"].get<QString>());
    detailedAthlete.setSex(j["sex"].get<QString>());
    detailedAthlete.setSummit(j["summit"].get<bool>());
    detailedAthlete.setCreatedAt(j["created_at"].get<QDateTime>());
    detailedAthlete.setUpdatedAt(j["updated_at"].get<QDateTime>());
    detailedAthlete.setFollowerCount(j["follower_count"].get<int>());
    detailedAthlete.setFriendCount(j["friend_count"].get<int>());
    detailedAthlete.setMeasurementPreference(j["measurement_preference"].get<QString>());
    detailedAthlete.setFtp(j["ftp"].get<int>());
    detailedAthlete.setWeight(j["weight"].get<qreal>());
    detailedAthlete.setClubs(j["clubs"].get<QVector<SummaryClub>>());
    detailedAthlete.setBikes(j["bikes"].get<QVector<SummaryGear>>());
    detailedAthlete.setShoes(j["shoes"].get<QVector<SummaryGear>>());
}

inline void from_json(const nlohmann::json &j, DetailedActivity &detailedActivity)
{
    detailedActivity.setAthlete(j["athlete"].get<MetaAthlete>());
    detailedActivity.setCommute(j["commute"].get<bool>());
    detailedActivity.setDistance(j["distance"].get<qreal>());
    detailedActivity.setElapsedTime(std::chrono::seconds{j["elapsed_time"].get<int>()});
    detailedActivity.setId(j["id"].get<quint64>());
    detailedActivity.setMovingTime(std::chrono::seconds{j["moving_time"].get<int>()});
    detailedActivity.setName(j["name"].get<QString>());
    detailedActivity.setResourceState(j["resource_state"].get<ResourceState>());
    detailedActivity.setTrainer(j["trainer"].get<bool>());
    detailedActivity.setType(j["type"].get<ActivityType>());
}

inline void from_json(const nlohmann::json &j, Upload &upload)
{
    upload.setId(j["id"].get<quint64>());
    upload.setIdStr(j["id_str"].get<QString>());

    if (!j["external_id"].is_null()) {
        upload.setExternalId(j["external_id"].get<QString>());
    }

    if (!j["error"].is_null()) {
        upload.setError(j["error"].get<QString>());
    }

    upload.setStatus(j["status"].get<QString>());

    if (!j["activity_id"].is_null()) {
        upload.setActivityId(j["activity_id"].get<quint64>());
    }
}
} // namespace QtStrava::Model

namespace QtStrava::Private {

template<typename T>
struct ExtractModel
{
    using Type = T;
};

template<typename T>
struct ExtractModel<QVector<T>>
{
    using Type = T;
};

template<typename T>
struct IsVectorOfT : std::false_type
{};

template<typename T>
struct IsVectorOfT<QVector<T>> : std::true_type
{};

template<typename T, typename Model = typename ExtractModel<T>::Type>
nonstd::expected<T, DeserializerError> deserialize(const QByteArray &data)
{
    try {
        auto doc = nlohmann::json::parse(std::cbegin(data), std::cend(data));

        QFile schemaFile{Model::JsonSchema};

        if (!schemaFile.open(QIODevice::ReadOnly)) {
            return nonstd::make_unexpected(DeserializerError{data,
                                                             QString{"Unable to open schema %1: %2"}
                                                                 .arg(Model::JsonSchema)
                                                                 .arg(schemaFile.errorString())});
        }

        auto schemaData = schemaFile.readAll();

        auto schemaDoc = nlohmann::json::parse(std::cbegin(schemaData), std::cend(schemaData));

        if constexpr (IsVectorOfT<T>::value) {
            schemaDoc.erase("$schema");

            nlohmann::json rootSchema{{"$schema", "http://json-schema.org/draft-07/schema"},
                                      {"type", "array"},
                                      {"items", schemaDoc}};

            if (schemaDoc.contains("definitions")) {
                rootSchema["definitions"] = schemaDoc["definitions"];
                schemaDoc.erase("definitions");
            }

            nlohmann::json_schema::json_validator validator{rootSchema};
            validator.validate(doc);
        } else {
            nlohmann::json_schema::json_validator validator{schemaDoc};
            validator.validate(doc);
        }

        return doc.get<T>();
    } catch (std::exception &e) {
        return nonstd::make_unexpected(DeserializerError{data, e.what()});
    }
}

} // namespace QtStrava::Private
