#include <ros/ros.h>
#include <turtlesim/Spawn.h>

int main(int argc, char **argv)
{

    ros::init(argc, argv, "Turtle_spawn_service");
    ros::NodeHandle node;
    // Wait if the service doesn't exist.
    ros::service::waitForService("spawn");
    // Add a service client
    ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("spawn");

    turtlesim::Spawn srv;
    srv.request.x = 2.0;
    srv.request.y = 2.0;
    srv.request.name = "trutle2";

    ROS_INFO("Call service to spawn a turtle!");
    add_turtle.call(srv);
    ROS_INFO("Turtle spawn successfully [name:%s]", srv.request.name.c_str());

    return 0;
}
