#include "usb_camera.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

usb_camera *create_usb_camera(const char *dev_name, int width, int height)
{
    usb_camera *usb_dev = (usb_camera *)malloc(sizeof(usb_camera));
    if (!usb_dev) {
        return NULL;
    }

    // Open Device
    usb_dev->fd = open(dev_name, O_RDWR, 0);
    if (usb_dev->fd < 0) {
        printf("Open %s failed!!!\n", dev_name);
        return NULL;
    }

    // Query Capability
    struct v4l2_capability cap;
    if (ioctl(usb_dev->fd, VIDIOC_QUERYCAP, &cap) < 0) {
        printf("VIDIOC_QUERYCAP failed\n");
        return NULL;
    }

    // Set Stream Format
    struct v4l2_fmtdesc fmtdesc;
    fmtdesc.index=0;
    fmtdesc.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    printf("Support format: \n");
    while(ioctl(usb_dev->fd, VIDIOC_ENUM_FMT, &fmtdesc) < 0)
    {
        printf("SUPPORT %d. %s\n", fmtdesc.index+1, fmtdesc.description);
        fmtdesc.index++;
    }

    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = VIDEO_FORMAT;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    if (ioctl(usb_dev->fd, VIDIOC_S_FMT, &fmt) < 0)
    {
        printf("VIDIOC_S_FMT failed \n");
        return NULL;
    }

    // Get Stream Format
    if (ioctl(usb_dev->fd, VIDIOC_G_FMT, &fmt) < 0) {
        printf("VIDIOC_G_FMT failed \n");
        return NULL;
    }

    struct v4l2_streamparm param;
    memset(&param,0,sizeof(param));
    param.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    param.parm.capture.timeperframe.numerator=1;
    param.parm.capture.timeperframe.denominator=30;
    param.parm.capture.capturemode = 1;
    if (ioctl(usb_dev->fd, VIDIOC_S_PARM, &param) < 0)
    {
        printf("VIDIOC_S_PARAM failed\n");
        return NULL;
    }

    if (ioctl(usb_dev->fd, VIDIOC_G_PARM, &param) < 0)  {
        printf("VIDIOC_G_PARAM failed \n");
        return NULL;
    }

    // Print Stream Format
    printf("Stream Format Informations: \n");
    printf(" type: %d\n", fmt.type);
    printf(" width: %d\n", fmt.fmt.pix.width);
    printf(" height: %d\n", fmt.fmt.pix.height);

    char fmtstr[8];
    memset(fmtstr, 0, 8);
    memcpy(fmtstr, &fmt.fmt.pix.pixelformat, 4);
    printf(" pixelformat: %s\n", fmtstr);
    printf(" field: %d\n", fmt.fmt.pix.field);
    printf(" bytesperline: %d\n", fmt.fmt.pix.bytesperline);
    printf(" sizeimage: %d\n", fmt.fmt.pix.sizeimage);
    printf(" colorspace: %d\n", fmt.fmt.pix.colorspace);
    //printf(" priv: %d", fmt.fmt.pix.priv);
    //printf(" raw_date: %s", fmt.fmt.raw_data);

    // Request buffers
    struct v4l2_requestbuffers reqbuf;
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory = V4L2_MEMORY_MMAP;
    reqbuf.count = BUFFER_COUNT;
    if (ioctl(usb_dev->fd , VIDIOC_REQBUFS, &reqbuf) < 0) {
        printf("VIDIOC_REQBUFS failed \n");
        return NULL;
    }

    // Queen buffers
    for(int i = 0; i < BUFFER_COUNT; i++)
    {
        // Query buffer
        usb_dev->buf.index = i;
        usb_dev->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        usb_dev->buf.memory = V4L2_MEMORY_MMAP;
        if (ioctl(usb_dev->fd , VIDIOC_QUERYBUF, &usb_dev->buf) < 0) {
            printf("VIDIOC_QUERYBUF (%d) failed\n", i);
            return NULL;
        }

        // mmap buffer
        usb_dev->mmap_buffer[i].length= usb_dev->buf.length;
        usb_dev->mmap_buffer[i].start = (unsigned char *)mmap(0, usb_dev->buf.length, 
            PROT_READ|PROT_WRITE, MAP_SHARED, usb_dev->fd, usb_dev->buf.m.offset);
        if (usb_dev->mmap_buffer[i].start == MAP_FAILED) {
            printf("mmap (%d) failed: %s \n", i, strerror(errno));
            return NULL;
        }

        // Queen buffer
        if (ioctl(usb_dev->fd , VIDIOC_QBUF, &usb_dev->buf) < 0) {
            printf("VIDIOC_QBUF (%d) failed  \n", i);
            return NULL;
        }
    }

    // Stream On
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(usb_dev->fd, VIDIOC_STREAMON, &type) < 0)
    {
        printf("VIDIOC_STREAMON failed\n");
        return NULL;
    }
    return usb_dev;
}

int get_data(usb_camera * usb_dev, FrameBuf *frame_buf)//读取数据到buf
{
    int ret;

    fd_set fds;
    struct timeval tv;
    int r;

    //将fd加入fds集合
    FD_ZERO(&fds);
    FD_SET(usb_dev->fd, &fds);

    /* Timeout. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    //监测是否有数据，最多等待5s
    r = select(usb_dev->fd + 1, &fds, NULL, NULL, &tv);
    if(r==-1)
    {
        printf("select err");
        return GLFW_FALS;
    }
    else if(r==0)
    {
        printf("select timeout");
        return GLFW_FALS;
    }

    // Get frame
    // 捕获数据
    if (ioctl(usb_dev->fd, VIDIOC_DQBUF, &usb_dev->buf) < 0) {
        printf("VIDIOC_DQBUF failed\n");
        return GLFW_FALS;
    }

    frame_buf->start  = usb_dev->mmap_buffer[usb_dev->buf.index].start;
    frame_buf->length = usb_dev->buf.bytesused;

    // Re-queen buffer
    // 将处理完毕的视频帧重新放回驱动程序的队列中，以供下一次捕获
    if (ioctl(usb_dev->fd, VIDIOC_QBUF, &usb_dev->buf) < 0) {
        printf("VIDIOC_QBUF failed\n");
        return GLFW_FALS;
    }

    return GLFW_TRUE;
}

int get_data_from_poll(usb_camera * usb_dev, FrameBuf *frame_buf)//读取数据到buf
{
    struct pollfd pfd;
    pfd.fd = usb_dev->fd;
    pfd.events = POLLIN | POLLPRI; 
  
    int ret;
    do {
        ret = poll(&pfd, 1, 0);
    } while(ret == -1 && errno == EINTR);

    if(ret < 0) {
        printf("poll failed: %s, %d\n", strerror(errno), ret);
        return GLFW_FALS;
    } else if (ret == 0)
    {
        return GLFW_TRUE;
    }
    
    // Get frame
    // 捕获数据
    if (ioctl(usb_dev->fd, VIDIOC_DQBUF, &usb_dev->buf) < 0) {
        printf("VIDIOC_DQBUF failed\n");
        return GLFW_FALS;
    }

    frame_buf->start  = usb_dev->mmap_buffer[usb_dev->buf.index].start;
    frame_buf->length = usb_dev->buf.bytesused;

    // Re-queen buffer
    // 将处理完毕的视频帧重新放回驱动程序的队列中，以供下一次捕获
    if (ioctl(usb_dev->fd, VIDIOC_QBUF, &usb_dev->buf) < 0) {
        printf("VIDIOC_QBUF failed\n");
        return GLFW_FALS;
    }

    return GLFW_TRUE;
}

void release_video(usb_camera * usb_dev)
{
    // Release the resource
    for (int i = 0; i < BUFFER_COUNT; i++) {
        munmap(usb_dev->mmap_buffer[i].start, usb_dev->mmap_buffer[i].length);
    }
    close(usb_dev->fd);
    printf("Camera release done.\n");
}
