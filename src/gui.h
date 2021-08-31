#ifndef GUI_H
#define GUI_H

#include <opencv2/highgui.hpp>
#include <vector>
#include "face.h"

namespace GUI{
    void draw_rectangles(std::vector<Face> &faces, cv::Mat &image);
};

#endif