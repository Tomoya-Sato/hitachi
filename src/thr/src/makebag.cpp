#include <ros/ros.h>
#include <rosbag/bag.h>

#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transform.h>
#include <pcl_conversions/pcl_conversions.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "const_bag");
    ros::NodeHandle n;
    ros::NodeHandle private_nh("~");

    ros::Rate loop_rate(10);

    sensor_msgs::PointCloud2 msg;
    pcl::PointCloud<pcl::PointXYZI>::Ptr scan(new pcl::PointCloud<pcl::PointXYZI>);

    pcl::io::loadPCDFile(rosbag_name, *scan);

    toROSMsg(*scan, msg);

    msg.header.frame_id = "velodyne";

    std::string output_bag_name;
    private_nh.param("outputfile", output_bag_name, std::string("output.bag"));
    ROS_INFO("Output bag name %s", output_bag_name.c_str());

    rosbag::Bag out_bag;
    out_bag.open(output_bag_name, rosbag::bagmode::Write);

    while (ros::ok())
    {
        msg.header.stamp = ros::Time::now();
        out_bag.write("/points_raw", scanf->header.stamp, *scan);

        loop_rate.sleep();
    }

    return 0;
}