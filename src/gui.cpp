#include "gui.h"

void GUI::draw_rectangles(std::vector<Face> &faces, cv::Mat &image){

    std::string label;
    for(auto face : faces){
        cv::Rect rect(face._xLeftBottom, face._yLeftBottom,
                  (face._xRightTop - face._xLeftBottom),
                  (face._yRightTop - face._yLeftBottom));
        cv::rectangle(image,rect,cv::Scalar(0,255,0));
        label = "Face: " + std::to_string(face._confidence) + face._emotion;
        cv::putText(image,label,
                    cv::Point(face._xLeftBottom,face._yLeftBottom),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,0));
    }
}