#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "learning_topic");
    ros::NodeHandle n;
    ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Rate loop_rate(1);
    

    int count = 0;
    while (ros::ok())
    { 
        using namespace geometry_msgs;
        Twist vel_msg;
        vel_msg.linear.x = 1;
        vel_msg.angular.z = 1;
        turtle_vel_pub.publish(vel_msg);
        ROS_INFO("Publish turtle velocity command[%0.2f m/s, %0.2f rand/s", vel_msg.linear.x, vel_msg.angular.z);
        
        loop_rate.sleep();
    }
}
