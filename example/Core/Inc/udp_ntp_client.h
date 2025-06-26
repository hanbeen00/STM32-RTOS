#ifndef __UDP_NTP_CLIENT_H
#define __UDP_NTP_CLIENT_H

#include "lwip/ip_addr.h"

// === NTP 관련 정의 ===
#define NTP_PORT             123
#define NTP_PACKET_SIZE      48
#define NTP_UNIX_OFFSET      2208988800UL  // 1970-01-01 기준

extern __IO uint32_t ntp_time_unix;
extern __IO uint8_t ntp_time_updated;

// === 함수 선언 ===
void udp_ntp_client_init(void);      // NTP 클라이언트 초기화 및 요청 전송
void udp_ntp_send(void);             // NTP 요청 수동 전송

#endif // __UDP_NTP_CLIENT_H
