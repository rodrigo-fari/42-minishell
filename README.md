# Minishell - Resumo e Organização do Projeto

## Partes principais do projeto (*Mandatory*)
1. **Prompt interativo**:
   - Deve exibir um *prompt* enquanto aguarda um comando.

2. **Execução de comandos**:
   - Deve buscar e executar o comando correto usando o `PATH` ou um caminho absoluto/relativo.

3. **Manipulação de sinais**:
   - `Ctrl+C`: Mostra um novo *prompt*.
   - `Ctrl+D`: Sai do shell.
   - `Ctrl+\`: Não faz nada.

4. **Citações e caracteres especiais**:
   - `'` (aspas simples): Ignora caracteres especiais no interior.
   - `"` (aspas duplas): Interpreta `$` para variáveis, mas ignora outros caracteres especiais.

5. **Redirecionamento e *pipes***:
   - `<`: Redireciona entrada.
   - `>`: Redireciona saída.
   - `>>`: Redireciona saída em modo *append*.
   - `<<`: Lê até encontrar um delimitador.
   - `|`: Conecta comandos via *pipe*.

6. **Variáveis de ambiente**:
   - Suporte a variáveis usando `$`.
   - `?`: Expande para o *exit status* do último comando.

7. **Comandos internos (*builtins*)**:
   - `echo` (com `-n`).
   - `cd` (com caminhos relativos ou absolutos).
   - `pwd` (sem opções).
   - `export` (sem opções).
   - `unset` (sem opções).
   - `env` (sem argumentos).
   - `exit` (sem opções).

---

## Regras importantes
1. **Norma da 42**:
   - Seguir as regras da *Norminette*.

2. **Sem vazamentos de memória**:
   - Toda memória alocada dinamicamente deve ser liberada corretamente.

3. **Uso de funções externas permitidas**:
   - *Readline library*: `readline`, `add_history`, etc.
   - Funções do sistema como: `fork`, `execve`, `pipe`, `dup2`, etc.
   - Manipulação de arquivos: `open`, `close`, `read`, `write`.

4. **Uso limitado de variáveis globais**:
   - Apenas uma variável global é permitida para tratar sinais.

5. **Readline pode vazar memória**:
   - Não precisa corrigir vazamentos dela, mas todo o seu código deve estar livre de vazamentos.

6. **Sem comportamento indefinido**:
   - Evitar falhas como *segmentation faults* ou *double frees*.

---

## Bibliotecas principais e funções associadas
### Bibliotecas
1. **<stdio.h>**
   - Funções: `printf`, `perror`.

2. **<stdlib.h>**
   - Funções: `malloc`, `free`, `exit`, `getenv`.

3. **<unistd.h>**
   - Funções: `write`, `access`, `read`, `close`, `fork`, `chdir`, `dup`, `dup2`, `isatty`, `ttyname`, `ttyslot`.

4. **<signal.h>**
   - Funções: `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`.

5. **<fcntl.h>**
   - Funções: `open`, `fcntl`.

6. **<sys/types.h>**, **<sys/stat.h>**
   - Funções: `stat`, `lstat`, `fstat`.

7. **<dirent.h>**
   - Funções: `opendir`, `readdir`, `closedir`.

8. **<string.h>**
   - Funções: `strerror`.

9. **<sys/ioctl.h>**
   - Funções: `ioctl`.

10. **<termios.h>**
    - Funções: `tcsetattr`, `tcgetattr`.

11. **<readline/readline.h>**
    - Funções: `readline`, `add_history`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`.

12. **<curses.h>** ou **<term.h>**
    - Funções: `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`.

---

## Observações importantes sobre as bibliotecas
1. **Bibliotecas externas**:
   - A biblioteca `readline` precisa estar instalada no sistema. Certifique-se de linká-la corretamente no *Makefile* com as flags apropriadas (exemplo: `-lreadline`).

2. **Libft**:
   - Você pode usar sua própria biblioteca `libft` para funções auxiliares como manipulação de strings (`ft_split`, `ft_strjoin`, etc.).

3. **Funções proibidas não mencionadas no *subject***:
   - Qualquer função que não esteja explicitamente listada (ex.: `system`, `strtok`) não deve ser utilizada.

---

## Como dividir o projeto em dupla
1. **Parsing e interpretação de comandos**:
   - Um membro pode focar no parsing de entrada do usuário (manipulação de strings, variáveis de ambiente, aspas, etc.).

2. **Execução de comandos e redirecionamento**:
   - O outro pode cuidar da execução dos comandos, incluindo redirecionamento e pipes.

3. **Controle de processos e sinais**:
   - Implementar o controle de processos (`fork`, `execve`, etc.) e manipulação de sinais.

4. **Comandos internos**:
   - Dividam os *builtins* (como `cd`, `echo`) entre vocês.

5. **Integração e testes**:
   - Ambos devem participar da integração das partes e realizar testes.

---

## O que estudar
- **Processos e Syscalls**:
  - `fork()`, `execve()`, `waitpid()`, `pipe()`, `dup2()`.

- **Redirecionamento de I/O**:
  - Manipulação de descritores de arquivos (`open`, `close`, `dup2`).

- **Sinais**:
  - Uso de `signal` e `sigaction`.

- **Manipulação de variáveis de ambiente**:
  - `getenv`, `setenv`.

---

## Plano inicial
1. Configure o **Makefile** com as regras básicas (`NAME`, `all`, `clean`, etc.).
2. Divida o trabalho entre as principais funcionalidades.
3. Comece implementando um *prompt* básico que exibe entrada do usuário.
4. Expanda para incluir parsing, execução de comandos, e outros recursos obrigatórios.
