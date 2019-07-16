#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Image window";

class CvShow{
public:
    cv::Mat image;

    CvShow() {
        ;;
    }

    void createMat(int width, int height) {
        image = cv::Mat(width, height, CV_8UC(1), cv::Scalar(0));
        
   }
};

