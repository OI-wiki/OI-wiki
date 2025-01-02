import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int u = input.nextInt();
        int d = input.nextInt();
        int time = 0, dist = 0;
        while (true) {  // 用死循环来枚举
            dist += u;
            time++;
            if (dist >= n) {
                break;  // 满足条件则退出死循环
            }
            dist -= d;
        }
        System.out.println(time);   // 输出得到的结果
        input.close();
    }
}
