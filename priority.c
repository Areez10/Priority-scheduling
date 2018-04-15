//preemptive
#include<stdio.h>

struct process
{
  char pname;
  int atime, btime, ctime, wtime, tatime, priority;
  int status;
}pqueue[10];

int limit;

void atime_Sorting()
{
  struct process temp;
  int i, j;
  for(i = 0; i < limit - 1; i++)
  {
        for(j = i + 1; j < limit; j++)
        {
              if(pqueue[i].atime > pqueue[j].atime)
              {
                    temp = pqueue[i];
                    pqueue[i] = pqueue[j];
                    pqueue[j] = temp;
              }
        }
  }
}

void main()
{
  int i, time=0, btime=0, max;
  char c;
  float wtime = 0, tatime = 0, avg_wtime, avg_tatime;
  printf("\nTotal Number of Processes:\t");
  scanf("%d", &limit);
  for(i = 0, c = 'A'; i < limit; i++, c++)
  {
        pqueue[i].pname = c;
        printf("\nDetails For Process[%C]:\n", pqueue[i].pname);
        printf("Arrival Time:\t");
        scanf("%d", &pqueue[i].atime );
        printf("Burst Time:\t");
        scanf("%d", &pqueue[i].btime);
        printf("Priority:\t");
        scanf("%d", &pqueue[i].priority);
        pqueue[i].status = 0;
        btime = btime + pqueue[i].btime;
  }
  atime_Sorting();
  pqueue[9].priority = -9999;
  printf("\nProcess Name	Arrival Time	Burst Time	Priority   Waiting Time");
  for(time = pqueue[0].atime; time < btime;)
  {
        max = 9;
        for(i = 0; i < limit; i++)
        {
              if(pqueue[i].atime <= time && pqueue[i].status != 1 && pqueue[i].priority > pqueue[max].priority)
              {
                    max = i;
              }
        }
        time = time + pqueue[max].btime;
        pqueue[max].ctime = time;
        pqueue[max].wtime = pqueue[max].ctime - pqueue[max].atime - pqueue[max].btime;
        pqueue[max].tatime = pqueue[max].ctime - pqueue[max].atime;
        pqueue[max].status = 1;
        wtime = wtime + pqueue[max].wtime;
        tatime = tatime + pqueue[max].tatime;
        printf("\n %c		%d		%d		%d		%d", pqueue[max].pname, pqueue[max].atime, pqueue[max].btime, pqueue[max].priority, pqueue[max].wtime);
  }
  avg_wtime = wtime / limit;
  avg_tatime = tatime / limit;
  printf("\n\nAverage waiting time:     %f\n", avg_wtime);
  printf("Average Turnaround Time:     %f\n", avg_tatime);
}
