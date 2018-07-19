#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>

typedef struct node{
    int data;
    struct node * link;
} Node;

void create(Node **p,int n){
    *p=(Node *)malloc(sizeof(Node));
    (*p)->data=n;
    (*p)->link=NULL;//새로운 노드를 생성합니다.
}

//마지막 추가
void add_last(Node **tail_p, int data){
    Node *new=(Node *)malloc(sizeof(Node)); //새로운 노드를 동적할당합니다.
    new->data=(data); //새로운 노드에 데이터를 저장합니다.
    new->link=NULL;//마지막 이므로 새로운 노드의 링크에 NULL을 저장합니다.
    (*tail_p)->link=new;//그 후 tail 뒤에 연결해줍니다.
    
    *tail_p=new;//tail의 포인터를 변경해줍니다.
}

//앞에 추가
void add_first(Node **head_p, int data){
    Node *new=(Node *)malloc(sizeof(Node)); //새로운 노드를 동적할당합니다.
    new->link=(*head_p);//새로운 노드와 헤더를 연결해줍니다.
    new->data=data;//새로운 노드에 데이터를 저장합니다.
    
    *head_p=new;//헤더의 포인터를 변경합니다.
}

//중간에 추가
void mid_insert(Node **head_p,int data){
    Node *temp=*head_p;
    Node *new=(Node *)malloc(sizeof(Node));//새로운 노드를 동적할당합니다.
    
    while(temp!=NULL){
        if(temp->data<data){//새로 넣으려고 하는 데이터가 현재 노드의 데이터보다 큰 상태에서
            if(temp->link->data>data){ //다음 노드의 데이터 보다 작은 상태라면 그 사이에 삽입해야 한다는 것을 알 수 있습니다.
                new->link=temp->link; //새로운 노드의 링크에 현재 노드 링크 값을 저장하고
                temp->link=new;//현재 노드의 링크 값에 새로운 노드의 주소값을 저장합니다.
                new->data=data;//그리고 새로운 노드에 데이터 값을 저장합니다.
                return;
            }
        }
        temp=temp->link;//찾지 못한다면 계속 찾을 때 까지 계속합니다.
        
    }
}


//비교하기 add_last, add_first, mid_insert
void compare(Node **head_p,Node **tail_p,int data){

    if(data<((*head_p)->data)) add_first(head_p,data); //OK
    else if(data>((*tail_p)->data)) add_last(tail_p,data); //OK
    else {
        mid_insert(head_p,data);
    }
}

//전체 노드가 어떤 상황인지 프린트 해줍니다.
void print_node(Node **head_p, Node **tail_p){
    Node *temp=*head_p;
    int i=1;
    printf("------------------------------------\n");
    printf("Head 주소: %d\n",*head_p);
    printf("Tail 주소: %d\n",*tail_p);
    ;    printf("연결 노드 상태\n");
    while(temp!=NULL){
        printf("주소 [%8d] 순서 [%d] %d \n",temp,i,temp->data);
        temp=temp->link;
        i++;
    }
    printf("------------------------------------\n\n");
}
//맨 앞에 있는 노드를 제거 합니다
void delete_firtst(Node **head_p){
    Node *temp=*head_p;
    (*head_p)=(*head_p)->link; //맨 앞에 있는 노드를 제거하기 위해 헤드의 포인터를 옮겨줍니다.
    free(temp);//그 후 temp의 값을 없애줍니다.
}

//데이터 값을 확인하여 노드를 삭제합니다.
void delete(Node **head_p,Node **tail_p, int data){
    Node *temp=*head_p;
    if(temp->data==data){
        delete_firtst(head_p);//맨 앞에 있는 노드를 제거합니다.
        return;
    }
    while(temp->link->link!=NULL){ //중간에 있는 노드인지를 확인하기 위함입니다.
        if(temp->link->data==data){//다음에 있는 노드의 데이터가 동일하다면
            temp->link=temp->link->link;//다음에 있는 노드를 제거하기 위해서 현재 노드의 링크를 그 다음 다음 주소로 변경해줍니다.
            free(temp->link);//중간의 제거할 노드를 free 해줍니다.
            return;
        }
        temp=temp->link;//확인할 때 까지 노드의 포인터를 변경합니다.
    }
    if(temp->link->data==data){ //while문을 나오게 되면 노드1 -> 노드2의 링크가가 NULL이라는 뜻으로 존재하지 않는다는 것을 의미합니다.
        free(temp->link); //그러므로 tail까지 확인이 완료되었다는 것을 의미합니다. 그래서 노드2의 값을 제거합니다.
        temp->link=NULL;//그 후 노드 1의 링크를 NULL로 변경합니다.
        *tail_p=temp; //tail의 포인터를 변경합니다.
        return;
    }
    
    printf("\n존재하지 않는 node 입니다\n");
}

int main(){
    Node *head=NULL;
    Node *tail=NULL;
    Node *temp=NULL;
    int input;
    int I,D,N=0;//I:예정 input 실행 수, D:예정 delete할 실행 수, N:node의 개수
    
    printf("원하는 node의 개수를 입력해주세요: ");
    scanf("%d",&I);
   
    printf("\n숫자를 입력해주세요: ");//첫 번째 숫자 입력
    scanf("%d",&input);
    create(&head,input);
    print_node(&head,&tail);
    
    printf("\n숫자를 입력해주세요: ");//두 번째 숫자 입력
    scanf("%d",&input);
    create(&tail,input);
    if(head->data>tail->data) { //두 개의 숫자 비교하여 정렬
        int temp=head->data;
        head->data=tail->data;
        tail->data=temp;
    }
    head->link=tail; //헤더와 테일로 결정한 다음에 연결
    print_node(&head,&tail);
    
    
    for(int i=0;i<I-2;i++){ //그 후에는 계속 받자마자 바로바로 연결
        printf("\n숫자를 입력해주세요: ");
        scanf("%d",&input);
        compare(&head,&tail,input);
        print_node(&head,&tail);
    }
    
    temp=head;
    while(temp!=NULL){
        N++;
        temp=temp->link;
    }
    
    printf("제거할 node의 수를 입력해주세요: ");
    scanf("%d",&D);
    
    while(N<D) { //존재하는 노드의 수와 제거 과정 실행 수를 비교합니다.
        printf("\nERROR: 존재하는 노드보다 제거 실행 수가 적습니다\n");
        printf("다시 입력해주세요\n");
        printf("\n제거할 node의 수를 입력해주세요: ");
        scanf("%d",&D);
    }
    
    for(int i=0;i<D;i++){ //제거를 합니다.
        printf("제거하고 싶은 수를 입력해주세요: ");
        scanf("%d",&input);
        delete(&head,&tail,input);
        print_node(&head,&tail);
    }
    
    printf("완료되었습니다.\n");
    return 0;
}
