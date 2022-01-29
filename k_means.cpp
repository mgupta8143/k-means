#include <random>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

struct Point {
    double x;
    double y;
    
    Point(double a, double b) : x(a), y(b) {}
    
    std::string print() {
        return "Point(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    }
    
};

Point generateRandomPoint(double x_low = 0.0, double x_high = 1.0, double y_low = 0.0, double y_high = 1.0) {
    std::uniform_real_distribution<double> x_unif(x_low, x_high);
    std::uniform_real_distribution<double> y_unif(y_low, y_high);
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    Point pt(x_unif(generator), y_unif(generator));
    return pt;
}

std::vector<Point> generatePointList(size_t size, double x_low = 0.0, double x_high = 1.0, double y_low = 0.0, double y_high = 1.0) {
    std::vector<Point> x;
    for (int i = 0; i < size; ++i) {
        x.push_back(generateRandomPoint(x_low, x_high, y_low, y_high));
    }
    return x;
}

double euclidean_dist(Point a, Point b) {
    return std::pow(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2), 0.5);
}

std::vector<Point> getSample(std::vector<Point> pop, int k) {
    std::random_device rd;
    std::mt19937 g(rd());
     
    std::shuffle(pop.begin(), pop.end(), g);
    std::vector<Point> result;
    
    for (int i = 0; i < k; ++i) {
        result.push_back(pop[i]);
    }
    
    return result;
}

Point getAverage(std::vector<Point>& points) {
    double x_sum = 0;
    double y_sum = 0;
    
    for (int i = 0; i < points.size(); ++i) {
        x_sum += points[i].x;
        y_sum += points[i].y;
    }
    
    Point avg(x_sum / points.size(), y_sum / points.size());
    return avg;
}

std::vector<std::vector<Point>> k_means(std::vector<Point>& points, int k, int iterations) {
    std::vector<Point> centroids = getSample(points, k);
    std::vector<std::vector<Point>> result;
    
    for (int i = 0; i < k; ++i) {
        std::vector<Point> cluster;
        result.push_back(cluster);
    }
    
    for (int m = 0; m < iterations; ++m ) {
        for (int i = 0; i < points.size(); ++i) {
            double min_dist = euclidean_dist(points[i], centroids[0]);
            size_t closestCluster = 0;
            
            for (int j = 1; j < k; ++j) {
                double new_dist = euclidean_dist(points[i], centroids[j]);
                if (new_dist < min_dist) {
                    min_dist = new_dist;
                    closestCluster = j;
                }
            }
            
            result[closestCluster].push_back(points[i]);
        }
        
        for (int i = 0; i < result.size(); ++i) {
            centroids[i] = getAverage(result[i]);
        }
        
        if (m == iterations - 1) break;
        
        result.clear();
        for (int i = 0; i < k; ++i) {
            std::vector<Point> cluster;
            result.push_back(cluster);
        }
    }
    
    return result;
}

void showClusters(std::vector<std::vector<Point>>& x) {
    for (int i = 0; i < x.size(); ++i) {
        std::cout << "Cluster " + std::to_string(i + 1) + ": ";
        
        for (int j = 0; j < x[i].size(); ++j) {
            std::cout << x[i][j].print() << ", ";
        }
        
        std::cout << std::endl;
    }
}


int main() {
    std::vector<Point> points = generatePointList(1000);
    std::vector<std::vector<Point>> clusters = k_means(points, 10, 100);
    
    
    
    
    showClusters(clusters);
    
}
