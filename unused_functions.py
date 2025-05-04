import os
import re

# Caminho do diretório do projeto
project_path = "/home/rde-fari/projects/42-minishell"

# Caminho do cabeçalho principal
header_file = os.path.join(project_path, "inc/minishell.h")

# Regex para capturar declarações de funções no cabeçalho
header_function_pattern = re.compile(r"\b[a-zA-Z_][a-zA-Z0-9_]*\s+\*?\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*;")

# Coletar todas as funções declaradas no cabeçalho
with open(header_file, "r") as f:
    header_content = f.read()
declared_functions = header_function_pattern.findall(header_content)

# Verificar se as funções declaradas são chamadas em qualquer arquivo do projeto
unused_functions = []
for func in declared_functions:
    is_used = False
    for root, _, files in os.walk(project_path):
        for file in files:
            if file.endswith((".c", ".h")):
                with open(os.path.join(root, file), "r") as f:
                    content = f.read()
                    # Verificar se a função específica está sendo chamada
                    if re.search(rf"\b{func}\s*\(", content):
                        is_used = True
                        break
        if is_used:
            break
    if not is_used:
        unused_functions.append(func)

# Exibir funções não utilizadas
print("Funções declaradas mas não utilizadas:")
for func in unused_functions:
    print(func)