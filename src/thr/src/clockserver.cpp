#include <ros/ros.h>
#include <rosgraph_msgs/Clock.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "clock_server");

    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<rosgraph_msgs::Clock>("/clock", 10);

    rosgraph_msgs::Clock msg;
    ros::Time tmp;
    ros::WallTime tmp_wall;

    while (ros::ok())
    {
        tmp_wall = ros::WallTime::now();
        tmp.sec = tmp_wall.sec;
        tmp.nsec = tmp_wall.nsec;
        msg.clock = tmp;
        pub.publish(msg);
    }

    return 0;
}