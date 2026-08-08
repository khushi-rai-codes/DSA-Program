#include <stdio.h>
struct Activity {
    int start;
    int finish;
};
void sortActivities(struct Activity activities[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (activities[j].finish > activities[j + 1].finish)
            {
                struct Activity temp = activities[j];
                activities[j] = activities[j + 1];
                activities[j + 1] = temp;
            }
        }
    }
}
void activitySelection(struct Activity activities[], int n)
{
    sortActivities(activities, n);
    int lastFinish = -1;
    printf("Selected Activities:\n");
    for (int i = 0; i < n; i++)
    {
        if (activities[i].start >= lastFinish)
        {
            printf("Activity: Start = %d, Finish = %d\n",
                   activities[i].start,
                   activities[i].finish);

            lastFinish = activities[i].finish;
        }
    }
}
int main()
{
    struct Activity activities[] = {
        {1, 2},
        {3, 4},
        {0, 6},
        {5, 7},
        {8, 9},
        {5, 9}
    };
    int n = sizeof(activities) / sizeof(activities[0]);
    activitySelection(activities, n);
    return 0;
}
