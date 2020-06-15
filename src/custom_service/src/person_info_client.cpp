#include <ros/ros.h>
#include "custom_service/person.h"
#include <string.h>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "person_info_client");
    ros::NodeHandle nh;
    ros::Rate loop_rate(2);

    //Wait until the service has started
    ros::service::waitForService("show_person");

    //Link to the service
    ros::ServiceClient person_clt = nh.serviceClient<custom_service::person>(
        "show_person");

    //Build the request data

    int count = 0;
    while (ros::ok())
    {
        custom_service::person person;
        person.request.name = "Jack";
        person.request.sex = custom_service::person::Request::male;
        person.request.age = count;
        count++;
        ROS_INFO("Calling server to show: [%s, %d, %d]",
                 person.request.name.c_str(),
                 person.request.age,
                 person.request.sex);

        person_clt.call(person);

        int result_copy = std::atoi(person.response.result.c_str());

        if (result_copy == person.request.age)
        {
            ROS_INFO("Show result: %s", person.response.result.c_str());
        }
        else
        {
            ROS_ERROR("Server closed or network failed. Node exit.");
            ros::shutdown();
            return 0;
        }

        loop_rate.sleep();
        ros::spinOnce();
    }

    return 0;
}