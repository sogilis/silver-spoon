#ifndef BLOB_H
#define BLOB_H

#include <opencv2/core/core.hpp>

class Blob
{
public:
    Blob();
    void detect(cv::Mat &img);

private:
    int iLowH, iHighH;
    int iLowS, iHighS;
    int iLowV, iHighV;

    void draw_contour_list(cv::Mat img, std::vector <std::vector <cv::Point> > contours, std::vector<cv::Vec4i> hierarchy);
};

#endif
