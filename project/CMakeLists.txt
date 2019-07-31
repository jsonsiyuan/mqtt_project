PROJECT( mqtt_client )
CMAKE_MINIMUM_REQUIRED( VERSION 2.4.7 )
ADD_SUBDIRECTORY( net_transport )
ADD_SUBDIRECTORY( mqtt_src )
ADD_SUBDIRECTORY( mqtt_component )
ADD_SUBDIRECTORY( list_component )

INCLUDE_DIRECTORIES( net_transport )
INCLUDE_DIRECTORIES( mqtt_src )
INCLUDE_DIRECTORIES( mqtt_component )
INCLUDE_DIRECTORIES( list_component )

ADD_EXECUTABLE(mqtt_client
    main.c
)
TARGET_LINK_LIBRARIES( mqtt_client transport mqtt mqtt_component list_component)
target_compile_definitions(mqtt_client PRIVATE MQTTCLIENT_PLATFORM_HEADER=MQTTLinux.h)