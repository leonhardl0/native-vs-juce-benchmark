# 🎛️ Engenharia de Reuso em Plugins de Áudio: Nativo vs. JUCE

**Um estudo de caso prático sobre os riscos e limites da abstração arquitetural no desenvolvimento de plugins para DAWs.**

Este repositório contém o código-fonte, os binários e os dados brutos de benchmark do Trabalho de Conclusão de Curso (TCC) em Engenharia de Software apresentado no Centro Universitário Unidade de Ensino Superior Dom Bosco (UNDB). O projeto analisa a tensão entre produtividade e sustentabilidade arquitetural em sistemas críticos de tempo real, comparando o desenvolvimento nativo com o uso de frameworks de abstração.

---

## 🏗️ Estrutura do Repositório e Variantes

Para garantir a validade interna do experimento e isolar o custo das camadas de integração, a mesma regra de negócio (um processamento de *delay* linear com buffer circular) foi implementada em duas arquiteturas distintas:

*   📂 **Variante Nativa (`/adelay.vst3`)**: Baseada estritamente no exemplo ADelay do VST3 SDK (Steinberg)[cite: 4]. Representa o desenvolvimento de baixo nível, com gerenciamento manual de dependências e menor abstração.
*   📂 **Variante Abstraída (`/adelay_JUCE.vst3`)**: Porta equivalente desenvolvida utilizando o framework multiplataforma JUCE 7.x[cite: 4]. Representa a abordagem de mercado focada em produtividade e compilação *multi-target*.

Os dados consolidados de coleta encontram-se no diretório `Plugin/`:
*   📄 `metricas_benchmark.json` (Dados brutos do hospedeiro/DAW)[cite: 4].
*   📄 `sonar_metrics.json` (Dados brutos de análise estática)[cite: 4].

---

## 📊 Principais Resultados do Estudo

O experimento avaliou o impacto das decisões arquiteturais em duas dimensões principais sob estresse (50 instâncias simultâneas no REAPER 7)[cite: 4]:

### 1. Overhead Computacional (DSP)
A inserção de camadas genéricas de adaptação tem um custo em ambientes de tempo real:
*   **Consumo de CPU:** A variante JUCE apresentou um incremento de **+7 p.p.** no consumo total de CPU em relação ao *baseline*, frente a apenas +1 p.p. da variante nativa[cite: 4].
*   **Consumo de RAM:** A abstração do framework consumiu **408 MB** contra **263 MB** da solução nativa[cite: 4].
*   **Carga FX:** O processamento exclusivo de áudio saltou de **1.3% (Nativo)** para **9.0% (JUCE)**[cite: 4].

### 2. Dívida Técnica e Sustentabilidade Arquitetural
A análise estática via SonarQube quantificou o *trade-off* do reuso:
*   **Redução de Boilerplate:** O JUCE derrubou o volume de código de **336** (Nativo) para **154** (JUCE) Linhas de Código (LoC), comprovando o ganho de produtividade ao mascarar a complexidade do *host*[cite: 4].
*   **Acoplamento Eferente (Ce):** Em contrapartida, o acoplamento saltou de **2.0** para **6.5**, evidenciando uma forte dependência estrutural do código à API do framework (violação potencial da Inversão de Dependência)[cite: 4].

---

## 🚀 Como Reproduzir o Experimento

### Pré-requisitos
*   DAW compatível com formato VST3 (Testado no REAPER 7.x).
*   SonarScanner e SonarQube (para replicação das métricas de código).

### Passos
1. Faça o *download* ou clone este repositório.
2. Copie os arquivos `.vst3` disponíveis na raiz para o seu diretório local de plugins da DAW (ex: `C:\Program Files\Common Files\VST3` no Windows).
3. Abra o seu hospedeiro, crie 50 pistas de áudio idênticas e instancie as variantes para aferir o comportamento do medidor de performance local.

---
