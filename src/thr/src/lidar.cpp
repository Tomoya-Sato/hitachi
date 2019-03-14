#include <stdio.h>
#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <errno.h>

#include <pcl_conversions/pcl_conversions.h>


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "lidar_publisher");

    ros::NodeHandle n;

    ros::Publisher points_pub = n.advertise<sensor_msgs::PointCloud2>("/points_raw", 1);

    ros::Rate loop_rate(10);

    sensor_msgs::PointCloud2 msg;
    pcl::PointCloud<pcl::PointXYZI>::Ptr scan(new pcl::PointCloud<pcl::PointXYZI>);

    pcl::io::loadPCDFile("const.pcd", *scan);

    toROSMsg(*scan, msg);

    std::cout << "frame_id: " << msg.header.frame_id << std::endl;

    msg.header.frame_id = "velodyne";

    while (ros::ok())
    {
        msg.header.stamp = ros::Time::now();
        points_pub.publish(msg);
        
        loop_rate.sleep();
    }

    return 0;
}