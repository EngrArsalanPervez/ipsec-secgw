#include "pkt_wrapper.h"

// Prepend Ethernet + IPv4 header and copy original payload
struct rte_mbuf *prepend_eth_ip_manual(struct rte_mbuf *orig, struct rte_mempool *pool,
                                       const struct rte_ether_addr *src_mac,
                                       const struct rte_ether_addr *dst_mac, uint32_t src_ip,
                                       uint32_t dst_ip)
{
    const uint16_t hdr_len = sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr);
    const uint16_t orig_len = rte_pktmbuf_pkt_len(orig);
    const uint16_t total_len = hdr_len + orig_len;

    // Allocate a new mbuf
    struct rte_mbuf *new_m = rte_pktmbuf_alloc(pool);
    if (!new_m) {
        printf("[ERR] Failed to allocate new mbuf\n");
        return NULL;
    }

    // Append enough space for headers + payload
    uint8_t *data = rte_pktmbuf_append(new_m, total_len);
    if (!data) {
        printf("[ERR] Not enough tailroom in new mbuf\n");
        rte_pktmbuf_free(new_m);
        return NULL;
    }

    // Copy original payload after the header space
    rte_memcpy(data + hdr_len, rte_pktmbuf_mtod(orig, void *), orig_len);

    // Build Ethernet header
    struct rte_ether_hdr *eth_hdr = (struct rte_ether_hdr *)data;
    rte_ether_addr_copy(dst_mac, &eth_hdr->dst_addr);
    rte_ether_addr_copy(src_mac, &eth_hdr->src_addr);
    eth_hdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);

    // Build IPv4 header
    struct rte_ipv4_hdr *ip_hdr = (struct rte_ipv4_hdr *)(eth_hdr + 1);
    ip_hdr->version_ihl = RTE_IPV4_VHL_DEF;
    ip_hdr->type_of_service = 0;
    ip_hdr->total_length = rte_cpu_to_be_16(total_len - sizeof(struct rte_ether_hdr));
    ip_hdr->packet_id = 0;
    ip_hdr->fragment_offset = 0;
    ip_hdr->time_to_live = 64;
    ip_hdr->next_proto_id = IPPROTO_IPIP; // inner IP encapsulation
    ip_hdr->src_addr = rte_cpu_to_be_32(src_ip);
    ip_hdr->dst_addr = rte_cpu_to_be_32(dst_ip);
    ip_hdr->hdr_checksum = rte_ipv4_cksum(ip_hdr);

    return new_m;
}

void encapsulate_pkt(struct rte_mbuf **pkts, uint8_t nb_pkts, struct rte_mempool *pool)
{
    struct rte_ether_addr src_mac, dst_mac;
    uint32_t src_ip, dst_ip;

    for (uint8_t i = 0; i < nb_pkts; i++) {
        struct rte_mbuf *m = pkts[i];

        unsigned char *pkt = rte_pktmbuf_mtod(m, unsigned char *);
        struct rte_ether_hdr *ethHdr = (struct rte_ether_hdr *)pkt;
        uint16_t ethType = rte_cpu_to_be_16(ethHdr->ether_type);

        if (ethType != RTE_ETHER_TYPE_IPV4)
            continue;

        struct rte_ipv4_hdr *ip4Hdr;
        ip4Hdr = (struct rte_ipv4_hdr *)&pkt[14];

        if (1) {
            rte_ether_unformat_addr("aa:bb:cc:dd:ee:ff", &src_mac);
            rte_ether_unformat_addr("11:22:33:44:55:01", &dst_mac);
            src_ip = RTE_IPV4(10, 10, 10, 1);
            dst_ip = RTE_IPV4(10, 10, 10, 2);
        } else {
            rte_ether_unformat_addr("aa:bb:cc:dd:ee:ff", &dst_mac);
            rte_ether_unformat_addr("11:22:33:44:55:01", &src_mac);
            src_ip = RTE_IPV4(10, 10, 10, 2);
            dst_ip = RTE_IPV4(10, 10, 10, 1);
        }
        struct rte_mbuf *new_m = prepend_eth_ip_manual(m, pool, &src_mac, &dst_mac, src_ip, dst_ip);

        if (new_m == NULL) {
            RTE_LOG(WARNING, USER1, "Encapsulation failed for packet %u — keeping original\n", i);
            continue;
        }

        // Replace and free original
        rte_pktmbuf_free(m);
        pkts[i] = new_m;
    }
}
