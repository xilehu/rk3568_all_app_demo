# rk3568开发板的应用demo

## 1. 准备工作

### 1.1 下载demo源码

```shell
git@github.com:xilehu/rk3568_all_app_demo.git
```
### 1.2 目录介绍

```shell
如下是rk3568_all_app_demo目录结构
├── camera_app_demo :   mipi相机应用demo
├── lcd_app_demo :      fb和drm是显示应用demo
├── 
├── 
└── 
```
### 1.3 编译
```shell
./build_all_demo.sh  #编译所有demo 
./build_all_demo.sh clean  #清理所有demo
```

## 2. mipi相机应用demo

## 3. drm显示应用demo
### 3.1 准备工作

```shell
#libdrm下载网址：https://dri.freedesktop.org/libdrm/
#本机ubuntu18.04，选取的是libdrm-2.4.100版本
#下载libdrm-2.4.100.tar.gz
#解压
#tar -zxvf libdrm-2.4.100.tar.gz
#进入libdrm-2.4.100目录
#./configure --host=aarch64-linux-gnu --prefix=/home/rock/rockchip/rk3568/libdrm/bin
#make
#make install

#把/home/rock/rockchip/rk3568/libdrm/bin目录下的lib下的.so拷贝到设备/usr/lib下即可
#参考：https://blog.csdn.net/M120674/article/details/120081352
```
