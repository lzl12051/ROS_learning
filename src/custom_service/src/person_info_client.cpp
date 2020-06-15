#include<ros/ros.h>
#include"custom_service/person.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "person_info_client");
    ros::NodeHandle nh;

    //Wait until the service has started
    ros::service::waitForService("show_person");

    //Link to the service
    ros::ServiceClient person_clt = nh.serviceClient<custom_service::person>(
        "show_person");

    //Build the request data
    custom_service::person person;
    person.request.name = "Jack";
    person.request.age = 22;
    person.request.sex = custom_service::person::Request::male;

    ROS_INFO("Calling server to show: [%s, %d, %d]", 
                person.request.name.c_str(),
                person.request.age,
                person.request.sex);
    person_clt.call(person);
    ROS_INFO("Show result: %s", person.response.result.c_str());

    return 0;
}