#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include "face.h"

class FaceDetector{

    private:
        const std::string _modelConfiguration = "../src/data/models/deploy.prototxt";
        const std::string _modelBinary = "../src/data/models/res10_300x300_ssd_iter_140000.caffemodel";
        cv::dnn::Net _net;
        size_t _width;
        size_t _height;
        double _scale;
        double _confidence;
    public:
        FaceDetector(size_t width, size_t height, double scale, double confidence);
        std::vector<Face> detect(cv::Mat &image);
};


#endif