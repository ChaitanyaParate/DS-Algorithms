#include <stdio.h>
#include <string.h>

#define SIZE 5

struct job
{
    int jobid;
    char name[50];
};

struct job j[SIZE];
int rear = -1;
int front = -1;
int id = 1;

int isempty()
{
    return front == -1;
}

int isfull()
{
    return (front == 0 && rear == SIZE - 1) || (rear == (front - 1) % (SIZE - 1));
}

void add_linear(struct job *j, char name[50])
{
    if (rear == SIZE - 1)
    {
        printf("Queue is full\n");
    }
    else
    {
        if (isempty())
        {
            front = 0;
        }
        rear++;
        strcpy(j[rear].name, name);
        j[rear].jobid = id++;
        printf("\nElement added: id = %d, name = %s\n", j[rear].jobid, j[rear].name);
    }
}

void processjob_linear()
{
    if (isempty())
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("\nDeleted item: id = %d, name = %s\n", j[front].jobid, j[front].name);
        front++;
        if (front > rear)
        {
            front = rear = -1;
        }
    }
}

void add_circular(struct job *j, char name[50])
{
    if (isfull())
    {
        printf("Queue is full\n");
    }
    else
    {
        if (isempty())
        {
            front = rear = 0;
        }
        else if (rear == SIZE - 1 && front != 0)
        {
            rear = 0;
        }
        else
        {
            rear++;
        }
        strcpy(j[rear].name, name);
        j[rear].jobid = id++;
        printf("\nElement added: id = %d, name = %s\n", j[rear].jobid, j[rear].name);
    }
}

void processjob_circular()
{
    if (isempty())
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("\nDeleted item: id = %d, name = %s\n", j[front].jobid, j[front].name);
        if (front == rear)
        {
            front = rear = -1;
        }
        else if (front == SIZE - 1)
        {
            front = 0;
        }
        else
        {
            front++;
        }
    }
}

void display(struct job *j)
{
    int i;
    if (isempty())
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("\nJobs in the queue:\n");
        if (rear >= front)
        {
            for (i = front; i <= rear; i++)
            {
                printf("id = %d || name = %s\n", j[i].jobid, j[i].name);
            }
        }
        else
        {
            for (i = front; i < SIZE; i++)
            {
                printf("id = %d || name = %s\n", j[i].jobid, j[i].name);
            }
            for (i = 0; i <= rear; i++)
            {
                printf("id = %d || name = %s\n", j[i].jobid, j[i].name);
            }
        }
    }
}

int main()
{
    int n;
    char name1[50];
    int cont = 1;
    int queue_type;

    printf("Select Queue Type:\n 1. Linear Queue\n 2. Circular Queue\n");
    scanf("%d", &queue_type);

    do
    {
        printf("\nEnter your choice:\n 1. Add Job\n 2. Delete Job\n 3. Display All Jobs\n 4. Exit\n");
        scanf("%d", &n);
        switch (n)
        {

        case 1:
            printf("Enter the job name: ");
            scanf("%s", name1);
            if (queue_type == 1)
            {
                add_linear(j, name1);
            }
            else if (queue_type == 2)
            {
                add_circular(j, name1);
            }
            break;

        case 2:
            if (queue_type == 1)
            {
                processjob_linear();
            }
            else if (queue_type == 2)
            {
                processjob_circular();
            }
            break;
        case 3:
            display(j);
            break;
        case 4:
            cont = 0;
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (cont == 1);
    return 0;
}
