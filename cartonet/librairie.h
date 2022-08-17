#include <pcap.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <hiredis/hiredis.h>
#include <netinet/ether.h>
#include "os.h"

#define QPAQUET 0
#define RACINE "hotes"
bpf_u_int32 adresse_reseau, masque_reseau;

typedef struct pcap_pkthdr entete_paquet;
typedef struct ether_header entete_ethernet;
typedef struct tcphdr tcphdr;
typedef struct udphdr udphdr;
typedef struct ip iphdr;

typedef struct peripherique {
  char nom[50];
  char adresse_ip[15];
  char masque_sous_reseau[15];
} peripherique;

entete_ethernet *trouver_entete_ether(u_char *donnees_paquet);
iphdr* trouver_entete_ip(u_char *donnees_paquet);
tcphdr* trouver_entete_tcp(u_char *donnees_paquet);
udphdr* trouver_entete_udp(u_char *donnees_paquet);
void obtenir_adresseIP_source(iphdr* entete_ip, char *adresseIP_source);
void obtenir_adresseIP_dest(iphdr* entete_ip, char *adresseIP_destination);
int adresse_valide(char *adresse);
u_int obtenir_port_source_tcp(u_char *donnees_paquet);
u_int obtenir_port_source_udp(u_char *donnees_paquet);
u_int obtenir_port_dest_tcp(u_char *donnees_paquet);
u_int obtenir_port_dest_udp(u_char *donnees_paquet);
void obtenir_os(u_char *donnees_paquet, char *OS);
redisContext* connection(const char *adresse, const int port);
redisReply *nettoyer_bd(redisContext *lien);
redisReply *creer_racine(redisContext *lien);
redisReply *creer_hote(redisContext *lien, char *adresse);
redisReply *initialiser_port(redisContext *lien, int port, char *adresse);
redisReply *ajouter_port(redisContext *lien, int port, char *adresse);
redisReply *inserer_os(redisContext *lien, char *OS, char *adresse);
redisReply *inserer_paquets_emis(redisContext *lien, int nombre, char *adresse);
redisReply *inserer_paquets_recus(redisContext *lien, int nombre, char *adresse);
redisReply *incrementer_paquet_emis(redisContext *lien, char *adresse);
redisReply *incrementer_paquets_recus(redisContext *lien, char *adresse);
redisReply *inserer_associe(redisContext *lien, char *hote, char *associe);
redisReply *ajouter_associe(redisContext *lien, char *hote, char *associe);
int hote_existe_deja(redisContext *connection_bd, char *adresseIP);
int port_existe_deja(redisContext *lien, int port, char *adresse);
int os_existe(redisContext *lien, char *adresse);
int associe_existe_deja(redisContext *lien, char *hote, char *associe);
void gestionnaire_paquet(u_char *arguments, entete_paquet *entete, u_char *donnees_paquet);
void trouver_interface(char *nom);
void adresse_interface(bpf_u_int32 ip_brute, char *adresse);
void masque_interface(bpf_u_int32 masque_brute, char *masque);
int adresses_interface(char *interface, bpf_u_int32 *ip_brute, bpf_u_int32 *masque_brute);
void lancer_capture(char *interface, int duree_decoute, pcap_handler gestionnaire_paquet);
int adresse_dans_reseau(bpf_u_int32 subnet_mask, bpf_u_int32 ip_address, char *target_address);
void finger_tcp(struct tcphdr *tcp, char *finger);
void finger_ip(struct ip *ip, char *finger);
void sniffer(const uint8_t* packet, char *OS);





