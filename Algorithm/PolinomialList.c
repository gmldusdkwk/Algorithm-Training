#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


//연결 리스트 노드의 구조입니다. 다항식에는 계수와 지수가 있으므로 coef와 expon가 존재합니다.
typedef struct listNode {
    int coef;
    int expon;
    struct listNode *link;
} ListNode;

//연결 리스트의 헤더의 구조입니다.
typedef struct listHeader {
    int length;
    ListNode *head;
    ListNode *tail;
} ListHeader;


void init(ListHeader *plist)
{
    plist->length = 0; //리스트의 헤더를 생성합니다.
    plist->head = NULL;
    plist->tail = NULL;
}

void create(ListHeader *plist,int coef,int expon){
    ListNode * new = (ListNode *)malloc(sizeof(ListNode));
    new->coef = coef;
    new->expon = expon;
    new->link = NULL;
    
    plist->head = new;//새로운 노드를 생성합니다.
}

//맨 앞 노드에 삽입 함수
void add_first(ListHeader *plist, int coef, int expon){
    ListNode * new = (ListNode *)malloc(sizeof(ListNode)); //새로운 노드를 동적할당합니다.
    ListNode * temp = plist->head;
    
    new->coef = coef;
    new->expon = expon;
    
    while(temp != NULL){
        plist->tail = temp;
        temp = temp->link;
    } //tail을 연결해줍니다.

    new->link = plist->head;//새로운 노드와 헤더를 연결해줍니다.
    plist->head = new;//헤더의 포인터를 변경합니다.
}

//마지막 노드에 삽입 함수
void add_last(ListHeader *plist, int coef, int expon){
    ListNode * new=(ListNode *)malloc(sizeof(ListNode)); //새로운 노드를 동적할당합니다.
    new->coef = coef;//새로운 노드에 데이터를 저장합니다.
    new->expon = expon;
    new->link = NULL;//마지막 이므로 새로운 노드의 링크에 NULL을 저장합니다.
    
    if(plist->tail == NULL) { //tail이 NULL 일 경우 새로 만들 노드를 tail로 생성합니다.
        if(plist->head == NULL) {
            plist->head = new;
            plist->tail = new;
            return;
        }
        plist->head->link = new;
        plist->tail = new;
        return;
    }
    
    plist->tail->link = new;//tail 뒤에 새로운 노드를 연결합니다.
    plist->tail = new;//tail의 포인터를 변경해줍니다.
}

//중간 삽입 함수
void mid_insert(ListHeader *plist,int coef,int expon){
    ListNode * temp = plist->head;
    ListNode * new = (ListNode *)malloc(sizeof(ListNode));//새로운 노드를 동적할당합니다.
    
    while(temp != NULL){
        if(temp->expon > expon){//새로 넣으려고 하는 데이터가 현재 노드의 데이터보다 큰 상태에서
            if(temp->link->expon < expon){ //다음 노드의 데이터 보다 작은 상태라면 그 사이에 삽입해야 한다는 것을 알 수 있습니다.
                new->link = temp->link; //새로운 노드의 링크에 현재 노드 링크 값을 저장하고
                temp->link = new;//현재 노드의 링크 값에 새로운 노드의 주소값을 저장합니다.
                
                new->expon = expon;//그리고 새로운 노드에 데이터 값을 저장합니다.
                new->coef = coef;
                return;
            }
        }
        temp = temp->link;//찾지 못한다면 계속 찾을 때 까지 계속합니다.
        
    }
}

//노드를 만들면서 바로 연결을 하는 함수
void create_sort_node(ListHeader *plist, int coef, int expon)
{
    if(plist->head==NULL) create(plist,coef,expon);
    if((plist->head->expon) < expon) //head 앞으로 노드 생성할 경우
        add_first(plist,coef,expon);
    
    else if(plist->tail == NULL)//tail이 없는 경우
        add_last(plist,coef,expon);
    
    else if((plist->tail->expon) > expon)//tail 뒤로 만들 경우
        add_last(plist,coef,expon);
    
    else
        mid_insert(plist,coef,expon);//사이에 삽입할 경우
    
    plist->length++;
}

//다항식의 덧셈 실행 함수
void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3)
{
    ListNode * list1 = plist1->head;
    ListNode * list2 = plist2->head;
    
    int sum;
    
    while (list1 != NULL && list2 != NULL) {
        if (list1->expon == list2->expon) { //지수가 같은 경우에는 계수를 더한다.
            sum = list1->coef + list2->coef;
            if (sum != 0) add_last(plist3, sum, list1->expon);
            list1 = list1->link;
            list2 = list2->link;
        }
        else if (list1->expon > list2->expon) { //지수가 다른 경우에서 다항식 1의 지수가 크면 큰 것부터 기록한다.
            add_last(plist3, list1->coef, list1->expon);
            list1 = list1->link;
        }
        else {
            add_last(plist3, list2->coef, list2->expon);//지수가 다른 경우 다항식 2의 지수가 크면 다항식 2의 지수를 기록한다.
            list2 = list2->link;
        }
    }
    while(list1 != NULL){
        add_last(plist3, list1->coef, list1->expon); //마지막으로 남은 것을 저장한다.
        list1 = list1->link;
    }
    while(list2 != NULL){
        add_last(plist3, list2->coef, list2->expon);
        list2 = list2->link;
    }
}

//다항식 프린트 함수 각각의 계수와 지수 리스트 형식으로 출력하는 함수
void poly_print(ListHeader *plist)
{
    ListNode * temp = plist->head;
    while(temp!=NULL) {
        printf("계수:%3d, 지수:%3d\n", temp->coef,temp->expon);
        temp=temp->link;
        
    }
}

//다항식 형식으로 출력하는 함수
void print_poly(ListHeader *plist){
    ListNode *temp = plist->head;
    
    printf("%dX^%d",temp->coef,temp->expon);
    temp=temp->link;
    
    while(temp!=NULL){
        printf("+%dx^%d",temp->coef,temp->expon);
        temp=temp->link;
    }
    printf("\n");
}


int main()
{
    ListHeader list1, list2, list3;
    int a,b;
    int i=1;
    
    init(&list1);
    init(&list2);
    init(&list3);
    
    printf("다항식 1의 계수와 지수를 입력하세요(0:완료): \n");
    printf("계수 [%d]: ",i);
    scanf("%d",&a);
    printf("지수 [%d]: ",i++);
    scanf("%d",&b);
    create(&list1,a,b);
    while(1){
        printf("계수 [%d]: ",i);
        scanf("%d",&a);
        if(a==0) break;
        printf("지수 [%d]: ",i++);
        scanf("%d",&b);
        create_sort_node(&list1, a, b);
    }
    
    i=1;
    printf("다항식 2의 계수와 지수를 입력하세요(0:완료): \n");
    printf("계수 [%d]: ",i);
    scanf("%d",&a);
    printf("지수 [%d]: ",i++);
    scanf("%d",&b);
    create(&list2,a,b);
    while(1){
        printf("계수 [%d]: ",i);
        scanf("%d",&a);
        if(a==0) break;
        printf("지수 [%d]: ",i++);
        scanf("%d",&b);
        create_sort_node(&list2, a, b);
    }
    
    printf("----------------------------\n");
    printf("다항식 1:\n");
    poly_print(&list1);
    print_poly(&list1);
    printf("\n");
    printf("\n");
    
    printf("다항식 2:\n");
    poly_print(&list2);
    print_poly(&list2);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
    
    printf("다항식 1 + 다항식 2:\n");
    poly_add(&list1,&list2,&list3);
    poly_print(&list3);
    printf("\n");
    print_poly(&list3);
    
    
}

