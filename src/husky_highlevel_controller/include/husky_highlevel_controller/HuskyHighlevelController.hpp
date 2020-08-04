#pragma once

#include <ros/ros.h>
#include <iostream>
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/Marker.h"
#include <math.h>

namespace husky_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class HuskyHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	HuskyHighlevelController(ros::NodeHandle& nodeHandle);
	void laserCallback(const sensor_msgs::LaserScan &msgs);

	/*!
	 * Destructor.
	 */
	virtual ~HuskyHighlevelController();

private:
	ros::NodeHandle nodeHandle_;
	geometry_msgs::Twist cmdVel;
	ros::Publisher cmdPublisher;
	ros::Publisher markerPulisher;
	ros::Subscriber laserSubscriber;
	visualization_msgs::Marker markerRviz;


};

} /* namespace */
