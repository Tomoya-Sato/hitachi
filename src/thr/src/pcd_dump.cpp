#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <errno.h>

#include <pcl_conversions/pcl_conversions.h>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

static int flag = 1;

void points_callback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
    if (flag == 1)
    {
        std::cout << "start dumping." << std::endl;
        pcl::PointCloud<pcl::PointXYZI> scan;
        pcl::fromROSMsg(*msg, scan);

        sleep(1);

        if (!pcl::io::savePCDFileBinary("const.pcd", scan))
        {
            perror("pcd dump error");
            exit(EXIT_FAILURE);
        }

        flag = 0;
        std::cout << "end dumping." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pcd_dumper");

    ros::NodeHandle n;

    ros::Subscriber point_sub = n.subscribe("/points_raw", 10, points_callback);

    ros::spin();

    return 0;
}