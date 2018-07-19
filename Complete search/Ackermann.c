#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int count=0;

int ack1(int m, int n)
{
    printf("A(%d, %d) 호출\n",m,n);
        if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        count++;
        return ack1(m - 1, 1);
    }
    else {
        count++;
        return ack1(m - 1, ack1(m, n - 1));
    }
}

int ack1_1(int m, int n)
{
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return ack1_1(m - 1, 1);
    }
    else {
        return ack1_1(m - 1, ack1_1(m, n - 1));
    }
}


int ack2(int m,int n){
    int index=0; //얼마만큼 저장되어있는지 확인이 가능합니다.
    int array[1000]; //아커만 함수를 계속 호출할 때 마다 저장하는 형식으로 배열 구현
    //하지만 배열의 크기를 정적으로 고정시켰다는 한계로 m과 n에 더 큰 수를 넣을 수 없었습니다.
    //그리고 더 큰 수를 넣으니 너무 많은 일을 하게 되어 CPU가 중지되는 일이 발생하였습니다.
    array[index]=m;
    array[index+1]=n;
    index++;//배열 안에 얼마만큼으로 m,n이 span되어 있는지 확인이 가능합니다.
    
    while(1){
        count++;
        for(int i=0;i<=index;i++)
            printf("%d ",array[i]);
        printf("\n");
        if(index==0){//배열 안에 한 개의 값만이 저장되어 있다는 뜻으로 이 값은 반환 값이 됩니다.
            return array[index];
        }
        else if(array[index-1]==0){ //예시 A(0,2) -> 3
            array[index-1]=array[index]+1;//m=0이고 n이 0이 아니라면 n+1을 반환합니다.
            array[index]=0;
            index--;
        }
        else if(array[index-1]==1 && array[index]==0){ //예시 A(1,0) -> A(0,1)
            array[index-1]=0;//n=1이고 m=0이면 n과 m의 위치를 변환합니다.
            array[index]=1;
        }
        else if(array[index-1]!=0 && array[index]==0){ //예시 A(2,0) -> A(1,1)
            array[index-1]=array[index-1]-1;//m이 0이 아니고 n=0이라면 m에서 1을 빼주고 n에서 1을 더해줍니다.
            array[index]=array[index]+1;
        }
        else if(array[index-1]!=0 && array[index]!=0){ //예시 A(3,2) -> 2,A(3,1)
            array[index+1]=array[index]-1;//m,n이 0이 아니면 n-1 값을 배열 맨 뒤에 추가해줍니다.
            array[index]=array[index-1];//m의 값을 예전 n이 저장되어있던 배열 위치에 저장해줍니다.
            array[index-1]=array[index-1]-1;//m-1의 값을 예전 m이 저장되어 있던 자리에 저장해줍니다.
            index++;
        }
    }
    
}

int ack2_2(int m,int n){
    int index=0;
    int array[1000];
    array[index]=m;
    array[index+1]=n;
    index++;
    
    while(1){
        
        if(index==0){
            return array[index];
        }
        else if(array[index-1]==0){ //A(0,2) -> 3
            array[index-1]=array[index]+1;
            array[index]=0;
            index--;
        }
        else if(array[index-1]==1 && array[index]==0){ //A(1,0) -> A(0,1)
            array[index-1]=0;
            array[index]=1;
        }
        else if(array[index-1]!=0 && array[index]==0){ //A(2,0) -> A(1,1)
            array[index-1]=array[index-1]-1;
            array[index]=array[index]+1;
        }
        else if(array[index-1]!=0 && array[index]!=0){ //A(3,2) -> 2,A(3,1)
            array[index+1]=array[index]-1;
            array[index]=array[index-1];
            array[index-1]=array[index-1]-1;
            index++;
        }
    }
    
}


int main()
{
    clock_t start1,finish1,start2,finish2;
    double duration;
   /*
    printf("Q1. A(3,2) = %3d\n",ack1(3,2));
    printf("\n");
    printf("Q2. A(2.3) = %3d\n",ack1(2,3));
    */
    count=0;
    /*printf("\n");
    printf("Q3. A(3.5) = %3d\n",ack1(3,5));
    start1=clock();
    ack1_1(3,5); // 오로지 걸리는 시간을 구하기 위해서 ack1과 ack1_1로 나누었습니다.
    finish1=clock();
    duration=finish1-start1;
    printf("Time(Recursive): %f\n",duration);
    printf("호출 수: %d\n\n",count);
    count=0;
   */
    printf("\n");
    printf("Q4. A(3.2) = %3d\n",ack2(3,2));
    /*start2=clock();
    ack2_2(3,5); //오로지 걸리는 시간을 구하기 위해서 ack2과 ack2_2로 나누었습니다.
    finish2=clock();
    duration=finish2-start2;
    printf("Time(Non-Recursive): %f\n",duration);
    printf("반복 수: %d\n\n",count);
    
    
*/
    
    printf("\n");
   
    return 0;
}


