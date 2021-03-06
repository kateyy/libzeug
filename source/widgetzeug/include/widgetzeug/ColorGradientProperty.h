#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <reflectionzeug/property/Property.h>

#include <widgetzeug/ColorGradient.h>

namespace
{

std::string gradientToString(const widgetzeug::ColorGradient & gradient)
{
    return QJsonDocument(gradient.toJson()).toJson(QJsonDocument::Compact).data();
}

bool gradientFromString(const std::string & string, widgetzeug::ColorGradient & gradient)
{
    QJsonDocument json = QJsonDocument::fromJson(QByteArray(string.c_str()));

    if (json.isNull() || json.isEmpty() || !json.isObject())
        return false;

    gradient = widgetzeug::ColorGradient::fromJson(json.object());
    return gradient.isValid();
}

}

namespace widgetzeug
{

class ColorGradientProperty : public reflectionzeug::AbstractTypedProperty<widgetzeug::ColorGradient>
{
public:
    template <typename... Args>
    ColorGradientProperty(Args&&... args) : 
        AbstractTypedProperty<widgetzeug::ColorGradient>(std::forward<Args>(args)...) {}

    virtual std::string toString() const 
    {
        return gradientToString(this->value());
    }

    virtual bool fromString(const std::string & string)
    {
        widgetzeug::ColorGradient value;
        if (!gradientFromString(string, value))
            return false;

        this->setValue(value);
        return true;
    }

    // [TODO] implement toVariant()/fromVariant()!
    // [TODO] implement accept()!
};

} // namespace

namespace reflectionzeug 
{

template <>
struct PropertTypeSelector<widgetzeug::ColorGradient>
{
    using Type = widgetzeug::ColorGradientProperty;
};

} // namespace widgetzeug
