idf_component_register(
  SRCS 
    "routes/pushBtn.c"
    "routes/toggleLed.c"
    "routes/helloWorld.c"
    "routes/magnetometer.c"
    "routes/servo.c"
    "main.c"
  INCLUDE_DIRS 
    "."
    "routes"
  )

spiffs_create_partition_image(spiffs ../site/dist FLASH_IN_PROJECT)                    