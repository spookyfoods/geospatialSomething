#include <emscripten/bind.h>
#include "ImageProcessor.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
    class_<ImageProcessor>("ImageProcessor")
        .constructor<>()
        .function("loadImage", &ImageProcessor::loadImage)
        .function("applyFilter", &ImageProcessor::applyFilter)
        .function("getWidth", &ImageProcessor::getWidth)
        .function("getHeight", &ImageProcessor::getHeight)
        .function("getPixelDataPtr", &ImageProcessor::getPixelDataPtr);
}
