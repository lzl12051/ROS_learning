#include<ros/ros.h>
#include"custom_msgs/Person.h"


int main(int argc, char **argv)
{
    using namespace ros;
    init(argc, argv, "Custom_msg_publisher");
    NodeHandle nh;
    Publisher custom_pub = nh.advertise<custom_msgs::Person>("/person_info", 10);
    Rate loop_rate(2);

    while(ros::ok())
    {   
        using namespace custom_msgs;
        Person person_msg;
        person_msg.name = "Jack";
        person_msg.age = 28;
        person_msg.sex = Person::male;

        custom_pub.publish(person_msg);
        ROS_INFO("Name: %s, Age: %d, Sex: %d", person_msg.name.c_str(), person_msg.age, person_msg.sex);
        
        loop_rate.sleep();
        
    }
    return 0;
}