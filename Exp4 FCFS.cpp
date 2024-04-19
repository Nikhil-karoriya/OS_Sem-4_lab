#include<bits/stdc++.h>

class PCB{
public:
    int pid, arrival, burst, turnaround;
};

void pline(int);

int main(){
    int i, n, j;
    float avg = 0.0, sum = 0.0;
    class PCB p[10], temp;
    printf("Enter the total number of processes: ");
    scanf("%d",&n);
    for( i = 0; i<n; i++){
        printf("Enter Arrival Time and Burst Time for process id %d :\n", i+1);
        scanf("%d %d",&p[i].arrival, &p[i].burst);
        p[i].pid = i+1;
    }
    for( i = 0; i<n-1; i++){
        for( j = 0; j<n-i-1; j++){
            if(p[j].arrival > p[j+1].arrival){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    for( i = 0; i<n; i++){
        sum = sum + p[i].burst;
        p[i].turnaround = sum;
    }
    sum = 0;
    pline(44);
    printf("PID\tArrival\tBurst\tTurnaround\n");
    pline(44);
    for( i = 0; i<n; i++){
        printf("%d\t%d\t%d\t%d\n",p[i].pid, p[i].arrival, p[i].burst, p[i].turnaround);
        sum+=p[i].turnaround;
    }
    pline(44);
    avg = sum/(float)(n);
    printf("Total Turnaround Time: %f", sum);
    printf("Average Turnaround Time : %.3f", avg);
    return 0;
}

void pline(int n){
    for(int i = 0; i<=n; i++){
        printf("-");
    }
    printf("\n");
}