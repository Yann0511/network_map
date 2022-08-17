/*#ifdef _OS_H
#define _OS_H*/

/*#include <stdio.h>
#include <string.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>*/


#define IPv4_ETHERTYPE 0x800


/* longueur de capture par défaut (octets maximum par paquet à capturer) */
#define SNAP_LEN 1518

/* les en-têtes Ethernet font toujours exactement 14 octets [1] */
#define SIZE_ETHERNET 14

/* Les adresses Ethernet font 6 octets */
//#define ETHER_ADDR_LEN 6

/* TCP protocol */
#define IP_PROTO_TCP 6  

/*
 *  La table d'hashage d'empreintes digitales a la structure suivante :
 *                                                                         
 *  WWWW:MSS:TTL:WS:S:N:D:T:F:LEN                                       
 *                                                                         
 *  WWWW: Champ hexadécimal à 4 chiffres indiquant la taille de la fenêtre TCP
 *  MSS : Champ hexadécimal à 4 chiffres indiquant la taille de segment maximale de l'option TCP
 * 		si omis dans le paquet ou inconnu c'est "_MSS"
 *  TTL : Champ hexadécimal à 2 chiffres indiquant la durée de vie IP
 *  WS  : Champ hexadécimal à 2 chiffres indiquant l'échelle de la fenêtre d'option TCP
 *        si omis dans le paquet ou inconnu, c'est "WS"
 *  S   : Champ à 1 chiffre indiquant si l'option TCP SACK autorisée est vraie
 *  N   : Champ à 1 chiffre indiquant si les options TCP contiennent un NOP
 *  D   : Champ à 1 chiffre indiquant si l'indicateur IP Don't Fragment est défini
 *  T   : Champ à 1 chiffre indiquant si l'horodatage TCP est présent
 *  F   : Champ ascii à 1 chiffre indiquant le drapeau du paquet
 *        S = SYN                                                          
 *        A = SYN + ACK                                                    
 *  LEN : Champ hexadécimal à 2 chiffres indiquant la longueur du paquet
 *        si non pertinent ou inconnu c'est "LT"                           
 */


enum 
{
   FINGER_LEN = 28,
   FINGER_WINDOW     = 0,
   FINGER_MSS        = 5,
   FINGER_TTL        = 10,
   FINGER_WS         = 13,
   FINGER_SACK       = 16,
   FINGER_NOP        = 18,
   FINGER_DF         = 20,
   FINGER_TIMESTAMP  = 22,
   FINGER_TCPFLAG    = 24,
   FINGER_LT         = 26,
};

/* En-tête Ethernet */
struct ethernet 
{
  uint8_t ether_dhost[ETHER_ADDR_LEN];    /* adresse de l'hôte de destination */
  uint8_t ether_shost[ETHER_ADDR_LEN];    /* adresse de l'hôte source */
  uint16_t ether_type;                     /* IP ? ARP ? RARP ? etc */
};


void* initialize_sniffer(void*);

void sniffer(const u_char* packet, char *OS);

void finger_ip(struct ip *ip, char *finger);

void finger_tcp(struct tcphdr *tcp, char *finger);

char* os(char *finger);

//#endif
