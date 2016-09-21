//
// Created by kaspersk on 9/19/16.
//

#ifndef LECTURE06_VARIANT_VISITOR_H
#define LECTURE06_VARIANT_VISITOR_H

#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>
#include <string>
#include <iostream>


namespace exercise02{
    struct ICanVisit : public boost::static_visitor<std::string>{
    std::string operator()(int &integers) const { return std::string("This guy is an integer: " + boost::lexical_cast<std::string>(integers)); }
    std::string operator()(double &doubles) const { return std::string("This guy is an double: " + boost::lexical_cast<std::string>(doubles)); }
    std::string operator()(char &chars) const { return std::string("This guy is a char: " + boost::lexical_cast<std::string>(chars)); }
    };
}

#endif //LECTURE06_VARIANT_VISITOR_H
