#include "../../render/render.h"
#include "../../render/box.h"
#include <chrono>
#include <string>
#include "kdtree.h"

template <typename PointT>
void clusterHelper(const std::vector<PointT, Eigen::aligned_allocator<PointT>>& points, std::vector<bool>& processedPoints, int index, std::vector<int>& cluster, KdTree<PointT>* tree, float distanceTol)
{
    processedPoints[index] = true;
    cluster.push_back(index);

    std::vector<int> proximity = tree->search(points[index], distanceTol);
    for (int id : proximity)
    {
        if (!processedPoints[id])
        {
            clusterHelper(points, processedPoints, id, cluster, tree, distanceTol);
        }
    }
}
template <typename PointT>
std::vector<std::vector<int>> euclideanCluster(const std::vector<PointT, Eigen::aligned_allocator<PointT>>& points, KdTree<PointT>* tree, float distanceTol)
{
    std::vector<std::vector<int>> clusters;
    std::vector<bool> processedPoints(points.size(), false);    // map the processed points

    for (int i = 0; i < points.size(); ++i)
    {
        if (processedPoints[i])
            continue;

        std::vector<int> cluster;
        clusterHelper(points, processedPoints, i, cluster, tree, distanceTol);
        clusters.push_back(cluster);
    }

    return clusters;
}
 