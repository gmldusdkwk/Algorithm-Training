//구슬 탈출 
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
 
 
class Main {
 
    static int MAX = 10;
    static int[][] map;
    static boolean[][][][] visited;
    static int N = 0;
    static int M = 0;
    static int[] dy = { -1, 1, 0, 0 };
    static int[] dx = { 0, 0, -1, 1 };
    static int ans = 0;
 
    static class Point {
        public int x, y;
 
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
     
    static class Queue_Data {
        Point R;
        Point B;
        int count;
         
         
        Queue_Data(Point R, Point B, int count) {
            this.R = new Point(R.x, R.y);
            this.B = new Point(B.x, B.y);
            this.count = count;
        }
    }
    public static void BFS(Point R,Point B) {
    	Queue<Queue_Data> q = new LinkedList<Queue_Data>(); //Red Point,Blue Point, count
        q.add(new Queue_Data(R,B,ans));                    
                
        while (!q.isEmpty()) {
            Queue_Data now = q.poll();
            R = new Point(now.R.x, now.R.y);
            B = new Point(now.B.x, now.B.y);
            ans = now.count;
            ans++;
            //System.out.println(R.x+" "+R.y);
            //System.out.println(B.x+" "+B.y);
            //System.out.println(ans);
             
            if (ans > 10) 
            	continue;//10번 넘어가면 안됨
 
            for (int i = 0; i < 4; i++) { //4 direction
                Point next_Red = new Point(R.x, R.y);
                Point next_Blue = new Point(B.x, B.y);
 
                while (map[next_Red.x + dx[i]][next_Red.y + dy[i]] != '#') {
                    next_Red.x += dx[i];
                    next_Red.y += dy[i];
                    if (map[next_Red.x][next_Red.y] == 'O') 
                    	break;
                }
                while (map[next_Blue.x + dx[i]][next_Blue.y + dy[i]] != '#') {
                    next_Blue.x += dx[i];
                    next_Blue.y += dy[i];
                    if (map[next_Blue.x][next_Blue.y] == 'O') 
                    	break;
                }
 
                //파란 공 나옴
                if (map[next_Blue.x][next_Blue.y] == 'O') {
                	continue;                	
                }                	
                    
                //빨간 공만 빠져나옴
                if (map[next_Red.x][next_Red.y] == 'O') {
                    System.out.println(ans);
                    System.exit(0);//종료
                }
                 
                //겹친 경우
                if (next_Red.x == next_Blue.x && next_Red.y == next_Blue.y) {
                	if(dx[i] == -1){ //위로 이동  
                		if(R.x > B.x) next_Red.x++; //빨간 구슬 파란 구슬보다 아래에 있을 경우   
                		else next_Blue.x++;
                	}
                	else if(dx[i] == 1) { //아래로 이동  
                		if(R.x > B.x) next_Blue.x--; //빨간 구슬이 파란 구슬보다 아래에 있을 경우  
                		else next_Red.x--;
                	}
                	else if(dy[i] == -1) { //좌로 이동 
                		if(R.y > B.y) next_Red.y++; //빨간 구슬이 오른쪽에 있을 경우 
                		else next_Blue.y++;
                	}
                	else {//우로 이동  
                		if(R.y > B.y) next_Blue.y--;
                		else next_Red.y--;
                	}                   
                }
 
                //방문 안한 것만 큐에 push
                if (visited[next_Red.x][next_Red.y][next_Blue.x][next_Blue.y] == true) 
                	continue;
                 
                q.add(new Queue_Data(next_Red,next_Blue,ans));
                visited[next_Red.x][next_Red.y][next_Blue.x][next_Blue.y] = true;
            }
        }
    }
 
    public static void main(String args[]) throws Exception {
         
    	Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
 
        map = new int[N][M];
        
        Point R = new Point(0,0);
        Point B = new Point(0,0);
         
        for (int i = 0; i < N; i++) {
            String tmp = sc.next();
            for (int j = 0; j < M; j++) {            	
                map[i][j] = tmp.charAt(j);
                
                if (map[i][j] == 'B') {
                    map[i][j] = '.';
                    B.x = i; 
                    B.y = j;
                }
                if (map[i][j] == 'R') {
                    map[i][j] = '.';
                    R.x = i; 
                    R.y = j;
                }
            }
        }
        //System.out.println(R.x+" "+R.y);
        //System.out.println(B.x+" "+B.y);
                         
        visited = new boolean[MAX][MAX][MAX][MAX]; // visited 저장  
        
        for(int i = 0;i < MAX; i++)
            for(int j = 0;j < MAX; j++)
                for(int k = 0;k < MAX; k++)                	
                    Arrays.fill(visited[i][j][k], false);
        
        visited[R.x][R.y][B.x][B.y] = true;
        
        BFS(R,B);
        System.out.println(-1);
         
    }
}
