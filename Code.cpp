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

