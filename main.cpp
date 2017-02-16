//#include <pcl/io/openni_grabber.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/visualization/cloud_viewer.h>
//#include <pcl/console/parse.h>

#include <octomap/octomap.h>
#include <octomap/OcTree.h>

#include <iostream>

#include "octothread.h"
#include "Map/octomap.h"
#include "Visualizer/Qvisualizer.h"
#include <GL/glut.h>
#include <qapplication.h>

using namespace std;
//using namespace pcl;
using namespace octomap;

//PointCloud<PointXYZRGBA>::Ptr cloudptr(new PointCloud<PointXYZRGBA>); // A cloud that will store color info.
//PointCloud<PointXYZ>::Ptr fallbackCloud(new PointCloud<PointXYZ>);    // A fallback cloud with just depth data.
//boost::shared_ptr<visualization::CloudViewer> viewer;                 // Point cloud viewer object.
//Grabber* openniGrabber;                                               // OpenNI grabber that takes data from the device.
unsigned int filesSaved = 0;                                          // For the numbering of the clouds saved to disk.
bool saveCloud(false), noColor(false);                                // Program control.
OcTree tree (0.01);
//OctoThread* thread = new OctoThread();

void
printUsage(const char* programName)
{
    cout << "Usage: " << programName << " [options]"
         << endl
         << endl
         << "Options:\n"
         << endl
         << "\t<none>     start capturing from an OpenNI device.\n"
         << "\t-v FILE    visualize the given .pcd file.\n"
         << "\t-h         shows this help.\n";
}

// This function is called every time the device has new data.
//void grabberCallback(const PointCloud<PointXYZRGBA>::ConstPtr& cloud)
//{
//    if (! viewer->wasStopped())
//        viewer->showCloud(cloud);

//    if(!thread->isRunning()) {
//        thread->setPointCloudData(cloud->points, cloud->sensor_origin_);
//        thread->start();
//    }


//    if (saveCloud)
//    {
//        stringstream stream;
//        stream << "inputCloud" << filesSaved << ".pcd";
//        string filename = stream.str();
//        if (io::savePCDFile(filename, *cloud, true) == 0)
//        {
//            filesSaved++;
//            cout << "Saved " << filename << "." << endl;
//        }
//        else PCL_ERROR("Problem saving %s.\n", filename.c_str());
//        stream <<"tree"<<filesSaved<<".bt";
//        tree.writeBinary(stream.str());
//        saveCloud = false;
//    }
//}

// For detecting when SPACE is pressed.
//void keyboardEventOccurred(const visualization::KeyboardEvent& event,
//                      void* nothing)
//{
//    if (event.getKeySym() == "space" && event.keyDown())
//        saveCloud = true;
//}

//// Creates, initializes and returns a new viewer.
//boost::shared_ptr<visualization::CloudViewer>
//createViewer()
//{
//    boost::shared_ptr<visualization::CloudViewer> v
//    (new visualization::CloudViewer("OpenNI viewer"));
//    v->registerKeyboardCallback(keyboardEventOccurred);

//    return (v);
//}

int main(int argc, char** argv) {
    std::cout << "Start\n";
    mapping::Map* map = mapping::createMapOcto();
    std::cout << map->getName() << "\n";

    QApplication application(argc,argv);
    setlocale(LC_NUMERIC,"C");
    glutInit(&argc, argv);

    QGLVisualizer visu;
    visu.setWindowTitle("Simulator viewer");
    visu.show();
    map->attachVisualizer(&visu);


    map->insertCloud();

    application.exec();

    std::cout << "Done\n";
//    thread->setTree(&tree);
//    if (console::find_argument(argc, argv, "-h") >= 0)
//    {
//        printUsage(argv[0]);
//        return -1;
//    }

//    bool justVisualize(false);
//    string filename;
//    if (console::find_argument(argc, argv, "-v") >= 0)
//    {
//        if (argc != 3)
//        {
//            printUsage(argv[0]);
//            return -1;
//        }

//        filename = argv[2];
//        justVisualize = true;
//    }
//    else if (argc != 1)
//    {
//        printUsage(argv[0]);
//        return -1;
//    }

//    // First mode, open and show a cloud from disk.
//    if (justVisualize)
//    {
//        // Try with color information...
//        try
//        {
//            io::loadPCDFile<PointXYZRGBA>(filename.c_str(), *cloudptr);
//        }
//        catch (PCLException e1)
//        {
//            try
//            {
//                // ...and if it fails, fall back to just depth.
//                io::loadPCDFile<PointXYZ>(filename.c_str(), *fallbackCloud);
//            }
//            catch (PCLException e2)
//            {
//                return -1;
//            }

//            noColor = true;
//        }

//        cout << "Loaded " << filename << "." << endl;
//        if (noColor)
//            cout << "This cloud has no RGBA color information present." << endl;
//        else cout << "This cloud has RGBA color information present." << endl;
//    }
//    // Second mode, start fetching and displaying frames from the device.
//    else
//    {
//        openniGrabber = new OpenNIGrabber();
//        if (openniGrabber == 0)
//            return -1;
//        boost::function<void (const PointCloud<PointXYZRGBA>::ConstPtr&)> f =
//            boost::bind(&grabberCallback, _1);
//        openniGrabber->registerCallback(f);
//    }

//    viewer = createViewer();

//    if (justVisualize)
//    {
//        if (noColor)
//            viewer->showCloud(fallbackCloud);
//        else viewer->showCloud(cloudptr);
//    }
//    else openniGrabber->start();

//    // Main loop.
//    while (! viewer->wasStopped())
//        boost::this_thread::sleep(boost::posix_time::seconds(1));

//    if (! justVisualize)
//        openniGrabber->stop();
}
