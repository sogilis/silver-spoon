#include <opencv2/core/core.hpp>

class KMeans
{
public:
    KMeans():nb_cluster(10){}
    void kmeans(cv::Mat &img);
private:
    uint8_t get_best_cluster(uint8_t* pixel);
    int dist(uint8_t* pix_a, uint8_t* pix_b);
    void recompute_means(cv::Mat pixels);

    int nb_cluster;
    uint8_t means[255][3]; //TODO nb_cluster
};
