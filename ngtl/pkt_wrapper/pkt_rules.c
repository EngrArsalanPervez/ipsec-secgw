#include "pkt_rules.h"
#include <rte_build_config.h>

pkt_rules_t active_rules[RTE_MAX_ETHPORTS] = { 0 };
client_ports_t client_ports;

void client_ports_init(void)
{
    client_ports.total = 0;
    client_ports.mask = 0;
}

bool client_ports_contains(uint8_t port)
{
    return client_ports.mask & (1ULL << port);
}

bool client_ports_add(uint8_t port)
{
    if (port >= MAX_CLIENT_PORTS)
        return false;

    if (client_ports_contains(port))
        return true;

    if (client_ports.total >= MAX_CLIENT_PORTS)
        return false;

    client_ports.ports[client_ports.total++] = port;
    client_ports.mask |= (1ULL << port);
    return true;
}

int config_hclos_lclos(char *optarg)
{
    client_ports_init();

    const pkt_rules_t *src_rules = NULL;
    uint32_t num_rules = 0;

    // --- Define all rules inside the function ---
    const pkt_rules_t pkt_rules_h1[1] = {
        { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf0 } },
          .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x01 } },
          .src_ip = RTE_IPV4(10, 10, 10, 1),
          .dst_ip = RTE_IPV4(10, 10, 10, 2) },
    };

    const pkt_rules_t pkt_rules_h2[4] = {
        { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x01 } },
          .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf0 } },
          .src_ip = RTE_IPV4(10, 10, 10, 2),
          .dst_ip = RTE_IPV4(10, 10, 10, 1) },
        { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf1 } },
          .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x02 } },
          .src_ip = RTE_IPV4(20, 20, 20, 1),
          .dst_ip = RTE_IPV4(20, 20, 20, 2) },
        { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf2 } },
          .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x03 } },
          .src_ip = RTE_IPV4(30, 30, 30, 1),
          .dst_ip = RTE_IPV4(30, 30, 30, 2) },
        { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf3 } },
          .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x04 } },
          .src_ip = RTE_IPV4(40, 40, 40, 1),
          .dst_ip = RTE_IPV4(40, 40, 40, 2) },
    };

    const pkt_rules_t pkt_rules_l1[1] = {
        { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf1 } },
          .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x02 } },
          .src_ip = RTE_IPV4(20, 20, 20, 1),
          .dst_ip = RTE_IPV4(20, 20, 20, 2) },
    };

    const pkt_rules_t pkt_rules_l2[1] = {
        { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x02 } },
          .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf1 } },
          .src_ip = RTE_IPV4(20, 20, 20, 2),
          .dst_ip = RTE_IPV4(20, 20, 20, 1) },
    };

    const pkt_rules_t pkt_rules_l3[1] = {
        { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf2 } },
          .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x03 } },
          .src_ip = RTE_IPV4(30, 30, 30, 1),
          .dst_ip = RTE_IPV4(30, 30, 30, 2) },
    };

    const pkt_rules_t pkt_rules_l4[1] = {
        { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x03 } },
          .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf2 } },
          .src_ip = RTE_IPV4(30, 30, 30, 2),
          .dst_ip = RTE_IPV4(30, 30, 30, 1) },
    };

    const pkt_rules_t pkt_rules_l5[1] = {
        { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf3 } },
          .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x04 } },
          .src_ip = RTE_IPV4(40, 40, 40, 1),
          .dst_ip = RTE_IPV4(40, 40, 40, 2) },
    };

    const pkt_rules_t pkt_rules_l6[1] = {
        { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x04 } },
          .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf3 } },
          .src_ip = RTE_IPV4(40, 40, 40, 2),
          .dst_ip = RTE_IPV4(40, 40, 40, 1) },
    };

    // --- Select rules based on input ---
    if (strcmp(optarg, "H1") == 0) {
        src_rules = pkt_rules_h1;
        num_rules = sizeof(pkt_rules_h1) / sizeof(pkt_rules_h1[0]);
        client_ports_add(0);
    } else if (strcmp(optarg, "H2") == 0) {
        src_rules = pkt_rules_h2;
        num_rules = sizeof(pkt_rules_h2) / sizeof(pkt_rules_h2[0]);
        client_ports_add(0);
        client_ports_add(1);
        client_ports_add(2);
        client_ports_add(3);
    } else if (strcmp(optarg, "L1") == 0) {
        src_rules = pkt_rules_l1;
        num_rules = sizeof(pkt_rules_l1) / sizeof(pkt_rules_l1[0]);
        client_ports_add(0);
    } else if (strcmp(optarg, "L2") == 0) {
        src_rules = pkt_rules_l2;
        num_rules = sizeof(pkt_rules_l2) / sizeof(pkt_rules_l2[0]);
        client_ports_add(0);
    } else if (strcmp(optarg, "L3") == 0) {
        src_rules = pkt_rules_l3;
        num_rules = sizeof(pkt_rules_l3) / sizeof(pkt_rules_l3[0]);
        client_ports_add(0);
    } else if (strcmp(optarg, "L4") == 0) {
        src_rules = pkt_rules_l4;
        num_rules = sizeof(pkt_rules_l4) / sizeof(pkt_rules_l4[0]);
        client_ports_add(0);
    } else if (strcmp(optarg, "L5") == 0) {
        src_rules = pkt_rules_l5;
        num_rules = sizeof(pkt_rules_l5) / sizeof(pkt_rules_l5[0]);
        client_ports_add(0);
    } else if (strcmp(optarg, "L6") == 0) {
        src_rules = pkt_rules_l6;
        num_rules = sizeof(pkt_rules_l6) / sizeof(pkt_rules_l6[0]);
        client_ports_add(0);
    } else {
        return -1; // unknown option
    }

    // Copy selected rules into global active array
    memcpy(active_rules, src_rules, num_rules * sizeof(pkt_rules_t));

    return 0;
}

void print_pkt_rules(const pkt_rules_t *r)
{
    if (!r) {
        printf("NULL pkt_rules_t pointer\n");
        return;
    }

    uint32_t src_ip = r->src_ip;
    uint32_t dst_ip = r->dst_ip;

    printf("src_mac=%02X:%02X:%02X:%02X:%02X:%02X, "
           "dst_mac=%02X:%02X:%02X:%02X:%02X:%02X, "
           "src_ip=%u.%u.%u.%u, "
           "dst_ip=%u.%u.%u.%u\n",

           r->src_mac.addr_bytes[0], r->src_mac.addr_bytes[1], r->src_mac.addr_bytes[2],
           r->src_mac.addr_bytes[3], r->src_mac.addr_bytes[4], r->src_mac.addr_bytes[5],

           r->dst_mac.addr_bytes[0], r->dst_mac.addr_bytes[1], r->dst_mac.addr_bytes[2],
           r->dst_mac.addr_bytes[3], r->dst_mac.addr_bytes[4], r->dst_mac.addr_bytes[5],

           (src_ip >> 24) & 0xFF, (src_ip >> 16) & 0xFF, (src_ip >> 8) & 0xFF, src_ip & 0xFF,

           (dst_ip >> 24) & 0xFF, (dst_ip >> 16) & 0xFF, (dst_ip >> 8) & 0xFF, dst_ip & 0xFF);
}
