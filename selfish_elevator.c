#include <stdio.h>
#include <limits.h>
#include <math.h>

#define NFLOORS 110 // 빌딩 총 층 갯수
#define MAX_RIDERS 50 // 엘베가 태울 수 있는 사람 수 

int stop[MAX_RIDERS]; // 몇번쨰 사람은 몇 번째 층에서 내리나요..?
int nriders; // 현재 엘베에 몇 명이 있나요
int nstops; // 몇 개 층만 선택할 수 있나요..?

int m[NFLOORS+1][MAX_RIDERS]; // cost 저장 => m(ij)
int p[NFLOORS+1][MAX_RIDERS]; // 부모 테이블을 저장한다 => 내가 i일때 k인 친구
int result[MAX_RIDERS]; // reconstruct path에서 laststop들을 저장하는 곳.
int cnt; // 현재 result에 몇 개가 저장이 되어있나.

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

int floors_walked(int previous, int current){
    
    int nsteps=0;
    int i;
    
    for (i=1; i<=nriders; i++){
        if((stop[i]>previous)&&(stop[i]<=current)){

            if (previous==0 && current!=INT_MAX){ // 0-3인데 1이 stop이면 1이아니라 2가 더해져야함.
                nsteps+=(current-stop[i]);
                continue; 
            }
            nsteps += min(stop[i]-previous, current-stop[i]); 
        }
    }
    
    
    return nsteps;
}

int optimize_floors(){
    
    int i, j, k;
    int cost;
    int laststop;
    
    for (i=0; i<=NFLOORS; i++){
        m[i][0] = floors_walked(0,INT_MAX);
        p[i][0] = -1;
    }
    
    for (j=1; j<=nstops; j++){
        for (i=0; i<=NFLOORS; i++){
            m[i][j] = INT_MAX;
            for(k=0; k<=i; k++){
                cost = m[k][j-1]-floors_walked(k,INT_MAX)+
                    floors_walked(k,i)+floors_walked(i,INT_MAX);
                if (cost<=m[i][j]){
                    
                    m[i][j]=cost;
                    p[i][j]=k;
                }
            }
        }
    }
    
    laststop=0;
    for (i=1; i<=NFLOORS; i++){
        if (m[i][nstops]<=m[laststop][nstops]){
            laststop=i;
            
        }
    }
    return laststop;
}

void reconstruct_path(int lastfloor, int stops_to_go)
{
    if(stops_to_go>1){
        reconstruct_path(p[lastfloor][stops_to_go], stops_to_go-1);
    }
    result[cnt]=lastfloor;
    cnt++;
}

int main()
{
    
    scanf("%d", &nriders);
    scanf("%d", &nstops);
    
    for (int i=1; i<=nriders; i++){
        scanf("%d", &stop[i]);
    }
    //printf("walk: %d\n",floors_walked(0,INT_MAX));

    reconstruct_path(optimize_floors(), nstops);
    
    for (int i=1; i<=nriders; i++){
        int closest = result[0];
        int minDiff = abs(stop[i]-result[0]);

        for (int j = 1; j <nstops; j++) {
            int diff = abs(stop[i] - result[j]);
            if (diff < minDiff) {
                minDiff = diff;
                closest = result[j];
            }
        }
        
        printf("%d\n", closest);  // 짝지어진 수 출력
    }
    



    return 0;
}
