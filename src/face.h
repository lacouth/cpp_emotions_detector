#ifndef FACE_H
#define FACE_H

#include <string>
#include <opencv2/imgproc.hpp>


class Face{
    public:
        int _xLeftBottom;
        int _xRightTop;
        int _yLeftBottom;
        int _yRightTop;
        double _confidence;
        cv::Mat _face;
        std::string _emotion;

        Face(){}
        Face(int xLeftBottom, int xRightTop, int yLeftBottom, int yRightTop, cv::Mat face, std::string emotion);
        Face(Face &other);
        Face(Face &&other);

        Face& operator=(Face &other);
        Face& operator=(Face &&other);
};

#endif