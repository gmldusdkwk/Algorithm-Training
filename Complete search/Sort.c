#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc/malloc.h>


void Print_Array(int *a,int n){
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}
void Swap(int *a, int *b){
    int temp=*b;
    *b=*a;
    *a=temp;
}

void Bubble_Sort(int *a, int n)
{
    int temp=0;
    int i, j;
    for(i=0; i<n; i++){
        for(j=1; j<n; j++)
            if(a[j-1]>a[j]){ //옆에 붙어있는 인덱스를 확인합니다.
            //Swap(&a[j-1], &a[j]); //만약에 앞에 있는 값이 더 크다면 둘의 자리를 변경해줍니다.
                temp=a[j];
                a[j]=a[j-1];
                a[j-1]=temp;
            }
        //print_array(a, n);
    }
}
int max(int *a,int n){
    int m=0;
      for(int i=0;i<n;i++)
        if(a[i]>m)
          m=a[i]; //maxinmum을 찾습니다
    return m;
}
void Radix_Sort(int *a,int n){
    int temp[n]; //임시로 저장하는 값입니다.
    int m=0; //최대의 숫자를 구해서 최대 자리수를 구하기 위해서 입니다.
    int exp=1;//자리 수 확인합니다.
    m=max(a,n);
    
    while(m/exp>0)
    {
        int bucket[10]={0};//0~9까지의 나머지를 의미하는 버킷 배열을 만듭니다.
        for(int i=0;i<n;i++){
            bucket[a[i]/exp%10]++;//자리 수 별로 나머지를 구해서 버킷의 갯수를 넣습니다.
        }
        for(int i=1;i<10;i++){
            bucket[i]+=bucket[i-1];//각 원소들의 순서를 알기 위해 버킷을 누적으로 저장합니다.
        }
        for(int i=n-1;i>=0;i--){
            temp[--bucket[a[i]/exp%10]]=a[i];//몇 번인지 알기 위해서 결과를 통해서 임시 저장소에 순서를 정렬해서 저장합니다.
        }
        for(int i=0;i<n;i++){
            a[i]=temp[i];//임시저장소에 저장되어 있던 결과 값을 결과 배열에 옮겨 줍니다.
        }
        exp*=10;//일의 자리, 십의 자리 계속 곱해서 확인합니다.
    }

}


void Merge(int *a, int l, int mid, int r,int N){
    int i=l; // i는 왼쪽 배열의 인덱스를 의미합니다.
    int j=mid+1;//j는 오른쪽 배열의 인덱스를 의미합니다.
    int k=l; // k는 a 배열의 인덱스를 의미합니다
    
    int temp[N]; //임시 저장소를 만들기 위해서 N=원래 데이터의 길이를 넣었습니다.
    
    while(i<=mid&&j<=r){//아직 양쪽배열에 둘 다 원소가 남아있는 경우
        if(a[i]<=a[j]){ //각각의 배열은 정렬이 되어있는 상태이므로 둘을 비교하여 작은 것 부터 저장합니다.
            temp[k++]=a[i++];
        }
        else temp[k++]=a[j++];
    }
    while(i<=mid){//왼쪽 배열의 원소만 남은 경우 남은 것을 전부 저장합니다.
        temp[k++]=a[i++];
    }
    while(j<=r){ //오른쪽 배열의 원소만 남은 경우 남은 것을 전부 저장합니다.
        temp[k++]=a[j++];
    }
    
    for(int i=l;i<=r;i++){
        a[i]=temp[i]; //temp의 있는 내용을 원래 데이터로 옮깁니다.
    }
}

void Merge_Sort(int *a,int l,int r,int N){
    if(l<r) {
        int mid=(l+r)/2; //가운데 인덱스를 생성합니다.
        Merge_Sort(a,l,mid,N); //왼쪽 배열을 분해합니다.
        Merge_Sort(a,mid+1,r,N); //오른쪽 배열을 분해합니다.
        Merge(a,l,mid,r,N);//분해가 완료되면 병합합니다.
    }
}


int main(){
    int N = 15; //배열의 숫자입니다.
    //int a[]={7,3,5,2,6,8,1,9,10,4};
    clock_t start1,finish1,start2,finish2,start3,finish3;
    
    int a[]={326,53,608,835,751,45,704,690,333,285,9719,243,3,163,561};
    int b[]={326,53,608,835,751,45,704,690,333,285,9719,243,3,163,561};
    int c[]={326,53,608,835,751,45,704,690,333,285,9719,243,3,163,561};
    //int d[]={97,57,84,26,34,11,80,46,75,23,67,51,92,12,31};
    //int e[]={97,57,84,26,34,11,80,46,75,23,67,51,92,12,31};
    
    
    
    printf("Original Data: \n");
    Print_Array(a, N);
    printf("\n");
    
    start1=clock();
    Bubble_Sort(a, N);
    finish1=clock();
    printf("Time(Bubble Sort): %lu\n",(finish1-start1));
    Print_Array(a, N);
    printf("\n");
    
    start1=clock();
    Radix_Sort(b, N);
    finish1=clock();
    printf("Time(Radix Sort): %lu\n",(finish1-start1));
    Print_Array(b, N);
    printf("\n");
    
    start3=clock();
    Merge_Sort(c,0,N-1,N);
    finish3=clock();
    printf("Time(Merge Sort): %lu\n",(finish3-start3));
    Print_Array(c, N);
    
    return 0;
    
}
