#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Task
{
    public:
    float arrival_time;
    float burst_time;
    float completion_time;
    float turn_around;
    float waiting_time;
    Task()
    {
        cout<<"Enter the arrival time of the task:";
        cin>>arrival_time;
        cout<<"Enter the burst time of the task:";
        cin>>burst_time;

    }

};
void sort_by_arrival(Task*ptr,int n)
{
    int i=0,j=0;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(ptr[j].arrival_time>ptr[j+1].arrival_time)
            {
                Task temp = ptr[j];
                ptr[j] = ptr[j + 1];
                ptr[j + 1] = temp;
            }
        }
    }

}
void sort_by_burst(Task* ptr, int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - i - 1 + start; j++) {
            if (ptr[j].burst_time > ptr[j + 1].burst_time) {
                Task temp = ptr[j];
                ptr[j] = ptr[j + 1];
                ptr[j + 1] = temp;
            }
        }
    }
}
void calc_turnaround(Task*ptr,int n)
{
    int i=0;
    for(i=0;i<n;i++)
    {
        ptr[i].turn_around=ptr[i].completion_time-ptr[i].arrival_time;
    }
}
void calc_waiting(Task *ptr,int n)
{
    int i=0;
    for(i=0;i<n;i++)
    {
        ptr[i].waiting_time=ptr[i].turn_around-ptr[i].burst_time;
    }
}

void firstIn_firstOut(Task* ptr,int n)
{
    sort_by_arrival(ptr,n);
    float idle_time = 0.0;
    int current_time = 0,i=0;
    float throughput=0.0;
    float avg_waiting = 0.0;
    float avg_taround = 0.0;
    for(i=0;i<n;i++){
        if (ptr[i].arrival_time > current_time)
        {
            idle_time += ptr[i].arrival_time - current_time;
            current_time = ptr[i].arrival_time;
        }
        ptr[i].completion_time = current_time + ptr[i].burst_time;
        ptr[i].turn_around = ptr[i].completion_time - ptr[i].arrival_time;
        avg_taround += ptr[i].turn_around;
        ptr[i].waiting_time = ptr[i].turn_around - ptr[i].burst_time;
        avg_waiting += ptr[i].waiting_time;
        current_time = ptr[i].completion_time;
    }
    throughput=n/ptr[i-1].completion_time;
    avg_taround /= n;
    avg_waiting /= n;
    cout << "Throughput: " <<throughput<<endl;
    cout << "Total Idle Time: " << idle_time << endl;
    cout << "Average waiting time: " << avg_waiting<<endl;
    cout << "Average turnaround time: " << avg_taround<<endl;

}

void shortest_job_first(Task* ptr, int n)
 {
    sort_by_arrival(ptr, n);

    float idle_time = 0;
    int current_time = 0,i=0;
    float throughput=0.0;
    float avg_waiting = 0.0;
    float avg_taround = 0.0;
    for (i = 0; i < n;) {
        int j = i;
        while (j < n && ptr[j].arrival_time <= current_time)
        {
            j++;
        }
        sort_by_burst(ptr, i, j);
        if (ptr[i].arrival_time > current_time)
        {
            idle_time += ptr[i].arrival_time - current_time;
            current_time = ptr[i].arrival_time;
        }
        ptr[i].completion_time = current_time + ptr[i].burst_time;
        ptr[i].turn_around = ptr[i].completion_time - ptr[i].arrival_time;
        avg_taround += ptr[i].turn_around;
        ptr[i].waiting_time = ptr[i].turn_around - ptr[i].burst_time;
        avg_waiting += ptr[i].waiting_time;
        current_time = ptr[i].completion_time;
        i++;
    }
    throughput=n/ptr[i-1].completion_time;
    avg_taround /= n;
    avg_waiting /= n;
    cout << "Throughput: " <<throughput<<endl;
    cout << "Total Idle Time: " << idle_time << endl;
    cout << "Average waiting time: " << avg_waiting<<endl;
    cout << "Average turnaround time: " << avg_taround<<endl;
}

void print_table(Task* ptr, int n) {
    cout << "\nArrival\t Burst\tCompletion\tTurnaround\tWaiting time\n";
    cout << "----------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout <<" " << ptr[i].arrival_time << "\t       " << ptr[i].burst_time << "\t\t\t" << ptr[i].completion_time << "\t\t\t"
             << ptr[i].turn_around << "\t\t    " << ptr[i].waiting_time << "\n";
    }
}

typedef struct details
{
    public:
        int sno;
        int temp;
        int arrival_time;
        int burst_time;
        int turnaround_time;
        int completion_time;
        int waiting_time;
        bool complete;
}details;

void getinfo(int n,details d[])
{
    int i=0;
    for(i=0;i<n;i++)
    {
        d[i].sno=i;
        cout<<"\n";
        cout<<"Enter the arrival time and burst time:";
        getchar();
        cin>>d[i].arrival_time>>d[i].burst_time;
        d[i].turnaround_time=0;
        d[i].completion_time=0;
        d[i].temp=0;
        d[i].waiting_time=0;
        d[i].complete=0;
    }
    cout<<"\n";

}

void roundrobin(int n,details d[])
{
    int ptime=0;int order=0;int i;int t;
    cout<<"\nEnter the quantum time:";
    cin>>t;
    cout<<"\n";

    for(i=0;i<n;i++)
    {
        d[i].temp=d[i].burst_time;
       // cout<<d[i].temp;
    }
    while(order<n)
    {
        for(i=0;i<n;i++)
        {

            if((d[i].arrival_time<=ptime)&&(d[i].complete==0))
            {
                if(d[i].temp<=t)
                {
                    ptime+=d[i].temp;
                    d[i].completion_time=ptime;
                    d[i].turnaround_time=d[i].completion_time-d[i].arrival_time;
                    d[i].waiting_time=d[i].turnaround_time-d[i].burst_time;
                    d[i].temp=0;
                    order++;
                    d[i].complete=1;

                }

                else
                {

                    d[i].temp-=t;
                    //ptime++;
                    ptime+=t;
                }
            }
            else
            {
                ptime++;
            }
        }
    }
}

void display(int n,details d[])
{
    int i=0;
    cout<<"\n";
    cout<<"Sno"<<"\t\t"<<"Arrival time"<<"\t\t"<<"burst time"<<"\t\t"<<"completion Time"<<"\t\t"<<"TurnAround time"<<"\t\t"<<"Waiting time";
    cout<<"\n";
    for(i=0;i<n;i++)
    {
        cout<<"\n";
        cout<<d[i].sno<<"\t\t\t"<<d[i].arrival_time<<"\t\t\t"<<d[i].burst_time<<"\t\t\t"<<d[i].completion_time<<"\t\t\t"<<d[i].turnaround_time<<"\t\t\t"<<d[i].waiting_time;
        cout<<"\n";
    }
}


void displayavg(int n,details d[])
{
    double avg_turnaround_time=0,avg_waiting_time=0,throughput=0; int total_time=0;
    int i=0;
    for(i=0;i<n;i++)
    {
        avg_turnaround_time+=d[i].turnaround_time;
    }
    avg_turnaround_time=avg_turnaround_time/n;

    for(i=0;i<n;i++)
    {
        avg_waiting_time+=d[i].waiting_time;
    }
    avg_waiting_time=avg_waiting_time/n;

    for(i=0;i<n;i++)
    {
        total_time+=d[i].burst_time;
    }

    throughput=n/total_time;

    cout<<"\n";
    cout<<"turnar:"<<avg_turnaround_time;
    cout<<"\nwait:"<<avg_waiting_time;
    cout<<"\nThroughput:"<<throughput;

}



int main() {
    int n,i=0;
    float sum=0;
    float waiting_sjf=0,throughput_sjf=0,taround_sjf=0;
    cout<<"Enter number of tasks: ";
    cin>>n;
    Task*ptr=new Task[n];

    cout<<"\nFirst In First Out\n"<<endl;
    firstIn_firstOut(ptr,n);
    print_table(ptr,n);

    cout<<"\nShortest Job First\n"<<endl;
    shortest_job_first(ptr, n);
    print_table(ptr,n);

	details d[n];
	getinfo(n,d);
	display(n,d);
	roundrobin(n,d);
	display(n,d);
    displayavg(n,d);
    system("C:\\Users\\Lenovo\\Desktop\\codeblocks\\Hackathon12\\pyhtonlink.py");
	return 0;

}