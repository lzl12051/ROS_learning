#include <ros/ros.h>
#include "custom_msgs/Person.h"

void subCallback(const custom_msgs::Person::ConstPtr &msg)
{
    ROS_INFO("Name %s, age: %d, gender: %d", msg->name.c_str(), msg->age, msg->sex);
}

int main(int argc, char **argv)
{
    using namespace ros;
    init(argc, argv, "Custom_msg_subsciber");
    NodeHandle nh;
    Subscriber person_sub = nh.subscribe("/person_info", 10, subCallback);

    spin();
    return 0;
}