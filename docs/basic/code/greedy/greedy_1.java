import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Arrays;

public class Main {
    // 定义一个Task类来表示每个任务，包含截止时间和利润两个属性
    static class Task {
        long deadline;
        long reward;
        
        Task(long deadline, long reward) {
            this.deadline = deadline;
            this.reward = reward;
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt(); // 读取任务的数量
        Task[] tasks = new Task[n + 1]; // 创建Task数组，用于存储所有任务
        for (int i = 1; i <= n; i++) {
            long d = input.nextLong(); // 读取任务的截止时间
            long p = input.nextLong(); // 读取任务的利润
            tasks[i] = new Task(d, p); // 创建Task对象并存储在数组中
        }
        // 根据任务的截止时间对任务进行排序
        Arrays.sort(tasks, 1, n + 1, (a, b) -> Long.compare(a.deadline, b.deadline));
        
        // 创建一个小根堆来维护当前接受的任务的利润
        PriorityQueue<Long> pq = new PriorityQueue<>();
        long ans = 0; // 用于累计最大利润
        for (int i = 1; i <= n; i++) {
            // 如果当前任务的数量已经超过了任务的截止时间
            if (tasks[i].deadline <= pq.size()) {
                // 如果小根堆的顶部（即最小利润的任务）的利润小于当前任务的利润
                if (pq.peek() < tasks[i].reward) {
                    ans += tasks[i].reward - pq.poll(); // 更新总利润，并执行“后悔操作”：替换最小利润的任务
                    pq.add(tasks[i].reward); // 将当前任务的利润加入小根堆
                }
            } else {
                // 如果当前任务数量没有超过截止时间，直接加入任务并更新总利润
                ans += tasks[i].reward;
                pq.add(tasks[i].reward);
            }
        }
        // 输出能够获得的最大利润
        System.out.println(ans);
        input.close();
    }
}
