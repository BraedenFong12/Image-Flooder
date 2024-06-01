#include "filler.h"
#include "colorPicker.h"
#include <string>
#include "cs221util/catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "filler.h"
#include "solidColorPicker.h"
#include "stripeColorPicker.h"
#include "quarterColorPicker.h"
#include "borderColorPicker.h"
#include "colorPicker.h"


class ImageFiller {
public:
    ImageFiller(const std::string& imagePath, const PixelPoint& seed, double tolerance, int frameFreq)
        : imagePath(imagePath), seed(seed), tolerance(tolerance), frameFreq(frameFreq) {}

    void fillSolidColor(const RGBAPixel& color, const std::string& outputImage) {
        SolidColorPicker solidPicker(color);
        runFill(solidPicker, outputImage);
    }

    void fillStripeColor(const RGBAPixel& color1, const RGBAPixel& color2, int stripeWidth, const std::string& outputImage) {
        StripeColorPicker stripePicker(stripeWidth, color1, color2);
        runFill(stripePicker, outputImage);
    }

    // Add other fill methods as needed...

private:
    std::string imagePath;
    PixelPoint seed;
    double tolerance;
    int frameFreq;

    void runFill(ColorPicker& picker, const std::string& outputImage) {
        filler::FillerConfig config;
        config.img.readFromFile(imagePath);
        config.frameFreq = frameFreq;
        config.tolerance = tolerance;
        config.seedpoint = seed;
        config.picker = &picker;

        animation anim = filler::FillBFS(config); // or use FillDFS
        PNG result = anim.write(outputImage);
        result.writeToFile(outputImage);
    }
};


int main() {
    PixelPoint seed(100, 100); // Example seed point
    ImageFiller filler("custom-img/braedenfong.png", seed, 0.2, 10);

    // Fill with a solid color
    filler.fillSolidColor(RGBAPixel(255, 0, 0), "custom-out/solid_fill.png");

    // Fill with a stripe pattern
    filler.fillStripeColor(RGBAPixel(0, 255, 0), RGBAPixel(0, 0, 255), 10, "custom-out/stripe_fill.png");

    return 0;
}
