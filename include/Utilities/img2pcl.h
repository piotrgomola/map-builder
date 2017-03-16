#ifndef IMG2PCL_H
#define IMG2PCL_H

#include "../include/Defs/defs.h"
#include "opencv2/opencv.hpp"
#include "../../3rdParty/Eigen/Dense"
#include "octomap/Pointcloud.h"
#include "octomap/math/Vector3.h"
#include "octomap/math/Quaternion.h"

#include "3rdParty/tinyXML/tinyxml2.h"
#include <fstream>
#include <string>
#include <math.h>

namespace mapping {

class img2pcl {
private:
    //Path of images catalog and format of their naming
    std::string path;
    std::string form;

    //File containing camera parameters
    std::string fileName;
    std::ifstream stateFile;

    //Grabbed images of scene
    int Timestamp;
    int color;

    cv::Mat depth;
    cv::Mat bgr;

    //Camera parameters
    float focalLength[2];
    float focalAxis[2];
    float factor;

    //Position and orientation of camera
    float t[3];
    float q[4];


    //Point Cloude generated from images
    PointCloud Cloud;
    //Position for each frame
    std::string pos;

    float z0(int u, int v, float_type d);
    float x0(int u, float z);
    float y0(int v, float z);

    Eigen::Vector3d xyz0(int u, int v, float_type d);
    Eigen::Matrix<float_type,3,3> Rot();
    Eigen::Vector3d Trans();
    octomap::pose6d FramePose();

    int depth2cloud();
    int depth2colorcloud();

public:
    img2pcl();
    img2pcl(std::string xmlPath);
    ~img2pcl();
    int grabFrame();
    int calcPCL();

    mapping::GrabbedImage returnPC();






};


    PointCloud depth2cloud(cv::Mat& depthImage);
    PointCloud depth2cloud(cv::Mat& depthImage, cv::Mat& colorImage);
    void getPoint(unsigned int u, unsigned int v, float_type depth, Eigen::Vector3d& point3D);
    void octopointToPointcloud(octomap::Pointcloud& fromCloud, mapping::PointCloud toCloud);
    void pointcloudToOctopoint(mapping::PointCloud& fromCloud, octomap::Pointcloud& toCloud);
}

#endif // IMG2PCL_H
