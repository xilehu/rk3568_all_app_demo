// #include <stdio.h>
// #include <stdlib.h>
// #include <linux/fb.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <sys/ioctl.h>
// #include <unistd.h>
// #include <sys/mman.h>
// #include <string.h>

// #define SCREEN_WIDTH 800
// #define SCREEN_HEIGHT 600
// #define BYTES_PER_PIXEL 4 // 32-bit color (RGBA)


// int main(int argc, char const *argv[])
// {
//     struct fb_fix_screeninfo fixed_info;
//     struct fb_var_screeninfo var_info;

//     int fd;

//     char *fbp = NULL; //framerbuffer 内存的指针

//     fd = open("/dev/fb0", O_RDWR);
//     if (fd < 0) {
//         perror("open fb0");
//         exit(1);
//     }
//     //获取FrameBuffer 设备固定的信息
//     if(ioctl(fd,FBIOGET_FSCREENINFO,&fixed_info)<0) {
//         perror("ioctl FBIOGET_FSCREENINFO");
//         exit(1);
//     }
//     //获取FrameBuffer 设备可变的信息
//     if(ioctl(fd,FBIOGET_VSCREENINFO,&var_info)<0) {
//         perror("ioctl FBIOGET_VSCREENINFO");
//         exit(1);
//     }
//     printf("固定信息：\n");
//     printf("帧缓冲内存起始地址： %lu\n", fixed_info.smem_start);
//     printf("帧缓冲内存长度：%d\n",fixed_info.smem_len);
//     printf("行长度：%d\n",fixed_info.line_length);
//     printf("帧缓冲颜色格式：%u\n",fixed_info.visual);
//     printf("水平方向移动一个像素的字节数： %u\n", fixed_info.xpanstep);
//     printf("垂直方向移动一个像素的字节数： %u\n", fixed_info.ypanstep);
//     printf("垂直方向回卷一个像素的字节数： %u\n", fixed_info.ywrapstep);
//     printf("一行像素占用的字节数： %u\n", fixed_info.line_length);
//     printf("内存映射 I/O 起始地址： %lu\n", fixed_info.mmio_start);

//     printf("\n 可变信息： \n");
//     printf("x 分辨率： %u\n", var_info.xres);
//     printf("y 分辨率： %u\n", var_info.yres);
//     printf("每个像素的位数： %u\n", var_info.bits_per_pixel);

//     // fbp = (char *)mmap(0,fixed_info.smem_len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
//     fbp = (char*)mmap(0, fixed_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//     printf("%x\n",fbp);
//     if((int)fbp == -1) {
//         perror("Error: 映射 framebuffer 设备到内存时出错");
//         exit(1);
//     }
    
//     // 计算线条的像素位置和颜色值
//     int x = atoi(argv[1]);
//     int y = atoi(argv[2]);
//     int length = atoi(argv[3]);
//     unsigned int color = 0xFFFF0000; // 红色 (格式： ARGB)

//     memset(fbp, 0, fixed_info.smem_len);

//     // 绘制线条
//     for (int i = 0; i < length; i++)
//     {
//         int location = (x + i) * BYTES_PER_PIXEL + (y * SCREEN_WIDTH * BYTES_PER_PIXEL);
//         *((unsigned int*)(fbp + location)) = color;
//     }

//     // 刷新 framebuffer 以显示绘制的线条
//     struct fb_var_screeninfo new_vinfo;
//     new_vinfo.activate = FB_ACTIVATE_VBL;
//     ioctl(fd, FBIOPUT_VSCREENINFO, &new_vinfo);


//     // 从用户空间中取消映射 framebuffer 设备内存
//     if (munmap(fbp, fixed_info.smem_len) == -1)
//     {
//         perror("Error: 从内存中取消映射 framebuffer 设备时发生错误");
//         exit(6);
//     }

//     close(fd);
//     printf("hello world\n");
//     return 0;
// }


#include <stdio.h>
#include <sys/types.h>		//open需要的头文件
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	        //write
#include <sys/types.h>
#include <sys/mman.h>		//mmap  内存映射相关函数库
#include <stdlib.h>	        //malloc free 动态内存申请和释放函数头文件
#include <string.h> 	
#include <linux/fb.h>
#include <sys/ioctl.h>

//32位的颜色
#define Black 	0x00000000
#define White 	0xffFFFFFF
#define Red 	0xffFF0000
#define Green 	0xff00ff00
#define Blue 	0xff99ffff

int fd;
unsigned int *fb_mem  = NULL;	//设置显存的位数为32位
struct fb_var_screeninfo var;
struct fb_fix_screeninfo fix;

int main(void)
{
	unsigned int i;
	int ret;

	/*--------------第一步--------------*/
	fd = open("/dev/fb0",O_RDWR);			//打开framebuffer设备
	if(fd == -1){
		perror("Open LCD");
		return -1;
	}
	/*--------------第二步--------------*/
 
 	//获取屏幕的可变参数
	ioctl(fd, FBIOGET_VSCREENINFO, &var);
	//获取屏幕的固定参数
	ioctl(fd, FBIOGET_FSCREENINFO, &fix);
   
  	//打印分辨率
	printf("xres= %d,yres= %d \n",var.xres,var.yres);
 	//打印总字节数和每行的长度
	printf("line_length=%d,smem_len= %d \n",fix.line_length,fix.smem_len);
	printf("xpanstep=%d,ypanstep= %d \n",fix.xpanstep,fix.ypanstep);
 
	/*--------------第三步--------------*/
	
  fb_mem = (unsigned int *)mmap(NULL, var.xres*var.yres*4, 		//获取显存，映射内存
			PROT_READ |  PROT_WRITE, MAP_SHARED, fd, 0);   
								  
	if(fb_mem == MAP_FAILED){
		perror("Mmap LCD");
		return -1;	
	}

	memset(fb_mem,0xff,var.xres*var.yres*4);		//清屏
	sleep(1);
	/*--------------第四步--------------*/
	//将屏幕全部设置成蓝色
	for(i=0;i< var.xres*var.yres ;i++)
		fb_mem[i] = Blue;
	sleep(2);
	memset(fb_mem,0x00,var.xres*var.yres*4);		//清屏
	
	munmap(fb_mem,var.xres*var.yres*4); //映射后的地址，通过mmap返回的值	
	close(fd); 			//关闭fb0设备文件
	return 0;			
}