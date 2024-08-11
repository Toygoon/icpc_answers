import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.PriorityQueue;

public class Q28707 {
    public static int N, M;
    public static int[] A;
    public static int[][] cost;
    public static final int INF = 1000000000;

    public static void main(String[] args) throws IOException {
        System.out.println(solve());
    }

    private static int solve() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.parseInt(br.readLine());
        A = Arrays.stream(br.readLine().split(" ")).map(String::trim).mapToInt(Integer::parseInt).toArray();
        M = Integer.parseInt(br.readLine());

        cost = new int[N][N];
        for (int i = 0; i < N; i++)
            Arrays.fill(cost[i], INF);

        for (int i = 0; i < M; i++) {
            String[] tmp = br.readLine().split(" ");
            int l = Integer.parseInt(tmp[0]) - 1, r = Integer.parseInt(tmp[1]) - 1, c = Integer.parseInt(tmp[2]);

            cost[l][r] = Math.min(cost[l][r], c);
            cost[r][l] = Math.min(cost[r][l], c);
        }

        br.close();

        return dijkstra(A);
    }

    private static int dijkstra(int[] start) {
        PriorityQueue<State> pq = new PriorityQueue<>();
        HashMap<State, Integer> dist = new HashMap<>();

        State first = new State(start);
        pq.offer(new State(start, 0));
        dist.put(first, 0);

        while (!pq.isEmpty()) {
            State cur = pq.poll();

            if (isSorted(cur.array))
                return cur.cost;

            if (cur.cost > dist.get(cur))
                continue;

            for (int i = 0; i < N - 1; i++) {
                for (int j = 1; j < N; j++) {
                    if (cost[i][j] != INF) {
                        int[] nextArr = Arrays.copyOf(cur.array, N);
                        swap(nextArr, i, j);

                        int nextCost = cur.cost + cost[i][j];
                        State nextState = new State(nextArr);

                        if (!dist.containsKey(nextState) || nextCost < dist.get(nextState)) {
                            dist.put(nextState, nextCost);
                            pq.offer(new State(nextArr, nextCost));
                        }
                    }
                }
            }
        }

        return -1;
    }

    private static void swap(int[] a, int i, int j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    private static boolean isSorted(int[] a) {
        for (int i = 1; i < N; i++)
            if (a[i] < a[i - 1])
                return false;

        return true;
    }


    private static class State implements Comparable<State> {
        public int[] array;
        public int cost;

        public State(int[] array) {
            this.array = array;
            this.cost = 0;
        }

        public State(int[] array, int cost) {
            this.array = array;
            this.cost = cost;
        }

        @Override
        public int compareTo(State o) {
            return Integer.compare(this.cost, o.cost);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o)
                return true;

            State s = (State) o;
            return Arrays.equals(this.array, s.array);
        }

        @Override
        public int hashCode() {
            return Arrays.hashCode(this.array);
        }
    }
}