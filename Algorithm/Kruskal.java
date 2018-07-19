//https://www.acmicpc.net/problem/1197
/*MST
 * 간선의 방향성이 없는 그래프에서 이용된다.
 * 
 */
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

public class Kruskal {
	static int V; //vertex
	static int E; //edge
	static int distance[];
	static boolean visited[][];
	static int parent[];
	static int inf = 1000000;
	static int ans;
	
	
	private static void Kruskal (PriorityQueue<Element> q) {
		
		
		while(!q.isEmpty()) {
			if (find(q.peek().v1) != find(q.peek().v2)) {
				union(q.peek().v1, q.peek().v2);
				ans += q.peek().cost;
			}
			q.poll();
		}

	}	
    public static int find(int x) {
    	if (x == parent[x])
			return x;

		int root = find(parent[x]);
		parent[x] = root;
		return root;
    }
	private static void union(int v1, int v2) {
		v1 = find(v1);
		v2 = find(v2);

		parent[v2] = v1;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);
		V = sc.nextInt();
		E = sc.nextInt();
		
		distance = new int[V+1];		
		
		PriorityQueue <Element> q = new <Element> PriorityQueue();
		
		for(int i = 1; i <= E; i++) {
			int t1 = sc.nextInt();
			int t2 = sc.nextInt();
			int t3 = sc.nextInt();

			q.offer(new Element(t1,t2,t3)); //저장을 하면서 비용을 오름차순으로 정렬한다.
		}
		
		parent = new int[V+1]; //사이클이 존재하는지 확인하기 위해서 모든 노드들의 대표 노드를 자기 자신으로 초기화한다.
		for(int i = 1; i <= V; i++) {
			parent[i] = i;
		}
				
		Kruskal(q);
		System.out.println(ans);
	}

}
