
import java.io.*;
import java.util.*;

class Element implements Comparable<Element> {
    int v1;
    int v2;
    int cost;
    Element(int v1, int v2, int cost) {
        this.v1 = v1;
        this.v2 = v2;
        this.cost = cost;
    }
    
    @Override
    public int compareTo(Element o) {
        if(this.cost < o.cost)
            return -1;
        else if(this.cost == o.cost)
            return 0;
        else
            return 1;
    }
}

public class Prim {
	static int V; // vertex
	static int E; // edge
	static int distance[];
	static boolean visited[];
	static int maps[][];
	static int nV = 0;
	static int inf = 1000000;
	static int ans;

	private static void prim(PriorityQueue<Element> q) {
		
//		while(!q.isEmpty()) {
//			int here = q.peek().v2;
//			int cost = q.peek().cost;
//			
//			q.poll();
//			
//			if(visited[here] == false)
//				continue;
//			
//			visited[here] = true;
//			
//			for (int i = 1; i <= V; i++) {
//				if (visited[i] == false && maps[here][i] != inf) {
//					if (maps[here][i] < distance[i])
//						distance[i] = maps[here][i];
//				}
//			}
//			
//			for(int i = 1; i <= V; i++) {
//				int there = q.peek().v2;
//				int therecost = q.peek().cost;
//				
//				q.add(new Element(q.peek().v1,there,therecost));
//			}
//			
//		}
		distance[1] = 0;
		while (nV < V) {
			int min = inf;
			int min_index = -1;

			for (int i = 1; i <= V; i++) {
				if (visited[i] == false && distance[i] < min) {
					min = distance[i];
					min_index = i;
				}
			}

			for (int i = 1; i <= V; i++) {
				if (visited[i] == false && maps[min_index][i] != inf) {
					if (maps[min_index][i] < distance[i])
						distance[i] = maps[min_index][i];
				}
			}
			nV++;
			ans += min;
			visited[min_index] = true; 
		}
	}

	public static void main(String[] args) {// 노드를 선택할 때 연결성이 존재하도록 선태한다.
		Scanner sc = new Scanner(System.in);
		V = sc.nextInt();
		E = sc.nextInt();

		visited = new boolean[V + 1];
		distance = new int[V + 1];
		maps = new int[V + 1][V + 1];

		for (int i = 1; i <= V; i++) {
			distance[i] = inf;
			visited[i] = false;

			for (int j = 1; j <= V; j++) {
				maps[i][j] = inf;
			}
		}
		
		PriorityQueue <Element> q = new <Element> PriorityQueue();


		for (int i = 1; i <= E; i++) {
			int t1 = sc.nextInt();
			int t2 = sc.nextInt();
			int t3 = sc.nextInt();

			
			maps[t1][t2] = t3; //인접행렬을 통해서 입력값을 저장한다.
			maps[t2][t1] = t3;//방향성이 존재하지 않기 때문에 양쪽 방향에 다 저장한다. 
		}

		prim(q);
		System.out.println(ans);
	}

}
