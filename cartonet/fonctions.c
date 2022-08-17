#include "librairie.h"
#include "os_hash.h"

entete_ethernet *trouver_entete_ether(u_char *donnees_paquet) {
  entete_ethernet *entete_eth = (entete_ethernet *) donnees_paquet;
  return entete_eth;
}

iphdr* trouver_entete_ip(u_char *donnees_paquet) {
  iphdr* entete_ip = entete_ip = (iphdr*) (donnees_paquet + sizeof(entete_ethernet));
  return entete_ip;
}

tcphdr* trouver_entete_tcp(u_char *donnees_paquet) {
  tcphdr *entete_tcp = (tcphdr*) (donnees_paquet + sizeof(entete_ethernet) + sizeof(iphdr));
  return entete_tcp;
}

udphdr* trouver_entete_udp(u_char *donnees_paquet) {
  udphdr *entete_udp = (udphdr*) (donnees_paquet + sizeof(entete_ethernet) + sizeof(iphdr));
  return entete_udp;
}

void obtenir_adresseIP_source(iphdr* entete_ip, char *adresseIP_source) {
  inet_ntop(AF_INET, &(entete_ip->ip_src), adresseIP_source, INET_ADDRSTRLEN);
}

void obtenir_adresseIP_dest(iphdr* entete_ip, char *adresseIP_destination) {
  inet_ntop(AF_INET, &(entete_ip->ip_dst), adresseIP_destination, INET_ADDRSTRLEN);
}

int adresse_valide(char *adresse) {
  char temp[10];
  char *c=adresse;
  char *d;
  int i=0;
  while(*c != '\0') {
    d=temp;
    while (*c != '.' && *c) {
      if (*c < '0' || *c > '9')
	return 1;
      *d=*c;
      c++;
      d++;
    }
    if(*c)
      c++;
    *d='\0';
    if(atoi(temp) > 255 || atoi(temp) < 0)
      return 1;
    i++;
  }
  return !(i==4);
}

u_int obtenir_port_source_tcp(u_char *donnees_paquet) {
  tcphdr* entete_tcp;
  u_int port_source;
  entete_tcp = trouver_entete_tcp(donnees_paquet);
  port_source = ntohs(entete_tcp->source);
  return port_source;
}

u_int obtenir_port_source_udp(u_char *donnees_paquet) {
  udphdr* entete_udp;
  u_int port_source;
  entete_udp = trouver_entete_udp(donnees_paquet);
  port_source = ntohs(entete_udp->source);
  return port_source;
}

u_int obtenir_port_dest_tcp(u_char *donnees_paquet) {
  tcphdr* entete_tcp;
  u_int port_dest;
  entete_tcp = trouver_entete_tcp(donnees_paquet);
  port_dest = ntohs(entete_tcp->dest);
  return port_dest;
}

u_int obtenir_port_dest_udp(u_char *donnees_paquet) {
  udphdr* entete_udp;
  u_int port_dest;
  entete_udp = trouver_entete_udp(donnees_paquet);
  port_dest = ntohs(entete_udp->dest);
  return port_dest;
}

void finger_ip(struct ip *ip, char *finger)
{
  char tmp[10];
  int old_lt = 0;

  /* ajouter le ttl finger buf */
  snprintf(tmp, sizeof(tmp), "%02X", ip->ip_ttl);
  memcpy(finger + FINGER_TTL, tmp, 2);

  /* ajouter le lt a finger buf */
  old_lt = strtoul(finger + FINGER_LT, NULL, 16); /* recuperer l'ancier lt qui etatit dans le buf au caus ou celui du tcp etait deja ajouté */
  snprintf(tmp, sizeof(tmp), "%02X", (ip->ip_hl*4) + old_lt);
  memcpy(finger + FINGER_LT, tmp, 2);

  /* ajouter le df a finger buf */
  if (ntohs(ip->ip_off) & IP_DF)
    {
      snprintf(tmp, sizeof(tmp), "%d", 1);
      memcpy(finger + FINGER_DF, tmp, 1);
    }
}

void finger_tcp(struct tcphdr *tcp, char *finger)
{
  char tmp[10];
  int old_lt = 0;
  unsigned char *opt_start, *opt_end;

  /* ajouter le windows finger buf */
  snprintf(tmp, sizeof(tmp), "%04X", tcp->th_win);
  memcpy(finger + FINGER_WINDOW, tmp, 4);

  /* Présence du flag  ACK*/
  if(tcp->th_flags & TH_ACK)
    {
      snprintf(tmp, sizeof(tmp), "%d", 1);
      memcpy(finger + FINGER_TCPFLAG, tmp, 1);
    }
  else
    {
      snprintf(tmp, sizeof(tmp), "%d", 0);
      memcpy(finger + FINGER_TCPFLAG, tmp, 1);
    }

  /* ajouter le lt a finger buf */
  old_lt = strtoul(finger + FINGER_LT, NULL, 16); /* recuperer l'ancier lt qui etatit dans le buf au caus ou celui du tcp etait deja ajouté */
  snprintf(tmp, sizeof(tmp), "%02X", (tcp->th_off*4) + old_lt);
  memcpy(finger + FINGER_LT, tmp, 2);

  /* Les option se trouve a la fin de l'entete tcp donc decaler le pointeur sur la structure tcp de 1 pour y accéder */
  opt_start = (unsigned char *)(tcp + 1);
  opt_end = (unsigned char*)tcp + tcp->th_off * 4;

  while (opt_start < opt_end)
    {
      switch (*opt_start)
	{
	case TCPOPT_EOL: 
	  /* end option EXIT */
	  opt_start = opt_end;
	  break;
	case TCPOPT_NOP:
	  snprintf(tmp, sizeof(tmp), "%d", 1);
	  memcpy(finger + FINGER_NOP, tmp, 1);
	  opt_start++;
	  break;
	case TCPOPT_SACK:
	  snprintf(tmp, sizeof(tmp), "%d", 1);
	  memcpy(finger + FINGER_SACK, tmp, 1);
	  opt_start += 2;
	  break;
	case TCPOPT_MAXSEG:
	  opt_start += 2;
	  snprintf(tmp, sizeof(tmp), "%04X", ntohs(*(uint16_t *)(opt_start)));
	  memcpy(finger + FINGER_MSS, tmp, 4);
	  opt_start += 2;
	  break;
	case TCPI_OPT_WSCALE:
	  opt_start += 2;
	  snprintf(tmp, sizeof(tmp), "%02X",  *opt_start);
	  memcpy(finger + FINGER_WS, tmp, 2);
	  opt_start++;
	  break;
	case TCPOPT_TIMESTAMP:
	  snprintf(tmp, sizeof(tmp), "%d", 1);
	  memcpy(finger + FINGER_TIMESTAMP, tmp, 1);
	  opt_start++;
	  if ((*opt_start) > 0)
	    opt_start += ((*opt_start) - 1);
	  break;
	default:
	  opt_start++;
	  if (*opt_start > 0)
	    opt_start += (*opt_start - 1);
	  break;
	}
    }
}

void sniffer(const uint8_t* packet, char *OS)
{
  struct ethernet *eth;
  struct ip *ip;
  struct tcphdr *tcp;
  int size_ip, size_tcp;
  char finger[FINGER_LEN+1];
  struct os_info *i;
  char *src, *dst;

  eth = (struct ethernet*) packet;
  
  /* Si c'est de l'IPv4 */
  if(ntohs(eth->ether_type) == IPv4_ETHERTYPE)
    {
      /* Récupéré l'entête ip */
      ip = (struct ip*) (packet + SIZE_ETHERNET);
	
      /* Verifie si c'est un paquet ip */
      if(ip->ip_v != 4)
	{
	  printf("pas paquet ip \n");
	  return;
	}
      
      /* Verifié la taille de l'entete ip */
      size_ip = ip->ip_hl * 4;
      if(size_ip < 20)
	{
	  printf("Longueur d'entete ip invalide : %d\n", ip->ip_hl);
	  return; 
	}

      /* Vérifié le protocole utilisé */
      if(ip->ip_p != IP_PROTO_TCP)
	{
	  printf("protocol non tcp utilisé \n");
	  return ; 
	}

      src = inet_ntoa(ip->ip_src);
      //      dst = inet_ntoa(ip->ip_dst);
      
      /* Récupéré l'entête tcp */
      tcp = (struct tcphdr*) (packet + SIZE_ETHERNET + size_ip);

      /* Vérifié la taille de l'entete tcp */
      size_tcp = tcp->th_off * 4;
      if(size_tcp < 20)
	{
	  printf("Longueur d'entete tcp invalide : %d\n", tcp->th_off);
	  return; 
	}

      strncpy(finger,"0000:_MSS:TT:WS:0:0:0:0:F:LT", 29);  

      finger_ip(ip, finger);
      finger_tcp(tcp, finger);

      printf("ip_src = %s \t \t finger = %s\n",src, finger);

      i = os_lookup(finger, 28);
      if(i) {
	strcpy(OS, i->os);
	printf("Trouve: %s\n", i->os);
      }
      else
	strcpy(OS, "");
    }
}

void obtenir_os(u_char *donnees_paquet, char *OS) {
  iphdr* entete_ip = trouver_entete_ip(donnees_paquet);
  if(entete_ip->ip_p == IPPROTO_TCP) {
    sniffer(donnees_paquet, OS);
  }
}

redisContext* connection(const char *adresse, const int port) {
  redisContext *lien = redisConnect(adresse, port);
  if(lien == NULL && lien->err)
    return NULL;
  return lien;
}

redisReply *nettoyer_bd(redisContext *lien) {
  redisReply *reponse = redisCommand(lien, "FLUSHALL");
  return reponse;
}

redisReply *creer_racine(redisContext *lien) {
  redisReply *reponse = redisCommand(lien, "JSON.SET %s . {}", RACINE);
  return reponse;
}

redisReply *creer_hote(redisContext *lien, char *adresse) {
  redisReply *reponse = redisCommand(lien, "JSON.SET %s [\"%s\"] {}", RACINE, adresse);
  return reponse;
}

redisReply *initialiser_port(redisContext *lien, int port, char *adresse) {
  redisReply *reponse = redisCommand(lien, "JSON.SET %s [\"%s\"].Port [%d]", RACINE, adresse, port);
  return reponse;
}

redisReply *ajouter_port(redisContext *lien, int port, char *adresse) {
  redisReply *reponse = redisCommand(lien, "JSON.ARRAPPEND %s [\"%s\"].Port %d", RACINE, adresse, port);
  return reponse;
}

redisReply *inserer_os(redisContext *lien, char *OS, char *adresse) {
  redisReply *reponse = redisCommand(lien, "JSON.SET %s [\"%s\"].OS \"%s\"", RACINE, adresse, OS);
  return reponse;
}

redisReply *inserer_paquets_emis(redisContext *lien, int nombre, char *adresse) {
  redisReply *reponse = redisCommand(lien, "JSON.SET %s [\"%s\"].PE %d", RACINE, adresse, nombre);
  return reponse;
}

redisReply *inserer_paquets_recus(redisContext *lien, int nombre, char *adresse) {
  redisReply *reponse = redisCommand(lien, "JSON.SET %s [\"%s\"].PR %d", RACINE, adresse, nombre);
  return reponse;
}

redisReply *inserer_associe(redisContext *lien, char *hote, char *associe) {
  redisReply *reponse = redisCommand(lien, "JSON.SET %s [\"%s\"].Assoc [\"%s\"]", RACINE, hote, associe);
  return reponse;
}

redisReply *ajouter_associe(redisContext *lien, char *hote, char *associe) {
  redisReply *reponse = redisCommand(lien, "JSON.ARRAPPEND %s [\"%s\"].Assoc \"%s\"", RACINE, hote, associe);
  return reponse;
}

redisReply *incrementer_paquet_emis(redisContext *lien, char *adresse) {
  int nombre;
  redisReply *reponse = redisCommand(lien, "JSON.GET %s [\"%s\"].PE", RACINE, adresse);
  nombre = atoi(reponse->str);
  nombre++;
  inserer_paquets_emis(lien, nombre, adresse);
  return reponse;
}

redisReply *incrementer_paquets_recus(redisContext *lien, char *adresse) {
  int nombre;
  redisReply *reponse = redisCommand(lien, "JSON.GET %s [\"%s\"].PR", RACINE, adresse);
  nombre = atoi(reponse->str);
  nombre++;
  inserer_paquets_recus(lien, nombre, adresse);
  return reponse;
}

int hote_existe_deja(redisContext *connection_bd, char *adresseIP) {
  redisReply *reponse;
  int i;
  reponse = redisCommand(connection_bd, "JSON.OBJKEYS %s", RACINE);
  for(i = 0; i < reponse->elements; i++) {
    if(strstr(reponse->element[i]->str, adresseIP) != NULL)
      return 0;
  }
  return 1;
}

int port_existe_deja(redisContext *lien, int port, char *adresse) {
  char chport[10];
  redisReply *reponse;
  sprintf(chport, "%d", port);
  reponse = redisCommand(lien, "JSON.GET %s [\"%s\"].Port", RACINE, adresse);	
  if(strstr(reponse->str, chport) == NULL)
    return 1;
  return 0;
}

int associe_existe_deja(redisContext *lien, char *hote, char *associe) {
  redisReply *reponse = redisCommand(lien, "JSON.GET %s [\"%s\"].Assoc", RACINE, hote);	
  if(strstr(reponse->str, associe) == NULL)
    return 1;
  return 0;
}

int os_existe(redisContext *lien, char *adresse) {
  redisReply *reponse = redisCommand(lien, "JSON.GET %s [\"%s\"].OS", RACINE, adresse);
  if((strstr(reponse->str, "ERR") != NULL) || (strcmp(reponse->str,"") == 0))
    return 1;
  return 0;
}

int adresse_dans_reseau(bpf_u_int32 subnet_mask, bpf_u_int32 ip_address, char *target_address) {
  // suppose we have declare ip and subnet mask variables and passed values to it.
  // bpf_u_int32 subnet_mask;
  // bpf_u_int32 ip_address;

  bpf_u_int32 x = subnet_mask;
  int numbits; // get the CIDR Prefix
  for (numbits = 0; x != 0; x >>= 1) {
    if (x & 0x01) {
      numbits++;
    }
  }

  // determine maximum and minimum host values.
  // we exclude the host and the broadcast (should we?)
  unsigned long hoststart;
  unsigned long hostend;
  hoststart = 1;
  hostend = (1 << (32 - numbits)) - 1;

  // mask off the network
  uint32_t network = htonl(ip_address & subnet_mask);

  // Calculate all host addresses in the range
  for (unsigned i = hoststart; i <= hostend; i++) {
    uint32_t hostip;
    int b1, b2, b3, b4;
    char ipstr[16];
    hostip = network + i;
    b1 = (hostip & 0xff000000) >> 24;
    b2 = (hostip & 0x00ff0000) >> 16;
    b3 = (hostip & 0x0000ff00) >> 8;
    b4 = (hostip & 0x000000ff);
    snprintf(ipstr, sizeof(ipstr), "%d.%d.%d.%d", b1, b2, b3, b4);
    if(strcmp(ipstr, target_address) == 0)
      return 0;
  }
  return 1;
}

void gestionnaire_paquet(u_char *arguments, entete_paquet *entete, u_char *donnees_paquet) {
  iphdr* entete_ip;
  entete_ethernet *entete_eth;
  char adresseIP_source[INET_ADDRSTRLEN], adresseIP_destination[INET_ADDRSTRLEN], OS[100];
  int port_source, port_dest, pq_emis = 0, pq_recus = 0;
  const char *adresse_bd = "127.0.0.1";
  const int port_bd = 6379;
  redisContext *connection_bd = connection(adresse_bd, port_bd);
  redisReply *reponse;
  entete_eth = trouver_entete_ether(donnees_paquet);
  if (ntohs(entete_eth->ether_type) == ETHERTYPE_IP) {
    entete_ip = trouver_entete_ip(donnees_paquet);
    obtenir_adresseIP_source(entete_ip, adresseIP_source);
    obtenir_adresseIP_dest(entete_ip, adresseIP_destination);
    printf("%s\t%s\n", adresseIP_source, adresseIP_destination);
    if(adresse_dans_reseau(masque_reseau, adresse_reseau, adresseIP_source) == 0) {
      if(hote_existe_deja(connection_bd, adresseIP_source) == 1) {
	creer_hote(connection_bd, adresseIP_source);
	if(entete_ip->ip_p == IPPROTO_TCP) {
	  port_source = obtenir_port_source_tcp(donnees_paquet);
	  initialiser_port(connection_bd, port_source, adresseIP_source);
	}
	else if(entete_ip->ip_p == IPPROTO_UDP) {
	  port_source = obtenir_port_source_udp(donnees_paquet);
	  initialiser_port(connection_bd, port_source, adresseIP_source);
	}
	obtenir_os(donnees_paquet, OS);
	inserer_os(connection_bd, OS, adresseIP_source);
	inserer_paquets_emis(connection_bd, ++pq_emis, adresseIP_source);
	if(adresse_dans_reseau(masque_reseau, adresse_reseau, adresseIP_destination) == 0)
	   inserer_associe(connection_bd, adresseIP_source, adresseIP_destination);
      }
      else {
	if(entete_ip->ip_p == IPPROTO_TCP) {
	  port_source = obtenir_port_source_tcp(donnees_paquet);
	  if(port_existe_deja(connection_bd, port_source, adresseIP_source) == 1)
	    ajouter_port(connection_bd, port_source, adresseIP_source);
	}
	else if(entete_ip->ip_p == IPPROTO_UDP) {
	  port_source = obtenir_port_source_udp(donnees_paquet);
	  if(port_existe_deja(connection_bd, port_source, adresseIP_source) == 1)
	    ajouter_port(connection_bd, port_source, adresseIP_source);
	}
	if(os_existe(connection_bd, adresseIP_source) == 1) {
	  obtenir_os(donnees_paquet, OS);
	  inserer_os(connection_bd, OS, adresseIP_source);
	}
	incrementer_paquet_emis(connection_bd, adresseIP_source);
	if(associe_existe_deja(connection_bd, adresseIP_source, adresseIP_destination) == 1) {
	  if(adresse_dans_reseau(masque_reseau, adresse_reseau, adresseIP_destination) == 0)
	     ajouter_associe(connection_bd, adresseIP_source, adresseIP_destination);
	}
      }
    }

    if(adresse_dans_reseau(masque_reseau, adresse_reseau, adresseIP_destination) == 0) {
      if(hote_existe_deja(connection_bd, adresseIP_destination) == 1) {
	creer_hote(connection_bd, adresseIP_destination);
	if(entete_ip->ip_p == IPPROTO_TCP) {
	  port_dest = obtenir_port_dest_tcp(donnees_paquet);
	  initialiser_port(connection_bd, port_dest, adresseIP_destination);
	}
	else if(entete_ip->ip_p == IPPROTO_UDP) {
	  port_dest = obtenir_port_dest_udp(donnees_paquet);
	  initialiser_port(connection_bd, port_dest, adresseIP_destination);
	}
	inserer_paquets_recus(connection_bd, ++pq_recus, adresseIP_destination);
	if(adresse_dans_reseau(masque_reseau, adresse_reseau, adresseIP_source) == 0)
	   inserer_associe(connection_bd, adresseIP_destination, adresseIP_source);
      }
      else {
	if(entete_ip->ip_p == IPPROTO_TCP) {
	  port_dest = obtenir_port_dest_tcp(donnees_paquet);
	  if(port_existe_deja(connection_bd, port_dest, adresseIP_destination) == 1)
	    ajouter_port(connection_bd, port_dest, adresseIP_destination);
	}
	else if(entete_ip->ip_p == IPPROTO_UDP) {
	  port_dest = obtenir_port_dest_udp(donnees_paquet);
	  if(port_existe_deja(connection_bd, port_dest, adresseIP_destination) == 1)
	    ajouter_port(connection_bd, port_dest, adresseIP_destination);
	}
	incrementer_paquets_recus(connection_bd, adresseIP_destination);
	if(associe_existe_deja(connection_bd, adresseIP_destination, adresseIP_source) == 1) {
	  if(adresse_dans_reseau(masque_reseau, adresse_reseau, adresseIP_source) == 0)
	     ajouter_associe(connection_bd, adresseIP_destination, adresseIP_source);
	}
      }
    }
  }
  redisFree(connection_bd);
}

void trouver_interface(char *nom) {
  char *peripherique, chaine_derreur[PCAP_ERRBUF_SIZE];
  peripherique = pcap_lookupdev(chaine_derreur);
  strcpy(nom, peripherique);
}

void adresse_interface(bpf_u_int32 ip_brute, char *adresse) {
  struct in_addr adr;
  adr.s_addr = ip_brute;
  strcpy(adresse, inet_ntoa(adr));
}

void masque_interface(bpf_u_int32 masque_brute, char *masque) {
  struct in_addr adr;
  adr.s_addr = masque_brute;
  strcpy(masque, inet_ntoa(adr));
}

int adresses_interface(char *interface, bpf_u_int32 *ip_brute, bpf_u_int32 *masque_brute) {
  char chaine_derreur[PCAP_ERRBUF_SIZE];
  int retour = pcap_lookupnet(interface, ip_brute, masque_brute, chaine_derreur);
  adresse_reseau = *ip_brute;
  masque_reseau = *masque_brute;
  return retour;
}

void lancer_capture(char *interface, int duree_decoute, pcap_handler gestionnaire_paquet) {
  char chaine_derreur[PCAP_ERRBUF_SIZE];
  pcap_t *prise = pcap_open_live(interface, BUFSIZ, 0, duree_decoute, chaine_derreur);
  pcap_loop(prise, QPAQUET, gestionnaire_paquet, NULL);
}

