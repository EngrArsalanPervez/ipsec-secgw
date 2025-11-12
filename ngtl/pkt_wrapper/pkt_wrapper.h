#ifndef _PKT_WRAPPER_H_
#define _PKT_WRAPPER_H_

#include <stdint.h>

#include <rte_mbuf.h>

void encapsulate_pkt(struct rte_mbuf **pkts, uint8_t nb_pkts);

#endif
