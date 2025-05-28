# Sistema CRUD em C++

Este projeto é um sistema CRUD (Create, Read, Update, Delete) básico implementado em C++, demonstrando uma arquitetura em camadas com forte separação de preocupações e uso de adaptadores para flexibilidade. Ele foi projetado para ser agnóstico em relação à camada de I/O (entrada/saída) e ao sistema de persistência de dados.

## Estrutura do Projeto

```
cppcrudbp/
├── CMakeLists.txt            # Configuração de build do projeto
├── docker-compose.yml        # Configuração Docker Compose
├── Dockerfile                # Definição do contêiner Docker
├── include/                  # Arquivos de cabeçalho (headers)
├── pgadminservers.json       # Configuração do PGAdmin
├── README.md                 # Documentação do projeto
├── run.sh                    # Script para execução rápida
├── sql/                      # Scripts SQL para configuração do banco
└── src/                      # Código-fonte da aplicação
    ├── application/          # Camada de aplicação (casos de uso)
    ├── common/               # Funcionalidades compartilhadas
    │   └── db_connection.cpp # Gerenciamento de conexão com BD
    ├── domain/               # Camada de domínio (entidades)
    ├── infrastructure/       # Implementações de interfaces
    ├── main.cpp              # Ponto de entrada da aplicação
    └── presentation/         # Camada de apresentação (UI/API)
```

## Arquitetura

O sistema segue princípios de Clean Architecture/Arquitetura Hexagonal, dividindo o código em camadas distintas:

* **Camada de Domínio (`src/domain`):** O coração da aplicação. Contém as entidades de negócio (`User`), objetos de valor e interfaces de repositório (`IUserRepository`). É totalmente independente de qualquer tecnologia ou framework.

* **Camada de Aplicação (`src/application`):** Orquestra as operações de negócio (casos de uso). Contém os serviços (`UserService`) que utilizam as interfaces de repositório e os DTOs (Data Transfer Objects) para comunicação entre as camadas.

* **Camada de Infraestrutura (`src/infrastructure`):** Fornece as implementações concretas para as interfaces definidas nas camadas de Domínio e Aplicação. Inclui a implementação do repositório PostgreSQL (`PostgreSQLUserRepository`).

* **Camada de Apresentação (`src/presentation`):** Lida com a interação do usuário e a exibição de informações. Inclui adaptadores para diferentes tipos de interação (CLI, HTTP - simulado) e controladores que traduzem as requisições para o Serviço da Aplicação.

* **Camada Comum (`src/common`):** Contém funcionalidades compartilhadas entre as diferentes camadas, como conexão com banco de dados.

**Princípios Chave:**

* **Inversão de Dependência:** As camadas de Domínio e Aplicação dependem de abstrações (interfaces), que são implementadas pela camada de Infraestrutura.

* **Injeção de Dependência:** As dependências são fornecidas aos componentes (geralmente via construtores), tornando o código mais testável e modular.

* **Configuração Externa:** O comportamento da aplicação é configurado através de arquivos externos, permitindo a seleção de diferentes adaptadores de persistência e I/O em tempo de execução.

## Tecnologias Utilizadas

* **C++17:** Linguagem de programação principal.

* **CMake:** Sistema de build para gerenciar a compilação e as dependências.

* **Docker/Docker Compose:** Para containerização e facilidade de ambiente de desenvolvimento.

* **PostgreSQL:** Sistema de gerenciamento de banco de dados relacional.

* **libpqxx:** Biblioteca C++ para interação com bancos de dados PostgreSQL.

## Pré-requisitos

Para construir e executar este projeto, você tem duas opções:

### Usando Docker (Recomendado)

* **Docker** e **Docker Compose** instalados no seu sistema.

1. Execute o ambiente completo com:
   ```bash
   docker-compose up
   ```

2. O sistema estará disponível e conectado ao PostgreSQL automaticamente.

### Instalação Local

* Um compilador C++ (GCC, Clang, MSVC) que suporte C++17.
* **CMake** (versão 3.10 ou superior).
* **libpqxx**: A biblioteca cliente C++ para PostgreSQL.
    * No Debian/Ubuntu: `sudo apt-get install libpqxx-dev`
    * No macOS (Homebrew): `brew install libpqxx`
    * No Windows: Baixe e instale a biblioteca ou use um gerenciador de pacotes como `vcpkg`.
* Um servidor **PostgreSQL** em execução.

## Configuração do Banco de Dados

Os scripts para configuração do banco de dados estão disponíveis no diretório `sql/`. Eles criam o banco de dados e a tabela `users` necessária para a aplicação.

Se estiver executando localmente:

1. Conecte-se ao seu servidor PostgreSQL (e.g., `psql -U postgres`).
2. Execute os scripts SQL encontrados no diretório `sql/`.

## Compilação e Execução (Instalação Local)

1. Configure o projeto com CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   ```

2. Compile o projeto:
   ```bash
   make
   ```

3. Execute a aplicação:
   ```bash
   ./cppcrudbp
   ```

Alternativamente, você pode usar o script `run.sh` para uma execução rápida.