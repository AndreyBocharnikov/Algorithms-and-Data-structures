#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
using namespace std;

struct point {
    int x1, y1, x2, y2;
};

int const N = 128;
int st_x_min[N][N][8][8];
int st_x_max[N][N][8][8];
int st_y_min[N][N][8][8];
int st_y_max[N][N][8][8];
int v[5];
int h[128];
point table[128][128];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);
            table[i][j] = {x1, y1, x2, y2};
        }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            st_x_min[i][j][0][0] = table[i][j].x2;
            st_x_max[i][j][0][0] = table[i][j].x1;
            st_y_min[i][j][0][0] = table[i][j].y2;
            st_y_max[i][j][0][0] = table[i][j].y1;
        }
    }

    for (int k1 = 0; k1 < 8; k1++) {
        for (int k2 = 0; k2 < 8; k2++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (k1 == 0 && k2 == 0)
                        continue;
                    if (k1 == 0 || (k1 != 0 && k2 != 0)) {
                        int r = min(m - 1, j + (1 << (k2 - 1)));
                        int left = st_x_min[i][j][k1][k2 - 1];
                        int right = st_x_min[i][r][k1][k2 - 1];
                        st_x_min[i][j][k1][k2] = min(left, right);
                        left = st_x_max[i][j][k1][k2 - 1];
                        right = st_x_max[i][r][k1][k2 - 1];
                        st_x_max[i][j][k1][k2] = max(left, right);

                        left = st_y_min[i][j][k1][k2 - 1];
                        right = st_y_min[i][r][k1][k2 - 1];
                        st_y_min[i][j][k1][k2] = min(left, right);
                        left = st_y_max[i][j][k1][k2 - 1];
                        right = st_y_max[i][r][k1][k2 - 1];
                        st_y_max[i][j][k1][k2] = max(left, right);
                    } else {
                        int r = min(n - 1, i + (1 << (k1 - 1)));
                        int left = st_x_min[i][j][k1 - 1][k2];
                        int right = st_x_min[r][j][k1 - 1][k2];
                        st_x_min[i][j][k1][k2] = min(left, right);
                        left = st_x_max[i][j][k1 - 1][k2];
                        right = st_x_max[r][j][k1 - 1][k2];
                        st_x_max[i][j][k1][k2] = max(left, right);

                        left = st_y_min[i][j][k1 - 1][k2];
                        right = st_y_min[r][j][k1 - 1][k2];
                        st_y_min[i][j][k1][k2] = min(left, right);
                        left = st_y_max[i][j][k1 - 1][k2];
                        right = st_y_max[r][j][k1 - 1][k2];
                        st_y_max[i][j][k1][k2] = max(left, right);
                    }
                }
            }
        }
    }

    for (int i = 2; i < 128; i++)
        h[i] = h[i / 2] + 1;
    int q, a, b;
    cin >> q >> a >> b >> v[0];
    int mod = 1000000007;
    int ans = 0;
    for (int i = 0; i < q; i++) {
        for (int j = 1; j <= 4; j++)
            v[j] = int((1LL * a * v[j - 1] + b) % mod);
        x1 = v[1] % n;
        y1 = v[2] % m;
        x2 = v[3] % n;
        y2 = v[4] % m;
        v[0] = v[4];
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);

        int len_x = h[x2 - x1 + 1], len_y = h[y2 - y1 + 1];
        int r = x2 - (1 << len_x) + 1;
        int r2 = y2 - (1 << len_y) + 1;
        int min_x = min(st_x_min[x1][y1][len_x][len_y], st_x_min[r][y1][len_x][len_y]);
        min_x = min(min_x, st_x_min[x1][r2][len_x][len_y]);
        min_x = min(min_x, st_x_min[r][r2][len_x][len_y]);

        int max_x = max(st_x_max[x1][y1][len_x][len_y], st_x_max[r][y1][len_x][len_y]);
        max_x = max(max_x, st_x_max[x1][r2][len_x][len_y]);
        max_x = max(max_x, st_x_max[r][r2][len_x][len_y]);

        int min_y = min(st_y_min[x1][y1][len_x][len_y], st_y_min[r][y1][len_x][len_y]);
        min_y = min(min_y, st_y_min[x1][r2][len_x][len_y]);
        min_y = min(min_y, st_y_min[r][r2][len_x][len_y]);

        int max_y = max(st_y_max[x1][y1][len_x][len_y], st_y_max[r][y1][len_x][len_y]);
        max_y = max(max_y, st_y_max[x1][r2][len_x][len_y]);
        max_y = max(max_y, st_y_max[r][r2][len_x][len_y]);

        if (min_x > max_x && min_y > max_y)
            ans += int((1LL * (max_x - min_x) * (max_y - min_y)) % mod);
        ans %= mod;
    }
    cout << ans;
}

