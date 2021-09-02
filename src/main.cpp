
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>


#include "facedetector.h"
#include "emotiondetector.h"
#include "face.h"
#include "gui.h"

int main(int argc, char** argv)
{
    
    // Init DNN

    FaceDetector faceDetector(300,300,1.0,0.5);
    EmotionDetector emotionDetector;
    std::vector<std::future<void>> futures;

    cv::VideoCapture cap;
    if (argc==1)
    {
        cap = cv::VideoCapture(0);
        if(!cap.isOpened())
        {
            std::cout << "Couldn't find  default camera" << std::endl;
            return -1;
        }
    }
    else
    {
        cap.open(argv[1]);
        if(!cap.isOpened())
        {
            std::cout << "Couldn't open image or video: " << argv[1] << std::endl;
            return -1;
        }
    }

    while(true)
    {
        cv::Mat frame;
        cap >> frame; 

        if (frame.empty())
        {
            cv::waitKey();
            break;
        }

        auto faces = faceDetector.detect(frame);
        emotionDetector.detect(faces);
                

        GUI::draw_rectangles(faces,frame);

        cv::imshow("detections", frame);
        if (cv::waitKey(1) >= 0) break;

    }

    return 0;
} 