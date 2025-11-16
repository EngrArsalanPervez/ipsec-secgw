#ifndef _PKT_RULES_H_
#define _PKT_RULES_H_

#include <stdint.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <stdbool.h>
#include <rte_lcore.h>

typedef struct {
    const struct rte_ether_addr src_mac;
    const struct rte_ether_addr dst_mac;
    const uint32_t src_ip;
    const uint32_t dst_ip;
} pkt_rules_t;

extern const pkt_rules_t *active_rules;

#define MAX_CLIENT_PORTS RTE_MAX_ETHPORTS

typedef struct {
    uint8_t ports[RTE_MAX_ETHPORTS];
    uint8_t total;
    uint64_t mask;
} client_ports_t;

typedef enum PORT_TYPE_e { CLIENT_PORT = 0, TUNNEL_PORT = 1 } PORT_TYPE;
typedef enum DEVICE_TYPE_e { DUAL_PORT = 0, MULTI_PORT = 1 } DEVICE_TYPE;

int config_hclos_lclos(char *optarg);
bool client_ports_contains(uint8_t port);
uint8_t get_outport(uint16_t portid);

#endif
