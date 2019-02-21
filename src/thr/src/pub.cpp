#include <stdio.h>
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>

#include <chrono>

#define N 1024


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "initialpose_publisher");

    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 1);
    ros::Publisher goal_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);

    geometry_msgs::PoseWithCovarianceStamped initPos;

    ros::Time time_now;
    
    initPos.header.frame_id = "world";
    initPos.pose.pose.position.x = -39.47;
    initPos.pose.pose.position.y = 13.73;
    initPos.pose.pose.position.z = 0.0;
    initPos.pose.pose.orientation.x = 0.0;
    initPos.pose.pose.orientation.y = 0.0;
    initPos.pose.pose.orientation.z = -0.2;
    initPos.pose.pose.orientation.w = 0.97;

    double tmp[36] = {0.25, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.06853891945200942};
    for (int i = 0; i < 36; i++) {
        initPos.pose.covariance[i] = tmp[i];
    }

    geometry_msgs::PoseStamped goalPos;

    goalPos.header.frame_id = "world";
    goalPos.pose.position.x = -58.4993209839;
    goalPos.pose.position.y = 14.6826095581;
    goalPos.pose.position.z = 0;
    goalPos.pose.orientation.x = 0.0;
    goalPos.pose.orientation.y = 0.0;
    goalPos.pose.orientation.z = 0.20759190785;
    goalPos.pose.orientation.w = 0.978215518071;

    int x;
    std::cout << "0: /initialpose, 1: /goalpose" << std::endl;
    while (scanf("%d", &x) != EOF) {
        if (x == 0) {
            time_now = ros::Time::now();
            initPos.header.stamp = time_now;

            pub.publish(initPos);
            std::cout << "publish /initialpose." << std::endl;
        }
        else if (x == 1) {
            time_now = ros::Time::now();
            goalPos.header.stamp = time_now;

            goal_pub.publish(goalPos);
            std::cout << "publish /goalpose." << std::endl;
        }
        std::cout << "0: /initialpose, 1: /goalpose" << std::endl;
    }

    return 0;
}
