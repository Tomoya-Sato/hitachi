#include <ros/ros.h>
#include <rosbag/bag.h>

#include <pcl_ros/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>

#include <std_msgs/Bool.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "const_bag");
    ros::NodeHandle n;
    ros::NodeHandle private_nh("~");

    ros::Rate loop_rate(30);

    std_msgs::Bool msg;
    msg.data = true;

    rosbag::Bag out_bag;
    out_bag.open("dammy.bag", rosbag::bagmode::Write);

    int cnt = 0;
    int max_loop;
    private_nh.param("max_loop", max_loop, 3000000);

    while (ros::ok())
    {
        out_bag.write("/dammy_bool", ros::Time::now(), msg);

        cnt++;
        if (cnt >= max_loop) break;

        if (cnt % 30 == 0) std::cout << "loop count: " << cnt << "\r" << std::flush;

        loop_rate.sleep();
    }

    std::cout << "finish." << std::endl;

    out_bag.close();

    // sensor_msgs::PointCloud2 msg;
    // pcl::PointCloud<pcl::PointXYZI>::Ptr scan(new pcl::PointCloud<pcl::PointXYZI>);

    // std::string pcd_name;
    // private_nh.param("pcdfile", pcd_name, std::string("dump.pcd"));
    // pcl::io::loadPCDFile(pcd_name, *scan);

    // toROSMsg(*scan, msg);

    // msg.header.frame_id = "velodyne";

    // std::string output_bag_name;
    // private_nh.param("outputfile", output_bag_name, std::string("output.bag"));
    // ROS_INFO("Output bag name %s", output_bag_name.c_str());

    // rosbag::Bag out_bag;
    // out_bag.open(output_bag_name, rosbag::bagmode::Write);

    // int cnt = 0;
    // int max_loop;
    // private_nh.param("max_loop", max_loop, 100000);
    // while (ros::ok())
    // {
    //     msg.header.stamp = ros::Time::now();
    //     out_bag.write("/points_raw", msg.header.stamp, msg);

    //     if (cnt >= max_loop) break;

    //     cnt++;
    //     std::cout << "loop count: " << cnt << "\r" << std::flush;

    //     loop_rate.sleep();
    // }

    // std::cout << std::endl;
    // out_bag.close();

    return 0;
}