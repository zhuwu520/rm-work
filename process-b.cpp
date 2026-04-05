#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"
#include <vector>
#include <climits>
#include <cmath>
class ProcessB : public rclcpp::Node
{
    private:
    rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr subscription_yellow;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr subscription_blue;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector <std::pair<int,int>>yellow_points;
    std::vector <std::pair<int,int>>blue_points;
    std::vector <std::vector<int>>map;
    //std::vector <int>publish;
public:
  ProcessB() : Node("process_b")
  {
    map.resize(12,std::vector<int>(13,0));
    publisher_ = this->create_publisher<std_msgs::msg::Int32MultiArray>("process_b", 10);
    subscription_yellow = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "publisher_yellow", 10, [&](const std_msgs::msg::Float32MultiArray::SharedPtr msg){
        for(size_t i=0;i<msg->data.size();i+=2){
          yellow_points.push_back(std::make_pair((int)(msg->data[i]+6.0f),(int)(msg->data[i+1]+6.0f)));
          Bresenham((int)(msg->data[i]+6.0f),(int)(msg->data[i+1]+6.0f),6,6);
        }
        RCLCPP_INFO(this->get_logger(), "已收到黄色数据");
        subscription_yellow.reset();    
        RCLCPP_INFO(this->get_logger(), "已停止订阅黄色数据");
      }
    );
    subscription_blue = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "publisher_blue", 10, [&](const std_msgs::msg::Float32MultiArray::SharedPtr msg){
        for(size_t i=0;i<msg->data.size();i+=2){
          blue_points.push_back(std::make_pair((int)(msg->data[i]+6.0f),(int)(msg->data[i+1]+6.0f)));
          auto near_point = NearestPoint(yellow_points,std::make_pair((int)(msg->data[i]+6.0f),(int)(msg->data[i+1]+6.0f)));
          Bresenham (near_point.first,near_point.second,(int)(msg->data[i]+6.0f),(int)(msg->data[i+1]+6.0f));
        }
        RCLCPP_INFO(this->get_logger(), "已收到蓝色数据");
        subscription_blue.reset();
        RCLCPP_INFO(this->get_logger(), "已停止订阅蓝色数据");
      }
    );
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]()
        {
          std::vector<int> publish;
          for(int  i=0;i<12;i++)
          {
              for(int j=0;j<13;j++)
              {
                  publish.push_back(i);
                  publish.push_back(j);
                  publish.push_back(map[i][j]);
              }
          }
        for(auto & i: yellow_points)
        {
          map[i.first][i.second] = -1;
        }
        for(auto & i: blue_points)
        {
          map[i.first][i.second] = -1;
        }
        auto msg = std_msgs::msg::Int32MultiArray();
        msg.data = publish;
        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "已成功发布地图信息");
      }
    );
  }
  void Bresenham(const int &x0,const int&y0,const int &target_x,const int &target_y)
  {
    if(x0 < 0 || x0 >= 12 || y0 < 0 || y0 >= 13) return;// 修复 2: 起点边界检查为什么会越界啊
    int dx=std::abs(target_x-x0);
    int dy=std::abs(target_y-y0);
    int y_increase=y0<target_y?1:-1;
    int x_increase=x0<target_x?1:-1;
    int E=dx-dy;
    int x=x0,y=y0;
    while (!(x==target_x&&y==target_y))
    {
        if(2*E>-dy)
        {
            E-=dy;
            x+=x_increase;
        }
        if(2*E<dx)
        {
            E+=dx;
            y+=y_increase;
        }
        if(x >= 0 && x < 12 && y >= 0 && y < 13)// 修复 2: 每次访问前检查边界
        map[x][y]++;
        else
        break;  
    }
  }
  std::pair<int,int> NearestPoint (const std::vector<std::pair<int,int>>& points,const std::pair<int,int>& point)
  {
    int min_distance=INT_MAX;
    int min_x=-1;
    int min_y=-1;
    for(auto& p:points)
    {
        int distance=sqrt(pow(point.first-p.first,2)+pow(point.second-p.second,2));
        if(distance<min_distance)
        {
            min_distance=distance;
            min_x=p.first;
            min_y=p.second;
        }
    }
    return std::make_pair(min_x,min_y);
  }
};
int main(int argc, char**argv)
{ 
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ProcessB>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}