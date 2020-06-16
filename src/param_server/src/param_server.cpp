#include <ros/ros.h>
#include <std_srvs/Empty.h>

void getParam(int size, std::string *keyIn)
{
    //std::cout<<sizeof(&keyIn)<<std::endl;
    for (int i = 0; i < size; i++)
    {
        int key1;
        ros::param::get(keyIn[i], key1);
        ROS_INFO("%d", key1);
        std::cout << i << "  " << keyIn[i] << std::endl;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Param_server");
    ros::NodeHandle nh;

    //std::string key = "/background_r";
    std::string key_list[] = {"/run_id",
                              "turtlesim/background_r",
                              "/turtlesim/background_b",
                              "/turtlesim/background_g"};
    //std::string key = "/run_id";
    //std::string *p = key_list;
    std::cout << sizeof(key_list) / 32 << std::endl;
    getParam(sizeof(key_list) / 32, key_list);

    return 0;
}