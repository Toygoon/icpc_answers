import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

public class Q9733 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        HashMap<String, Integer> map = new HashMap<>();
        int total = 0;
        String s;
        while ((s = br.readLine()) != null) {
            for (String k : s.split(" ")) {
                map.merge(k, 1, Integer::sum);
                total++;
            }
        }

        StringBuilder sb = new StringBuilder();
        for (String x : "Re,Pt,Cc,Ea,Tb,Cm,Ex".split(",")) {
            int count = map.getOrDefault(x, 0);

            sb.append(x).append(' ').append(count).append(' ');
            if (count == 0) {
                sb.append("0.00");
            } else {
                sb.append(String.format("%.2f", (double) count / total));
            }
            sb.append('\n');
        }

        sb.append("Total ").append(total).append(" 1.00");
        System.out.println(sb);

        br.close();
    }
}
