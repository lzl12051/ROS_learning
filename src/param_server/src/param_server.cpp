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
        //std::cout << i << "  " << keyIn[i] << std::endl;
    }
}

void setParam(int size, std::string *keyIn, double *valueIn)
{
    for (int i = 0; i < size; i++)
    {
        ros::param::set(keyIn[i], valueIn[i]);
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
    int size_of_list = sizeof(key_list) / 32;
    getParam(sizeof(key_list) / 32, key_list);
    double value_list[size_of_list];
    for(int i=0;i<size_of_list;i++)
    {
        std::cout<<"Please input the parameter "<<i<<": ";
        std::cin>>value_list[i];
    }
    setParam(size_of_list, key_list, value_list);
    getParam(sizeof(key_list) / 32, key_list);


    return 0;
}