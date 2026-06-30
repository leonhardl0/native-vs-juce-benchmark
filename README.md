# 🎛️ Engenharia de Reuso em Plugins de Áudio: Nativo vs. JUCE

**Um estudo de caso prático sobre os riscos e limites da abstração arquitetural no desenvolvimento de plugins para DAWs.**

Este repositório contém o código-fonte, os binários e os dados brutos de benchmark do Trabalho de Conclusão de Curso (TCC) em Engenharia de Software apresentado no Centro Universitário Unidade de Ensino Superior Dom Bosco (UNDB). O projeto analisa a tensão entre produtividade e sustentabilidade arquitetural em sistemas críticos de tempo real, comparando o desenvolvimento nativo com o uso de frameworks de abstração.

> ⚠️ **Nota de Integridade Acadêmica e Autoria:** Esclarece-se que o algoritmo núcleo de processamento de sinal (DSP — delay linear com buffer circular) utilizado neste projeto pertence à biblioteca de exemplos da Steinberg (VST3 SDK). O esforço de engenharia e a contribuição autoral deste estudo restringem-se ao isolamento desse algoritmo nativo, à sua adaptação/porte para o framework JUCE e à estruturação do ambiente controlado de testes empíricos (*benchmark*).

---

## 🏗️ Estrutura do Repositório e Variantes

Para garantir a validade interna do experimento e isolar o custo das camadas de integração, a mesma regra de negócio foi implementada em duas arquiteturas distintas:

* 📂 **Variante Nativa (`/adelay.vst3`)**: Baseada estritamente no exemplo ADelay do VST3 SDK (Steinberg). Representa o desenvolvimento de baixo nível, com gerenciamento manual de dependências e menor abstração.
* 📂 **Variante Abstraída (`/adelay_JUCE.vst3`)**: Porta equivalente desenvolvida utilizando o framework multiplataforma JUCE 7.x. Representa a abordagem de mercado focada em produtividade e compilação *multi-target*.

---

## 📊 Principais Resultados do Estudo

O experimento avaliou o impacto das decisões arquiteturais em duas dimensões principais sob estresse (50 instâncias simultâneas no REAPER 7). Para garantir o rigor estatístico, os dados reportados representam a média de **10 execuções independentes (n=10)** utilizando o driver de baixa latência **ASIO4ALL**:

### 1. Overhead Computacional (DSP)

A inserção de camadas genéricas de adaptação tem um custo mensurável em ambientes de tempo real:

* **Consumo de CPU:** A variante JUCE apresentou um consumo médio de **37,4% (± 6,13)**, enquanto a variante nativa registrou **28,9% (± 4,18)**. O cenário *baseline* (sem efeitos) operou em 23,5%. O framework gerou um incremento médio substancial de 13,9 pontos percentuais frente ao *baseline*.
* **Consumo de RAM:** A abstração do framework consumiu, em média, **425,5 MB**, contra **307,3 MB** da solução nativa (com o cenário *baseline* consumindo 266,6 MB).

### 2. Dívida Técnica e Sustentabilidade Arquitetural

A análise estática via SonarQube quantificou o *trade-off* do reuso:

* **Redução de Boilerplate:** O JUCE derrubou o volume de código estrutural de **336** (Nativo) para **154** (JUCE) Linhas de Código (LoC), comprovando o massivo ganho de produtividade ao mascarar a complexidade do hospedeiro.
* **Acoplamento Eferente (Ce):** Em contrapartida, o acoplamento saltou de **2.0** para **6.5**, evidenciando uma forte dependência estrutural do código à API do framework, com potenciais violações do Princípio da Inversão de Dependência.

---

## 🚀 Como Reproduzir o Experimento

### Pré-requisitos

* DAW compatível com formato VST3 (Testado no REAPER 7.x).
* Driver de áudio de baixa latência (ASIO4ALL recomendado para Windows).
* SonarScanner e SonarQube (para replicação das métricas de código, opcional).
* *Para compilação:* CMake, VST3 SDK (Steinberg), Projucer (JUCE) e um compilador C++ (ex: Visual Studio 2022).

### Compilação a partir do código-fonte

Para verificação independente, siga os passos abaixo para gerar os binários localmente a partir dos arquivos disponibilizados:

**Variante Nativa (VST3 SDK):**

1. Clone o repositório oficial do VST3 SDK da Steinberg.
2. Substitua os arquivos do diretório `public.sdk/samples/vst/adelay` pelos arquivos correspondentes fornecidos neste repositório.
3. Utilize o CMake para gerar o projeto e compile o *target* `adelay` em modo *Release*.

**Variante Abstraída (JUCE):**

1. Abra o arquivo de projeto `.jucer` fornecido utilizando o Projucer (JUCE 7.x).
2. Exporte o projeto para a sua IDE de preferência.
3. Compile o projeto selecionando o formato de saída VST3 em modo *Release*.

### Execução do Benchmark

1. Caso não deseje compilar manualmente, utilize os arquivos `.vst3` pré-compilados e disponíveis na raiz deste repositório.
2. Copie os binários para o diretório padrão de plugins VST3 do seu sistema (ex: `C:\Program Files\Common Files\VST3` no Windows).
3. Abra o REAPER 7 e configure o sistema de áudio em **Options > Preferences > Device** para utilizar o **ASIO4ALL** com tamanho de *buffer* em 1024 amostras.
4. Carregue 50 pistas de áudio idênticas (*loop* em formato `.ogg` ou `.wav`).
5. Instancie uma variante por pista e acompanhe os dados agregados no *Performance Meter* (`Ctrl+Alt+P`).
