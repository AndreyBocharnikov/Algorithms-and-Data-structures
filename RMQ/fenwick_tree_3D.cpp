#include <bits/stdc++.h>
#define f first
#define s second
#define ui unsigned int
#define vv_ll vector <vector <vector <ui> > >

using namespace std;

struct fuck_pcms {
    int y1, z1, y2, z2;
};
int nx, ny, nz;
struct arrays {
    ui *B1, *B2, *B3, *B4, *B5, *B6, *B7, *B8;
};

ui B1[1000001];
ui B2[1000001];
ui B3[1000001];
ui B4[1000001];
ui B5[1000001];
ui B6[1000001];
ui B7[1000001];
ui B8[1000001];

void update(ui *B, int x, int y, int l, ui val) {
    for (; l < nz; l = l | (l + 1)) {
        B[x * ny * nz + y * nz + l] += val;
    }
}

void update(ui *B_one, ui *B_two, int x, int y, int z1, int z2, ui val) {
    for (int cur_y = y; cur_y < ny; cur_y = cur_y | (cur_y + 1))
        update(B_one, x, cur_y, z1, val),
        update(B_one, x, cur_y, z2 + 1, -val),
        update(B_two, x, cur_y, z1, val * (z1 - 1)),
        update(B_two, x, cur_y, z2 + 1, -val * z2);
}

ui query(ui *B, int x, int y, int l) {
    ui res = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1)
        for (int cur_y = y; cur_y >= 0; cur_y = (cur_y & (cur_y + 1)) - 1)
            for (int cur_l = l; cur_l >= 0; cur_l = (cur_l & (cur_l + 1)) - 1)
                res += B[x * ny * nz + cur_y * nz + cur_l];
    return res;
}

ui query(arrays a, int x, int y, int z) {
    ui val = (query(a.B1, x, y, z) * z - query(a.B2, x, y, z)) * y;
    ui val2 = (val - (query(a.B3, x, y, z) * z - query(a.B4, x, y, z))) * x;
    ui val3 = (query(a.B5, x, y, z) * z - query(a.B6, x, y, z)) * y;
    ui val4 = -(query(a.B7, x, y, z) * z - query(a.B8, x, y, z));
    return val2 - (val3 + val4);
}

ui query(arrays a, int x1, int y1, int z1, int x2, int y2, int z2) {
    ui val = query(a, x2, y2, z2) - query(a, x1 - 1, y2, z2);
    ui val2 = -query(a, x2, y2, z1 - 1) + query(a, x1 - 1, y2, z1 - 1);
    ui val3 = -query(a, x2, y1 - 1, z2) + query(a, x1 - 1, y1 - 1, z2);
    ui val4 = query(a, x2, y1 - 1, z1 - 1) - query(a, x1 - 1, y1 - 1, z1 - 1);
    return val + val2 + val3 + val4;
}

void update(ui *B_one, ui *B_two, ui *B_th, ui *B_f, int x, fuck_pcms a, ui val) {
    for (int cur_x = x; cur_x < nx; cur_x = cur_x | (cur_x + 1))
        update(B_one, B_two, cur_x, a.y1, a.z1, a.z2, val),
        update(B_one, B_two, cur_x, a.y2 + 1, a.z1, a.z2, -val),
        update(B_th, B_f, cur_x, a.y1, a.z1, a.z2, val * (a.y1 - 1)),
        update(B_th, B_f, cur_x, a.y2 + 1, a.z1, a.z2, -val * a.y2);
}

void update(arrays a, int x1, int y1, int z1, int x2, int y2, int z2, ui val) {
    update(a.B1, a.B2, a.B3, a.B4, x1, {y1, z1, y2, z2}, val);
    update(a.B1, a.B2, a.B3, a.B4, x2 + 1, {y1, z1, y2, z2}, -val);

    update(a.B5, a.B6, a.B7, a.B8, x1, {y1, z1, y2, z2}, val * (x1 - 1));
    update(a.B5, a.B6, a.B7, a.B8, x2 + 1, {y1, z1, y2, z2}, -val * x2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q;
    cin >> nx >> ny >> nz >> q;
    for (int i = 0; i < 1000001; i++)
        B1[i] = 0,
        B2[i] = 0,
        B3[i] = 0,
        B4[i] = 0,
        B5[i] = 0,
        B6[i] = 0,
        B7[i] = 0,
        B8[i] = 0;
    arrays pcms_is_shit = {B1, B2, B3, B4, B5, B6, B7, B8};
    for (int i = 0; i < q; i++) {
        char x;
        int x1, y1, z1, x2, y2, z2;
        ui val;
        cin >> x;
        if (x == 'a') {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> val;
            x2--;
            y2--;
            z2--;
            update(pcms_is_shit, x1, y1, z1, x2, y2, z2, val);
        } else {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            x2--;
            y2--;
            z2--;
            cout << query(pcms_is_shit, x1, y1, z1, x2, y2, z2) << '\n';
        }
    }
}

