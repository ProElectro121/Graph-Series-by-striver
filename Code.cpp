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
