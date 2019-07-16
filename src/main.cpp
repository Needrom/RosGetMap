#include <cstdio>
#include "ros/ros.h"
#include "ros/console.h"
#include "nav_msgs/GetMap.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "geometry_msgs/Quaternion.h"
#include "getmap/cvShow.h"

using namespace std;

class MapGenerator
{
	public:
        std::string mapname_;
        ros::Subscriber map_sub_;
        bool saved_map_;
        int threshold_occupied_;
        int threshold_free_;
        CvShow cvshow = CvShow();

        MapGenerator(const std::string& mapname, int threshold_occupied, int threshold_free) : mapname_(mapname), saved_map_(false), threshold_occupied_(threshold_occupied), threshold_free_(threshold_free) 
        {
            ros::NodeHandle n;
            ROS_INFO("waitting for the map");
            map_sub_ = n.subscribe("map", 1, &MapGenerator::mapCallback, this);
//            ros::Rate r(10);
        }

        void mapCallback(const nav_msgs::OccupancyGridConstPtr& map)
        {
            ROS_INFO("Received a %d X %d map @ %.3f m/pix",
                    map->info.width,
                    map->info.height,
                    map->info.resolution);
            
            cvshow.createMat(map->info.width, map->info.height);

            for(unsigned int y = 0; y < map->info.height; y++) {
                uchar* data = cvshow.image.ptr<uchar>(y);
                for(unsigned int x = 0; x < map->info.width; x++) {
                    unsigned int i = x + (map->info.height - y -1) * map->info.width;
                    if(map->data[i] >= 0 && map->data[i] <= threshold_free_) {
                        *data++ = 254;
                        ;;                       
                    }
                    else if (map->data[i] >= threshold_occupied_) {
                        *data++ = 000;
                        ;;
                    }
                    else {
                        *data++ = 205;
                        ;;
                    }
                }
            }
            
            cv::imshow("test", cvshow.image);
            cv::waitKey(30);
        }
};

int main(int argc, char** argv) {
   ros::init(argc, argv, "get_map");

   int threshold_occupied = 65;
   int threshold_free = 25;

   MapGenerator mapGen = MapGenerator("test", threshold_occupied, threshold_free);
    while(ros::ok()) {
        ros::spinOnce();
    }

	return 0;
}
