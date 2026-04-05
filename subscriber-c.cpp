#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"
#include <climits>
#include <queue>
#include <algorithm> 
#include <vector>
#include <limits>

class SubscriberC : public rclcpp::Node
{
private:
    rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr subscription_;
    std::vector<std::vector<int>> map;

public:
    SubscriberC() : Node("subscriber_c")
    {
        map.resize(12, std::vector<int>(13, 0));
        subscription_ = this->create_subscription<std_msgs::msg::Int32MultiArray>(
            "process_b", 10, [this](const std_msgs::msg::Int32MultiArray::SharedPtr msg)
            {
    for(size_t i = 0; i < msg->data.size(); i+=3)
    {
        map[msg->data[i]][msg->data[i+1]]=msg->data[i+2];
    }
    RCLCPP_INFO(this->get_logger(),"已接受到地图数据"); 
    std::vector<std::pair<int,int>>path=Dijkstra(map,std::make_pair(1,11),std::make_pair(10,1)); 
    RCLCPP_INFO(this->get_logger(),"已处理完数据");
    path_print(path);
    });
    }
    std::vector<std::pair<int, int>> Dijkstra(const std::vector<std::vector<int>> &map, const std::pair<int, int> &start, const std::pair<int, int> &target)
    {
        std::vector<std::vector<int>> dist(12, std::vector<int>(13, std::numeric_limits<int>::max()));
        std::vector<std::vector<bool>> visited(12, std::vector<bool>(13, false));
        std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> q;
        std::vector<std::vector<std::pair<int, int>>> path_temp(12, std::vector<std::pair<int, int>>(13, std::make_pair(-1, -1)));
        dist[start.first][start.second] = 0;
        q.push(std::make_pair(0, start));
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        while (!q.empty())
        {
            auto id = q.top().second;
            q.pop();
            int x = id.first;
            int y = id.second;
            if (visited[x][y])continue;
            visited[x][y] = true;
            if (x == target.first && y == target.second)break;
            for (int i = 0; i < 4; i++)
            {
                int new_x = x + dx[i];
                int new_y = y + dy[i];
                if (new_x < 0 || new_x >= 12 || new_y < 0 || new_y >= 13) continue; // 矩阵越界
                if (map[new_x][new_y] == -1)continue; // 边界
                if (visited[new_x][new_y])continue; // 已访问
                int new_value = dist[x][y] + map[new_x][new_y];
                if (new_value < dist[new_x][new_y])
                {
                    dist[new_x][new_y] = new_value;
                    path_temp[new_x][new_y] = std::make_pair(x, y);
                    q.push(std::make_pair(new_value, std::make_pair(new_x, new_y)));
                }
            }
        }
        std::vector<std::pair<int, int>> result;
        auto temp = target;
        while (temp.first != -1&&temp.second != -1)
        {
            result.push_back(temp);
            if (temp.first == start.first && temp.second == start.second) break;
            temp = path_temp[temp.first][temp.second];
        }
        std::reverse(result.begin(), result.end()); 
        return result;
    }
    void path_print(const std::vector<std::pair<int,int>>&path)
    {
        for(auto i:path)
        {
            std::cout<<"("<<i.first-6<<","<<i.second-6<<")"<<"->";
        }
    }
};
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SubscriberC>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}