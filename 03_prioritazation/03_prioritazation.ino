//use only 1 core for demo projects
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else 
  static const BaseType_t app_cpu = 1;
#endif

//Base string to print
const char msg[] = "Barkadeer brig Arr booty run.";

//Task handle
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

//**********************************************************************
//Task

//Task 1 - Print to serial terminal with lower priority
void StartTask1(void *parameter) {
  int msg_len = strlen(msg);

  //Print string to terminal
  while(1) {
    Serial.println();
    for(int i = 0; i < msg_len; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
//
////Task 2 - Print to serial terminal with higher priority
void StartTask2(void *parameter) {
  while(1) {
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // go slow(so that we can visualize the things)
  Serial.begin(300);

  //wait a moment so that we don't miss the serial output
  vTaskDelay(10000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("====Free RTOS Demo========");

  //print self priority
  Serial.print("setup and loop task running on the core ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.println(uxTaskPriorityGet(NULL));
  //vTaskDelay(1000 / portTICK_PERIOD_MS);
  
  //Task to run forever
  xTaskCreatePinnedToCore(StartTask1, "Task 1", 1024, NULL, 1, &task_1, app_cpu);
  xTaskCreatePinnedToCore(StartTask2, "Task 2", 1024, NULL, 2, &task_2, app_cpu);
  
}

void loop() {
  //Serial.println("check");
  //vTaskDelay(1000 / portTICK_PERIOD_MS);
    for(int i = 0; i < 3; i++) {
      vTaskSuspend(task_2);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
      vTaskResume(task_2);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

    if(task_1 != NULL) {
      vTaskDelete(task_1);
      task_1 = NULL;
    }
}
