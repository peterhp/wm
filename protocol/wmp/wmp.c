#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "util/macros.h"
#include "util/errors.h"
#include "util/crc.h"

#include "protocol/wmp/wmp.h"

int wmp_serialize(byte *buf, const wmp_pkt *pkt, uint blen) {
    uint len = WMP_HEAD_LEN + pkt->data_len + WMP_TAIL_LEN;
    if (blen < len) {
        return ERROR_INSUFFICIENT_BUFFER;
    }

    memcpy(buf, pkt, WMP_HEAD_LEN);
    memcpy(buf + WMP_HEAD_LEN, pkt->data, pkt->data_len);
    memcpy(buf + WMP_HEAD_LEN + pkt->data_len, &pkt->postfix, 2);
    return len;
}

int wmp_deserialize(wmp_pkt *pkt, const byte *data, uint blen) {
    if (blen < WMP_HEAD_LEN + WMP_TAIL_LEN) {
        return ERROR_INVALID_PACKET_LEN;
    }

    memcpy(pkt, data, WMP_HEAD_LEN);
    if (blen != WMP_HEAD_LEN + pkt->data_len + WMP_TAIL_LEN) {
        return ERROR_INVALID_PACKET_LEN;
    }

    memcpy(pkt->data, data + WMP_HEAD_LEN, pkt->data_len);
    memcpy(&pkt->postfix, data + WMP_HEAD_LEN + pkt->data_len, 2);

    return (WMP_HEAD_LEN + pkt->data_len + WMP_TAIL_LEN);
}

/**
 * It's an internal function to pack data in wmp protocol.
 * All packets share a single build timestamp for one wm context.
 * 
 * @param pkt: dst packet
 * @param cxt: wm data context
 * @param pnum: current packet number of this cxt (0, 1, 2, ...)
 * @param ts: timestamp of packing this cxt
 * @return plen: length of current packing data
**/
static uint wmp_pack(wmp_pkt *pkt, const wm_cxt *cxt, uint pnum, uint32 ts) {
    uint pos = WMP_MAX_DATA_SIZE * pnum;

    memset(pkt, 0, sizeof(wmp_pkt));

    // basic packet information
    pkt->prefix = WMP_PREFIX;
    pkt->protocol_type = PROTO_WMP;
    pkt->packet_type = cxt->type;
    pkt->timestamp = ts;
    pkt->packet_count = DIV_CEIL(cxt->dlen, WMP_MAX_DATA_SIZE);
    pkt->packet_number = pnum;

    memcpy(pkt->wm_id, cxt->wm_id, WMD_SIZE_WM_ID);
    memcpy(pkt->hub_id, cxt->hub_id, WMD_SIZE_HUB_ID);

    // packet data
    pkt->data_len = MIN(cxt->dlen - pos, WMP_MAX_DATA_SIZE);
    memcpy(pkt->data, cxt->data + WMP_MAX_DATA_SIZE * pos, pkt->data_len);
    pkt->check_sum = crc16(pkt->data, pkt->data_len);
    
    return pkt->data_len;
}

wmp_plist *build_wmp_packets(const wm_cxt *cxt) {
    uint32 timestamp = (uint32)time(NULL);

    wmp_plist *pkts = (wmp_plist *)malloc(sizeof(wmp_plist));
    pkts->count = DIV_CEIL(cxt->dlen, WMP_MAX_DATA_SIZE);
    pkts->plist = (wmp_pkt *)malloc(sizeof(wmp_pkt) * pkts->count);

    for (int pi = 0; pi < pkts->count; ++pi) {
        wmp_pack(pkts->plist + pi, cxt, pi, timestamp);
    }

    return pkts;
}

void destroy_wmp_packets(wmp_plist **plist) {
    if (*plist) {
        free((*plist)->plist);
        free(*plist);
        *plist = NULL;
    }
}
