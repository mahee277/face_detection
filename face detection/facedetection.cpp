#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Unable to open camera" << endl;
        return -1;
    }

    Mat frame;
    CascadeClassifier classifier;
    classifier.load("Resources/haarcascade_frontalface_default.xml");
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cerr << "Error: Blank frame grabbed" << endl;
            break;
        }

        vector<Rect> faces;
        classifier.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(30, 30));

        for (const auto& face : faces) {
            rectangle(frame, face, Scalar(0, 165, 255), 4);  
        }

        cv::imshow("Face Detection", frame);

        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
