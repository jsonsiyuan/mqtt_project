PROJECT( mqtt_client )
CMAKE_MINIMUM_REQUIRED( VERSION 2.4.7 )
ADD_SUBDIRECTORY( net_transport )
ADD_SUBDIRECTORY( mqtt_src )

INCLUDE_DIRECTORIES( net_transport )
INCLUDE_DIRECTORIES( mqtt_src )


ADD_EXECUTABLE(mqtt_client
    main.c
)
TARGET_LINK_LIBRARIES( mqtt_client transport mqtt)