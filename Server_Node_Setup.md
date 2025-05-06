# Raspberry Pi IoT Server using Docker (MQTT, Node-RED, InfluxDB, Grafana)

This guide walks you through setting up a Raspberry Pi IoT server using Docker containers with the help of [IoTStack](https://github.com/SensorsIot/IOTstack). It includes:

-  Mosquitto (MQTT Broker)  
-  Node-RED (Flow-based programming)  
-  InfluxDB (Time-Series Database)  
-  Grafana (Data Visualization)  
-  Portainer-CE (Docker GUI Manager) : Optional

## ✅ Requirements

- Raspberry Pi 4  
- Raspberry Pi OS 64-bit Lite (headless preferred)  
- SSH access to your Pi  
- Internet connection
- Sensor Node (ESP32 with BME280 Sensor)

## 🛠️ Setup Steps

### 1. Update Your Pi

```bash
sudo apt update
sudo apt upgrade
```

### 2. Install IoTStack

```bash
curl -fsSL https://raw.githubusercontent.com/SensorsIot/IOTstack/master/install.sh | bash
sudo shutdown -r now
```

### 3. Configure the Stack

After rebooting your Pi:

```bash
cd IOTstack/
./menu.sh
```

In the menu:
- Use arrow keys to navigate
- Space bar to select the following:
  - Mosquitto
  - Node-RED
  - InfluxDB
  - Grafana
  - Portainer-CE
- Press Enter to generate the `docker-compose.yml`

### 4. Start the Stack

```bash
docker-compose up -d
docker-compose ps
```

### 5. Create InfluxDB Database

```bash
docker exec -it influxdb influx
```

Inside the Influx shell:

```sql
CREATE DATABASE sensor_data;
quit;
```

### 6. Node-RED JSON Function

Use this function node in Node-RED:

```javascript
return {
    payload: {
        temperature: msg.payload.t,
        pressure: msg.payload.p,
        humidity: msg.payload.h,
    }
};
```

### 7. Check Data in InfluxDB

```bash
docker exec -it influxdb influx
```

Then:

```sql
USE sensor_data;
SHOW MEASUREMENTS;
SELECT * FROM sensor_data;
quit;
```

### 8. Setup the Dashboard
- Log into the Grafana
- Customize your Weather station dashboard as you prefer

## 🌐 Web Interfaces

| Service      | Default URL                         |
|--------------|-------------------------------------|
| Node-RED     | http://<raspberry_pi_ip>:1880       |
| Grafana      | http://<raspberry_pi_ip>:3000       |
| Portainer    | http://<raspberry_pi_ip>:9000       |
| Mosquitto    | MQTT Broker on port 1883            |
| InfluxDB     | Port 8086                           |


## 📦 Credits

- IoTStack by [@SensorsIot](https://github.com/SensorsIot/IOTstack)
