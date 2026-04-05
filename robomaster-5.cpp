// #include <iostream>
// #include <cmath>
// #include <vector>
// #include <queue>
//
// struct point
// {
//     int x, y;
//     point(int x=0, int y=0): x(x), y(y) {}
//      bool operator==(const point& other) const { return x == other.x && y == other.y; };//第60行使point能==const point
// };
// struct node
// {
//     point father_node;
//     point this_node;
//     double distance_start;
//     double distance_end;
//     double distance_total ;
//     node(point father_node, point this_node,double start,double end): father_node(father_node),this_node(this_node),distance_start(start),distance_end(end),distance_total(distance_start+distance_end){}
// };
// void Bresenham(const point &start,const point &target);
// double distance(const point &start,const point &target);
// void jps(const point &start,const point &target);
// void jump(int &nx,int &ny,const int &dx,const int &dy,node &temp, const point &target);//直线方法
// void jump2(node &temp,const point &target);//斜线方法
// void result(const int &x,const int &y);
// struct cmp
// {
//     bool operator()(const node &a,const node &b)
//     {return a.distance_total>b.distance_total;}
// };
// std::queue<point> path;
// std::priority_queue<node,std::vector<node>,cmp> jump_point;
// std::vector<std::vector<bool>> map(18, std::vector<bool>(14, 1));//开大一圈防越界
// std::vector<std::vector<bool>> visited(18, std::vector<bool>(14, false));//标记访问过的跳点
// std::vector<std::vector<point>>jump_back(17, std::vector<point>(13,point(-1,-1)));//标记相连跳点
// std::vector<std::vector<double>>value(17, std::vector<double>(13,INT_MAX));//记录跳点的总权重
// int dx[]={0, 0, 1, -1,1,1,-1,-1};
// int dy[]={1, -1, 0, 0,1,-1,1,-1};
//
// int main()
// {
//     map[3][9]=map[4][9]=map[5][9]=map[6][9]=0;
//     map[6][3]=map[6][4]=map[6][5]=map[6][6]=0;
//     map[7][5]=map[8][5]=map[9][5]=map[10][5]=map[11][5]=0;
//     map[12][3]=map[12][4]=map[12][5]=map[12][5]=0;
//     jps(point(9,4),point(4,11));
//     result(4,11);
//     while(!path.empty())
//     {
//         std::cout<<"("<<path.front().x<<","<<path.front().y<<")"<<std::endl;
//         path.pop();
//     }
// }
// void result(const int &x,const int &y)
//     {
//     if (x==-1)return;
//     Bresenham(jump_back[x][y],point(x,y));
//     result(jump_back[x][y].x,jump_back[x][y].y);
//     }
// void jps(const point &start,const point &target)
// {
//     jump_point.push(node(start, start, 0, distance(start, target)));
//     while (!jump_point.empty())
//     {
//         auto temp = jump_point.top();
//         jump_point.pop();
//         if (visited[temp.this_node.x][temp.this_node.y]) continue;
//         visited[temp.this_node.x][temp.this_node.y] = true;
//         //8个方向搜索
//         if (temp.this_node == target)break;
//         for (int i=0;i<8;i++)
//         {
//             int nx = temp.this_node.x + dx[i];
//             int ny = temp.this_node.y + dy[i];
//             if (nx < 1 || nx >= 17 || ny < 1 || ny >= 13||!map[nx][ny])continue;
//             if (target.x == nx && target.y == ny)
//             {
//                 jump_back[target.x][target.y] = temp.this_node;
//                 return;
//             }
//             if (dx[i]==0||dy[i]==0)//直线方向
//             {
//                 jump(nx,ny,dx[i],dy[i],temp,target);
//             }
//             else
//             {
//                 while (nx >= 1 && nx < 17 && ny >= 1 && ny < 13)
//                 {
//                     if (target.x == nx && target.y == ny)
//                     {
//                         jump_back[target.x][target.y] = temp.this_node;
//                         return;
//                     }
//                     if (!map[nx][ny])break;
//                     jump(nx,ny,dx[i],0,temp,target);
//                     jump(nx,ny,0,dy[i],temp,target);
//                     nx += dx[i]; ny += dy[i];
//                 }
//                // node new_node(temp.this_node,point(nx,ny),0,0);
//                //  jump2(new_node,target);
//             }
//         }
//     }
// }
// void jump(int &temp_nx,int &temp_ny,const int &dx,const int &dy,node &temp, const point &target)
// {
//     int nx=temp_nx,ny=temp_ny;
//     while (nx >= 1 && nx < 17 && ny >= 1 && ny < 13)
//     {
//         if (target.x == nx && target.y == ny)
//         {
//             jump_back[target.x][target.y] = temp.this_node;
//             return;
//         }
//         if (!map[nx][ny])break;
//         if (dx==0)
//         {
//             if (!map[nx+1][ny]||!map[nx-1][ny])
//             {
//                 node new_node(temp.this_node,point(nx,ny),temp.distance_start+distance(temp.this_node,point(nx,ny)),distance(point(nx,ny),target));
//                 if (value[nx][ny]>new_node.distance_total)
//                 {
//                     value[nx][ny] = new_node.distance_total;
//                     jump_back[nx][ny]=temp.this_node;
//                     jump_point.push(new_node);
//                 }
//             }
//         }
//         if (dy==0)
//         {
//             if (!map[nx][ny+1]||!map[nx][ny-1])
//             {
//                 node new_node(temp.this_node,point(nx,ny),temp.distance_start+distance(temp.this_node,point(nx,ny)),distance(point(nx,ny),target));
//                 if (value[nx][ny]>new_node.distance_total)
//                 {
//                     value[nx][ny] = new_node.distance_total;
//                     jump_back[nx][ny]=temp.this_node;
//                     jump_point.push(new_node);
//                 }
//             }
//         }
//         nx+=dx;
//         ny+=dy;
//     }
// }
//
// // void jump2(node &temp,const point &target)
// // {
// //     for (int i=0;i<8;i++)
// //     {
// //         int nx = temp.this_node.x + dx[i];
// //         int ny = temp.this_node.y + dy[i];
// //         if (nx < 1 || nx >= 17 || ny < 1 || ny >= 13||!map[nx][ny])continue;
// //         if (target.x == nx && target.y == ny)
// //         {
// //             jump_back[target.x][target.y] = temp.this_node;
// //             return;
// //         }
// //         if (dx[i]==0||dy[i]==0)//直线方向
// //         {
// //             jump(nx,ny,i,temp,target);
// //         }
// //         else
// //         {
// //             node new_node(temp.this_node,point(nx,ny),0,0);
// //             jump2(new_node,target);
// //         }
// //     }
// // }
// void Bresenham(const point &start,const point &target)
// {
//     if(start.x < 1 || start.x >= 17 || start.y < 1 || start.y >= 13) return;
//     int dx=std::abs(target.x-start.x);
//     int dy=std::abs(target.y-start.y);
//     int y_increase=start.y<target.y?1:-1;
//     int x_increase=start.x<target.x?1:-1;
//     int E=dx-dy;
//     int x=start.x,y=start.y;
//     while (!(x==target.x&&y==target.y))
//     {
//         if(2*E>-dy)
//         {
//             E-=dy;
//             x+=x_increase;
//         }
//         if(2*E<dx)
//         {
//             E+=dx;
//             y+=y_increase;
//         }
//         if(x >= 1 && x < 17 && y >= 1 && y < 13)
//             path.emplace(x,y);
//         else
//             break;
//     }
// }
// double distance(const point &start,const point &target)
// {
//     return sqrt((target.x-start.x)*(target.x-start.x)+(target.y-start.y)*(target.y-start.y));
// }
// // if (start.x < 1 || start.x >= 17 || start.y < 1 || start.y >= 13) return;
// //     if (target.x < 1 || target.x >= 17 || target.y < 1 || target.y >= 13) return;50行不需要的边界判断
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <climits>  // 添加 INT_MAX
#include <functional>

struct point
{
    int x, y;
    point(int x=0, int y=0): x(x), y(y) {}
    bool operator==(const point& other) const { return x == other.x && y == other.y; }
};

struct node
{
    point father_node;
    point this_node;
    double distance_start;
    double distance_end;
    double distance_total;
    node(point father_node, point this_node, double start, double end)
        : father_node(father_node), this_node(this_node),
          distance_start(start), distance_end(end),
          distance_total(distance_start + distance_end) {}
};

// 统一数组大小为 18×14
std::vector<std::vector<bool>> map(18, std::vector<bool>(14, true));
std::vector<std::vector<bool>> visited(18, std::vector<bool>(14, false));
std::vector<std::vector<point>> jump_back(18, std::vector<point>(14, point(-1, -1)));
std::vector<std::vector<double>> value(18, std::vector<double>(14, INT_MAX));

std::queue<point> path;
std::priority_queue<node, std::vector<node>,
    std::function<bool(const node&, const node&)>>
    jump_point([](const node& a, const node& b) {
        return a.distance_total > b.distance_total;
    });

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

double distance(const point& start, const point& target)
{
    return sqrt(pow(target.x - start.x, 2) + pow(target.y - start.y, 2));
}

void Bresenham(const point& start, const point& target)
{
    if (start == target) return;
    if (start.x < 1 || start.x >= 17 || start.y < 1 || start.y >= 13) return;
    if (target.x < 1 || target.x >= 17 || target.y < 1 || target.y >= 13) return;

    int x = start.x, y = start.y;
    int target_x = target.x, target_y = target.y;
    int dx = std::abs(target_x - x);
    int dy = std::abs(target_y - y);
    int sx = (x < target_x) ? 1 : -1;
    int sy = (y < target_y) ? 1 : -1;
    int err = dx - dy;

    while (x != target_x || y != target_y)
    {
        if (x >= 1 && x < 17 && y >= 1 && y < 13)
            path.emplace(x, y);

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
    }
    // 添加终点
    if (target_x >= 1 && target_x < 17 && target_y >= 1 && target_y < 13)
        path.emplace(target_x, target_y);
}

void jump(int cx, int cy, int dx, int dy, node& temp, const point& target)
{
    while (cx >= 1 && cx < 17 && cy >= 1 && cy < 13)
    {
        if (!map[cx][cy]) break;

        // 到达目标点
        if (cx == target.x && cy == target.y)
        {
            jump_back[cx][cy] = temp.this_node;
            double g = temp.distance_start + distance(temp.this_node, point(cx, cy));
            if (value[cx][cy] > g)
            {
                value[cx][cy] = g;
                jump_point.push(node(temp.this_node, point(cx, cy), g, 0));
            }
            return;
        }

        // 跳点检测：直线方向有障碍物或到达边界
        bool is_jump_point = false;
        if (dx == 0 && (!map[cx + 1][cy] || !map[cx - 1][cy]))
            is_jump_point = true;
        if (dy == 0 && (!map[cx][cy + 1] || !map[cx][cy - 1]))
            is_jump_point = true;

        if (is_jump_point)
        {
            double g = temp.distance_start + distance(temp.this_node, point(cx, cy));
            double h = distance(point(cx, cy), target);
            if (value[cx][cy] > g + h)
            {
                value[cx][cy] = g + h;
                jump_back[cx][cy] = temp.this_node;
                jump_point.push(node(temp.this_node, point(cx, cy), g, h));
            }
        }

        cx += dx;
        cy += dy;
    }
}

void jps(const point& start, const point& target)
{
    // 初始化
    for (auto& row : visited) std::fill(row.begin(), row.end(), false);
    for (auto& row : value) std::fill(row.begin(), row.end(), INT_MAX);
    for (auto& row : jump_back) std::fill(row.begin(), row.end(), point(-1, -1));

    // 起点处理
    visited[start.x][start.y] = true;
    value[start.x][start.y] = 0;
    jump_point.push(node(start, start, 0, distance(start, target)));

    while (!jump_point.empty())
    {
        auto temp = jump_point.top();
        jump_point.pop();

        if (visited[temp.this_node.x][temp.this_node.y]) continue;
        visited[temp.this_node.x][temp.this_node.y] = true;

        // 到达目标
        if (temp.this_node == target)
        {
            jump_back[target.x][target.y] = temp.father_node;
            break;
        }

        // 8 个方向搜索
        for (int i = 0; i < 8; i++)
        {
            int nx = temp.this_node.x + dx[i];
            int ny = temp.this_node.y + dy[i];

            if (nx < 1 || nx >= 17 || ny < 1 || ny >= 13 || !map[nx][ny])
                continue;

            if (dx[i] == 0 || dy[i] == 0)  // 直线方向
            {
                jump(nx, ny, dx[i], dy[i], temp, target);
            }
            else  // 斜线方向
            {
                // 斜线方向也需要检查强制邻居
                jump(nx, ny, dx[i], dy[i], temp, target);
            }
        }
    }
}

void result(const point& start, const point& target)
{
    int cx = target.x, cy = target.y;
    int count = 0;
    int max_count = 18 * 14;  // 防止死循环

    while (count < max_count)
    {
        if (cx < 1 || cx >= 17 || cy < 1 || cy >= 13) break;

        point parent = jump_back[cx][cy];
        if (parent.x == -1 && parent.y == -1) break;

        Bresenham(parent, point(cx, cy));

        // 到达起点
        if (parent == start) break;

        cx = parent.x;
        cy = parent.y;
        count++;
    }
}

int main()
{
    // 设置障碍物 (0 表示障碍)
    map[3][9] = map[4][9] = map[5][9] = map[6][9] = false;
    map[6][3] = map[6][4] = map[6][5] = map[6][6] = false;
    map[7][5] = map[8][5] = map[9][5] = map[10][5] = map[11][5] = false;
    map[12][3] = map[12][4] = map[12][5] = false;

    point start(9, 4);
    point target(4, 11);

    jps(start, target);
    result(start, target);

    std::cout << "Path length: " << path.size() << std::endl;
    while (!path.empty())
    {
        std::cout << "(" << path.front().x << "," << path.front().y << ")" << std::endl;
        path.pop();
    }

    return 0;
}