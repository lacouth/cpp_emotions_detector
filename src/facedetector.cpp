#include "facedetector.h"

FaceDetector::FaceDetector(size_t width, size_t height, double scale, double confidence){
    
    _net = cv::dnn::readNetFromCaffe(_modelConfiguration, _modelBinary);

    if(_net.empty()){
        std::cout << "Can't load facedetector network!" << std::endl;
        std::cout << "Model is available here: "<< std::endl;
        std::cout << "https://github.com/opencv/opencv_3rdparty/blob/dnn_samples_face_detector_20170830/res10_300x300_ssd_iter_140000.caffemodel" << std::endl;
        exit(-1);
    }

    _width = width;
    _height = height;
    _scale = scale;
    _confidence = confidence;    
}

std::vector<Face> FaceDetector::detect(cv::Mat &image){
    
    cv::Scalar _meanVal(104.0,177.0,123.0);

    cv::Mat inputBlob = cv::dnn::blobFromImage(image,
                                  _scale,
                                  cv::Size(_width, _height), 
                                  _meanVal, false, false);
    _net.setInput(inputBlob, "data");
    cv::Mat detection = _net.forward("detection_out");
    cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    
    std::vector<Face> faces;
    
    for(int i = 0; i < detectionMat.rows; ++i){
        Face face;
        face._confidence = detectionMat.at<float>(i,2);
        if( face._confidence > _confidence){
            face._xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * image.cols);
            face._yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * image.rows);
            face._xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols);
            face._yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows);
            face._face = image(cv::Range(face._yLeftBottom,face._yRightTop),cv::Range(face._xLeftBottom,face._xRightTop));
            faces.emplace_back(std::move(face));
        }
    }
    return faces;
}