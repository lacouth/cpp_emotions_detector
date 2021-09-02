#ifndef EMOTIONDETECTOR_H
#define EMOTIONDETECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <future>
#include <mutex>

#include <opencv2/dnn.hpp>
#include "face.h"

class EmotionDetector{

    private:
        const std::string _emotions[7]{"Angry" , "Disgust" , "Fear" , "Happy"  , "Neutral" ,  "Sad" , "Surprise"};
        std::vector<std::future<void>> _futures;
        cv::dnn::Net _net;
        std::mutex _mtx; 

        void run_detector(Face &face);
    public:
        void detect(std::vector<Face> &faces);
        EmotionDetector();
};
  


#endif