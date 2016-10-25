#include <SilverSpoon/Blob.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//----------------------------------------------------------------------------//
Blob::Blob()
: iLowH(0),
  iHighH(255),
  iLowS(0),
  iHighS(255),
  iLowV(0),
  iHighV(255)
{
    //create window for trackbars
    cv::namedWindow("Control", CV_WINDOW_AUTOSIZE);
    cv::moveWindow("Control", 100, 600);

    //create trackbars in "Control" window
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
}
//----------------------------------------------------------------------------//
void Blob::detect(cv::Mat &img)
{
    cv::Mat imgHSV, imgThresholded;

    cv::Mat hue_per_sat = cv::Mat::zeros(256, 256, CV_8UC1);
    cv::Mat sat_per_val = cv::Mat::zeros(256, 256, CV_8UC1);
    cv::Mat val_per_hue = cv::Mat::zeros(256, 256, CV_8UC1);

    //Convert the captured frame from BGR to HSV
    cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    for (size_t i = 0; i < imgHSV.rows; i++)
    {
        for (size_t j = 0; j < imgHSV.cols; j++)
        {
            uint8_t hue = imgHSV.at<cv::Vec3b>(i,j)[0];
            uint8_t sat = imgHSV.at<cv::Vec3b>(i,j)[1];
            uint8_t val = imgHSV.at<cv::Vec3b>(i,j)[2];

            hue_per_sat.at<uint8_t>(hue, sat) = std::max((uint8_t)(hue_per_sat.at<uint8_t>(hue, sat)+1), hue_per_sat.at<uint8_t>(hue, sat));
            sat_per_val.at<uint8_t>(sat, val) = std::max((uint8_t)(sat_per_val.at<uint8_t>(sat, val)+1), sat_per_val.at<uint8_t>(sat, val));
            val_per_hue.at<uint8_t>(val, hue) = std::max((uint8_t)(val_per_hue.at<uint8_t>(val, hue)+1), val_per_hue.at<uint8_t>(val, hue));
        }
    }

    //Threshold the image
    inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded);

    //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    //morphological closing (fill small holes in the foreground)
    dilate(imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(imgThresholded, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    cv::Mat fill = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);

    //draw contours
    // if(contours.size() > 0)
    // {
    //     for(int i=0;i >= 0;i = hierarchy[i][0])
    //     {
    //         cv::drawContours(fill, contours, i, cv::Scalar(255,0,0), CV_FILLED, 8, hierarchy);
    //         cv::drawContours(fill, contours, i, cv::Scalar(0,255,0), 1, 8, hierarchy);
    //     }
    //     img += fill;
    // }

    // cvtColor(imgHSV, img, cv::COLOR_HSV2BGR);
    imshow("hue per sat", hue_per_sat);
    imshow("sat per val", sat_per_val);
    imshow("val per hue", val_per_hue);
}
//----------------------------------------------------------------------------//
