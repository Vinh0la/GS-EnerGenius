# EnerGenius IoT Energy Monitor

Este projeto utiliza o ESP32 para monitorar e controlar o consumo de energia elétrica em ambientes residenciais ou comerciais. Ele também publica os dados coletados em um dashboard do ThingSpeak para visualização em tempo real.

## 🛠️ **Componentes Utilizados**
- **ESP32**
- **Sensor de corrente (via potenciômetro simulado)**
- **Sensor de presença PIR**
- **Relé**
- **LEDs indicativos (verde, amarelo, vermelho)**
- **Resistores (220 kΩ)**

### ⚙️ **Circuito**
![Diagrama do Circuito](https://github.com/user-attachments/assets/78deaf41-9739-40bd-a428-0a2f949846c3)

---

## 📋 **Funcionalidades**

1. **Monitoramento de Energia**:
   - Mede a corrente consumida (simulada por um potenciômetro).
   - Calcula o consumo total acumulado.

2. **Indicação Visual**:
   - LEDs indicam os níveis de consumo:
     - **Verde**: Consumo ≤ 110V.
     - **Amarelo**: Consumo entre 110V e 199V.
     - **Vermelho**: Consumo > 199V.

3. **Controle de Dispositivos**:
   - Aciona um relé se a sala estiver ocupada (detectada pelo sensor PIR).

4. **Envio de Dados ao ThingSpeak**:
   - Publica dados como corrente, consumo total e status de ocupação.

---

## 🚀 **Como Replicar o Projeto**

1. **Clone o Repositório**
   ```bash
   git clone https://github.com/SEU_USUARIO/iot-energy-monitor.git

### **Abra no Simulador Wokwi**
1. Acesse o [Wokwi](https://wokwi.com).
2. Clique em **ESP32**.
3. No editor, copie e cole o `diagram.json` para carregar o circuito completo.

---

### **Configurações do ThingSpeak**
1. Abra o código no editor do Wokwi.
2. Substitua a linha com `#define THINGSPEAK_API_KEY` pela sua própria chave de API:
   ```cpp
   #define THINGSPEAK_API_KEY "SUA_API_KEY"

---

### **Compile e Execute**
1. No simulador Wokwi, clique no botão **"Play"** para iniciar a simulação.
2. Verifique os logs no monitor serial para validar as medições e o envio de dados para o ThingSpeak.

---

### **Visualização no ThingSpeak**
1. Crie uma conta no [ThingSpeak](https://thingspeak.com).
2. Configure um canal:
   - Acesse **"Channels" > "New Channel"**.
   - Adicione três campos:
     - **Field 1**: consumo_total.
     - **Field 2**: corrente.
     - **Field 3**: ocupacao.
3. Copie a **API Key** do canal e insira no código.
4. Configure os Widgets por sua preferência, os widgets utilizados pelo grupo estão disponiveis no arquivo .txt "Link ThingSpeak" e podem vê-lo na captura de tela abaixo.

---

### **Exemplo de Dados no ThingSpeak**
Os dados são enviados automaticamente para o ThingSpeak, permitindo a visualização em gráficos em tempo real no painel do canal.

---

### **Screenshots**
#### **Dashboard no ThingSpeak**
![Dashboard no ThingSpeak](https://github.com/user-attachments/assets/dd6a4070-6bda-4f32-a3a5-a505372ed384)


