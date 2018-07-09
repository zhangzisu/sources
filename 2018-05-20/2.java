import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.ArrayList;

class data implements Comparable<data> {
    public double r;
    public int x, y;

    public data() {
    }

    public data(double r, int x, int y) {
        this.r = r;
        this.x = x;
        this.y = y;
    }

    @Override
    public int compareTo(data obj) {
        return this.r < obj.r ? 1 : 0;
    }
}

class HouseProtection {
    final int MAXN = 210;
    final double EPS = 1e-5;
    final double PI = Math.acos(-1);
    int n, m, k, r;
    int[] _x, _y, x_, y_;
    double ans, rd;

    double S(double x) {
        return x * x * PI;
    }

    double sqr(int x) {
        return 1. * x * x;
    }

    double dist(int x0, int y0, int x1, int y1) {
        return Math.sqrt(sqr(x0 - x1) + sqr(y0 - y1));
    }

    int match[] = new int[MAXN];
    boolean vis[] = new boolean[MAXN];
    boolean skip[] = new boolean[MAXN];
    boolean ban[][] = new boolean[MAXN][MAXN];

    boolean h(int x) {
        for (int i = 1; i <= m; i++) {
            if (!ban[x][i])
                continue;
            if (vis[i])
                continue;
            vis[i] = true;
            if (match[i] == 0 || h(match[i])) {
                match[i] = x;
                return false;
            }
        }
        return true;
    }

    public double safetyFactor(int _x[], int _y[], int x_[], int y_[], int R) {
        n = _x.length;
        m = x_.length;

        List<data> list = new ArrayList<data>();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                double d = dist(_x[i], _y[i], x_[j], y_[j]) / 2;
                if (d < r + EPS)
                    list.add(new data(d, i, j));
            }
        }
        list.add(new data(r, 0, 0));
        Collections.sort(list);
        int cnt = 0;
        for (data d : list) {
            for (int j = 1; j <= m; j++)
                skip[match[j]] = true;
            for (int j = 1; j <= n; j++)
                if (!skip[j]) {
                    Arrays.fill(vis, false);
                    if (h(j))
                        cnt++;
                }
            int res = n + m - cnt;
            // printf("Radius %lf: count %d, ans %lf\n", dt[i].first, res, S(dt[i].first) *
            // res);
            ans = Math.max(ans, S(d.r) * res);
            ban[d.x][d.y] = true;
        }
        return ans;
    }
}