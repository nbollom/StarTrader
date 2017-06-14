//
// Created by nbollom on 12/04/17.
//

#ifndef STARTRADER_STRUCTS_H
#define STARTRADER_STRUCTS_H

#include "../common/common.h"

typedef struct {
    double x;
    double y;
    double z;
} Point3F;

inline Point3F MakePoint3F(const double x, const double y, const double z) {
    Point3F p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

inline void PrintPoint(const Point3F p) {
    debug << "{" << std::endl;
    debug << "  x:" << p.x << std::endl;
    debug << "  y:" << p.y << std::endl;
    debug << "  z:" << p.z << std::endl;
    debug << "}" << std::endl;
}

#endif //STARTRADER_STRUCTS_H
