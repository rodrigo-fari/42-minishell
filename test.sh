#!/bin/bash

# Testes para o minishell
tests=(
	# Testes simples
	"echo"
	"echo ola mundo"
	"echo \"ola mundo\""
	"echo 'ola mundo'"
	"echo \" 'ola mudo' \""
	"echo ' \" ola mundo \" '"
	"echo ' ' ' ' ' ola mundo ' ' ' ' '"
	"echo \" \" \" \" \" ola mundo \" \" \" \" \""
	"echo \" \" \" ' ola mundo ' \" \""
	"echo ' ' ' \" ola mundo \" ' '"
	"echo ' ' ' ' \" ola mundo \" ' ' ' '"
	"echo \" \" \" \" ' ola mundo ' \" \" \" \""

	# Testes com caracteres no comando
	"e""c""h""o"
	"e""c""h""o ola mundo"
	"e""c""h""o 'ola mundo'"
	"e""c""h""o \"ola mundo\""
	"e""c""h""o \" 'ola mudo' \""

	# Testes com caracteres especiais
	"echo \$HOME"
	"echo \\"
	"echo | cat -e"
	"echo hello > test.txt"
	"echo hello >> test.txt"

	# Testes com variáveis de ambiente
	"echo \$USER"
	"echo \$PATH"
	"echo \$SHELL"
	"echo \"\$USER is logged in\""
	"echo 'User is \$USER'"

	# Testes com comandos embutidos
	"echo \"Today is \$(date)\""
	"echo \"Files: \$(ls -1 | wc -l)\""
	"echo \"Logged in as: \$(whoami)\""

	# Testes com longas strings
	"echo $(printf 'a%.0s' {1..1000})"
	"echo $(printf 'b%.0s' {1..1000})"

	# Testes com unicode
	"echo \"Olá, mundo 🌍!\""
	"echo \"你好，世界！\""
	"echo \"こんにちは世界！\""
	"echo \"안녕하세요 세계!\""
)

# Gerar um arquivo temporário para armazenar os comandos
tmpfile=$(mktemp)

# Adicionar todos os testes ao arquivo temporário
for test in "${tests[@]}"; do
	echo "$test" >> "$tmpfile"
done

# Adicionar comando de saída ao final do arquivo

# Executar o minishell com os comandos do arquivo temporário
./minishell < "$tmpfile"

# Remover o arquivo temporário
rm -f "$tmpfile"
