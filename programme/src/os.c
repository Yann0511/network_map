#include "../include/os.h"

/*void* initialize_sniffer(void*)*/
int main(void)
{
  pcap_t *handle; /* Descripteur de session */ 
  char *dev; /* Le peripherique à renifler */ 
  char errbuf[PCAP_ERRBUF_SIZE]; /* Chaîne d'erreur */
  struct bpf_program fp; /* Le filtre compilé */ 
  char filter_exp[] = "tcp"; /* L'expression du filtre */ 
  bpf_u_int32 mask; /* Notre masque de réseau */ 
  bpf_u_int32 net; /* Notre adresse IP */ 
  struct pcap_pkthdr header ; /* L'en-tête que pcap nous donne */ 
  const u_char *packet; /* Le paquet réel */ 
  
  
  /* Définit le périphérique */ 
  dev = pcap_lookupdev(errbuf); 
  if (dev == 0)
    { 
      printf("Impossible de trouver le périphérique par défaut : %s : %s\n", dev, errbuf);
      return 84; 
    }

  /* Trouver les propriétés du périphérique */ 
  if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
    { 
      printf("Impossible d'obtenir le masque de réseau pour le périphérique %s : %s\n", dev, errbuf); 
      net = 0 ; 
      mask = 0 ; 
    }

  /* Ouvre la session en mode promiscuité */ 
  handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf); 
  if (handle == 0)
    { 
      printf("Impossible d'ouvrir le périphérique %s : %s\n", dev, errbuf); 
      return 84; 
    }


  /* Compile et applique le filtre */ 
  if (pcap_compile(handle, &fp, filter_exp, 0x100, net) == -1)
    { 
      printf("Impossible de compiler le filter %s: %s\n", filter_exp , pcap_geterr(handle));
    }
  
  if (pcap_setfilter(handle, &fp) == -1)
    { 
      printf("Impossible d'installer le filtre %s : %s\n", filter_exp, pcap_geterr(handle)); 
      return 1; 
    } 
  
  //  pcap_loop(handle, -1, sniffer, 0);

  while(1)
    {

      packet = pcap_next(handle, &header);
    
      sniffer(&header, packet);
    }
    
  return 0;
}


void sniffer(const struct pcap_pkthdr* pkthdr, const uint8_t* packet)
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
      if(i)
	printf("%s \n", i->os);

    }
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
