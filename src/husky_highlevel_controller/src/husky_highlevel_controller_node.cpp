#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

void callback(const sensor_msgs::LaserScan &msg)
{
    float smallest_distence=100;

    int arr_size = floor((msg.angle_max - msg.angle_min)/msg.angle_increment);

    for (int i=0;i<arr_size; i++)
    {
        if (msg.ranges[i] < smallest_distence)
        {
            smallest_distence = msg.ranges[i];
        }
    }
    
    ROS_INFO("ROS_INFO Minimum laser distance(m): %lf", smallest_distence);
}

int main(int argc, char **argv)
{
    using namespace ros;
    init(argc, argv, "scan_subscriber");
    NodeHandle nh;
    Subscriber scan_sub;
    scan_sub = nh.subscribe("/scan", 200, callback);

    spin();
    return 0;

}