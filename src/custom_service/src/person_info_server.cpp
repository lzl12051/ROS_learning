#include <ros/ros.h>
#include "custom_service/person.h"
// No need to include all three header files
// #include"custom_service/personRequest.h"
// #include"custom_service/personResponse.h"

bool serverCallback(custom_service::person::Request &req,
                    custom_service::person::Response &res)
{
    ROS_INFO("Got request from client!\n[%s, %d, %d]",
             req.name.c_str(),
             req.age,
             req.sex);
    res.result = "Info received";

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Person_info_server");
    ros::NodeHandle nh;

    ros::ServiceServer person_srv = nh.advertiseService("show_person", serverCallback);

    ROS_INFO("Server is ready...");
    ros::spin();

    return 0;
}