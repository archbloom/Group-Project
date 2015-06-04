//Assignment No.: 3

#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <net/ethernet.h>   // Ethernet header structure
#include <netinet/ip.h>	   // Internet Protocol header structure
#include <netinet/tcp.h>	   // TCP header structure
#include <netinet/udp.h>	   // UDP header structure
#include <netinet/ip_icmp.h>   // ICMP header structure
#include <arpa/inet.h>	  //ntohs & ntohl functions

#define IPV4PACKET 0x0800
#define ARPPACKET 0x0806
#define IPV6PACKET 0x86DD

#define ARP_REQUEST 1
#define ARP_REPLY 2
/* ARP Packet Header */
typedef struct arphdr
{
	u_int16_t htype;
	u_int16_t ptype;
	u_char hlen;
	u_char plen;
	u_int16_t oprcode;
	u_char sha[6];
	u_char sipa[4];
	u_char tha[6];
	u_char tipa[4];
}arphdr_t;



int main(int argc,char **argv)
{
	pcap_t *handle;
	int packet_count=0;
	long int current_ts=0;
	const u_char *packet;
	struct pcap_pkthdr *header=NULL;
	struct ether_header *eth_header=NULL;
	struct iphdr *ip_header =NULL;
	struct tcphdr *tcp_header=NULL;
	struct udphdr *udp_header=NULL;
	struct icmphdr *icmp_header=NULL;
	arphdr_t *arp_header=NULL;
	char err_buf[PCAP_ERRBUF_SIZE];
	int i=0,tcp_count=0,udp_count=0,icmp_count=0,arp_count=0,filecount = 1;
	if(argc<2)
	{
		printf("Please enter the file name as first argument!\n");
		exit(1);
	}
	while(filecount < argc)
	{
    	handle=pcap_open_offline(argv[filecount],err_buf);	//call pcap library function
    	if(handle==NULL)
    	{
    		printf("Cannot open the pcap file %s : %s",argv[1],err_buf);
    		exit(1);
    	}

	//begin processing the packets in this particular file, one at a time
    	while((pcap_next_ex(handle,&header,&packet))>0)
    	{
    		packet_count++;
    		printf("\n\n\nPacket #%d",packet_count);
    		eth_header = (struct ether_header *) packet;
		if (ntohs (eth_header->ether_type) == IPV4PACKET)  //IP packet
		{
  		printf("\nEthernet Packet \nPacket Length : %d",header->caplen);
	     	ip_header = (struct iphdr*)(packet + ETHER_HDR_LEN);     //get the  IP header

		switch (ip_header->protocol) //Check the Protocol and do accordingly...
		{
		case 1:  //ICMP Protocol
			icmp_count++;
			icmp_header = (struct icmphdr *)(packet + ETHER_HDR_LEN + ip_header->ihl*4);	//get the ICMP Header
			printf("ICMP Header\n");
    			printf("   |-Type : %d",(unsigned int)(icmp_header->type));
    			printf("   |-Code : %d\n",(unsigned int)(icmp_header->code));
    			printf("   |-Checksum : %d\n",ntohs(icmp_header->checksum));
    			if((unsigned int)(icmp_header->type) == 11)
        			printf("  (TTL Expired)\n");
    			else if((unsigned int)(icmp_header->type) == ICMP_ECHOREPLY)
      				printf("  (ICMP Echo Reply)\n");
			break;
		case 6:  //TCP Protocol
			tcp_count++;
			tcp_header=(struct tcphdr *)(packet + ETHER_HDR_LEN + ip_header->ihl*4);       //get the TCP Header
			printf("\nTCP Header");
			printf("\n   |-Source IP : %s",(inet_ntoa(*(struct in_addr *)&ip_header->saddr)));
			printf("\n   |-Destination IP : %s",(inet_ntoa(*(struct in_addr *)&ip_header->daddr)));
			printf("\n   |-Source Port : %d",ntohs(tcp_header->th_sport));
			printf("\n   |-Destination Port : %d",ntohs(tcp_header->th_dport));
			printf("\n   |-ACK : %u",ntohl(tcp_header->th_ack));
			printf("\n   |-SEQ : %u",ntohl(tcp_header->th_seq));
			printf("\n");
			break;

		case 17: //UDP Protocol
			udp_count++;
			udp_header = (struct udphdr*)(packet + ETHER_HDR_LEN + ip_header->ihl*4);   //get the UDP Header
			printf("\nUDP Header");
			printf("\n   |-Source Port      : %d" , ntohs(udp_header->source));
    			printf("\n   |-Destination Port : %d" , ntohs(udp_header->dest));
    			printf("\n   |-UDP Length       : %d" , ntohs(udp_header->len));
    			printf("\n   |-UDP Checksum     : %d" , ntohs(udp_header->check));
			printf("\n");
			break;

		}

		}
		else if (ntohs (eth_header->ether_type) == ARPPACKET)   // ARP packet
		{
			arp_count++;
			printf("\nARP Packet \nPacket Length : %d",header->caplen);
			printf("\nARP Header");
			arp_header=(arphdr_t *)(packet + ETHER_HDR_LEN);  //get the ARP Header
			printf("\n   |-Hardware Type : %s ",(ntohs(arp_header->htype)==1)? "Ethernet":"Unknown");
			printf("\n   |-Protocol Type : %s ",(ntohs(arp_header->ptype)==0X0800)? "IPv4":"Unknown");
			printf("\n   |-Operation : %s ",(ntohs(arp_header->oprcode)==ARP_REQUEST)? "ARP Request":"ARP Reply");

			printf("\n   |-Sender MAC : ");
			for(i=0;i<6;i++)
				printf("%02X:",arp_header->sha[i]);	//S'ender H'ardware A'ddress
			printf("\n   |-Target MAC : ");
			for(i=0;i<6;i++)
				printf("%02X:",arp_header->tha[i]);    //T'arget H'ardware A'ddress
			printf("\n   |-Sender IP Address : ");
			for(i=0;i<4;i++)
				printf("%d.",arp_header->sipa[i]);	//S'ender IP A'ddress
			printf("\n   |-Target IP Address : ");
			for(i=0;i<4;i++)
				printf("%d.",arp_header->tipa[i]);	//T'arget IP A'ddress
			printf("\n");
		}

    	}
    pcap_close(handle);
    filecount++;
    }
    for(i=0;i<150;i++)
	printf("=");
    printf("\n Summary:");
    printf("\n Total Packets : %d",packet_count);
    printf("\n   |-ICMP Packets : %d",icmp_count);
    printf("\n   |-TCP Packets : %d",tcp_count);
    printf("\n   |-UDP Packets : %d",udp_count);
    printf("\n   |-ARP Packets : %d",arp_count);
    printf("\n");
    for(i=0;i<150;i++)
	printf("=");
    printf("\n");
    return 0;
}
