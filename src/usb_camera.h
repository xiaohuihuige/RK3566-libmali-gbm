#ifndef __USB_CAMERA_H__
#define __USB_CAMERA_H__

#include <fcntl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include "egl_context.h"

#define VIDEO_FORMAT V4L2_PIX_FMT_MJPEG //V4L2_PIX_FMT_YUYV
#define BUFFER_COUNT 4

//使用的摄像头必须要支持MJPEG
//SUPPORT 1.Motion-JPEG
//SUPPORT 2.YUYV 4:2:2

typedef struct 
{
  unsigned char *start;
  int length;
} FrameBuf;

typedef struct {
   int fd;
   FrameBuf mmap_buffer[BUFFER_COUNT];//图像数据虚拟地址
   struct v4l2_buffer buf;//图像数据
} usb_camera;

usb_camera *create_usb_camera(const char *dev_name, int width, int height);
void release_video(usb_camera *usb_dev);
int get_data(usb_camera *usb_dev, FrameBuf *frame_buf);

#endif