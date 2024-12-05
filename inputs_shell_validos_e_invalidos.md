
### Inputs Válidos e Inválidos para Operadores no Shell

#### 1. Pipe (`|`)

O operador `|` é usado para criar um pipeline, conectando a saída de um comando à entrada de outro.

- **Válidos**:
  ```bash
  cmd1 | cmd2      # Redireciona saída de cmd1 para entrada de cmd2
  cmd1 || cmd2     # Executa cmd2 apenas se cmd1 falhar (short-circuit lógico)
  cmd1 | cmd2 | cmd3 # Encadeia múltiplos pipelines
  ```

- **Inválidos**:
  ```bash
  | cmd             # Pipe sem comando anterior
  cmd |             # Pipe sem comando seguinte
  |||               # Não é um operador válido
  ```

#### 2. Redirecionamento de entrada (`<`)

O operador `<` redireciona a entrada padrão de um arquivo para um comando.

- **Válidos**:
  ```bash
  cmd < file       # Usa 'file' como entrada para o comando
  cmd1 < file | cmd2 # Redireciona entrada para cmd1 e cria um pipeline
  ```

- **Inválidos**:
  ```bash
  < cmd            # Redirecionamento sem comando
  cmd <<| cmd2     # Combinação inválida
  ```

#### 3. Redirecionamento de saída (`>` e `>>`)

- `>` redireciona a saída padrão para um arquivo (sobrescrevendo).
- `>>` redireciona a saída padrão para um arquivo (anexando).

- **Válidos**:
  ```bash
  cmd > file       # Redireciona saída para 'file'
  cmd >> file      # Anexa saída a 'file'
  cmd > file | cmd2 # Redireciona saída e cria pipeline
  ```

- **Inválidos**:
  ```bash
  > cmd            # Redirecionamento sem comando
  cmd >| cmd2      # '>|' não é válido sem configuração especial
  ```

#### 4. Heredoc (`<<`)

O operador `<<` é usado para redirecionar a entrada de um bloco de texto diretamente no terminal (*heredoc*).

- **Válidos**:
  ```bash
  cmd << END
  some input
  END
  ```

- **Inválidos**:
  ```bash
  << cmd           # Sem terminador ou comando associado
  ```

#### 5. Combinações inválidas (geral)

Aqui estão algumas combinações que são **sempre inválidas**, independentemente do contexto:

- **Inválidas**:
  ```bash
  <|              # Não faz sentido no Bash
  >|              # Precisa de permissões específicas ou configuração
  cmd ||| cmd2    # Não existe operador de triplo pipe
  <<< file        # Bash usa '<<<' para *here-strings*, mas não como arquivo
  ```

#### Tabela Resumida de Operadores Válidos e Inválidos

| Operador   | Válido                          | Inválido             |
|------------|----------------------------------|----------------------|
| `|`        | `cmd1 | cmd2`                   | `| cmd`, `cmd |||`   |
| `||`       | `cmd1 || cmd2`                  | `|| cmd`             |
| `<`        | `cmd < file`                    | `< cmd`, `<|`        |
| `<<`       | `cmd << END`                    | `<< cmd`             |
| `>`        | `cmd > file`                    | `> cmd`, `>| cmd`    |
| `>>`       | `cmd >> file`                   | `>>` sem comando     |

#### Como tratar no parsing:

1. **Detecção de operadores isolados**:
   - Certifique-se de que os operadores como `|`, `<`, ou `>` não aparecem no início ou fim da linha.
   - Verifique se cada operador tem um comando válido antes e depois.

2. **Validação de combinações inválidas**:
   - Rejeite combinações como `<|`, `||`, ou `|>` imediatamente.
   - Garanta que operadores como `<<` tenham terminadores válidos.

3. **Priorize clareza no erro**:
   - Quando detectar um operador inválido, informe exatamente o que está errado no input. Isso ajuda na depuração e na usabilidade.
