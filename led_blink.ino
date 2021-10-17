//Use only 1 core for demo process
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Pins
static const int led_pin = LED_BUILTIN;

//Out task: blink and LED
void toggleLED(void* parameter)
{
  while(1) 
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  //Configure pin
  pinMode(led_pin, OUTPUT);

  //Task to run forever
  xTaskCreatePinnedToCore (
    toggleLED,    //Function to be called
    "Toogle LED", //Name of the task
    1024,         //Stack size in bytes
    NULL,         //Parameter to pass the function
    1,            //Task priority(0 to configMAX_PRIORITIES = 1)
    NULL,         //Task handle
    app_cpu);     //Number of core used      
}

void loop() {
  // put your main code here, to run repeatedly:

}
