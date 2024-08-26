cmake_minimum_required(VERSION  3.10)

project(rk3568_all_app_demo)


#libdrm头文件路径
include_directories(
    ${CMAKE_SOURCE_DIR}/third_package/libdrm-2.4.100/bin/include
    ${CMAKE_SOURCE_DIR}/third_package/libdrm-2.4.100/bin/include/libdrm/)
#libdrm库文件路径
set (LIBDRM "${CMAKE_SOURCE_DIR}/third_package/libdrm-2.4.100/bin/lib/libdrm.so")


# 设置C和C++编译器  
set(CMAKE_C_COMPILER   
    /home/book/workspace/rk3568_work/rk3568_linux_kernel/rk356x_linux/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc)



#设置输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


#lcd_fb_app
add_executable(lcd_fb_app lcd_app_demo/lcd_fb_app.c)
#lcd_drm_app
add_executable(lcd_drm_app lcd_app_demo/lcd_drm_app.c)
target_link_libraries(lcd_drm_app ${LIBDRM})











