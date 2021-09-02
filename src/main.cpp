
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
    cv::VideoCapture cap;
    cv::Mat frame;
    FaceDetector faceDetector(300,300,1.0,0.5);
    EmotionDetector emotionDetector;
    std::vector<Face> faces;

    switch (getopt(argc,argv,"wi:v:")){
        case 'w':
            cap = cv::VideoCapture(0);
            if(!cap.isOpened()){
                std::cout << "Couldn't find default camera" << std::endl;
                return -1;
            }
            cap >> frame;
            break;
        case 'i':
            frame = cv::imread(optarg);
            if(frame.data == NULL){
                std::cout << "Couldn't open image" << std::endl;
                return -1;
            }
            
            break;
        case 'v':
            cap = cv::VideoCapture(optarg);
            if(!cap.isOpened()){
                std::cout << "Couldn't open video: " << optarg << std::endl;
                return -1;
            }
            cap >> frame;
            break;

        default:
            std::cout << "Invalid option" << std::endl;
            break;
    }
   

    while(true){

        auto faces = faceDetector.detect(frame);
        emotionDetector.detect(faces);

        GUI::draw_rectangles(faces,frame);
        cv::imshow("Emotion Detector", frame);

        if (cv::waitKey(1) >= 0) break;

        cap >> frame;
        if(frame.data==NULL){
            cv::waitKey(0);
            break;            
        } 
    }

    return 0;
} 