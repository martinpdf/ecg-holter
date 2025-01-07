# Projet IoT Holter Connecté

## Description

Ce projet vise à concevoir un système IoT de surveillance cardiaque basé sur deux cartes Arduino et une communication LoRa via The Things Network (TTN). Le dispositif mesure la fréquence cardiaque, détecte les anomalies comme les tachycardies ou bradycardies, et envoie des alertes en cas de dépassement de seuils définis. Les données collectées sont ensuite stockées dans une base PostgreSQL pour un suivi médical.

## Détails des fichiers

### `ecg.ino`
Programme Arduino simulant des signaux cardiaques avec une sortie PWM. 
- **Utilisation principale** : Génère une séquence analogique pour simuler des battements cardiaques réglables via un potentiomètre.
- **Matériel requis** : Arduino Uno, potentiomètre, LED, circuit électronique pour signal.

### `passerelle.ino`
Programme de surveillance et transmission des données ECG.
- **Utilisation principale** : Lit les données d'un capteur ECG, calcule la fréquence cardiaque et envoie des notifications via LoRaWAN.
- **Matériel requis** : Arduino Leonardo avec module LoRa, capteur ECG, passerelle TTN.

---

## Installation et Configuration

### Prérequis
1. **Matériel** :
   - Arduino Uno et Leonardo.
   - Module LoRa compatible (par ex. MKR WAN 1310).
   - Potentiomètre, LED et câbles.
   - Capteur ECG.

2. **Logiciels** :
   - Arduino IDE (pour téléverser le code).
   - Node-RED (pour le traitement des données).
   - PostgreSQL (pour le stockage des données).
   - Compte TTN actif.

---

### Étape 1 : Téléchargement du code source
Clonez ce dépôt GitHub :
```bash
git clone https://github.com/martinpdf/ecg-holter.git
```

---

### Étape 2 : Configuration Arduino
1. **Ouvrir les fichiers** `ecg.ino` et `passerelle.ino` dans l’IDE Arduino.
2. **Configurer le matériel** :
   - Connectez le circuit ECG et le potentiomètre aux broches spécifiées dans chaque programme.
3. **Téléverser le code** :
   - Sélectionnez la carte appropriée et téléversez chaque fichier `.ino` sur les cartes correspondantes.

---

### Étape 3 : Configuration TTN
1. Créez une application sur TTN et configurez les identifiants (`AppEUI`, `DevEUI`, `AppKey`).
2. Enregistrez votre dispositif en sélectionnant les paramètres LoRa adaptés à votre région (Europe 863-870 MHz).
3. Ajoutez un décodeur de données (`Payload Formatters`) pour extraire et interpréter les valeurs BPM transmises par LoRa.

---

### Étape 4 : Configuration Node-RED
1. Installez Node-RED :
   ```bash
   sudo apt update && sudo apt install -y nodejs npm
   sudo npm install -g --unsafe-perm node-red
   ```
2. Lancez Node-RED :
   ```bash
   node-red
   ```
3. Configurez les flux pour recevoir les données MQTT depuis TTN, décodez les valeurs BPM et affichez-les dans un tableau de bord.

---

### Étape 5 : Configuration PostgreSQL
1. Installez PostgreSQL :
   ```bash
   sudo apt install -y postgresql postgresql-contrib
   ```
2. Créez une base et une table :
   ```sql
   CREATE DATABASE ecg_data;
   CREATE TABLE ecg_data (
       id SERIAL PRIMARY KEY,
       timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       bpm INT NOT NULL
   );
   ```
3. Configurez Node-RED pour envoyer les données décodées dans cette base.

---

## Fonctionnement
1. **ecg.ino** : Génère des signaux cardiaques simulés via une sortie PWM.
2. **passerelle.ino** : Lit les données ECG, calcule le BPM et transmet les alertes via LoRa.
3. **TTN** : Traite les données LoRaWAN et transmet les informations décodées.
4. **Node-RED** : Surveille les BPM en temps réel et affiche un historique.
5. **PostgreSQL** : Stocke les données pour un suivi à long terme.

---

## Lien vers le dépôt
Pour consulter ou contribuer au projet : [GitHub](https://github.com/martinpdf/ecg-holter/)
