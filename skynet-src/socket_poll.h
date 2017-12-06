#ifndef socket_poll_h
#define socket_poll_h

#include <stdbool.h>

//统一使用的句柄类型
typedef int poll_fd;
//转存的内核通知的结构体
struct event {
	void * s;	//通知的句柄
	bool read;//通知的句柄
	bool write;//是否可写
	bool error;//是否出錯
};

#if 0
static bool sp_invalid(poll_fd fd);
static poll_fd sp_create();
static void sp_release(poll_fd fd);
static int sp_add(poll_fd fd, int sock, void *ud);
static void sp_del(poll_fd fd, int sock);
static void sp_write(poll_fd, int sock, void *ud, bool enable);
static int sp_wait(poll_fd, struct event *e, int max);
static void sp_nonblocking(int sock);

#else
/**
*定义了外部使用的接口，具体实现在 socket_epoll.h 和 socket_kqueue.h 中定义
*/
//错误检测接口（fd: 检测的文件描述符(句柄)，返回true表示有错误）
static bool sp_invalid(poll_fd fd);
//创建句柄（可通过sp_invalid检测是否创建失败，poll_fd是创建好的句柄）
static poll_fd sp_create();
//释放句柄
static void sp_release(poll_fd fd);
/*
 * 在轮序句柄fd中添加一个指定sock文件描述符，用来检测该socket
 * fd    : sp_create() 返回的句柄
 * sock  : 待处理的文件描述符, 一般为socket()返回结果
 * ud    : 自己使用的指针地址特殊处理
 *       : 返回0表示添加成功, -1表示失败
 */
static int sp_add(poll_fd fd, int sock, void *ud);
/*
 * 在轮询句柄fd中删除注册过的sock描述符
 * fd    : sp_create()创建的句柄
 * sock  : socket()创建的句柄
 */
static void sp_del(poll_fd fd, int sock);
/*
 * 在轮序句柄fd中修改sock注册类型
 * fd    : 轮询句柄
 * sock  : 待处理的句柄
 * ud    : 用户自定义数据地址
 * enable: true表示开启写, false表示还是监听读
 */
static void sp_write(poll_fd, int sock, void *ud, bool enable);
/*
 * 轮询句柄,等待有结果的时候构造当前用户层结构struct event结构描述中
 * fd    : sp_create()创建的句柄
 * e     : 一段struct event内存的首地址
 * max   : e内存能够使用的最大值
 *       : 返回等待到的变动数, 相对于e
 */
static int sp_wait(poll_fd, struct event *e, int max);
/*
 * 为套接字描述符设置为非阻塞的
 * sock  : 文件描述符
 */
static void sp_nonblocking(int sock);

#endif
#ifdef __linux__
#include "socket_epoll.h"
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined (__NetBSD__)
#include "socket_kqueue.h"
#endif

#endif
