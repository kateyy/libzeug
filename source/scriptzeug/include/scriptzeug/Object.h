#pragma once


#include <string>
#include <vector>
#include <propertyzeug/PropertyGroup.h>
#include "scriptzeug/Function.h"


namespace scriptzeug
{


/** \brief Base class for reflectable classes that can expose properties and functions
 */
class SCRIPTZEUG_API Object : public zeug::PropertyGroup
{
public:
    Object(const std::string & name);
    virtual ~Object();

    const std::vector<AbstractFunction *> & functions() const;

    template <typename RET, typename... Arguments>
    void addFunction(const std::string & name, RET (*fn)(Arguments...))
    {
        Function<RET, Arguments...> * func = new Function<RET, Arguments...>(name, fn);
        m_functions.push_back(func);
    }

    template <class T, typename RET, typename... Arguments>
    void addFunction(const std::string & name, T * obj, RET (T::*member)(Arguments...))
    {
        Method<T, RET, Arguments...> * method = new Method<T, RET, Arguments...>(name, obj, member);
        m_functions.push_back(method);
    }

protected:
    std::vector<AbstractFunction *> m_functions;
};


} // namespace scriptzeug