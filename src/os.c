#include <os.h>

char finger[FINGER_LEN+1];

void* initialize_sniffer(void*)
{
  pcap_t *handle; /* Descripteur de session */ 
  char *dev; /* Le peripherique à renifler */ 
  char errbuf[PCAP_ERRBUF_SIZE]; /* Chaîne d'erreur */ 
  struct pcap_pkthdr header ; /* L'en-tête que pcap nous donne */ 
  const uint8_t *packet; /* Le paquet réel */ 


  /* Définit le périphérique */ 
  dev = pcap_lookupdev(errbuf); 
  if (dev == 0)
    { 
      fprintf(stderr, "Impossible de trouver le périphérique par défaut : %s : %s\n", dev, errbuf);
      return 0; 
    }

  /* Ouvre la session en mode promiscuité */ 
  handle = pcap_open_live(dev, BUFSIZ, 1, 0, errbuf); 
  if (handle == 0)
    { 
      fprintf(stderr, "Impossible d'ouvrir le périphérique %s : %s\n", dev, errbuf); 
      return 0; 
    } 
  	
  pcap_loop(handle, 0, sniffer, 0);
}


void sniffer(const struct pcap_pkthdr* pkthdr, const uint8_t* packet);
{
  struct ethernet *eth;
  struct ip *ip;
  struct tcphdr *tcp;

  eth = (struct ethernet*) packet;

  /* Si c'est de l'IPv4 */
  if(ntohs(eth->ether_type) == IPv4_ETHERTYPE)
    {
      /* Récupéré l'entête ip */
      ip = (struct ip*) (packet + SIZE_ETHERTYPE);
      
      /* Verifie si c'est un paquet ip */
      if(ip->v != 4)
	  return;
      
      /* Verifié la taille de l'entete ip */
      if(ip->hl < 20)
	{
	  fprintf(stderr, "Longueur d'entete ip invalide : %d\n", ip->hl);
	  return; 
	}

      /* Vérifié le protocole utilisé */
      if(ip->p != IP_PROTO_TCP)
	{
	  fprintf(stderr, "Protocol non tcp utilisé \n", ip->hl);
	  return ; 
	}

      /* Récupéré l'entête tcp */
      tcp = (struct tcp*) (packet + SIZE_ETHERTYPE + ip->hl);

      /* Vérifié la taille de l'entete tcp */
      if(tcp->th_off < 20)
	{
	  fprintf(stderr, "Longueur d'entete tcp invalide : %d\n", tcp->th_off);
	  return; 
	}

      finger_ip(ip);
      finger_tcp(tcp);
    }
}


void finger_ip(struct ip *ip)
{
}

void finger_tcp(struct tcphdr *tcp)
{
}


char* os(finger)
{
}
