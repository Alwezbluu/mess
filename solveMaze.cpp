#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<iterator>
#define _CONTAINER_DEBUG_LEVEL 1

using namespace std;
//int maze[100][100] = { 0 };//最大地图 内存溢出了
enum status{safe,wall,visited,entry,out};//地图上格子的三种情况，0对应可以走，1对应墙，2对应已经走过，3为入口，4为出口

struct node {
    int x;
    int y;
    int di;//走过的方向
    status STATUS;
    node* prev;
};

bool valid(int x, int y,int row,int col,node* ROAD) {
    if (x >= col || x < 0 || y >= row || y < 0)
        return false;
    if (ROAD[x * col + y].STATUS == 1|| ROAD[x * col + y].STATUS == 2)
        return false;
    return true;
}//判断该位置是否可移动

pair<int, int>nextmove(int latestx, int latesty, int row, int col, node* ROAD) {
    bool find = false;
    int temp1=0, temp2=0;
    while (ROAD[latestx * col + latesty].di < 4 && !find)//依次查找四个方向
    {   
        
        ROAD[latestx * col + latesty].di++;//初值为-1
       
        switch (ROAD[latestx * col + latesty].di)//四个方向
        {
        case 0:temp1 = latestx + 1, temp2 = latesty; break;
        case 1:temp1 = latestx - 1, temp2 = latesty; break;
        case 2:temp1 = latestx, temp2 = latesty + 1; break;
        case 3:temp1 = latestx, temp2 = latesty - 1; break;
        }
        if (valid(temp1, temp2, row,  col,  ROAD))
        {
            find = true;//找到可走方块(temp1,temp2)
            return make_pair(temp1, temp2);
        }
    }
    if (ROAD[latestx * col + latesty].di >= 4 && !find) {
        ROAD[latestx * col + latesty].di = -1;
    }//>=4即四个方向访问完毕，没有可走路径，即将回溯，将当前位置的di重新改为-1，意为可以尝试该节点的其他方向
    return make_pair(-1, -1);
}

//最短路径长度初始化
void getpath(int x, int y, int finalx, int finaly,int maze[13][13],int row,int col,node* ROAD){//,int&shortestlength,stack<node*>shortest) {
    int order = 1;//shortest path order
    int num = 1;//路径编号
    int flag = 0;//found or not
    int min = 9999;
    stack<node*>nodestack;//用于存储即将访问节点
    ROAD[x * col + y].STATUS = visited;//起点状态改为visited防止重复
    
    nodestack.push(&ROAD[x*col+y]);//起点压入当前即将访问栈
   

    while (!nodestack.empty()) {//还有即将访问节点就一直循环，直到全部访问结束
      
       node* current = nodestack.top();
        pair<int,int>location=make_pair(current->x,current->y);//当前坐标
       
        
      //找到终
        if ( location.first==finalx&&location.second==finaly) {
            flag = 1;//founded
            if (nodestack.size() + 1 < min) {//判断是否为最短路径
                min = nodestack.size() + 1;
                order = num;//最短长度为当前路径
            }
            stack<pair< int, int>> track;
           while (current!=nullptr) {
               track.push(make_pair(current->x, current->y));
               current = current->prev;
           }//压入track栈再输出路径
     
           cout << "路径" << num++ << ":";
           while (!track.empty()) {
               pair<int, int>coord = track.top();
               track.pop();
               cout << "(" << coord.first << "," << coord.second << ")";
               
              
           }
           
           cout << endl;
           if(!nodestack.empty()){nodestack.top()->STATUS = safe;//问题的关键，，之前都是走到终点前一个死活到不了，，原来是因为没有修改重点状态就pop掉了
           if (!nodestack.empty()) {
               nodestack.pop();
               if (!nodestack.empty()) {
                   nodestack.top()->STATUS = safe;
                   current = nodestack.top();
               }
           }}
           
           
          continue;
       }//输出路径正常运作
       
       pair<int, int>coordinate = nextmove(location.first, location.second, row, col, ROAD);
       if (coordinate.first==-1) {//没有能走的路了
           if (!nodestack.empty()) {
               //回溯上一位置
              nodestack.top()->STATUS = safe;
               nodestack.pop();
               
           }
          
        
       }
       
        else {
           //current = nodestack.top();
            int h = coordinate.first;
            int j = coordinate.second;
            node* next = &(ROAD[h * col + j]);
            nodestack.push(next);//这部没起作用，哪里出了问题   判断完nextmove后current没有改变依然是起点，//好了
            next->STATUS = visited;//可以访问，将该位置标记为访问ed
            next->prev = current;//连上，后面输出路径
            //现在栈顶为新位置
        }

    }
    if (flag == 1) {
        cout << "最短路径为路径" << order;
    }
    else { cout << "没有通路:-(" << endl; }
}
 



int main() {
    int maze[13][13] = { 0 };
//1,0,1,1,1,1,1,1,1,1,1,1,1,
//1,0,0,0,0,0,1,0,0,0,0,0,1,
//1,1,1,1,1,0,1,0,1,1,1,0,1,
//1,0,0,0,1,0,1,0,0,0,1,0,1,
//1,0,1,1,1,0,1,1,1,0,1,1,1,
//1,0,0,0,1,0,0,0,1,0,0,0,1,
//1,0,1,0,1,1,1,0,1,0,1,0,1,
//1,0,1,0,1,0,0,0,0,0,1,0,1,
//1,0,1,0,1,0,1,0,1,1,1,0,1,
//1,0,1,0,0,0,1,0,1,0,0,0,1,
//1,0,1,1,1,1,1,1,1,0,1,0,1,
//1,0,0,0,0,0,0,0,0,0,1,0,0,
//1,1,1,1,1,1,1,1,1,1,1,1,1
//}; 

    node ROAD[200] = { 0 };
    //int m=13, n=13;
int m = 0, n = 0;
    cout << "请输入目标迷宫行数及列数" << endl;
    scanf_s("%d %d", &m, &n);//
    cout << "请输入目标迷宫：" << endl;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < m;j++) {
            cin >> maze[i][j];
            ROAD[i * n + j] = { i,j,-1,status(maze[i][j]) };
        }
    }//导入迷宫
    //int a =11, b=12 ;
    int a = 0, b = 0;
    cout << "请输入迷宫终点" << endl;
    cin >> a >> b;
    ROAD[a * n + b].STATUS = status(0);
    maze[a][b] = 0;
    //int c=0 , d =1;
    int c=0,d=0;
    cout << "请输入迷宫起点" << endl;
    cin >> c >> d;
    ROAD[c * n + d].STATUS = status(0);
    maze[c][d] = 0;
    cout << "所有路径:" << endl;
    //bfs(c, d, a, b, maze, m, n, ROAD);
    getpath(c, d, a, b, maze, m, n, ROAD);//,shortestlength,shortest);
    
    return 0;


}