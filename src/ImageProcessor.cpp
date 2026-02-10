#include <cstdint>
#include <span>
#include "ImageProcessor.h"
#include <iostream>
#include "isPrime.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Pixel{
    uint8_t r,g,b,a;
    Pixel operator+(int value){
        r+=value;
        g+=value;
        b+=value;
        return *this;
    }
};

ImageProcessor::ImageProcessor() : width(0), height(0), channels(0), pixelData(nullptr) {
    std::cout << "[C++] ImageProcessor Initialized" << std::endl;
}

ImageProcessor::~ImageProcessor() {
    stbi_image_free(pixelData);
}

bool ImageProcessor::loadImage(uintptr_t bufferPtr, int size) {
    const unsigned char* rawData = reinterpret_cast<const unsigned char*>(bufferPtr);
    if(pixelData){
        stbi_image_free(pixelData);
        pixelData=nullptr;
    }
    pixelData=stbi_load_from_memory(
        rawData,
        size,
        &width,
        &height,
        &channels,
        4
    );
    if(!pixelData){
        std::cerr << "[C++] Failed to load image." << '\n';
        return false;
    }
    std::cout << "[C++] Loaded Image: " << width << "x" << height << " (RGBA)" <<'\n';
    return true;
}

void ImageProcessor::applyFilter() {
    if(!pixelData){
        std::cerr << "[C++] Failed to process image." << std::endl;
    }
    std::span<Pixel> image_view(reinterpret_cast<Pixel*>(pixelData),width*height);
    for(int i{0};i<width*height;i++){
        if(isPrime(i)){
            image_view[i]=image_view[i]+(-255);
        }
    }
}

int ImageProcessor::getWidth() const { return width; }
int ImageProcessor::getHeight() const { return height; }
uintptr_t ImageProcessor::getPixelDataPtr() const { return reinterpret_cast<uintptr_t>(pixelData); }
