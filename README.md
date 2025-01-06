# Projets Arduino pour ECG et passerelle IoT

## Description

Ce dépôt contient deux projets Arduino pour des cas d'utilisation différents :

1. **ecg.ino** : Un programme qui simule une sortie PWM basée sur une séquence et ajuste dynamiquement son rythme à l'aide d'un potentiomètre.
2. **passerelle.ino** : Un programme passerelle pour lire les signaux ECG, calculer la fréquence cardiaque et envoyer des notifications via LoRa vers The Things Network (TTN).

---

## Détails des projets

### ecg.ino
Ce programme génère une séquence de signaux analogiques sur une broche PWM, simulant des formes d'onde ECG, tout en permettant à l'utilisateur d'ajuster le rythme de répétition à l'aide d'un potentiomètre.

**Fonctionnalités :**
- Lit les valeurs d'un potentiomètre pour contrôler le temps de délai.
- Produit des signaux PWM basés sur une séquence prédéfinie (`val[]`).
- Fournit un retour visuel via une LED intégrée.

**Matériel requis :**
- Une carte Arduino (par exemple, Uno).
- Un potentiomètre connecté à la broche analogique A0.
- Une LED connectée à la broche 13.
- Un dispositif ou circuit connecté à la broche PWM 9.

### passerelle.ino
Ce programme détecte les battements cardiaques, calcule la fréquence cardiaque (en BPM) et envoie des notifications à TTN via un module LoRa.

**Fonctionnalités :**
- Lit les signaux ECG à partir d'une entrée analogique.
- Calcule les intervalles de temps entre les battements pour en déduire la fréquence cardiaque.
- Envoie des notifications à TTN lorsque la fréquence cardiaque dépasse un seuil (100 BPM).
- Détecte et signale la déconnexion des câbles ECG.

**Matériel requis :**
- Une carte Arduino compatible avec un module LoRa (par exemple, MKR WAN 1310).
- Un capteur ECG connecté à la broche analogique A0.
- Un module LoRa configuré pour TTN (plan de fréquence EU868).
- Des fils connectés aux broches 8 et 9 pour la détection des câbles.

---

## Installation et utilisation

1. Clonez ce dépôt sur votre machine locale.
   ```bash
   git clone https://github.com/martinpdf/arduino-ecg-iot.git
   ```

2. Ouvrez le fichier `.ino` correspondant dans l'IDE Arduino.

3. Sélectionnez la carte et le port appropriés dans l'IDE Arduino.

4. Téléversez le programme sur votre carte Arduino.

5. Connectez les composants matériels requis comme décrit ci-dessus.

6. Surveillez la sortie via le moniteur série de l'IDE Arduino.

---

## Fonctionnement

### ecg.ino
Le programme lit la valeur du potentiomètre à l'aide de `analogRead()` et la convertit en un délai compris entre 150 ms et 1000 ms. Ensuite, il parcourt le tableau `val[]` pour générer des signaux PWM sur la broche 9 et allume la LED sur la broche 13 pendant l'exécution de la séquence.

### passerelle.ino
Le programme lit les signaux ECG depuis la broche A0 et calcule la fréquence cardiaque en fonction des intervalles entre les pics. Si la fréquence cardiaque dépasse un seuil prédéfini, une notification est envoyée à TTN via LoRa. Les broches 8 et 9 surveillent les connexions des câbles ECG et signalent toute déconnexion.
