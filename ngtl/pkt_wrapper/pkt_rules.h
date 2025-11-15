#ifndef _PKT_RULES_H_
#define _PKT_RULES_H_

#include <stdint.h>
#include <rte_ether.h>
#include <rte_ip4.h>

typedef struct {
    struct rte_ether_addr src_mac;
    struct rte_ether_addr dst_mac;
    uint32_t src_ip;
    uint32_t dst_ip;
} pkt_rules_t;

extern const pkt_rules_t pkt_rules_h1[RTE_MAX_ETHPORTS];
extern const pkt_rules_t pkt_rules_h2[RTE_MAX_ETHPORTS];
extern const pkt_rules_t pkt_rules_l2[RTE_MAX_ETHPORTS];
extern const pkt_rules_t pkt_rules_l4[RTE_MAX_ETHPORTS];

#endif
