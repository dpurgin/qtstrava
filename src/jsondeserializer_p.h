#pragma once

#include <QtCore/qbytearray.h>
#include <QtCore/qexception.h>
#include <QtCore/qfile.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>

#include <nonstd/expected.hpp>

#include <QtStrava/Model/detailedathlete.h>
#include <QtStrava/Model/error.h>
#include <QtStrava/Model/fault.h>
#include <QtStrava/Model/summaryactivity.h>
#include <QtStrava/deserializererror.h>

#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>

inline void from_json(const nlohmann::json &j, QDateTime &dateTime)
{
    dateTime = QDateTime::fromString(QString::fromStdString(j.get<std::string>()));
}

inline void from_json(const nlohmann::json &j, QString &string)
{
    string = QString::fromStdString(j.get<std::string>());
}

template<typename T>
inline void from_json(const nlohmann::json &j, QVector<T> &vector)
{
    for (const auto &item : j) {
        vector.push_back(item.get<T>());
    }
}

namespace QtStrava::Model {

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
    activity.setId(j["id"].get<long>());
    activity.setName(j["name"].get<QString>());
    activity.setDistance(j["distance"].get<qreal>());
    activity.setMovingTime(j["movingTime"].get<int>());
    activity.setStartDate(j["start_date"].get<QDateTime>());
}

inline void from_json(const nlohmann::json &j, DetailedAthlete &detailedAthlete)
{
    detailedAthlete.setId(j["id"].get<long>());
    detailedAthlete.setFirstName(j["firstname"].get<QString>());
    detailedAthlete.setLastName(j["lastname"].get<QString>());
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

template<typename T, typename Model = typename ExtractModel<T>::Type>
nonstd::expected<T, DeserializerError> deserialize(const QByteArray &data)
{
    try {
        auto doc = nlohmann::json::parse(std::cbegin(data), std::cend(data));

        QFile schemaFile{Model::JsonSchema};

        if (!schemaFile.open(QIODevice::ReadOnly)) {
            return nonstd::make_unexpected(QString{"Unable to open schema %1: %2"}
                                               .arg(Model::JsonSchema)
                                               .arg(schemaFile.errorString()));
        }

        auto schemaData = schemaFile.readAll();

        auto schemaDoc = nlohmann::json::parse(std::cbegin(schemaData), std::cend(schemaData));

        nlohmann::json_schema::json_validator validator{schemaDoc};
        validator.validate(doc);

        return doc.get<T>();
    } catch (std::exception &e) {
        return nonstd::make_unexpected(DeserializerError{e.what()});
    }
}

} // namespace QtStrava::Private
