#ifndef _QPT_HEADER_WATER_METER_PROTOCOL_H_
#define _QPT_HEADER_WATER_METER_PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#include "protocol/wm_context.h"

#define WMP_PREFIX  0xFEFE
#define WMP_POSTFIX 0xEDED

#define PROTO_WMP   0x53

#define WMP_HEAD_LEN        64
#define WMP_TAIL_LEN        2
#define WMP_MAX_DATA_SIZE   800

typedef struct wmp_packet {
    uint16  prefix;         // FE FE
    uint8   protocol_type;  // 53
    uint8   packet_type;

    uint32  timestamp;

    byte    wm_id[WMD_SIZE_WM_ID];
    byte    hub_id[WMD_SIZE_HUB_ID];

    byte    signature[32];

    uint8   packet_count;
    uint8   packet_number;
    uint16  reserved;

    uint16  data_len;
    uint16  check_sum;

    byte    data[WMP_MAX_DATA_SIZE];

    uint16  postfix;        // ED ED
} wmp_pkt;

//extern bool wmp_validate(const wmp_pack *pack);

extern int wmp_serialize(byte *buf, const wmp_pkt *pkt, uint blen);
extern int wmp_deserialize(wmp_pkt *pkt, const byte *data, uint blen);

typedef struct wmp_packet_list {
    uint32 count;
    wmp_pkt *plist;
} wmp_plist;

extern wmp_plist *build_wmp_packets(const wm_cxt *cxt);
extern void destroy_wmp_packets(wmp_plist **plist);

#ifdef __cplusplus
}
#endif

#endif // wmp.h
