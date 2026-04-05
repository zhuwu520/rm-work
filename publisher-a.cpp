#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

std::vector<float> yellow = {
    -6.0,6.0,-5.0,6.3,-4.0,6.6,-3.0,6.9,-2.0,6.6,-1.0,6.3,0.0,6.0,1.0,6.3,2.0,6.6,3.0,6.6,4.0,6.3,5.0,6.0,
    5.2,5.0,5.4,4.0,5.6,3.0,5.4,2.0,5.2,1.0,5.0,0.0,5.2,-1.0,5.4,-2.0,5.6,-3.0,5.4,-4.0,5.2,-5.0,5.0,-6.0,
    4.0,-6.3,3.0,-6.6,2.0,-6.6,1.0,-6.3,0.0,-6.0,-1.0,-6.3,-2.0,-6.6,-3.0,-6.9,-4.0,-6.6,-5.0,-6.3,-6.0,-6.0,
    -5.2,-5.0,-5.4,-4.0,-5.6,-3.0,-5.4,-2.0,-5.2,-1.0,-5.0,0.0,-5.2,1.0,-5.4,2.0,-5.6,3.0,-5.4,4.0,-5.2
};
std::vector<float> blue = {
  -4.0,4.1,-2.5,3.7,-4.0,-3.9,1.2,0.3,2.7,3.3,3.9,-1.1  
};
class PublisherA : public rclcpp::Node
{
private:
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher_yellow;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher_blue;
    rclcpp::TimerBase::SharedPtr timer_;

public:
    PublisherA() : Node("publisher_a")
    {
        publisher_yellow = this->create_publisher<std_msgs::msg::Float32MultiArray>("publisher_yellow", 10);
        publisher_blue = this->create_publisher<std_msgs::msg::Float32MultiArray>("publisher_blue", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000),[this](){
                auto msg_yellow = std_msgs::msg::Float32MultiArray();
                auto msg_blue = std_msgs::msg::Float32MultiArray();
                msg_yellow.data = yellow;
                msg_blue.data = blue;
                this->publisher_yellow->publish(msg_yellow);
                this->publisher_blue->publish(msg_blue);
            });
            RCLCPP_INFO(this->get_logger(), "Publishera已经发布");
    }
};
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PublisherA>());
  rclcpp::shutdown();
  return 0;
}