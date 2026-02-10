#pragma once
#include <cstdint>
#include <string>

class ImageProcessor {
private:
    int width;
    int height;
    int channels;
    unsigned char* pixelData; // BUCKET B (The raw pixels)

public:
    ImageProcessor();
    ~ImageProcessor();


    bool loadImage(uintptr_t bufferPtr, int size);


    void applyFilter();

    int getWidth() const;
    int getHeight() const;
    uintptr_t getPixelDataPtr() const; // Returns address of BUCKET B
};
