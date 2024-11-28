import java.rmi.server.ExportException;
import java.util.*;
import java.io.*;

public class LearningToCode {
    public static void main(String[] args) throws Exception {
        (new Doit()).doit();
        return;
    }
}

class Doit {
    static final public String var   = "var";
    static final public String print = "print";
    static final int LIM = 15000;
    static Map<String, String> vars = new TreeMap<>();
    public void doit() throws Exception {
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        while(true) {
            String line = stdin.readLine();
            if(line.equals("end.")) {
                break;
            }
            else if(line.startsWith(var)) {
                line = line.substring(var.length() + 1, line.length() - 1);
                int pos = line.indexOf('=');
                String varName = line.substring(0, pos - 1);
                String value = line.substring(pos + 2);
                vars.put(varName, parseExpr(value));
            }
            else {
                line = line.substring(print.length() + 1, line.length() - 1);
                System.out.println(parseExpr(line));
            }
        }
        stdin.close();
        return;
    }
    String parseExpr(String expr) throws Exception {
        int N = expr.length();
        Stack<Integer>stk = new Stack<Integer>();
        int[] match = new int[N];
        for (int i = 0; i < N; i++) {
            if (expr.charAt(i) == '{') {
                stk.push(i);
            } else if (expr.charAt(i) == '}') {
                int pos = stk.peek();
                stk.pop();
                match[pos] = i;
                match[i] = pos;
            }
        }
        LimitStringBuilder ret = new LimitStringBuilder(LIM);
        recExpr(expr, 0, N - 1, match, ret);
        return ret.toString();
    }
    void recExpr(String expr, int L, int R, int[] match, LimitStringBuilder ret) throws Exception{
        if(L > R) return;
        if(expr.charAt(L) == '"') {
            ret.append(expr.substring(L + 1, R));
            return;
        }
        if (expr.charAt(L) == '`') {
            for (int i = L + 1; i < R; i++) {
                if (expr.charAt(i) == '$' && i + 1 < R && expr.charAt(i + 1) == '{') {
                    recExpr(expr, i + 2, match[i + 1] - 1, match, ret);
                    i = match[i + 1];
                } else {
                    ret.append(expr.charAt(i));
                }
            }
            return;
        }
        ret.append(vars.get(expr.substring(L, R + 1)));
        return;
    }
}

class LimitStringBuilder {
    public LimitStringBuilder(int maxCapacity) {
        sb = new StringBuilder(maxCapacity);
        this.maxCapacity = maxCapacity;
    }
    public String toString() {
        return sb.toString();
    }
    public void append(String s) {
        if (sb.length() + s.length() > maxCapacity) return;
        sb.append(s);
    }
    public void append(char c) {
        if (sb.length() == maxCapacity) return;
        sb.append(c);
    }
    private StringBuilder sb;
    private int maxCapacity;
}