#include <stdio.h>
#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/PointCloud2.h>
#include <errno.h>

#include <chrono>

std::chrono::time_point<std::chrono::system_clock> start, end;

void start_callback(const sensor_msgs::PointCloud2::ConstPtr &msg)
{
    start = std::chrono::system_clock::now();
    return;
}

void end_callback(geometry_msgs::PoseStamped msg)
{
    end = std::chrono::system_clock::now();
    double time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;

    FILE *fp = fopen("round_trip.csv", "a");
    if (fp == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%lf\n", time);
    fclose(fp);

    return;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "time_measure");

    ros::NodeHandle n;

    ros::Subscriber start_sub = n.subscribe("/points_raw", 1, start_callback);
    ros::Subscriber end_sub = n.subscribe("/ndt_pose", 1, end_callback);

    ros::spin();

    return 0;
}