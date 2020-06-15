#include <ros/ros.h>
#include <signal.h>
#include "custom_service/person.h"
#include <string.h>
// No need to include all three header files
// #include"custom_service/personRequest.h"
// #include"custom_service/personResponse.h"
bool running_flag = 1;

void shutdownServer(int sig)
{
    running_flag = 0;
    //signal(SIGINT, SIG_DFL);
}

bool serverCallback(custom_service::person::Request &req,
                    custom_service::person::Response &res)
{
    ROS_INFO("Got request from client!\n[%s, %d, %d]",
             req.name.c_str(),
             req.age,
             req.sex);
    std::string age = std::to_string(req.age);
    if (running_flag)
    {
        res.result = age;
    }
    else
    {
        res.result = "-1";
    }

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Person_info_server");
    ros::NodeHandle nh;

    ros::ServiceServer person_srv = nh.advertiseService("show_person", serverCallback);

    ROS_INFO("Server is ready...");
    signal(SIGINT, shutdownServer);
    while (ros::ok())
    {
        if (running_flag)
        {
            ros::spinOnce();
        }
        else
        {
            ROS_ERROR("Server shuting down...");
            ros::shutdown();
            return 0;
        }
    }

    return 0;
}