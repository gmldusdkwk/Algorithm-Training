import java.io.*;
import java.util.*;

class Main {

	static boolean[] visited = new boolean[10];
	static int[] numbers = new int[11]; //숫자 배열 
	static int[] operation = new int[4]; //연산 배열 
	static int N;
	static int max = Integer.MIN_VALUE;
	static int min = Integer.MAX_VALUE;
	static int ans = 0;

	static class Queue_Data {
		int ans;
		int index;
		int plus;
		int min;
		int mul;
		int div;

		Queue_Data(int ans, int index, int plus, int min, int mul, int div) {
			this.ans = ans;
			this.index = index;
			this.plus = plus;
			this.min = min;
			this.mul = mul;
			this.div = div;
		}
	}

	public static void main(String args[]) throws Exception {

		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();		

		for (int i = 0; i < N; i++) {
			numbers[i] = sc.nextInt();
		}

		for (int i = 0; i < 4; i++) {
			operation[i] = sc.nextInt();
		}

		dfs(1, numbers[0]);
		System.out.println(max);
		System.out.println(min);
		

		bfs(1, numbers[0]);		

	}

	public static void dfs(int index, int amount) { //숫자의 인덱스, 재귀 함수를 갔을 때의 합 
		//연산자들을 다 본다. 
		if (index == N) {
			max = Integer.max(max, amount);
			min = Integer.min(min, amount);
		}

		if (operation[0] > 0) {
			operation[0]--;
			dfs(index + 1, amount + numbers[index]);
			operation[0]++;
		}
		if (operation[1] > 0) {
			operation[1]--;
			dfs(index + 1, amount - numbers[index]);
			operation[1]++;
		}
		if (operation[2] > 0) {
			operation[2]--;
			dfs(index + 1, amount * numbers[index]);
			operation[2]++;
		}
		if (operation[3] > 0) {
			operation[3]--;
			dfs(index + 1, amount / numbers[index]);
			operation[3]++;
		}
	}

	public static void bfs(int index, int amount) { 
		//근데 이 방법도 dfs 인듯 하다. 결국 스택에 저장해서 스택 값을 읽는 것이기 때문이다. 
		Stack<Queue_Data> q = new Stack<Queue_Data>();
		q.add(new Queue_Data(numbers[0], index, operation[0], operation[1], operation[2], operation[3]));

		while (!q.isEmpty()) {
			Queue_Data now = q.pop();
			amount = now.ans;
			index = now.index;
//			System.out.println(numbers[index]);
//			System.out.println(index);
//			System.out.println(now.ans);
//			System.out.println(now.plus);
//			System.out.println(now.min);
//			System.out.println(now.mul);
//			System.out.println(now.div);
			

			if (index == N) {
				max = Integer.max(max, amount);
				min = Integer.min(min, amount);
			
				continue;
			}
			if (now.plus > 0) {
				q.add(new Queue_Data(amount + numbers[index], index + 1, now.plus - 1, now.min, now.mul, now.div));						
			}
			if (now.min > 0) {
				q.add(new Queue_Data(amount - numbers[index], index + 1, now.plus, now.min - 1, now.mul, now.div));						
			}
			if (now.mul > 0) {
				q.add(new Queue_Data(amount * numbers[index], index + 1, now.plus, now.min, now.mul - 1, now.div));
			}
			if (now.div > 0) {
				q.add(new Queue_Data(amount / numbers[index], index + 1, now.plus, now.min, now.mul, now.div - 1));
			}
		}
		System.out.println(max);
		System.out.println(min);
	}

}
