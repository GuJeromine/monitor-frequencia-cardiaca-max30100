# Monitor de Frequência Cardíaca e Oxigenação (MAX30100)

Este projeto apresenta o desenvolvimento de um sistema embarcado para monitoramento de sinais vitais, focado na medição da frequência cardíaca e da oxigenação sanguínea. O trabalho abrange desde a identificação do problema até o desenvolvimento de uma Placa de Circuito Impresso (PCB) dedicada.

## 1. Introdução
O projeto foi desenvolvido para ser um produto de fácil utilização em áreas de saúde, como hospitais, farmácias ou para monitoramento rápido em casa após atividades físicas. O sistema utiliza um sensor de oximetria e pulso para exibir informações em tempo real em um display.

## 2. Especificações do Sistema
Para o funcionamento adequado, foram utilizados os seguintes componentes e tecnologias:

* **Microcontrolador:** Arduino UNO para gerenciamento das informações.
* **Sensor:** MAX-30100, que utiliza luz infravermelha e vermelha para medir a absorção e emissão de luz no sangue.
* **Interface:** Display LCD 16x2 (duas linhas de 16 caracteres).
* **Componentes Adicionais:** Resistores de 4.7K, jumpers e uma PCB customizada.
* **Software:** Arduino IDE para o desenvolvimento do código em C/C++.

## 3. Desenvolvimento

### 3.1 Prototipagem
Os testes iniciais foram realizados em uma protoboard para integrar o código com o hardware e realizar ajustes de calibração no sensor e no display.

### 3.2 Projeto da PCB
O circuito foi desenhado utilizando o software **EasyEDA**. A fabricação da placa seguiu o método térmico (transferência de toner para o cobre), seguido de corrosão e soldagem dos componentes. Foram utilizadas barras de pinos fêmea para o encaixe dos componentes, evitando problemas de conexão direta.

### 3.3 Lógica do Código
O algoritmo baseia-se na biblioteca `MAX30100_PulseOximeter.h`. A lógica principal inclui:
* Atualização constante da leitura do sensor via `pox.update()`.
* Filtros de validação: os valores só são exibidos se o batimento estiver entre 30 e 220 BPM e a oxigenação acima de 80%.
* Intervalo de exibição de 1000ms entre as amostras.

## 4. Resultados e Conclusão
O projeto obteve resultados satisfatórios na maioria dos testes, com valores de oxigenação e pulso estáveis após o tempo de inicialização do sensor.

**Desafios Técnicos:**
* **Display na PCB:** Houve uma falha na exibição de dados diretamente no display soldado à PCB, possivelmente devido a problemas de continuidade nas trilhas ou conexões de cobre.
* **Validação via Serial:** Apesar da falha no display da placa física, o funcionamento do sensor foi validado com sucesso através do **Monitor Serial** da Arduino IDE, onde os valores de BPM e SpO2 foram registrados e exibidos corretamente.

## 5. Autores
* **Gustavo Allan Jeromine**
* **Danilo Bressiani Solek**

## 6. Referências
* SOUZA, Jonas. "Como utilizar o Sensor de Frequência Cardíaca e Oxímetro MAX30100 com Arduino". Blog da Robótica, 2023.
