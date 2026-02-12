#include <memory>
#include <cstdint>
#include <span>
#include <mdspan>
#include "ImageProcessor.h"
#include <iostream>
#include "isPrime.h"
#include "Pixel.h"
#include <Filters.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



ImageProcessor::ImageProcessor() : width(0), height(0), channels(0), pixelData(nullptr) {
    std::cout << "[C++] ImageProcessor Initialized" << std::endl;
}

ImageProcessor::~ImageProcessor() {
    delete[] pixelData;
}

bool ImageProcessor::loadImage(uintptr_t bufferPtr, int size) {
    const unsigned char* rawData = reinterpret_cast<const unsigned char*>(bufferPtr);
    int tempW, tempH, tempC;
    unsigned char* tempStbData = stbi_load_from_memory(
        rawData,
        size,
        &tempW,
        &tempH,
        &tempC,
        4
    );
    if (!tempStbData) {
        std::cerr << "[C++] Failed to load image." << '\n';
        return false;
    }
    if (pixelData) {
        delete[] pixelData;
    }
    width = tempW;
    height = tempH;
    channels = 4;

    pixelData = new unsigned char[width * height * 4];

    std::memcpy(pixelData, tempStbData, width * height * 4);

    stbi_image_free(tempStbData);
    
    std::cout << "[C++] Loaded Image: " << width << "x" << height << " (RGBA)" <<'\n';
    return true;
}

void ImageProcessor::applyFilter(int kernelSize) {
    if(!pixelData){
        std::cerr << "[C++] Failed to process image." << std::endl;
    }
    // kernel size must be odd and a square => (2n+1) x (2n+1)
    int borderWidth=(kernelSize-1)/2;

    std::mdspan inputGrid(reinterpret_cast<Pixel*>(pixelData), height, width);

    int newWidth{width+2*(borderWidth)};
    int newHeight{height+2*(borderWidth)};
    auto borderedPixelData = std::make_unique_for_overwrite<unsigned char[]>(newWidth * newHeight * 4);
    
    std::mdspan outputGrid(reinterpret_cast<Pixel*>(borderedPixelData.get()), newHeight, newWidth);

    // Creating the top and bottom border
    for(int i{0};i<borderWidth;i++){
        for(int j{};j<newWidth;j++){
            outputGrid[i, j] = 0;
            outputGrid[newHeight - borderWidth + i, j] = 0;
        }
    }

    // Filling in the original image in the middle and also creating the side borders

    for(int i{borderWidth}; i < newHeight - borderWidth; i++) {
        // Write Left Border
        for(int j{0}; j < borderWidth; j++) {
            outputGrid[i, j] = 0;
        }

        // Copy Image
        for(int k{borderWidth}; k < newWidth - borderWidth; k++) {
            outputGrid[i, k] = inputGrid[i-borderWidth, k-borderWidth];
        }

        // Write Right Border
        for(int j{0}; j < borderWidth; j++) {
            outputGrid[i, newWidth - borderWidth + j] = 0;
        }
    }
    // Iterating through the cells of input grid
    for(int i{0};i<height;i++){
        for(int j{0};j<width;j++){
            placeholderFilter(inputGrid,outputGrid,i,j);
        }
    }

    std::cout << "Pixel 0:\t" << (int)inputGrid[0, 0].r<<" "<<(int)inputGrid[0, 0].g<<" "<<(int)inputGrid[0, 0].b << std::endl;
    std::cout << "Working..." << std::endl;
    std::cout << "Pixel 0:\t" << (int)outputGrid[1, 1].r<<" "<<(int)outputGrid[1, 1].g<<" "<<(int)outputGrid[1, 1].b << std::endl;
}

int ImageProcessor::getWidth() const { return width; }
int ImageProcessor::getHeight() const { return height; }
uintptr_t ImageProcessor::getPixelDataPtr() const { return reinterpret_cast<uintptr_t>(pixelData); }
