package dijkstra;

import java.util.*;

class Element implements Comparable<Element> {
	int dest;
	int cost;

	Element(int dest, int cost) {
		this.dest = dest;
		this.cost = cost;
	}

	@Override
	public int compareTo(Element o) {
		if (this.cost < o.cost)
			return -1;
		else if (this.cost == o.cost)
			return 0;
		else
			return 1;
	}
}

public class dijkstra {
	static int V; // vertex
	static int E; // edges
	static int StartV;
	static int distance[];// 최단 거리를 저장할 변수
	static boolean visited[];// 해당 노드를 방문했는지 체크할 변수
	static int inf = 1000000;

	public static void dijkstra(ArrayList<Element>[] a) {
		distance[StartV] = 0;

		PriorityQueue<Element> q = new PriorityQueue<Element>(); // 우선순위 큐
		q.offer(new Element(StartV, 0));

		while (!q.isEmpty()) {
			Element e = q.poll(); // 큐에 들어있는 간선중 가장 가중치가 낮은 것 찾음.
			if (visited[e.dest] == true) {
				continue;
			}
			visited[e.dest] = true;
			for (Element k : a[e.dest]) {
				if (visited[k.dest] == false) {
					distance[k.dest] = Math.min(distance[k.dest], distance[e.dest] + k.cost);
					q.offer(new Element(k.dest, distance[k.dest]));
				}
			}
		}
	}
	
	private static void floyd(int d[][], int V) {
		for (int k = 1; k <= V; k++)
			for (int i = 1; i <= V; i++)
				for (int j = 1; j <= V; j++) {
					if (d[i][j] > d[i][k] + d[k][j]) {
						d[i][j] = d[i][k] + d[k][j];
					}
				}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		V = sc.nextInt();
		E = sc.nextInt();
		StartV = sc.nextInt();

		distance = new int[V + 1];
		visited = new boolean[V + 1];

		ArrayList<Element>[] a = (ArrayList<Element>[]) new ArrayList[V + 1];

		for (int i = 1; i <= V; i++) {
			visited[i] = false;
			distance[i] = inf;

			a[i] = new ArrayList<Element>();
		}

		for (int i = 0; i < E; i++) {
			int t1 = sc.nextInt();
			int t2 = sc.nextInt();
			int t3 = sc.nextInt();

			a[t1].add(new Element(t2, t3));
		}

		dijkstra(a);

		for (int i = 1; i <= V; i++) {
			if (distance[i] == inf) {
				System.out.println("INF");
			} else {
				System.out.println(distance[i]);
			}
		}
	}

}
