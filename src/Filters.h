#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "ImageProcessor.h"
#include <Pixel.h>
#include <mdspan>
#include <vector>


void placeholderFilter(std::mdspan<Pixel, std::dextents<size_t, 2>>& outputGrid, 
                       size_t rowNum, size_t colNum) {
    
    std::vector<Pixel> copyBuffer(outputGrid.extent(0) * outputGrid.extent(1));
    std::mdspan readOnlyGrid(copyBuffer.data(), outputGrid.extents());


    for(size_t y = 0; y < outputGrid.extent(0); ++y) {
        for(size_t x = 0; x < outputGrid.extent(1); ++x) {
            readOnlyGrid[y, x] = outputGrid[y, x];
        }
    }

    int accR = 0;
    int accG = 0;
    int accB = 0;
    int count = 0;

    for(int y = -1; y <= 1; y++) {
        for(int x = -1; x <= 1; x++) {
            Pixel p = readOnlyGrid[rowNum + y, colNum + x];
            
            accR += p.r;
            accG += p.g;
            accB += p.b;
            count++;
        }
    }

    outputGrid[rowNum, colNum] = Pixel{
        static_cast<uint8_t>(accR / count),
        static_cast<uint8_t>(accG / count),
        static_cast<uint8_t>(accB / count),
        255
    };
}

#endif
