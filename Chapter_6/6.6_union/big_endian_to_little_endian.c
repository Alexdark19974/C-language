#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <malloc.h>
#define BYTES 64
#define PRINT_BORDER() printf("--------------------------------------\n")
#define PRINT_BIG_ENDIAN(arg) printf(">>>>>>> BIG_ENDIAN <<<<<<<\n"); printf("converting ipaddr(%s) into an unsigned integer of network byte order (big-endian).\n", arg)
#define PRINT_LITTLE_ENDIAN(arg) printf(">>>>>>> LITTLE_ENDIAN <<<<<<<\n"); printf("converting ipaddr(%s) into an unsigned integer of host byte order (little-endian)\n", arg)
#define PROMPT() printf("If you think that if you change the last octet of \"192.168.1.1\" and the new ip address will be \"192.168.1.2\", you are set for failure.\n")
#define INET_NETWORK_CONVERT(arg) (u_int) inet_network(arg)
#define INET_ADDR_CONVERT(arg) (u_int) inet_addr(ipp)
#define INCREMENT_VAL(arg, val) *arg = *arg + 1
#define DECREMENT_VAL(arg, val) *arg = *arg - 1
#define DISPLAY_VAL_AND_BYTES(arg) printf("val=0x%x;\nbyte1=%u, byte2=%u, byte3=%u, byte4=%u\n",arg->ipaddr, arg->bytes.byte1, arg->bytes.byte2, arg->bytes.byte3, arg->bytes.byte4)
#define FREE_MEMORY(arg) if (arg) { \
                            free(arg); \
                             arg = NULL; \
                         }
#define ALLOCATE_MEMORY(arg, size)  if ((arg = calloc(1, size)) == NULL) { \
                                        perror("calloc"); \
                                        goto exit; \
                                    }
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef char * StringP;
StringP check_endianess(void);
void LE_2_BE_ip_addr(void);

typedef union Ipaddr {
    struct {
        u_char byte1;
        u_char byte2;
        u_char byte3;
        u_char byte4;
    } bytes;
    u_int ipaddr;
} Ipaddr, *IpaddrP;

int main(void)
{
    LE_2_BE_ip_addr();
    return EXIT_SUCCESS;
}

void LE_2_BE_ip_addr(void)
{
    StringP ipp = NULL, bytep = NULL;
    IpaddrP ipaddrp = NULL;
    struct in_addr addr = {0};
    size_t bytes = sizeof(*ipaddrp);

    ALLOCATE_MEMORY(ipp, BYTES);
    ALLOCATE_MEMORY(ipaddrp, bytes);

    strcpy(ipp, "192.168.1.1");

    PRINT_BORDER();
    PRINT_LITTLE_ENDIAN(ipp);

    ipaddrp->ipaddr = INET_NETWORK_CONVERT(ipp);
    DISPLAY_VAL_AND_BYTES(ipaddrp);

    bytep= (char *) &(ipaddrp->bytes.byte4);
    INCREMENT_VAL(bytep, 1);

    PROMPT();
    addr.s_addr = ipaddrp->ipaddr;
    printf("the result of the 4th byte incremented: %s\n", inet_ntoa((struct in_addr) addr));
    printf("Why? Because the host is %s", check_endianess());

    DECREMENT_VAL(bytep, 1);
    PRINT_BORDER();

    PRINT_BORDER();
    PRINT_BIG_ENDIAN(ipp);

    ipaddrp->ipaddr = INET_ADDR_CONVERT(ipp);
    DISPLAY_VAL_AND_BYTES(ipaddrp);
    INCREMENT_VAL(bytep, 1);

    addr.s_addr = ipaddrp->ipaddr;
    printf("the result of the 4th byte incremented: %s\n", inet_ntoa((struct in_addr) addr));
    PRINT_BORDER();

    FREE_MEMORY(ipp);
    FREE_MEMORY(ipaddrp);
exit:
    return;
}

StringP check_endianess(void)
{
    u_int what_endianess = 0xFF00;
    char *bytep = (char *) &what_endianess;
    return *bytep ? "big-endian.\n" : "little-endian.\n";
}
