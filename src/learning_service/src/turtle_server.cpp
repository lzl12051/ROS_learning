#include <ros/ros.h>
#include <std_srvs/Trigger.h>
#include <geometry_msgs/Twist.h>

ros::Publisher turtle_vel_pub;
bool pubCommand = false;

bool serverCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
    pubCommand = !pubCommand;
    ROS_INFO("Publish turtle velocity command [%s]", pubCommand == true ? "Yes" : "No");
    res.success = true;
    res.message = "Change turtle command state";

    return true;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_server");
    ros::NodeHandle nh;
    ros::ServiceServer server = nh.advertiseService("/turtle_command", serverCallback);
    turtle_vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);

    ROS_INFO("Ready to receive turtle command.");

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        //Need this to check the callback function queue
        ros::spinOnce();

        if (pubCommand)
        {
            geometry_msgs::Twist vel;
            vel.angular.z = 0.2;
            vel.linear.x = 0.5;
            turtle_vel_pub.publish(vel);
        }

        loop_rate.sleep();
    }

    return 0;
}