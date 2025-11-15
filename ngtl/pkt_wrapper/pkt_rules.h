#ifndef _PKT_RULES_H_
#define _PKT_RULES_H_

#include <stdint.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <stdbool.h>
#include <rte_lcore.h>

typedef struct {
    struct rte_ether_addr src_mac;
    struct rte_ether_addr dst_mac;
    uint32_t src_ip;
    uint32_t dst_ip;
} pkt_rules_t;

extern pkt_rules_t active_rules[RTE_MAX_ETHPORTS];

#define MAX_CLIENT_PORTS RTE_MAX_ETHPORTS

typedef struct {
    uint8_t ports[RTE_MAX_ETHPORTS];
    uint8_t total;
    uint64_t mask;
} client_ports_t;

int config_hclos_lclos(char *optarg);
bool client_ports_contains(uint8_t port);
void print_pkt_rules(const pkt_rules_t *r);

#endif
