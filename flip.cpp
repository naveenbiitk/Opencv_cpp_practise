#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry>
#include <mav_msgs/RollPitchYawrateThrust.h>
#include <sensor_msgs/Imu.h>
#include <stdio.h>
#include <tf/transform_datatypes.h>

using namespace std;

geometry_msgs::Pose current_pose;
double vel_z=0, roll_=0, pitch_=0;


void imu_callback(const sensor_msgs::Imu &msg)
{
	tf::Quaternion quat_(msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w);
	tf::Matrix3x3 m1(quat_);
	double yaw_marker =0;
	m1.getRPY(roll_,pitch_,yaw_marker);
	cout<<"roll "<<roll_<<endl;
}


void pose_callback(const nav_msgs::Odometry& msg)
{
	current_pose.position.z=msg.pose.pose.position.z;
	vel_z=msg.twist.twist.linear.z;
}


int main(int argc,char** argv)
{
	ros::init(argc,argv,"flip_node");
	ros::Nodehandle nh;
	
	nh.Publisher thrust_pub=nh.advertise<mav_msgs::RollPitchYawrateThrust>("/mavros/setpoint_raw/roll_pitch_yawrate_thrust",10);

	nh.Subscriber current_pose_sub=nh.subscribe("/mavros/local_position/odom",100,pose_callback);
	nh.Subscriber imu_sub=nh.subscribe("/mavros/imu/data",100,imu_callback);
	ros::Rate loop_rate(100);

	float last_position = 0;
	int i=0, count=0;
	float k_d,k_p;
	string mode_;

	while(ros::ok())
	{

		nh.getParam("/flip_node/mode_",mode_);
		nh.getParam("/flip_node/k_d",k_d);
		nh.getParam("/flip_node/k_p",k_p);

		geometry_msgs::Pose msg;
		msg.position.z=current_pose.position.z;

		float error_z;
		mav_msgs::RollPitchYawrateThrust thrust_cmd;
		thrust_cmd.header.stamp=ros::Time::now();
		error_z=3-msg.position.z;

		if(mode_=="hover")
		{
			if(i>0)
				thrust_cmd.thrust.z= (19.1 + (error_z*k_p) - ((msg.position.z-last_position)*k_d));
		}
		if(mode_=="flip")
		{
			if((vel_z<3) && (roll_<1 && roll_>-1) && count<1 )
				thrust_cmd.thrust.z=100;
			else
			{
				if(count<30)
				{
					thrust_cmd.roll=3.1;
					thrust_cmd.thrust.z=15;
					count++;
				}
				else
					thrust_cmd.thrust.z=0;

				if((roll_ < -0.2) && (roll_ > -1))
				{
					nh.setParam("/flip_node/mode_","hover");
					count=0;
				}
			}
		}

		thrust_pub.publish(thrust_cmd);

		last_position = msg.position.z;
		i++;
		ros::spinOnce();
		loop_rate.sleep();
	}
}

