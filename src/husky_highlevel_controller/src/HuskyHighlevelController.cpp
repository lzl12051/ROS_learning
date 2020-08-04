#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

namespace husky_highlevel_controller {

    void HuskyHighlevelController::laserCallback(const sensor_msgs::LaserScan &msgs) {
        double smallestDis = 100;
        int angleIncrement = 0;
        float smallestAng = 0;
        int scanArrSize = floor((msgs.angle_max - msgs.angle_min) / msgs.angle_increment);

        for (int i = 0; i < scanArrSize; i++) {
            if (msgs.ranges[i] < smallestDis) {
                smallestDis = msgs.ranges[i];
                angleIncrement = i;
            }
        }
        smallestAng = angleIncrement * msgs.angle_increment;
        ROS_INFO("The smallest angle: %f", smallestAng);
        //P controller
        float vel_p, ang_p;
        HuskyHighlevelController::nodeHandle_.getParam("p_vel_gain", vel_p);
        HuskyHighlevelController::nodeHandle_.getParam("p_ang_gain", ang_p);
        HuskyHighlevelController::cmdVel.angular.z = (ang_p + 0.2) * (2.35619 - smallestAng);
        if (smallestDis == 100) {
            HuskyHighlevelController::cmdVel.linear.x = 0;
        } else {
            HuskyHighlevelController::cmdVel.linear.x = vel_p * smallestDis - 0.2;
        }
        HuskyHighlevelController::cmdPublisher.publish(cmdVel);

        markerRviz.pose.position.x = smallestDis * std::cos(2.35619 - smallestAng);
        markerRviz.pose.position.y = smallestDis * std::sin(2.35619 - smallestAng);
        markerRviz.pose.position.z = 0.5;
        markerRviz.pose.orientation.w = -1.0;

        markerPulisher.publish(markerRviz);

        //ROS_INFO("Max Ang: %f, Min Ang: %f", msgs.angle_max, msgs.angle_min);
        ROS_INFO("The angle: %f, The speed: %f", cmdVel.angular.z, cmdVel.linear.x);
        ROS_INFO("Smallest range is %lf", smallestDis);
    }

    HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle &nodeHandle) :
            nodeHandle_(nodeHandle) {
        ROS_INFO("Function running");
        int queueSize;
        HuskyHighlevelController::nodeHandle_.getParam("queueSize", queueSize);
        HuskyHighlevelController::laserSubscriber = nodeHandle_.subscribe("/scan", queueSize,
                                                                          &HuskyHighlevelController::laserCallback,
                                                                          this);
        HuskyHighlevelController::cmdPublisher = nodeHandle_.advertise<geometry_msgs::Twist>("/cmd_vel", queueSize);
        HuskyHighlevelController::markerPulisher = nodeHandle_.advertise<visualization_msgs::Marker>(
                "visualization_marker", queueSize);

        markerRviz.type = visualization_msgs::Marker::SPHERE;
        markerRviz.action = visualization_msgs::Marker::ADD;
        markerRviz.scale.x = 1;
        markerRviz.scale.y = 1;
        markerRviz.scale.z = 1;
        markerRviz.pose.position.z = 0;
        markerRviz.id = 1;
        markerRviz.ns = "Husky";
        markerRviz.header.frame_id = "base_laser";
        markerRviz.header.stamp = ros::Time();
        markerRviz.color.a = 1;
        markerRviz.color.r = 0;
        markerRviz.color.g = 1;
        markerRviz.color.b = 0;

    }

    HuskyHighlevelController::~HuskyHighlevelController() {
    }

} /* namespace */
