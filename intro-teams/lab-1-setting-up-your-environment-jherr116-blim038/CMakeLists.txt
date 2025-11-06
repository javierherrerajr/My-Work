CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_EXECUTABLE(area_calculator
	src/main1.cpp
	src/rectangle.cpp
)

ADD_EXECUTABLE(bigger_area_calculator
    src/new_main.cpp
    src/rectangle.cpp
)
ADD_EXECUTABLE(shape_area_calculator
    src/shape_main.cpp
    src/rectangle.cpp
    src/triangle.cpp
)