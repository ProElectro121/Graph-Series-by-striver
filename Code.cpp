/* Way of storing a adhanecy matrix
space complexity -> O(n*n)
*/
void solve() {
    int n , m;
    cin >> n >> m;

    int adj[n + 1][n + 1];

    for (int i = 0; i < m; i++) {
        int x , y;
        cin >> x >> y;

        adj[x][y] = 1;
        adj[y][x] = 1;
    }
}

/*Way of stroring a adjanecy list
 Each index act as a node which contains all the Nodes which are directly connected to it.
*/

void solve() {
    int n , m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for(int i = 0; i < n; i++) {
        int x , y;
        cin >> x >> y;
        //x --> y
        adj[x].push_back(y);
        //y --> x
        adj[y].push_back(x);
    }
    
}


/* BFS traversal in a graph 
  Time complexity -> O(n) + O(2*E)
  
  as each node is going once in the queue and for each node we are aierating over it's neighbour
  as number of neightbour are equal to 2*E
*/

public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        vector<int> BFS;
        int vis[V] = {0};
        
        queue<int> Q;
        Q.push(0);
        vis[0] = 1;
        
        while(!Q.empty()) {
            int node = Q.front();
            Q.pop();
            BFS.push_back(node);
            for(auto &it: adj[node]) {
                if(vis[it] == 0) {
                    Q.push(it);
                    vis[it] = 1;
                }
            }
        }
        return BFS;
    }
};

/*DFS traversal in a graph
so basically in this traversal technique we go in depth until a markded node occour ,  occour we return and move 
on to the next node in the adjaency list.
Let n be the number of nodes
space compexity --> O(n) for storing the DFS nodes ie traversal 
                              +
                   O(n) for visited array
                              +
                   O(n) for recurrsion stack (Worst case  -->  skewed graph)
                   ~ O(n)
                   
 Time complexity --> O(n) for traversing the visited array  and vsiting each node once + O(2*E) --> summation of all the neighbour it degrees
                    O(n) + O(2*E)
*/
class Solution {
  private:
    void dfs(int node , int vis[] , vector<int> adj[] , vector<int>& DFS) {
        vis[node] = 1;
        DFS.push_back(node);
        
        for(auto &it: adj[node]) {
            if(!vis[it])
              dfs(it , vis , adj , DFS);
        }
    }
  public:
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int> DFS;
        int vis[V] = {0};
        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                dfs(i ,  vis , adj , DFS);
            }
        }
        return DFS;
    }
};

/*Find number of Province or we can simply say find number of connected componenet in a graph
  space complexity -> O(n) -> vis array + O(n) -> recursion stack
  time complexity -> O(n) + O(V + 2*E)
*/

class Solution {
private:
    void dfs(int node , vector<vector<int>>& adj , vector<int>& vis) {
        vis[node] = 1;

        for(auto &it: adj[node]) {
            if(!vis[it]) {
                dfs(it , adj , vis);
            }
        }
    }
    void bfs(int node , vector<vector<int>>& adj , vector<int>& vis) {
        queue<int> q;
        q.push(node);
        vis[node] = 1;

        while(!q.empty()) {
            int currNode = q.front();
            q.pop();
            
            for(auto &it: adj[currNode]) {
               if(!vis[it]) {
                   vis[it] = 1;
                   q.push(it);
               }
            }
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<vector<int>> adj(isConnected.size());
        
        for(int i = 0; i < isConnected.size(); i++) {
            for(int j = 0; j < isConnected.size(); j++) {
                if(isConnected[i][j] == 1) {
                    adj[i].push_back(j);
                }
            }
        }

        int NoOfProvince = 0;
        int n = isConnected.size();
        vector<int> vis(n , 0);
        for(int i = 0; i < isConnected.size(); i++) {
            if(!vis[i]) {
                NoOfProvince++;
                bfs(i , adj , vis);
            }
        }
        return NoOfProvince;
    }
};

/*Numbers of islands 
  just simply perform a dfs such that we we found a part of a island we simply marked the whole island as 1 so it does not take
  part in further traversal , ie in this way we can get the unique numbers of traversal.
  
  Space complexity --> O(n^2) --> visited matrix + O(n^2) --> for queue(Worst case when all the matrix is a island ie all elements == 1)
  
  Time complexity -->  ~ O(n^2) + O(n^2) * 4 == ~= O(n^2)
*/

class Solution {
private:
    bool valid(int newx , int newy , int m , int n) {
        if(newx >= 0 and newy >= 0 and newx < m)
           return true;
           return false;
    }
    //  Using BFS
    
    void bfs(int row , int col , vector<vector<int>>& vis ,vector<vector<char>>& grid , int dx[] ,int dy[] ,int m ,int n) {
        queue<pair<int , int>> q;
        q.push({row , col});
        vis[row][col] = 1;

        while(!q.empty()) {
            pair<int , int> node = q.front();
            row = node.first;
            col = node.second;
            q.pop();
            for(int i = 0; i < 4; i++) {
                int newx = row + dx[i];
                int newy = col + dy[i];

                if(valid(newx , newy , m , n) and !vis[newx][newy] and grid[newx][newy] == '1') {
                    q.push({newx , newy});
                    vis[newx][newy] = 1;
                }
            }
        }
    }
    
    // Using DFS
    void dfs(int row , int col , vector<vector<int>>& vis ,vector<vector<char>>& grid , int dx[] ,int dy[] ,int m ,int n) {
        vis[row][col] = 1;
        for(int i = 0; i < 4; i++) {
            int newx = row + dx[i];
            int newy = col + dy[i];
            if(valid(newx , newy , m , n) and newy < n and !vis[newx][newy] and grid[newx][newy] == '1')
              dfs(newx , newy , vis , grid , dx , dy , m , n);
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int islandCount = 0;
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m ,vector<int> (n , 0));

        int dx[] = {0 , 1 , 0 , -1};
        int dy[] = {1 , 0 , -1 , 0};

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(!vis[i][j] and grid[i][j] == '1') {
                    dfs(i , j , vis , grid , dx , dy , m , n);
                    islandCount++;
                }
            }
        }
        return islandCount;
    }
};

/*Flood Fill algoritham
 TIme complexity --> O(x) + O(x)*4  where X = m*n
 Space complexity --> O(x) + O(x) + O(x) , one for vis array ,  one for finalimage , one for recurrsion stack 
 
*/

//Using BFS
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int m = image.size();
        int n = image[0].size();
        vector<vector<int>> finalImage(image);
        queue<pair<int,int>> q;

        q.push({sr , sc});
        vector<vector<int>> vis(m , vector<int> (n , 0));
        int dx[] = {0 , 1 , 0, -1};
        int dy[] = {1 , 0 , -1, 0};
        vis[sr][sc] = 1;
        int reqColor = image[sr][sc];
        while(!q.empty()) {
            pair<int,int> pixel = q.front();
            q.pop();
            int newx = pixel.first;
            int newy = pixel.second;
            finalImage[newx][newy] = color;
            
            for(int i = 0; i < 4; i++) {
                int newxx = newx + dx[i];
                int newyy = newy + dy[i];

            if(newxx >= 0 and newyy >= 0 and newxx < m and newyy < n and !vis[newxx][newyy] and finalImage[newxx][newyy] == reqColor) {
                 q.push({newxx , newyy});
                 vis[newxx][newyy] = 1;  
              }
            } 
        }
        return finalImage;
    }
};

// Using DFS

class Solution {
private:
    void dfs(int x , int y , int newcolor , int initialColor, vector<vector<int>>& ans , int dx[] , int dy[] , vector<vector<int>>& image){
        ans[x][y] = newcolor;
        int m = ans.size();
        int n = ans[0].size();
        for(int i = 0; i < 4; i++){
            int newx = x + dx[i];
            int newy = y + dy[i];
            if(newx >= 0 and newx < m and newy >=0 and newy < n and ans[newx][newy] == initialColor and image[newx][newy] != newcolor){
                dfs(newx , newy , newcolor , initialColor , ans , dx , dy , image);
            }
        }
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int initialColor = image[sr][sc];
        vector<vector<int>> ans(image);
        int dx[] = {0 , 1 , 0 , -1};
        int dy[] = {1 , 0 , -1 , 0};
        dfs(sr , sc , color , initialColor , ans , dx , dy , image);
        return ans;
    }
};

/*Rotten Oranges -- > Currently incorrect had to do some debugging.. abhi man nahi kar raha😂*/

class Solution {
private:
    int bfs(int row , int col , vector<vector<int>>& grid ,vector<vector<int>>& vis) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<pair<int,int>,int>> q;
        q.push({{row , col} , 0});
        vis[row][col] = 1;
        int maxi = 0;
        int dx[] = {0 , 1, 0, -1};
        int dy[] = {1 , 0 , -1, 0};
        while(!q.empty()) {
            pair<pair<int,int>, int> temp = q.front();
            q.pop();
            
            int x = temp.first.first;
            int y = temp.first.second;
            int level = temp.second;
            maxi = max(maxi , level);
            for(int i = 0; i < 4; i++) {
                int newx = x + dx[i];
                int newy = y + dy[i];

                if(newx >= 0 and newy >= 0 and newx < m and newy < n and !vis[newx][newy] and grid[newx][newy] == 1) {
                    vis[newx][newy] = 1;
                    q.push({{newx ,newy} , level + 1});
                    
                }
            }
        }
        return maxi;
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vis(m , vector<int>(n , 0));
        
        int maxi = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 2 and !vis[i][j]) {
                   maxi = max(bfs(i , j , grid , vis) , maxi);
                }
            }
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n ;j++) {
                if(grid[i][j] == 1 and vis[i][j] == 0)
                  return -1;
            }
        }
        return maxi;
    }
};

/*0/1 matrix -- > basically we have to find the distance of nearest cell containing elemnt 0
 So basically if the element at index is 0 , then the distance is also 0
 and for other cells we think in such a way that we start from 0 and find the cloaset cell ie 1
 
 Time complexity ---> O(m*n) + 4*O(m*n)
 space complexity ---> O(m*n) --> vis matrix + O(m*n) --> answer matrix  + O(m*n) --> for queue approx ~ O(m*n) 
*/

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        vector<vector<int>> vis(m , vector<int>(n , 0));
        vector<vector<int>> finalmat(m , vector<int>(n , 0));
        queue<pair<int, pair<int,int>>> q;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(mat[i][j] == 1) continue;

                vis[i][j] = 1;
                q.push({0 , {i , j}});
            }
        }
        int dx[] = {0, 1, 0 , -1};
        int dy[] = {1 , 0, -1, 0};

        while(!q.empty()) {
            auto temp = q.front();
            q.pop();
            int level = temp.first;
            int x = temp.second.first;
            int y = temp.second.second;
            
            finalmat[x][y] = level;

            for(int i = 0; i < 4; i++) {
                int newx = x + dx[i];
                int newy = y + dy[i];

                if(newx >= 0 and newy >= 0 and newx < m and newy < n and vis[newx][newy] == 0 and mat[newx][newy] == 1) {
                    q.push({level + 1 , {newx , newy}});
                    vis[newx][newy] = 1;
                }
            }
        }
        return finalmat;
    }
}

/*Sorrounded region --> basically we have to find the 
Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.
  so we can simply see that the 'O' which are in the edges and all the 'O' which are connected to it still going to remain same
  else all other will became X.
*/

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        vector<vector<int>> vis(m , vector<int>(n , 0));

        queue<pair<int,int>> q;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if((i == 0 or i == m - 1 or j == 0 or j == n - 1) and board[i][j] == 'O') {
                    vis[i][j] = 1;
                    q.push({i , j});
                }
            }
        }
        int dx[] = {0 , 1,  0, -1};
        int dy[] = {1 , 0, -1, 0};
        while(!q.empty()) {
            auto temp = q.front();
            q.pop();

            int x = temp.first;
            int y = temp.second;

            for(int i = 0;i < 4; i++) {
                int newx = x + dx[i];
                int newy = y + dy[i];

                if(newx >= 0 and newy >= 0 and newx < m and newy < n and board[newx][newy] == 'O' and vis[newx][newy] == 0) {
                    vis[newx][newy] = 1;
                    q.push({newx , newy});
                }
            }
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(vis[i][j] == 1)
                  board[i][j] = 'O';
                  else
                  board[i][j] = 'X';
            }
        }
    }
};

/*Number of enclaves --> basically we have to find the number of islands from which we can come form the grid --> exacly same as sorrounded region*/

class Solution {
public:
    int numEnclaves(vector<vector<int>>& board) {
          int m = board.size();
        int n = board[0].size();

        vector<vector<int>> vis(m , vector<int>(n , 0));

        queue<pair<int,int>> q;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if((i == 0 or i == m - 1 or j == 0 or j == n - 1) and board[i][j] == 1) {
                    vis[i][j] = 1;
                    q.push({i , j});
                }
            }
        }
        int dx[] = {0 , 1,  0, -1};
        int dy[] = {1 , 0, -1, 0};
        while(!q.empty()) {
            auto temp = q.front();
            q.pop();

            int x = temp.first;
            int y = temp.second;

            for(int i = 0;i < 4; i++) {
                int newx = x + dx[i];
                int newy = y + dy[i];

                if(newx >= 0 and newy >= 0 and newx < m and newy < n and board[newx][newy] == 1 and vis[newx][newy] == 0) {
                    vis[newx][newy] = 1;
                    q.push({newx , newy});
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == 1 and vis[i][j] == 0) ans++;
            }
        }
        return ans;
    }
};

/*
 Number of distince island --> So we main basic idea is to somehow retain the shape of island , we can do this we the help of set data structure
*/

class Solution {
  public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        map<set<pair<int,int>> , int> distinceIsland;
        
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<int>> vis(m , vector<int> (n , 0));
        
        bool ok = false;
        int dx[] = {0 , 1, 0, -1};
        int dy[] = {1 , 0, -1, 0};
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1 and vis[i][j] == 0) {
                   queue<pair<int,int>> q;
                   
                   vis[i][j] = 1;
                   q.push({i , j});
                   vector<pair<int,int>> p;
                   while(!q.empty()) {
                       auto temp = q.front();
                       int x = temp.first;
                       int y = temp.second;
                       q.pop();
                       p.push_back({x , y});
                       for(int i = 0; i < 4; i++) {
                           int newx = x + dx[i];
                           int newy = y + dy[i];
                           
                           if(newx >= 0 and newy >= 0 and newx < m and newy < n and vis[newx][newy] == 0 and grid[newx][newy] == 1) {
                               q.push({newx , newy});
                               vis[newx][newy] = 1;
                           }
                       }
                   }
                   sort(p.begin() , p.end());
                   set<pair<int,int>> temps;
                   for(int j = 1; j < p.size(); j++) {
                       temps.insert({ p[j].first - p[0].first ,p[j].second - p[0].second});
                   }
                   distinceIsland[temps]++;
                }
            }
        }
        return (int)distinceIsland.size();
    }
};


/*Checking weather the given graph is bipartite 
  Graph is bipartite only when these is a cycle of odd length
  but we are not gonna go that way,  we simply gonna color the node and if we found a already colored node 
  we check weather the given is colored oppositively or not
  if not then the grpah is not bipartite
  
  Time and space complexity same as that of a bfs algoritham
*/
class Solution {
private:
    bool bfs(int node , vector<int>& color , vector<vector<int>>& graph) {
        queue<int> q;
        q.push(node);
        color[node] = 0;
        while(!q.empty()) {
            int currNode = q.front();
            q.pop();

            for(auto &it: graph[currNode]) {
                if(color[it] == -1) {
                    color[it] = 1 - color[currNode];
                    q.push(it);
                }
                else if(color[it] == color[currNode]) {
                    return false;
                }
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int v = graph.size();
        
        vector<int> color(v , -1);
       
        
        for(int i = 0; i < v; i++) {
            if(color[i] == -1) {
               if(!bfs(i , color , graph))
                return false;
            }
        }
       
        return true;
    }
};

/*Checking Bipartiteness of graph using dfs*/

class Solution {
private:
    void dfs(int node , int parentNode,vector<int> &color , vector<vector<int>>& graph , bool& ans ,int currColor) {
        color[node] = currColor;

        for(auto &it: graph[node]) {
            if(it == parentNode) continue;
            if(color[it] == -1) {
                dfs(it , node, color , graph,  ans, 1 - currColor);
            }
            else if(color[it] == color[node]) {
                ans = false;
                return;
            }
        }
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int v = graph.size();
        bool ans = true;
        vector<int> color(v , -1);
        int currColor = 0;
        for(int i = 0; i < v; i++) {
            if(color[i] == -1) {
               dfs(i ,-1, color , graph , ans , currColor);
            }
        }
       
        return ans;
    }
};

/*Checking weather a directed graph contain cycle or not
 Time complexity ---> O(V + E)
 
 We can simplify the expression by using a single visited array ie marking 2 if both visited and pathvited and marking 1 in the backtracking preocess.
*/

class Solution {
  private:
    bool dfs(int node , int vis[] , int pathVis[] , vector<int> adj[]) {
        vis[node] = 1;
        pathVis[node] = 1;
        
        for(auto &it: adj[node]) {
            if(!vis[it]) {
                if(dfs(it , vis , pathVis , adj)) return true;
            }
            else if(vis[it] and pathVis[it]) return true;
            
        }
        pathVis[node] = 0;
        return false;
    }
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        int vis[V] = {0};
        int pathVis[V] = {0};
        
        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                if(dfs(i , vis , pathVis , adj)) return 1;;
            }
        }
        return 0;
    }
};

/*Find eventual safe states --> So we have to find the all the nodes from which any path ends to an terminal node 
Idea ---> so basically all the nodes which are part of a cycle or leads to a cycle can never be a safe nodes

we can also use pathVis array to to get the safe nodes just check weather the pathvis array is zero or not if zero --> safeNode elsse not a safe node.
*/

class Solution {
private:
    bool dfs(int node , vector<int>& vis , vector<int>& pathVis , vector<int>& check ,vector<vector<int>>& graph) {
        vis[node] = 1;
        pathVis[node] = 1;
        //initially check[node] is 0.
        for(auto &it: graph[node]) {
            if(!vis[it]) {
                if(dfs(it , vis , pathVis , check , graph) == true){
                    check[node] = 0;
                  return true;
                }    
            }
            else if(pathVis[it] == true) {
              check[node] = 0;
              return true;
            }    
        }
        // marking the node as 1 ie it is a safe node
        check[node] = 1;
        pathVis[node] = 0;
        return false;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<int> vis(V , 0);
        vector<int> pathVis(V , 0);
        vector<int> check(V , 0);

        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                dfs(i , vis , pathVis , check , graph);
            }
        }
        vector<int> safeNodes;
        for(int i = 0; i < V; i++) {
            if(check[i] == 1) {
                safeNodes.push_back(i);
            }
        }
        return safeNodes;
    }
};
/*
Topologiclal sort --> means if there is a edge between u and v then u should appear before v in the linear ordering
this can done using stack

intution  --> untill and untill the dfs call of a node gets completed, then we push the node in the stack =..

Ex -->   1 --> 2 --> 3 --> 4

then we should put 4 in the stack assuming all the element after 4 are already in the linear order 
then we do same for the remaining node.
*/
class Solution {
    private:
    void dfs(int node , int vis[] , vector<int> adj[] ,stack<int>& st) {
         vis[node] = 1;
         
         for(auto &it: adj[node]) {
             if(!vis[it])
               dfs(it , vis , adj , st);
             
         }
        st.push(node); 
    }
	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) {
	   stack<int> st;
	   int vis[V] = {0};
	   
	   for(int i = 0; i < V; i++) {
	       if(!vis[i]) {
	           dfs(i , vis , adj , st);
	       }
	   }
	   vector<int> linearOrder;
	   while(!st.empty()) {
	       linearOrder.push_back(st.top());
	       st.pop();
	   }
	   return linearOrder;
	}
};

/*Topological sort using BFS algoritham -----> KAHN ALGORITHAM
 first we create a check array that will count the number of incoming edges to index(node)
 Then we are gonna put all the node with 0 edges coming to it in the queue
 
 then we will pop then node and disconnect the node it make every edge connected to it to 0 this can be done
 by decreasing the value at the nodes
 if now the number of nodes become 0 we are again push the node in the queue
 check array or indegree array
 
 Time complexity --> for a DAC --> O(V + E).
*/

class Solution
{
	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) {
	    int check[V] = {0};
	    vector<int> linearOrder;
	    for(int i = 0; i < V; i++) {
	        for(auto &it: adj[i]) {
	            check[it]++;
	        }
	    }
	    queue<int> q;
	    
	    for(int i = 0; i <V; i++) {
	        if(check[i] == 0) {
	            q.push(i);  
	        }
	    }
	    while(!q.empty()) {
	        auto it = q.front();
	        linearOrder.push_back(it);
	        q.pop();
	        for(auto &i: adj[it]) {
	            check[i]--;
	            if(check[i] == 0) 
	              q.push(i);
	        }
	    }
	    return linearOrder;
	}
};

/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.
*/

class Solution {
public:
    bool canFinish(int num, vector<vector<int>>& p) {
        vector<int> adj[num];

        for(int i = 0; i < p.size(); i++) {
             adj[p[i][0]].push_back(p[i][1]);
        }

        int indegree[num];
        for(int i = 0; i < num; i++) indegree[i] = 0;
        for(int i = 0; i < num;i++) {
            for(auto &j: adj[i]) {
                indegree[j]++;
            }
        }
        queue<int> q;
        for(int i = 0; i < num; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            for(auto &i: adj[node]) {
                indegree[i]--;
                if(indegree[i] == 0) {
                    q.push(i);
                }
            }

        }
        for(int i = 0; i < num; i++) {
            if(indegree[i] != 0) {
                return false;
            }
        }
        return true;
    }
};

/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. 
If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.
*/

class Solution {
public:
    vector<int> findOrder(int num, vector<vector<int>>& p) {
         vector<int> adj[num];

        for(int i = 0; i < p.size(); i++) {
             adj[p[i][1]].push_back(p[i][0]);
        }

        int indegree[num];
        for(int i = 0; i < num; i++) indegree[i] = 0;
        for(int i = 0; i < num;i++) {
            for(auto &j: adj[i]) {
                indegree[j]++;
            }
        }
        queue<int> q;
        for(int i = 0; i < num; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        vector<int> linearOrder;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            linearOrder.push_back(node);
            for(auto &i: adj[node]) {
                indegree[i]--;
                if(indegree[i] == 0) {
                    q.push(i);
                }
            }

        }
        for(int i = 0; i < num; i++) {
            if(indegree[i] != 0) {
                return vector<int>();
            }
        }
        return linearOrder;
    }
};

/*
Given a sorted dictionary of an alien language having N words and k starting alphabets of standard dictionary. 
Find the order of characters in the alien language.

*/

class Solution{
    private:
    void dfs(int node , vector<vector<int>>& graph , int vis[] , stack<int>& st) {
        vis[node] = 1;
        
        for(auto &i: graph[node]) {
            if(!vis[i]) {
                dfs(i , graph , vis , st);
            }
        }
        st.push(node);
    }
    public:
    string findOrder(string dict[], int N, int k) {
        vector<vector<int>> graph(k);
        
        for(int i = 0; i < N - 1; i++) {
            string first = dict[i];
            string second = dict[i + 1];
            
            int sz = min((int)first.size() , (int)second.size());
            
            for(int j = 0; j < sz; j++) {
                if(first[j] != second[j]) {
                    graph[first[j] - 'a'].push_back(second[j] - 'a');
                    break;
                }
            }
        }
        vector<int> indegree(k , 0);
        string ans;  
        for(auto &i: graph) {
            for(auto &j: i) {
                indegree[j]++;
            } 
        }
        queue<int> q;
        for(int i = 0; i < k; i++) {
            if(indegree[i] == 0)
              q.push(i);
        }
        
        while(!q.empty()) {
            auto node = q.front();
            q.pop();
            ans.push_back(node + 'a');
            
            for(auto &i: graph[node]) {
                indegree[i]--;
                if(indegree[i] == 0)
                 q.push(i);
            }
        }
        return ans;
    }
};


class Solution {
  private:
     void dfs(int node , int vis[] , vector<vector<pair<int,int>>>& graph, stack<int>& st) {
         vis[node] = 1;
         
         for(auto &it: graph[node]) {
             if(!vis[it.first]) {
                 dfs(it.first , vis , graph , st);
             }
         }
         st.push(node);
     }
  public:
     vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
        vector<vector<pair<int,int>>> graph(N);
        int src = 0;
        for(int i = 0; i < M; i++) {
           graph[edges[i][0]].push_back({edges[i][1] , edges[i][2]});
        }
        stack<int> st;
        int vis[N] = {0};
        for(int  i = 0; i < N; i++) {
            if(!vis[i]) {
                dfs(i , vis , graph , st);
            }
        }
        
        vector<int> dist(N , 1e9);
        
        dist[src] = 0;
        
        while(!st.empty()) {
            auto it = st.top();
            st.pop();
            
            for(auto &i: graph[it]) {
                int node = i.first;
                int wt = i.second;
                dist[node] = min(dist[node] , wt + dist[it]);
            }
        }
        for(auto &i: dist) {
            i = (i == 1e9 ? -1 : i);
        }
        return dist;
    }
};

/*Dijkstra's Algorithm - Using Priority Queue

basic logic is to use a priority queue and ..

first insert a the src node and dist 0

then starting iterating to adjacent node of the top of the priority queue and check if the distance of the adjacent node from the src node is 
less the distace that is mentioneed the disance array ,, if less then insert the adjacent node and the newdistamnce back in the queue

repqeat this process till the priority queue is empty

Time complexity --> O(E * log(V))

*/
class Solution
{
	public:
	//Function to find the shortest distance of all the vertices
    //from the source vertex S.
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int src){
        vector<int> dist(V , 1e9);
        
        priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;
        pq.push({0 , src});
        
        dist[src] = 0;
        
        while(!pq.empty()) {
            pair<int,int> pr = pq.top();
            pq.pop();
            
            int node = pr.second;
            int distance = pr.first;
            
            for(auto &it: adj[node]) {
                int newNode = it.front();
                int currDistance = it.back();
                
                if(dist[newNode] > distance + currDistance) {
                    pq.push({distance + currDistance , newNode});
                    dist[newNode] = distance + currDistance;
                }
            }
        }
        return dist;
    }
};

/*Using set data strucure instead of a priority queue*/

class Solution
{
	public:
	//Function to find the shortest distance of all the vertices
    //from the source vertex S.
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int src){
        vector<int> dist(V , 1e9);
        
        set<pair<int,int>> pq;
        pq.insert({0 , src});
        
        dist[src] = 0;
        
        while(!pq.empty()) {
            pair<int,int> pr = *pq.begin();
            pq.erase(pq.begin());
            
            int node = pr.second;
            int distance = pr.first;
            
            for(auto &it: adj[node]) {
                int newNode = it.front();
                int currDistance = it.back();
                
                if(dist[newNode] > distance + currDistance) {
                    
                    if(dist[newNode] != 1e9) {
                        pq.erase({dist[newNode] , newNode});
                    }
                    pq.insert({distance + currDistance , newNode});
                    dist[newNode] = distance + currDistance;
                }
            }
        }
        return dist;
    }
};


/*Shortest Path in Weighted undirected graph
You are given a weighted undirected graph having n+1 vertices numbered from 0 to n and m edges describing there
are edges between a to b with some weight, find the shortest path between the vertex 1 and the vertex n and if path
does not exist then return a list consisting of only -1
*/

class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        vector<pair<int,int>> graph[n + 1];
        int src = 1; 
        // Creation of graph
        for(int i = 0; i < edges.size(); i++) {
            graph[edges[i][0]].push_back({edges[i][1] , edges[i][2]});
            graph[edges[i][1]].push_back({edges[i][0] , edges[i][2]});
        }
        vector<int> dist(n + 1 , 1e9);
        vector<int> parent(n + 1, -1);
        priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;
        
        pq.push({0 , src});
        parent[1] = 1;
        dist[1] = 0;
        while(!pq.empty()) {
            pair<int,int> pr = pq.top();
            pq.pop();
            
            int distance = pr.first;
            int node = pr.second;
            
            for(auto &it: graph[node]) {
                int currDist = it.second;
                int currNode = it.first;
                
                if(distance + currDist < dist[currNode]) {
                    dist[currNode] = distance + currDist;
                    pq.push({dist[currNode] , currNode});
                    
                    parent[currNode] = node;
                }
            }
        }
        
        if(dist[n] == 1e9) {
            return vector<int>(1 , -1);
        }
        vector<int> shortestPath;
        
        int node = n;
        
        while(node != parent[node]) {
            shortestPath.push_back(node);
            
            node = parent[node];
        }
        shortestPath.push_back(1);

        reverse(shortestPath.begin() , shortestPath.end());
        
        return shortestPath;
    }
};


/*
Minimum spanning Tree
initial condition required ---> a priority queue containgin the any node and edgeWeight as 0 and parent as -1;
popping the top element in the priority queue and if the current node is visited we continue in the while loop
else
we go through the adjacent edgdes and check if the current Node is visited or not , if visited continue else we push the currnode and curredge in the priority queue

Time complexity --> Elog(E)

space complexity --> O(E + V)
*/
class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]){
        vector<int> vis(V , 0);
        
        priority_queue<pair<int , pair<int,int>> , vector<pair<int , pair<int,int>>> , greater<pair<int , pair<int,int>>>> pq;
        int MinimumSum = 0;
        
        pq.push({0 , {0 , -1}});
        vector<pair<int,int>> edgesOfMst;
        
        while(!pq.empty()) {
            pair<int,pair<int,int>> data = pq.top();
            pq.pop();
            
            int node = data.second.first;
            int edgeWeight = data.first;
            int parent = -1;
            if(vis[node]) {
                continue;
            }
            MinimumSum += edgeWeight;
            
            vis[node] = 1;
            if(parent != -1) {
                edgesOfMst.push_back({node , parent});
            }
            
            for(auto &it: adj[node]) {
                int currNode = it.front();
                int currEdgeWeight = it.back();
                
                if(!vis[currNode]) {
                    pq.push({currEdgeWeight , {currNode , node}});
                }
            }
        }
        return MinimumSum;
    }
};

/*
Disjoint set data strcture 
Time complexity fo chcking --> O(4*a) where a -> 1
*/ 
class Disjointset {
    vector<int> rank , parent , size;
public:
    Disjointset(int n) {
        rank.resize(n + 1 , 0);
        parent.resize(n + 1);
        size.resize(n + 1 , 1);

        for (int i = 0; i < n + 1; i++) {
            parent[i] = i;
        }
    }

    int ultimateParent(int node) {
        if (node == parent[node]) {
            return node;
        }

        return parent[node] = ultimateParent(parent[node]);
    }

    void UnionByRank(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int rank_u = rank[ultimateParent_u];
        int rank_v = rank[ultimateParent_v];

        if (rank_u == rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            rank[ultimateParent_u]++;
        }
        else if (rank_u > rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
        }
    }

    void UnionBySize(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int size_u = size[ultimateParent_u];
        int size_v = size[ultimateParent_v];

        if (size_u == size_v) {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
        else if (size_u > size_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            size[ultimateParent_u] += size[ultimateParent_v];
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
    }
};

/*
Minimum spanning tree algoritham using krskal algoritham
*/

class Disjointset {
    vector<int> rank , parent , size;
public:
    Disjointset(int n) {
        rank.resize(n + 1 , 0);
        parent.resize(n + 1);
        size.resize(n + 1 , 1);

        for (int i = 0; i < n + 1; i++) {
            parent[i] = i;
        }
    }

    int ultimateParent(int node) {
        if (node == parent[node]) {
            return node;
        }

        return parent[node] = ultimateParent(parent[node]);
    }

    void UnionByRank(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int rank_u = rank[ultimateParent_u];
        int rank_v = rank[ultimateParent_v];

        if (rank_u == rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            rank[ultimateParent_u]++;
        }
        else if (rank_u > rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
        }
    }

    void UnionBySize(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int size_u = size[ultimateParent_u];
        int size_v = size[ultimateParent_v];

        if (size_u == size_v) {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
        else if (size_u > size_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            size[ultimateParent_u] += size[ultimateParent_v];
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
    }
};



class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]){
        vector<pair<int , pair<int,int>>> edges;
        
        for(int i = 0; i < V; i++) {
            for(auto &it: adj[i]) {
                int u = i;
                int v = it[0];
                int edgeWeight = it[1];
            
                edges.push_back({edgeWeight , {u , v}});
            }
        }
        
        sort(edges.begin() , edges.end());
        int MinimumSum = 0;
        
        Disjointset ds(V);
        for(int i = 0; i < edges.size(); i++) {
            int edgeWeight = edges[i].first;
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            
            if(ds.ultimateParent(u) != ds.ultimateParent(v)) {
                MinimumSum += edgeWeight;
                ds.UnionBySize(u , v);
            }
        }
        return MinimumSum;
    }
};

/*
Number of province using disjoint set data structure
*/


class Disjointset {
public:    
    vector<int> rank , parent , size;
    Disjointset(int n) {
        rank.resize(n + 1 , 0);
        parent.resize(n + 1);
        size.resize(n + 1 , 1);

        for (int i = 0; i < n + 1; i++) {
            parent[i] = i;
        }
    }

    int ultimateParent(int node) {
        if (node == parent[node]) {
            return node;
        }

        return parent[node] = ultimateParent(parent[node]);
    }

    void UnionByRank(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int rank_u = rank[ultimateParent_u];
        int rank_v = rank[ultimateParent_v];

        if (rank_u == rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            rank[ultimateParent_u]++;
        }
        else if (rank_u > rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
        }
    }

    void UnionBySize(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int size_u = size[ultimateParent_u];
        int size_v = size[ultimateParent_v];

        if (size_u == size_v) {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
        else if (size_u > size_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            size[ultimateParent_u] += size[ultimateParent_v];
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
    }
};


class Solution {
  public:
    int numProvinces(vector<vector<int>> adj, int V) {
        int n = adj.size();
        
        Disjointset ds(V);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(adj[i][j] == 1) {
                    ds.UnionBySize(i , j);
                }
            }
        }
        int countProvince = 0;
        for(int i = 0; i < V ; i++) {
            countProvince += (i == ds.parent[i]);
        }
        return countProvince;
    }
};

/*Connecting the graph .. ie tell minimum no edges to take out from the graph and add to other component to make it a;; connected

TC - O(M(4alpha)) ---> M = edge.size()
SC - O(2V) or O(2N)

*/


class Disjointset {
    
public:
    vector<int> rank , parent , size;
    Disjointset(int n) {
        rank.resize(n + 1 , 0);
        parent.resize(n + 1);
        size.resize(n + 1 , 1);

        for (int i = 0; i < n + 1; i++) {
            parent[i] = i;
        }
    }

    int ultimateParent(int node) {
        if (node == parent[node]) {
            return node;
        }

        return parent[node] = ultimateParent(parent[node]);
    }

    void UnionByRank(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int rank_u = rank[ultimateParent_u];
        int rank_v = rank[ultimateParent_v];

        if (rank_u == rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            rank[ultimateParent_u]++;
        }
        else if (rank_u > rank_v) {
            parent[ultimateParent_v] = ultimateParent_u;
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
        }
    }

    void UnionBySize(int u , int v) {
        int ultimateParent_u = ultimateParent(u);
        int ultimateParent_v = ultimateParent(v);

        if (ultimateParent_u == ultimateParent_v) {
            return;
        }

        int size_u = size[ultimateParent_u];
        int size_v = size[ultimateParent_v];

        if (size_u == size_v) {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
        else if (size_u > size_v) {
            parent[ultimateParent_v] = ultimateParent_u;
            size[ultimateParent_u] += size[ultimateParent_v];
        }
        else {
            parent[ultimateParent_u] = ultimateParent_v;
            size[ultimateParent_v] += size[ultimateParent_u];
        }
    }
};


class Solution {
  public:
    int Solve(int n, vector<vector<int>>& edge) {
        int countConnectedComponent = 0 , extraEdges = 0;
        
        Disjointset ds(n);
        for(int i = 0; i < edge.size(); i++) {
            int u = edge[i].front();
            int v = edge[i].back();
           
            if(ds.ultimateParent(u) == ds.ultimateParent(v)) {
                extraEdges++;
            }
            
            ds.UnionByRank(u , v);
            ds.UnionByRank(v , u);
            
         
        }
        
        for(int i = 0; i < n; i++) {
            countConnectedComponent += (i == ds.parent[i]);
        }
        
        if(extraEdges >= countConnectedComponent - 1) {
            return countConnectedComponent - 1;
        }
        return -1;
    }
};

