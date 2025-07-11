//#include "main.h"
#include "lwip/ip6_addr.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "lwip/inet.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

#define NTP_PORT 123
#define NTP_PACKET_SIZE 48
#define NTP_UNIX_OFFSET 2208988800UL

static struct udp_pcb *ntp_pcb;
static ip_addr_t ntp_server_ip;
static uint8_t ntp_packet[NTP_PACKET_SIZE];

__IO uint32_t ntp_time_unix = 0;
__IO uint8_t ntp_time_updated = 0;


// ===== 콜백 함수 =====
void udp_ntp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    if (p->len >= NTP_PACKET_SIZE)
    {
        uint32_t seconds;

        memcpy(&seconds, (uint8_t *)p->payload + 40, 4);
        seconds = ntohl(seconds);

        if (seconds > NTP_UNIX_OFFSET)
        {
            ntp_time_unix = seconds - NTP_UNIX_OFFSET;

            // UNIX time -> 시간 구조체 변환
            time_t rawtime = (time_t)ntp_time_unix;
            struct tm *timeinfo = gmtime(&rawtime);

            printf("NTP Time: %04d-%02d-%02d %02d:%02d:%02d (UTC)\r\n",
                timeinfo->tm_year + 1900,
                timeinfo->tm_mon + 1,
                timeinfo->tm_mday,
                timeinfo->tm_hour,
                timeinfo->tm_min,
                timeinfo->tm_sec);
        }
    }

    pbuf_free(p);
}

// ===== 요청 전송 함수 =====
void udp_ntp_send(void)
{
    struct pbuf *p;

    // NTP 요청 패킷 초기화
    memset(ntp_packet, 0, sizeof(ntp_packet));
    ntp_packet[0] = 0x1B; // LI=0, VN=3, Mode=3 (Client)

    p = pbuf_alloc(PBUF_TRANSPORT, NTP_PACKET_SIZE, PBUF_POOL);
    if (p != NULL)
    {
        pbuf_take(p, ntp_packet, NTP_PACKET_SIZE);
        udp_send(ntp_pcb, p);
        pbuf_free(p);
    }
}

// ===== NTP 서버 연결 및 요청 시작 =====
void udp_ntp_client_init(void)
{
    ntp_pcb = udp_new();
    if (ntp_pcb == NULL)
    {
        printf("Failed to create UDP PCB\r\n");
        return;
    }

    // NTP 서버 IP 설정 (예: time.google.com = 216.239.35.0)
    IP4_ADDR(&ntp_server_ip, 216, 239, 35, 0);

    udp_connect(ntp_pcb, &ntp_server_ip, NTP_PORT);
    udp_recv(ntp_pcb, udp_ntp_receive_callback, NULL);

    udp_ntp_send();  // 요청 전송
}
