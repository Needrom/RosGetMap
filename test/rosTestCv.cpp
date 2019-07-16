#include "ros/ros.h"
#include "ros/console.h"
#include "getmap/cvShow.h"

int main(int argc, char** argv) {
    CvShow cvshow = CvShow();
    cvshow.createMat(20, 20);
    cv::imshow("test", cvshow.image);
    cv::waitKey(0);
    return 0;
}
