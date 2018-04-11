import java.util.*;

class tmp {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        String input = cin.nextLine();
        if (input.equals("ChthoIIy")) {
            int t = cin.nextInt();
            for (int tt = 0; tt < t; tt++) {
                int n = cin.nextInt();
                int k = cin.nextInt();
                int m = cin.nextInt();
                int ans[][] = new int[m + 1][];
                int now[] = new int[k + 1];
                for (int i = 1; i <= k; i++)
                    now[i] = 1;
                for (int i = 1; i <= m; i++) {
                    ans[i] = new int[k + 1];
                    for (int j = 1; j <= k; j++) {
                        ans[i][j] = cin.nextInt();
                        now[j] += ans[i][j];
                        if (now[j] > n)
                            now[j] -= n;
                    }
                }
                int goal[] = new int[k + 1];
                for (int i = 1; i <= k; i++)
                    goal[i] = cin.nextInt();
                boolean flag = false;
                for (int i = 1; i <= m; i++) {
                    boolean ok = true;
                    for (int j = 1; j <= k; j++) {
                        int tmp = now[j] - ans[i][j];
                        if (tmp < 1)
                            tmp += n;
                        if (tmp != goal[j])
                            ok = false;
                    }
                    if (ok) {
                        for (int j = 1; j <= k; j++)
                            System.out.print(ans[i][j] + " ");
                        System.out.println();
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    continue;
                for (int i = 1; i <= k; i++) {
                    int tmp = goal[i] - now[i];
                    if (tmp < 1)
                        tmp += n;
                    System.out.print(tmp + " ");
                }
                System.out.println();
            }
        } else {
            int t = cin.nextInt();
            for (int tt = 0; tt < t; tt++) {
                int n = cin.nextInt();
                int k = cin.nextInt();
                int m = cin.nextInt();
                int ans[] = new int[k + 1];
                for (int i = 1; i <= k; i++)
                    ans[i] = 1;
                for (int i = 1; i <= m; i++) {
                    for (int j = 1; j <= k; j++) {
                        int tmp = cin.nextInt();
                        ans[j] += tmp;
                        if (ans[j] > n)
                            ans[j] -= n;
                    }
                }
                for (int i = 1; i <= k; i++)
                    System.out.print(ans[i] + " ");
                System.out.println();
            }
        }
        cin.close();
    }
}