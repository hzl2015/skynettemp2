#ifndef socket_poll_h
#define socket_poll_h

#include <stdbool.h>

//ͳһʹ�õľ������
typedef int poll_fd;
//ת����ں�֪ͨ�Ľṹ��
struct event {
	void * s;	//֪ͨ�ľ��
	bool read;//֪ͨ�ľ��
	bool write;//�Ƿ��д
	bool error;//�Ƿ���e
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
*�������ⲿʹ�õĽӿڣ�����ʵ���� socket_epoll.h �� socket_kqueue.h �ж���
*/
//������ӿڣ�fd: �����ļ�������(���)������true��ʾ�д���
static bool sp_invalid(poll_fd fd);
//�����������ͨ��sp_invalid����Ƿ񴴽�ʧ�ܣ�poll_fd�Ǵ����õľ����
static poll_fd sp_create();
//�ͷž��
static void sp_release(poll_fd fd);
/*
 * ��������fd�����һ��ָ��sock�ļ�����������������socket
 * fd    : sp_create() ���صľ��
 * sock  : ��������ļ�������, һ��Ϊsocket()���ؽ��
 * ud    : �Լ�ʹ�õ�ָ���ַ���⴦��
 *       : ����0��ʾ��ӳɹ�, -1��ʾʧ��
 */
static int sp_add(poll_fd fd, int sock, void *ud);
/*
 * ����ѯ���fd��ɾ��ע�����sock������
 * fd    : sp_create()�����ľ��
 * sock  : socket()�����ľ��
 */
static void sp_del(poll_fd fd, int sock);
/*
 * ��������fd���޸�sockע������
 * fd    : ��ѯ���
 * sock  : ������ľ��
 * ud    : �û��Զ������ݵ�ַ
 * enable: true��ʾ����д, false��ʾ���Ǽ�����
 */
static void sp_write(poll_fd, int sock, void *ud, bool enable);
/*
 * ��ѯ���,�ȴ��н����ʱ���쵱ǰ�û���ṹstruct event�ṹ������
 * fd    : sp_create()�����ľ��
 * e     : һ��struct event�ڴ���׵�ַ
 * max   : e�ڴ��ܹ�ʹ�õ����ֵ
 *       : ���صȴ����ı䶯��, �����e
 */
static int sp_wait(poll_fd, struct event *e, int max);
/*
 * Ϊ�׽�������������Ϊ��������
 * sock  : �ļ�������
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
