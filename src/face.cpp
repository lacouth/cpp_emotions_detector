#include "face.h"

Face::Face(int xLeftBottom, 
           int xRightTop, 
           int yLeftBottom, 
           int yRightTop, 
           cv::Mat face, 
           std::string emotion) : _xLeftBottom(xLeftBottom),
                                  _xRightTop(xRightTop),
                                  _yLeftBottom(yLeftBottom),
                                  _yRightTop(yRightTop),
                                  _face(face),
                                  _emotion(emotion){}
Face::Face(Face &other){
    _xLeftBottom = other._xLeftBottom;
    _xRightTop = other._xRightTop;
    _yLeftBottom = other._yLeftBottom;
    _yRightTop = other._yRightTop;
    _face = other._face;
    _emotion = other._emotion;
    _confidence = other._confidence;
}
Face::Face(Face &&other){
    _xLeftBottom = std::move(other._xLeftBottom);
    _xRightTop = std::move(other._xRightTop);
    _yLeftBottom = std::move(other._yLeftBottom);
    _yRightTop = std::move(other._yRightTop);
    _face = std::move(other._face);
    _emotion = std::move(other._emotion);
    _confidence = std::move(other._confidence);
}

Face& Face::operator=(Face &other){
    _xLeftBottom = other._xLeftBottom;
    _xRightTop = other._xRightTop;
    _yLeftBottom = other._yLeftBottom;
    _yRightTop = other._yRightTop;
    _face = other._face;
    _emotion = other._emotion;
    _confidence = other._confidence;
    return *this;
}
Face& Face::operator=(Face &&other){
    _xLeftBottom = std::move(other._xLeftBottom);
    _xRightTop = std::move(other._xRightTop);
    _yLeftBottom = std::move(other._yLeftBottom);
    _yRightTop = std::move(other._yRightTop);
    _face = std::move(other._face);
    _emotion = std::move(other._emotion);
    _confidence = std::move(other._confidence);
    return *this;
}