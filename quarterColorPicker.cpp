/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

using namespace std;

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    // Complete your implementation below
    this->referenceimg = inputimg;
    this->brightamount = b_amount;
	scale();
    
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    // find position based on the scaled image
    unsigned int x = (unsigned int) p.x % scaledimg.width();
    unsigned int y = (unsigned int) p.y % scaledimg.height();
    // add brightness
    RGBAPixel brighten = *scaledimg.getPixel(x,y);
    brighten.r = (unsigned char) std::min((int) brighten.r + (int) brightamount, 255);
    brighten.g = (unsigned char) std::min((int) brighten.g + (int) brightamount, 255);
    brighten.b = (unsigned char) std::min((int) brighten.b + (int) brightamount, 255);
    // return
    return brighten;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */

void QuarterColorPicker::scale() {
    scaledimg = PNG(referenceimg.width()/2, referenceimg.height()/2);
    for (unsigned int sy_new = 0, y_old = 0; y_old < referenceimg.height(); y_old += 2, sy_new++) {
        for (unsigned int sx_new = 0, x_old = 0; x_old < referenceimg.width(); x_old += 2, sx_new++) {
            *scaledimg.getPixel(sx_new, sy_new) = binterpolate(referenceimg.getPixel(x_old, y_old), referenceimg.getPixel(x_old + 1, y_old), 
                                            referenceimg.getPixel(x_old, y_old + 1), referenceimg.getPixel(x_old + 1, y_old + 1));
        }
    }
}


RGBAPixel QuarterColorPicker::binterpolate(RGBAPixel* tl, RGBAPixel* tr, RGBAPixel* bl, RGBAPixel* br) {
    double red = ((double) tl->r + (double) tr->r)/2;
    double green = ((double) tl->g + (double) tr->g)/2;
    double blue = ((double) tl->b + (double) tr->b)/2;

    double red2 = ((double) bl->r + (double) br->r)/2;
    double green2 = ((double) bl->g + (double) br->g)/2;
    double blue2 = ((double) bl->b + (double) br->b)/2;

    double red3 = (red+red2)/2;
    double green3 = (green+green2)/2;
    double blue3 = (blue+blue2)/2;  
    return RGBAPixel((int)red3, (int) green3, (int) blue3);
}