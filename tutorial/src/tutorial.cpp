#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

class TurtleSim{
	public:
		TurtleSim();
		void poseCallback(const turtlesim::PoseConstPtr& pose);

	private:
		ros::Publisher vel_pub;
		ros::Subscriber pose_sub;
		ros::NodeHandle nh;
};

TurtleSim::TurtleSim(){
	vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
	pose_sub = nh.subscribe<turtlesim::Pose>("turtle1/pose", 1, &TurtleSim::poseCallback, this);
}

void TurtleSim::poseCallback(const turtlesim::PoseConstPtr& pose)
{
    ROS_INFO("x= %lf\ty= %lf", pose->x, pose->y);

    geometry_msgs::Twist nya;
    nya.linear.x = 1.0;
    nya.angular.z = 0.2;

    vel_pub.publish(nya);
}

int main(int argc, char **argv){
	
	ros::init(argc, argv, "move_turtlesim");
	TurtleSim turtleSim;
	
	ROS_INFO("Hello World");
	while(ros::ok()){
		ros::spin();
	}
	return 0;
}
