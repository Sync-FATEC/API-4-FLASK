# Sistema de Monitoramento Ambiental - Broker

<div align="center">
  <h3>🌿 TecSus - Monitoramento Ambiental</h3>
  <p>Sistema broker para integração de dados das estações meteorológicas</p>
  
  ![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
  ![MQTT](https://img.shields.io/badge/MQTT-3C5280?style=for-the-badge&logo=eclipse-mosquitto&logoColor=white)
  ![MongoDB](https://img.shields.io/badge/MongoDB-4EA94B?style=for-the-badge&logo=mongodb&logoColor=white)
  ![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)
</div>

<div align="center">
  <a href="#-sobre">Sobre</a> •
  <a href="#-tecnologias">Tecnologias</a> •
  <a href="#-funcionalidades">Funcionalidades</a> •
  <a href="#-como-executar">Execução</a> •
  <a href="#-estrutura">Estrutura</a> •
  <a href="#-time">Time</a>
</div>

## 📋 Sobre

O Sistema de Monitoramento Ambiental é uma solução completa desenvolvida para a TecSus, focada no gerenciamento e monitoramento de dados ambientais. O broker é responsável por:

- Integração entre estações meteorológicas e o sistema de armazenamento
- Recepção e processamento de dados dos sensores via MQTT
- Armazenamento de medições em banco de dados MongoDB
- Simulação de estações para ambiente de desenvolvimento

## 🚀 Tecnologias

### Core
- **Python** (v3.9+) - Linguagem de programação versátil e robusta
- **MQTT** - Protocolo de mensageria leve para IoT
- **MongoDB** - Banco de dados NoSQL para armazenamento das medições
- **Docker** - Containerização da aplicação

### Principais Dependências
- **Paho-MQTT** (v2.1.0) - Cliente MQTT para Python
- **PyMongo** (v4.12.0) - Driver MongoDB para Python
- **Python-Dotenv** (v1.1.0) - Gerenciamento de variáveis de ambiente
- **DNSPython** (v2.7.0) - Resolução DNS para conexão com MongoDB

### Arquitetura e Padrões
- **Pub/Sub** - Padrão de comunicação Publisher/Subscriber via MQTT
- **Event-Driven** - Processamento baseado em eventos
- **Document Store** - Armazenamento de dados em formato de documentos no MongoDB
- **IoT Gateway** - Ponte entre dispositivos IoT e sistemas de armazenamento

## ⚙️ Funcionalidades

### 1. Recepção de Dados via MQTT
- Subscrição no tópico `fatec/api/sync/`
- Processamento de mensagens JSON
- Decodificação e validação de payloads
- Tratamento de eventos de conexão e reconexão

### 2. Armazenamento no MongoDB
- Conexão com banco de dados configurável via variáveis de ambiente
- Inserção de medições na coleção "measures"
- Armazenamento de dados no formato nativo JSON/BSON
- Suporte a alta taxa de inserções

### 3. Simulação de Estações
- Script dedicado para emular estações meteorológicas
- Geração de dados aleatórios para diferentes parâmetros
- Suporte a múltiplas estações com IDs únicos (UUID)
- Configuração de parâmetros como temperatura, umidade, pressão, etc.

### 4. Configuração Flexível
- Configuração via variáveis de ambiente
- Conexão com brokers MQTT públicos ou privados
- Personalização de conexão com MongoDB
- Execução standalone ou via container

## 🚦 Como Executar

### Pré-requisitos
- Python 3.9 ou superior
- Pip (gerenciador de pacotes Python)
- Acesso a um broker MQTT (padrão: test.mosquitto.org)
- Acesso a um servidor MongoDB
- Docker (opcional)

### Instalação

1. Clone o repositório
```bash
git clone https://github.com/Sync-FATEC/API-2025.1-4SEM.git
cd API-2025.1-4SEM/broker
```

2. Instale as dependências
```bash
pip install -r requirements.txt
```

3. Configure o ambiente
```bash
# Crie um arquivo .env com as seguintes variáveis
MONGO_URL=mongodb+srv://seu_usuario:sua_senha@seu_cluster.mongodb.net
MONGO_DB_NAME=seu_banco_de_dados
```

4. Inicie o broker
```bash
# Execução do broker principal
python main.py

# Simulação de dados (em outro terminal)
python simulate/simulate_data.py
```

### Scripts Disponíveis
- `python main.py`: Inicia o broker MQTT para receber dados
- `python simulate/simulate_data.py`: Simula o envio de dados de estações

## 📁 Estrutura de Diretórios
```
broker/
├── main.py          # Aplicação principal do broker
├── requirements.txt # Dependências do projeto
├── .env             # Variáveis de ambiente (não versionado)
└── simulate/        # Scripts de simulação de dados
    └── simulate_data.py # Gerador de dados simulados
```

## 👥 Time

| Nome | Função |
|------|--------|
| João Gabriel Solis | Scrum Master |
| Ana Laura Moratelli | Product Owner |
| Ana Clara Marques | Desenvolvedora |
| Erik Yokota | Desenvolvedor |
| Filipe Colla | Desenvolvedor |
| Kauê Francisco | Desenvolvedor |

## 📄 Licença

Este projeto está sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes. 
