#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<iterator>
#define _CONTAINER_DEBUG_LEVEL 1

using namespace std;
//int maze[100][100] = { 0 };//����ͼ �ڴ������
enum status{safe,wall,visited,entry,out};//��ͼ�ϸ��ӵ����������0��Ӧ�����ߣ�1��Ӧǽ��2��Ӧ�Ѿ��߹���3Ϊ��ڣ�4Ϊ����

struct node {
    int x;
    int y;
    int di;//�߹��ķ���
    status STATUS;
    node* prev;
};

bool valid(int x, int y,int row,int col,node* ROAD) {
    if (x >= col || x < 0 || y >= row || y < 0)
        return false;
    if (ROAD[x * col + y].STATUS == 1|| ROAD[x * col + y].STATUS == 2)
        return false;
    return true;
}//�жϸ�λ���Ƿ���ƶ�

pair<int, int>nextmove(int latestx, int latesty, int row, int col, node* ROAD) {
    bool find = false;
    int temp1=0, temp2=0;
    while (ROAD[latestx * col + latesty].di < 4 && !find)//���β����ĸ�����
    {   
        
        ROAD[latestx * col + latesty].di++;//��ֵΪ-1
       
        switch (ROAD[latestx * col + latesty].di)//�ĸ�����
        {
        case 0:temp1 = latestx + 1, temp2 = latesty; break;
        case 1:temp1 = latestx - 1, temp2 = latesty; break;
        case 2:temp1 = latestx, temp2 = latesty + 1; break;
        case 3:temp1 = latestx, temp2 = latesty - 1; break;
        }
        if (valid(temp1, temp2, row,  col,  ROAD))
        {
            find = true;//�ҵ����߷���(temp1,temp2)
            return make_pair(temp1, temp2);
        }
    }
    if (ROAD[latestx * col + latesty].di >= 4 && !find) {
        ROAD[latestx * col + latesty].di = -1;
    }//>=4���ĸ����������ϣ�û�п���·�����������ݣ�����ǰλ�õ�di���¸�Ϊ-1����Ϊ���Գ��Ըýڵ����������
    return make_pair(-1, -1);
}

//���·�����ȳ�ʼ��
void getpath(int x, int y, int finalx, int finaly,int maze[13][13],int row,int col,node* ROAD){//,int&shortestlength,stack<node*>shortest) {
    int order = 1;//shortest path order
    int num = 1;//·�����
    int flag = 0;//found or not
    int min = 9999;
    stack<node*>nodestack;//���ڴ洢�������ʽڵ�
    ROAD[x * col + y].STATUS = visited;//���״̬��Ϊvisited��ֹ�ظ�
    
    nodestack.push(&ROAD[x*col+y]);//���ѹ�뵱ǰ��������ջ
   

    while (!nodestack.empty()) {//���м������ʽڵ��һֱѭ����ֱ��ȫ�����ʽ���
      
       node* current = nodestack.top();
        pair<int,int>location=make_pair(current->x,current->y);//��ǰ����
       
        
      //�ҵ���
        if ( location.first==finalx&&location.second==finaly) {
            flag = 1;//founded
            if (nodestack.size() + 1 < min) {//�ж��Ƿ�Ϊ���·��
                min = nodestack.size() + 1;
                order = num;//��̳���Ϊ��ǰ·��
            }
            stack<pair< int, int>> track;
           while (current!=nullptr) {
               track.push(make_pair(current->x, current->y));
               current = current->prev;
           }//ѹ��trackջ�����·��
     
           cout << "·��" << num++ << ":";
           while (!track.empty()) {
               pair<int, int>coord = track.top();
               track.pop();
               cout << "(" << coord.first << "," << coord.second << ")";
               
              
           }
           
           cout << endl;
           if(!nodestack.empty()){nodestack.top()->STATUS = safe;//����Ĺؼ�����֮ǰ�����ߵ��յ�ǰһ��������ˣ���ԭ������Ϊû���޸��ص�״̬��pop����
           if (!nodestack.empty()) {
               nodestack.pop();
               if (!nodestack.empty()) {
                   nodestack.top()->STATUS = safe;
                   current = nodestack.top();
               }
           }}
           
           
          continue;
       }//���·����������
       
       pair<int, int>coordinate = nextmove(location.first, location.second, row, col, ROAD);
       if (coordinate.first==-1) {//û�����ߵ�·��
           if (!nodestack.empty()) {
               //������һλ��
              nodestack.top()->STATUS = safe;
               nodestack.pop();
               
           }
          
        
       }
       
        else {
           //current = nodestack.top();
            int h = coordinate.first;
            int j = coordinate.second;
            node* next = &(ROAD[h * col + j]);
            nodestack.push(next);//�ⲿû�����ã������������   �ж���nextmove��currentû�иı���Ȼ����㣬//����
            next->STATUS = visited;//���Է��ʣ�����λ�ñ��Ϊ����ed
            next->prev = current;//���ϣ��������·��
            //����ջ��Ϊ��λ��
        }

    }
    if (flag == 1) {
        cout << "���·��Ϊ·��" << order;
    }
    else { cout << "û��ͨ·:-(" << endl; }
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
    cout << "������Ŀ���Թ�����������" << endl;
    scanf_s("%d %d", &m, &n);//
    cout << "������Ŀ���Թ���" << endl;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < m;j++) {
            cin >> maze[i][j];
            ROAD[i * n + j] = { i,j,-1,status(maze[i][j]) };
        }
    }//�����Թ�
    //int a =11, b=12 ;
    int a = 0, b = 0;
    cout << "�������Թ��յ�" << endl;
    cin >> a >> b;
    ROAD[a * n + b].STATUS = status(0);
    maze[a][b] = 0;
    //int c=0 , d =1;
    int c=0,d=0;
    cout << "�������Թ����" << endl;
    cin >> c >> d;
    ROAD[c * n + d].STATUS = status(0);
    maze[c][d] = 0;
    cout << "����·��:" << endl;
    //bfs(c, d, a, b, maze, m, n, ROAD);
    getpath(c, d, a, b, maze, m, n, ROAD);//,shortestlength,shortest);
    
    return 0;


}