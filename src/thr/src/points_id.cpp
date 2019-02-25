#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <grid_map_msgs/GridMap.h>

int points_raw = 0;
int filtered_points = 0;
int ndt_pose = 0;
int ground_filter = 0;
int real_cost = 0;
int grid_map = 0;

void print_cnt() {
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "points_raw     : " << points_raw << std::endl;
    std::cout << "filtered_points: " << filtered_points << std::endl;
    std::cout << "ndt_pose       : " << ndt_pose << std::endl;
    std::cout << "ground_filter  : " << ground_filter << std::endl;
    std::cout << "real_cost      : " << real_cost << std::endl;
    std::cout << "grid_map       : " << grid_map << std::endl;
}

void points_callback(const sensor_msgs::PointCloud2::ConstPtr &msg) {

    points_raw++;

    // print_cnt();
}

void filtered_callback(const sensor_msgs::PointCloud2::ConstPtr &msg) {

    filtered_points++;
    // print_cnt();
}

void ndt_callback(geometry_msgs::PoseStamped msg) {

    ndt_pose++;
    // print_cnt();
}

void ground_callback(const sensor_msgs::PointCloud2::ConstPtr &msg) {

    ground_filter++;
    // print_cnt();
}

void real_callback(nav_msgs::OccupancyGrid msg) {

    real_cost++;
    // print_cnt();
}

void grid_callback(grid_map_msgs::GridMap msg) {

    grid_map++;
    // print_cnt();
}

int main(int argc, char *argv[]) {

    ros::init(argc, argv, "id_server");

    ros::NodeHandle n;
    ros::NodeHandle private_nh("~");

    private_nh.param("points_raw_number", points_raw, 0);
    private_nh.param("filtered_points_number", filtered_points, 0);
    private_nh.param("ndt_pose_number", ndt_pose, 0);
    private_nh.param("points_no_ground_number", ground_filter, 0);
    private_nh.param("realtime_cost_map_number", real_cost, 0);
    private_nh.param("filtered_grid_map_number", grid_map, 2);

    ros::Subscriber points_sub = n.subscribe("points_raw", 10, points_callback);
    ros::Subscriber filtered_sub = n.subscribe("filtered_points", 100, filtered_callback);
    ros::Subscriber ndt_sub = n.subscribe("ndt_pose", 100, ndt_callback);
    ros::Subscriber ground_sub = n.subscribe("points_no_ground", 100, ground_callback);
    ros::Subscriber real_sub = n.subscribe("realtime_cost_map", 100, real_callback);
    ros::Subscriber grid_sub = n.subscribe("filtered_grid_map", 100, grid_callback);

    while (ros::ok())
    {
        ros::spinOnce();

        private_nh.setParam("points_raw_number", points_raw);
        private_nh.setParam("filtered_points_number", filtered_points);
        private_nh.setParam("ndt_pose_number", ndt_pose);
    }

    return 0; 
}