#include "librairie.h"

int main() {
  peripherique p1;
  char interface[10];
  bpf_u_int32 ip_brute, masque_brute;
  int duree_decoute = 10000;
  const char *adresse_bd = "127.0.0.1";
  const int port_bd = 6379;
  redisContext *connection_bd = connection(adresse_bd, port_bd);
  nettoyer_bd(connection_bd);
  creer_racine(connection_bd);
  redisFree(connection_bd);
  trouver_interface(p1.nom);
  strcpy(interface, p1.nom);
  adresses_interface(interface, &ip_brute, &masque_brute);
  adresse_interface(ip_brute, p1.adresse_ip);
  masque_interface(masque_brute, p1.masque_sous_reseau);
  printf("Interface\tAdresse\t\tMasque\n");
  printf("%s\t\t%s\t%s\n\n", p1.nom, p1.adresse_ip, p1.masque_sous_reseau);
  printf("Source\t\tDestination\n");
  lancer_capture(interface, duree_decoute, (pcap_handler) gestionnaire_paquet);
  return 0;
}
