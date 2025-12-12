#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint32_t currentTaskID = 0;

#define NO_TASK_ID 0

static uint32_t Get_New_Task_ID(void){
    currentTaskID++;
    if (currentTaskID == 0) currentTaskID++;
    return currentTaskID;
}

void SCH_Init(void){
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }
    currentTaskID = 0;
}

uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
    uint32_t sumDelay = 0;
    uint32_t newDelay;
    uint8_t index;
    uint32_t taskID;

    for (index = 0; index < SCH_MAX_TASKS; index++) {

        sumDelay += SCH_tasks_G[index].Delay;

        // Insert into middle
        if (sumDelay > DELAY) {

            newDelay = DELAY - (sumDelay - SCH_tasks_G[index].Delay);
            SCH_tasks_G[index].Delay = sumDelay - DELAY;

            // Shift down
            for (int i = SCH_MAX_TASKS - 1; i > index; i--) {
                SCH_tasks_G[i] = SCH_tasks_G[i - 1];
            }

            SCH_tasks_G[index].pTask = pFunction;
            SCH_tasks_G[index].Delay = newDelay;
            SCH_tasks_G[index].Period = PERIOD;
            SCH_tasks_G[index].RunMe = (newDelay == 0);

            taskID = Get_New_Task_ID();
            SCH_tasks_G[index].TaskID = taskID;

            return taskID;
        }

        // Empty slot → Put here
        if (SCH_tasks_G[index].pTask == 0) {

            SCH_tasks_G[index].pTask = pFunction;
            SCH_tasks_G[index].Delay = DELAY - sumDelay;
            SCH_tasks_G[index].Period = PERIOD;
            SCH_tasks_G[index].RunMe = (SCH_tasks_G[index].Delay == 0);

            taskID = Get_New_Task_ID();
            SCH_tasks_G[index].TaskID = taskID;

            return taskID;
        }
    }

    return 0; // no space
}

uint8_t SCH_Delete_Task(const uint32_t taskID){
    if (taskID == 0) return 0;

    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].TaskID == taskID) {

            if (i < SCH_MAX_TASKS - 1 && SCH_tasks_G[i + 1].pTask != 0) {
                SCH_tasks_G[i + 1].Delay += SCH_tasks_G[i].Delay;
            }

            // Shift up
            for (uint8_t j = i; j < SCH_MAX_TASKS - 1; j++) {
                SCH_tasks_G[j] = SCH_tasks_G[j + 1];
            }

            // Clear last
            uint8_t last = SCH_MAX_TASKS - 1;
            SCH_tasks_G[last].pTask = 0;
            SCH_tasks_G[last].Delay = 0;
            SCH_tasks_G[last].Period = 0;
            SCH_tasks_G[last].RunMe = 0;
            SCH_tasks_G[last].TaskID = 0;

            return 1;
        }
    }

    return 0;
}

void SCH_Update(void){
    if (SCH_tasks_G[0].pTask != 0 && SCH_tasks_G[0].RunMe == 0) {
        if (SCH_tasks_G[0].Delay > 0)
            SCH_tasks_G[0].Delay--;

        if (SCH_tasks_G[0].Delay == 0)
            SCH_tasks_G[0].RunMe = 1;
    }
}

void SCH_Dispatch_Tasks(void){
    if (SCH_tasks_G[0].RunMe > 0 && SCH_tasks_G[0].pTask != 0) {

        sTasks tmp = SCH_tasks_G[0];

        tmp.pTask();  // Run task
        SCH_tasks_G[0].RunMe--;

        SCH_Delete_Task(tmp.TaskID);

        if (tmp.Period != 0) {
            SCH_Add_Task(tmp.pTask, tmp.Period, tmp.Period); // không dùng existingID
        }
    }
}
