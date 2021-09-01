
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <algorithm>
#include <vector>

#include "facedetector.h"
#include "emotiondetector.h"
#include "face.h"
#include "gui.h"

using namespace cv;
using namespace std;
using namespace cv::dnn;

// Set up configuration
// float confidenceThreshold = 0.5;
// String modelConfiguration = "../src/data/model/deploy.prototxt";
// String modelBinary = "../src/data/model/res10_300x300_ssd_iter_140000.caffemodel";

// String emotionModelConfiguration = "../src/data/model/deploy_emotion.prototxt";
// String emotionModelBinary = "../src/data/model/EmotiW_VGG_S.caffemodel";


// const size_t inWidth = 300;
// const size_t inHeight = 300;
// const double inScaleFactor = 1.0;
// const Scalar meanVal(104.0, 177.0, 123.0);

// const string emotions[]{"Angry" , "Disgust" , "Fear" , "Happy"  , "Neutral" ,  "Sad" , "Surprise"};

int main(int argc, char** argv)
{
    
    // Init DNN
    // Net net = readNetFromCaffe(modelConfiguration, modelBinary);
    // dnn::Net emotion_net = readNetFromCaffe(emotionModelConfiguration, emotionModelBinary);
    FaceDetector faceDetector(300,300,1.0,0.5);
    EmotionDetector emotionDetector;
    
   

    VideoCapture cap;
    if (argc==1)
    {
        cap = VideoCapture(0);
        if(!cap.isOpened())
        {
            cout << "Couldn't find  default camera" << endl;
            return -1;
        }
    }
    else
    {
        cap.open(argv[1]);
        if(!cap.isOpened())
        {
            cout << "Couldn't open image or video: " << argv[1] << endl;
            return -1;
        }
    }

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera/video or read image

        if (frame.empty())
        {
            waitKey();
            break;
        }

        auto faces = faceDetector.detect(frame);
        
        for(Face &face : faces){
            emotionDetector.detectEmotion(face);
        }

        
        GUI::draw_rectangles(faces,frame);


        //! [Prepare blob]
       // Mat inputBlob = blobFromImage(frame, inScaleFactor,
        //                              Size(inWidth, inHeight), meanVal, false, false); //Convert Mat to batch of images
        
        //! [Set input blob]
        //net.setInput(inputBlob, "data"); //set the network input
        
        //! [Make forward pass]
        //Mat detection = net.forward("detection_out"); //compute output
        
        //Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

        // for(int i = 0; i < detectionMat.rows; i++)
        // {
        //     float confidence = detectionMat.at<float>(i, 2);

        //     if(confidence > confidenceThreshold)
        //     {
        //         int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
        //         int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
        //         int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
        //         int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

        //         Rect object((int)xLeftBottom, (int)yLeftBottom,
        //                     (int)(xRightTop - xLeftBottom),
        //                     (int)(yRightTop - yLeftBottom));
                                
        //         //Mat cropped = frame(Range(yLeftBottom,yRightTop),Range(xLeftBottom,xRightTop));
                
        //         //Mat inputBlob2 = blobFromImage(cropped, inScaleFactor,
        //          //                     Size(256, 256), meanVal, false, false); //Convert Mat to batch of images
        
        //         //! [Set input blob]
        //         //emotion_net.setInput(std::move(inputBlob2), "data"); //set the network input
                
        //         //! [Make forward pass]
        //         //vector<float> detection2(emotion_net.forward("prob")); //compute output
        //         //int idx = max_element(detection2.begin(), detection2.end()) - detection2.begin();

        //         //cout << emotions[idx] << endl;


        //         rectangle(frame, object, Scalar(0, 255, 0));

        //         stringstream ss;
        //         ss.str("");
        //         ss << confidence;
        //         String conf(ss.str());
        //         String label = "Face: " + conf;
        //         int baseLine = 0;
        //         Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        //         rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
        //                               Size(labelSize.width, labelSize.height + baseLine)),
        //                   Scalar(255, 255, 255), FILLED);
        //         putText(frame, label, Point(xLeftBottom, yLeftBottom),
        //                 FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
        //     }
        // }

        imshow("detections", frame);
        if (waitKey(1) >= 0) break;
    }

    return 0;
} 