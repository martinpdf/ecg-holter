#include <TheThingsNetwork.h>

// Configuration TTN
const char *appEui = "0202020202020202"; // Remplacez par votre AppEUI
const char *appKey = "052995BE6876D536CF917A5C99917324"; // Remplacez par votre AppKey

#define loraSerial Serial1
#define debugSerial Serial
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

// Variables pour la détection de fréquence cardiaque
unsigned long lastBeatTime = 0; // Temps du dernier battement
unsigned long currentTime = 0; // Temps actuel
int beatThreshold = 550; // Seuil pour détecter un battement
int previousReading = 0; // Lecture précédente d'A0
int currentReading = 0; // Lecture actuelle d'A0
unsigned long beatInterval = 0; // Intervalle entre les battements (en ms)
float heartRate = 0.0; // Fréquence cardiaque en BPM

// Variables pour la gestion des notifications
bool sendNotification = false;
uint16_t notificationBPM = 0;

void setup() {
  // Initialisation des ports série
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Attendre un maximum de 10s pour le moniteur série
  while (!debugSerial && millis() < 10000);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  // Initialisation des broches pour la détection
  pinMode(8, INPUT); // Détection leads off LO +
  pinMode(9, INPUT); // Détection leads off LO -
}

void loop() {
  // Lecture de la valeur de A0
  currentReading = analogRead(A0);

  // Détecter un battement lorsque la lecture dépasse le seuil
  if (currentReading > beatThreshold && previousReading <= beatThreshold) {
    currentTime = millis(); // Enregistrer l'heure du battement

    // Si c'est le premier battement, on ne peut pas encore calculer la fréquence
    if (lastBeatTime > 0) {
      // Calculer l'intervalle entre les battements en ms
      beatInterval = currentTime - lastBeatTime;

      // Calcul de la fréquence cardiaque (BPM)
      heartRate = 60000.0 / beatInterval;

      // Afficher la fréquence cardiaque
      debugSerial.print("Fréquence cardiaque: ");
      debugSerial.print(heartRate);
      debugSerial.println(" BPM");

      // Si la fréquence cardiaque dépasse 100 BPM, préparer une notification
      if (heartRate > 100.0 && !sendNotification) {
        notificationBPM = (uint16_t)heartRate;
        sendNotification = true; // Activer l'envoi en arrière-plan
      }
    }

    // Mettre à jour le temps du dernier battement
    lastBeatTime = currentTime;
  }

  // Mise à jour de la lecture précédente
  previousReading = currentReading;

  // Vérification si les câbles sont déconnectés
  if ((digitalRead(8) == 1) || (digitalRead(9) == 1)) {
    debugSerial.println("Leads off!");
  }

  // Gestion asynchrone des notifications
  if (sendNotification) {
    sendHeartRateNotification(notificationBPM);
    sendNotification = false; // Notification envoyée
  }

  delay(10); // Attendre un peu avant de lire à nouveau
}

// Fonction pour envoyer une notification via TTN
void sendHeartRateNotification(uint16_t bpm) {
  // Préparer la charge utile (2 octets pour le BPM)
  byte payload[2];
  payload[0] = highByte(bpm);
  payload[1] = lowByte(bpm);

  // Envoyer la charge utile via LoRa
  debugSerial.println("Envoi de la notification...");
  ttn.sendBytes(payload, sizeof(payload));
  debugSerial.println("Notification envoyée !");
}
