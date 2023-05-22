cmake_minimum_required(VERSION 3.10)

set(SYSTEM_PARTITION
        #${INCLUDES_DIR}/System/System.h
        ${INCLUDES_DIR}/System/ErrorCode.h
        #${INCLUDES_DIR}/System/TypeTraits.hpp
        )

set(COLOR_PARTITION
        ${INCLUDES_DIR}/Color/Interface/IColor.h
        ${INCLUDES_DIR}/Color/RGB.h
        RGB.cpp
        )

set(MATH_PARTITION
        #${INCLUDES_DIR}/Math/Vec.hpp
        #${INCLUDES_DIR}/Math/Algorithms.hpp
        )

set(CANVAS_PARTITION
        ${INCLUDES_DIR}/Canvas.hpp
        )

add_executable(${PROJECT_NAME}
        main.cpp
        ${SYSTEM_PARTITION}
        ${COLOR_PARTITION}
        ${MATH_PARTITION}
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC ${INCLUDES_DIR}
        )