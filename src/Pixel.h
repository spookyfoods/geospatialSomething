#ifndef PIXEL_H
#define PIXEL_H

#include <algorithm>
#include <cstdint>
struct Pixel{
    uint8_t r,g,b,a;
    Pixel& operator+=(int value){
        r=static_cast<uint8_t>(std::clamp(r + value, 0, 255));
        g=static_cast<uint8_t>(std::clamp(g + value, 0, 255));
        b=static_cast<uint8_t>(std::clamp(b + value, 0, 255));
        return *this;
    }
    Pixel& operator+=(const Pixel& other){
        r=static_cast<uint8_t>(std::clamp(other.r + r, 0, 255));
        g=static_cast<uint8_t>(std::clamp(other.g + g, 0, 255));
        b=static_cast<uint8_t>(std::clamp(other.b + b, 0, 255));
        return *this;
    }
    Pixel& operator=(const Pixel& other){
        r=other.r;
        g=other.g;
        b=other.b;
        a=other.a;
        return *this;
    }
    Pixel& operator=(int assignmentValue){
        r=assignmentValue;
        g=assignmentValue;
        b=assignmentValue;
        a=assignmentValue;
        return *this;
    }
    Pixel operator/=(int dividedBy){
        r/=dividedBy;
        g/=dividedBy;
        b/=dividedBy;
        return *this;
    }
};
#endif
