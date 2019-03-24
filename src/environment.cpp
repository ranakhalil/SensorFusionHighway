/* \author Aaron Brown */
// Create simple 3d highway enviroment using PCL
// for exploring self-driving car sensors

#include "sensors/lidar.h"
#include "render/render.h"
#include "processPointClouds.h"
// using templates for processPointClouds so also include .cpp to help linker
#include "processPointClouds.cpp"

class Player
{
public:

	float x_pos, y_pos, rotation;

	Player()
		: x_pos(0), y_pos(0), rotation(0)
	{}

	void Forward()
	{
		x_pos+=0.2*cos(rotation);
		y_pos+=0.2*sin(rotation);
	}
	void Back()
	{
		x_pos-=0.2*cos(rotation);
		y_pos-=0.2*sin(rotation);
	}
};

Player player;


void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event, void* viewer_void)
{
	pcl::visualization::PCLVisualizer* viewer = static_cast<pcl::visualization::PCLVisualizer*>(viewer_void);
  	if (event.getKeySym () == "f" && event.keyDown ())
  	{
    	player.Forward();
  	}
  	else if(event.getKeySym () == "b" && event.keyDown ())
  	{
  		player.Back();
  	}
  	viewer->setCameraPosition ( player.x_pos, 0, 1.5, player.x_pos+10, 0, 0, 0, 0, 1);

}

int main (int argc, char** argv)
{
    std::cout << "starting enviroment" << std::endl;

    pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    viewer->setBackgroundColor (0, 0, 0);
	viewer->setCameraPosition (0 , 0, 1.5, 10, 0, 0, 0, 0, 1);
    renderHighway(viewer);

    viewer->registerKeyboardCallback(keyboardEventOccurred, (void*)viewer.get());
    
    while (!viewer->wasStopped ())
    {
        viewer->spinOnce ();
    } 
    

}