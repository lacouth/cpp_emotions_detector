#include "emotiondetector.h"

EmotionDetector::EmotionDetector(){

    const std::string _modelConfiguration = "../src/data/models/deploy_emotion.prototxt";
    const std::string _modelBinary = "../src/data/models/EmotiW_VGG_S.caffemodel";
        
    _net = cv::dnn::readNetFromCaffe(_modelConfiguration, _modelBinary);
    
    if(_net.empty()){
        std::cout << "Can't load emotiontector network!" << std::endl;
        std::cout << "Model is available here: "<< std::endl;
        std::cout << "https://gist.github.com/GilLevi/54aee1b8b0397721aa4b" << std::endl;
        exit(-1);
    }

}

void EmotionDetector::detect(std::vector<Face> &faces){
    for(Face &face : faces){
        // _futures.emplace_back(std::async(std::launch::deferred, [&](){this->run_detector(face);}));
        this->run_detector(face);
    }

    for(const std::future<void> &f : _futures){
        f.wait();
    }
}

void EmotionDetector::run_detector(Face &face){
    
   
    cv::Mat input = cv::dnn::blobFromImage(face._face,
                                            1.0,
                                            cv::Size(256,256),
                                            cv::Scalar(0),
                                            false,
                                            false);
    _net.setInput(std::move(input),"data");

    std::unique_lock<std::mutex> lock(_mtx);
    std::vector<float> detections(_net.forward("prob"));
    lock.unlock();

    int idx = std::max_element(detections.begin(),detections.end()) - detections.begin();
    face._emotion = _emotions[idx];
}