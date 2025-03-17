
import matplotlib.pyplot as plt

a=float(input("Enter the turnaround time for FCFS:"))
b=float(input("Enter the turnaround time for SJF:"))
c=float(input("Enter the turnaround time for Round-Robin:"))

d=float(input("Enter the throughput for FCFS:"))
e=float(input("Enter the throughput for SJF:"))
f=float(input("Enter the throughput for Round-Robin:"))


g=float(input("Enter the throughput for FCFS:"))
h=float(input("Enter the throughput for SJF:"))
i=float(input("Enter the throughput for Round-Robin:"))



labels = ['FCFS', 'SJF', 'ROUND_ROBIN']
sizes1 = [a, b, c]
sizes2=[d,e,f]
sizes3=[g,h,i]

fig,axes=plt.subplots(1,3)

# Colors 
colors = ['#ff9999','#66b3ff','#99ff99']

# Create pie chart
axes[0].pie(sizes1, labels=labels, colors=colors,  autopct='%1.1f%%', startangle=140)
axes[0].set_title('Turaround Time')

axes[1].pie(sizes2, labels=labels, colors=colors,  autopct='%1.1f%%', startangle=140)
axes[1].set_title('Throughput')

axes[2].pie(sizes3, labels=labels, colors=colors,  autopct='%1.1f%%', startangle=140)
axes[2].set_title('Waiting time')


# Equal aspect ratio ensures that pie is drawn as a circle.
plt.axis('equal')

# Show the plot
plt.show()

