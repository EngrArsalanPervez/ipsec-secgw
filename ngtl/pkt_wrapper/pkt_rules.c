#include "pkt_rules.h"

const pkt_rules_t pkt_rules_h1[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf0 } },
            .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x01 } },
            .src_ip = RTE_IPV4(10, 10, 10, 1),
            .dst_ip = RTE_IPV4(10, 10, 10, 2) },
};

const pkt_rules_t pkt_rules_h2[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x01 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf0 } },
            .src_ip = RTE_IPV4(10, 10, 10, 2),
            .dst_ip = RTE_IPV4(10, 10, 10, 1) },
    [1] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf1 } },
            .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x02 } },
            .src_ip = RTE_IPV4(20, 20, 20, 1),
            .dst_ip = RTE_IPV4(20, 20, 20, 2) },
    [2] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf2 } },
            .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x03 } },
            .src_ip = RTE_IPV4(30, 30, 30, 1),
            .dst_ip = RTE_IPV4(30, 30, 30, 2) },
    [3] = { .src_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf3 } },
            .dst_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x04 } },
            .src_ip = RTE_IPV4(40, 40, 40, 1),
            .dst_ip = RTE_IPV4(40, 40, 40, 2) },
};

const pkt_rules_t pkt_rules_l2[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x02 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf1 } },
            .src_ip = RTE_IPV4(20, 20, 20, 2),
            .dst_ip = RTE_IPV4(20, 20, 20, 1) },
};

const pkt_rules_t pkt_rules_l4[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x03 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf2 } },
            .src_ip = RTE_IPV4(30, 30, 30, 2),
            .dst_ip = RTE_IPV4(30, 30, 30, 1) },
};

const pkt_rules_t pkt_rules_l6[RTE_MAX_ETHPORTS] = {
    [0] = { .src_mac = { .addr_bytes = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x04 } },
            .dst_mac = { .addr_bytes = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xf3 } },
            .src_ip = RTE_IPV4(40, 40, 40, 2),
            .dst_ip = RTE_IPV4(40, 40, 40, 1) },
};
