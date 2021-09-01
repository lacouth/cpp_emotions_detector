#ifndef EMOTIONDETECTOR_H
#define EMOTIONDETECTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <opencv2/dnn.hpp>
#include "face.h"



class EmotionDetector{
  private:
    const std::string _modelConfiguration = "../src/data/model/deploy_emotion.prototxt";
    const std::string _modelBinary = "../src/data/model/EmotiW_VGG_S.caffemodel";
    const std::string _emotions[7]{"Angry" , "Disgust" , "Fear" , "Happy"  , "Neutral" ,  "Sad" , "Surprise"};
    cv::dnn::Net _net;
  public:
    EmotionDetector();
    void detectEmotion(Face &face);

};

#endif