#include "emotiondetector.h"

EmotionDetector::EmotionDetector(){
    _net = cv::dnn::readNetFromCaffe(_modelConfiguration, _modelBinary);
    if(_net.empty()){
        std::cout << "Can't load emotiontector network!" << std::endl;
        std::cout << "Model is available here: "<< std::endl;
        std::cout << "https://gist.github.com/GilLevi/54aee1b8b0397721aa4b" << std::endl;
        exit(-1);
    }
}

void EmotionDetector::detectEmotion(Face &face){
    cv::Mat input = cv::dnn::blobFromImage(face._face,
                                            1.0,
                                            cv::Size(256,256),
                                            cv::Scalar(0),
                                            false,
                                            false);
    _net.setInput(std::move(input),"data");
    std::vector<float> detections(_net.forward("prob"));
    int idx = std::max_element(detections.begin(),detections.end()) - detections.begin();
    face._emotion = _emotions[idx];
}