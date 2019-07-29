ADD_LIBRARY( mqtt_component STATIC  MQTTClient.c MQTTLinux.c)
INCLUDE_DIRECTORIES( ../mqtt_src )
TARGET_LINK_LIBRARIES( mqtt_component mqtt )
target_compile_definitions(mqtt_component PRIVATE MQTTCLIENT_PLATFORM_HEADER=MQTTLinux.h)