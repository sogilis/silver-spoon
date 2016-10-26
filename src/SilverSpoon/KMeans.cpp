#include <SilverSpoon/KMeans.h>

//----------------------------------------------------------------------------//
void KMeans::kmeans(cv::Mat &img)
{
    cv::Mat pixels = cv::Mat::zeros(img.rows, img.cols, CV_8UC4);

    //TODO
    // define seeds

    for (int a = 0; a < 20; a++)
    {
        for (int i = 0; i < pixels.cols; i++)
        {
            for (int j = 0; j < pixels.rows; j++)
            {
                //TODO
                // uint8_t cluster_id = get_best_cluster(pixels.at<uint8_t>(i,j));
                // img.at<uint8_t>(i,j)[3] = cluster_id;
            }
        }
        recompute_means(pixels);
    }
}
//----------------------------------------------------------------------------//
uint8_t KMeans::get_best_cluster(unsigned char* pixel)
{
    int best_fit = 2000000000;//TODO
    int best_fit_id = 0;
    for (int i = 0; i < nb_cluster; i++)
    {
        int fit = dist(pixel, means[i]);
        if(fit < best_fit)
        {
            best_fit = fit;
            best_fit_id = i;
        }
    }
    return best_fit_id;
}
//----------------------------------------------------------------------------//
int KMeans::dist(uint8_t* pix_a, uint8_t* pix_b)
{
    return abs(pix_a[0] - pix_b[0]) +
           abs(pix_a[1] - pix_b[1]) +
           abs(pix_a[2] - pix_b[2]);
}
//----------------------------------------------------------------------------//
void KMeans::recompute_means(cv::Mat pixels)
{
    for (int a = 0; a < nb_cluster; a++)
    {
        double average[3] = {0,0,0};
        int counter = 0;
        for(int i = 0; i < pixels.cols; i++)
        {
            for(int j = 0; j < pixels.rows; j++)
            {
                if(pixels.at<uint8_t>(i,j)[3] == a)
                {
                    counter++;
                    average[0] += pixels.at<uint8_t>(i,j)[0];
                    average[1] += pixels.at<uint8_t>(i,j)[1];
                    average[2] += pixels.at<uint8_t>(i,j)[2];
                }
            }
            if(counter != 0)
            {
                means[a][0] = average[0] / counter;
                means[a][1] = average[1] / counter;
                means[a][2] = average[2] / counter;
            }
        }
    }
}
//----------------------------------------------------------------------------//
