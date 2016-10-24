#include <SilverSpoon/Blob.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    cv::VideoCapture video(0);
    if(!video.isOpened())
    {
        std::cerr << "Unable to access camera." << std::endl;
        exit(0);
    }

    std::string window_name = "SilverSpoon";
    cv::namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    Blob blob;
    cv::Mat img;
    while(true)
    {
        if(video.grab())
        {
            video.retrieve(img);
            blob.detect(img);

            imshow(window_name, img);
            if(cv::waitKey(30) >= 0)
                exit(0);
        }
        else
        {
            std::cerr << "Camera connection lost." << std::endl;
            exit(0);
        }
    }

    return 0;
}
