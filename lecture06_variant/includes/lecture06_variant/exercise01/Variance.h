//
// Created by kaspersk on 9/19/16.
//

#ifndef LECTURE06_VARIANT_VARIANCE_H
#define LECTURE06_VARIANT_VARIANCE_H

#include <stdlib.h>
#include <boost/lexical_cast.hpp>

namespace exercise01 {
    struct IAmUserDefined {
        size_t ICanBeBig;
        unsigned int IAmSmallAndHappy;
        int ICanBeNegative;

        IAmUserDefined() {
            ICanBeBig = 123456;
            IAmSmallAndHappy = 0xFF;
            ICanBeNegative = -1;
        }

        void Shuffle() {
            ICanBeBig = std::rand() % 100000;
            IAmSmallAndHappy = std::rand() % 255;
            ICanBeNegative = std::rand() % 127;
        }
    };

    std::ostream& operator <<(std::ostream& stream, const IAmUserDefined& thisGuy){
        return stream << "ICanBeBig: " << thisGuy.ICanBeBig << " IAmSmallAndHappy " << boost::lexical_cast<std::string>(thisGuy.IAmSmallAndHappy) << " ICanBeNegative " << boost::lexical_cast<std::string>(thisGuy.ICanBeNegative);
    }
}

#endif //LECTURE06_VARIANT_VARIANCE_H
