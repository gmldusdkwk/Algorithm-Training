#include <iostream>
#include <stdio.h>

using namespace std;

int width [1001];
int input;
int output;

int check(int index){
    int center = width[index + 2];
    int center_index = index + 2;
    int compare = 256;
    for(int i = index; i < index + 5; i++){
        if(i == center_index) continue;
        if(center - width[i] < 0 )
            return 0;
    }
    for(int i = index; i < index + 5; i++){
        if(i == center_index) continue;
        if(compare > center - width[i])
            compare = center - width[i];
    }
    return compare;
}

int main(void){
    int tc = 10;
    for(int j = 0; j < tc; j++){
        scanf("%d", &input);
    
        for (int i = 0; i < input; i++){
            scanf("%d", &width[i]);
        }
        
        for (int i = 0; i <=input - 5; i++){
            output += check(i);
        }
        printf("#%d %d\n", j + 1, output);
        output = 0;
    }
    return 0;
}
