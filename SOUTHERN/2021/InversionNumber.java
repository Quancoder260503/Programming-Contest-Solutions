import java.util.*;

class FenwickTree {
  long f[];
  int N;
  public FenwickTree(int N) {
    this.N = N;
    f = new long[N];
  }
  public long query(int i) {
    long c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c += f[i];
    }
    return c;
  }
  public void update(int i, int diff) {
    for (++i; i < N; i += (i & -i)) {
      f[i] += diff;
    }
  }
}

class Element {
  int value;
  int ind;
  public Element(int ind, int value) {
    this.value = value;
    this.ind = ind;
  }
  public String toString() {
    return "(" + this.ind + ", " + this.value + ")";
  }
}

public class Main {
  public static void main(String[] args) {
    Scanner stdin = new Scanner(System.in);
    int N = stdin.nextInt();
    Element[] a = new Element[N];
    for (int i = 0; i < N; i++) {
      a[i] = new Element(i + 1, stdin.nextInt());
    }
    Arrays.sort(a, (i1, i2) -> i1.value - i2.value);
    long acc = 0;
    long[] cache = new long[N];
    FenwickTree fenw = new FenwickTree(N + 7);
    for (int i = N - 1; i >= 0; i--) {
      cache[i] += acc;
      acc += fenw.query(a[i].ind);
      fenw.update(a[i].ind, 1);
    }
    acc = 0;
    fenw = new FenwickTree(N + 7);
    for (int i = 0; i < N; i++) {
      cache[i] += acc;
      acc += (fenw.query(N + 1) - fenw.query(a[i].ind));
      fenw.update(a[i].ind, 1);
    }
    long ans = (1L << 62);
    for (int i = 0; i < N; i++) {
      ans = Math.min(ans, cache[i]);
    }
    System.out.println(ans);
    stdin.close();
  }
}