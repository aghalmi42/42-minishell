#!/bin/bash

echo "========================================="
echo "  TESTS MEMORY LEAKS - MINISHELL"
echo "========================================="

# Fonction pour tester avec valgrind
test_leak() {
    local test_name="$1"
    local command="$2"
    
    echo ""
    echo "--- Test: $test_name ---"
    echo "Command: $command"
    
    # Lance valgrind et capture le résultat
    valgrind --leak-check=full --show-leak-kinds=definite --suppressions=ignore.supp \
        ./minishell <<< "$command" 2>&1 | grep -E "(definitely lost|ERROR SUMMARY)"
}

echo ""
echo "=== TESTS COMMANDES SIMPLES ==="
test_leak "echo simple" "echo hello"
test_leak "pwd" "pwd"
test_leak "env" "env"
test_leak "export" "export TEST=value"
test_leak "unset" "unset PATH"
test_leak "cd" "cd /tmp"
test_leak "commande invalide" "commandeinvalide"

echo ""
echo "=== TESTS PIPES ==="
test_leak "pipe simple" "echo hello | cat"
test_leak "pipe double" "echo hello | cat | cat"
test_leak "pipe triple" "echo hello | cat | cat | cat"
test_leak "pipe avec grep" "echo hello | grep h"
test_leak "pipe complexe" "ls -la | grep minishell | wc -l"

echo ""
echo "=== TESTS REDIRECTIONS ==="
test_leak "redir output" "echo hello > /tmp/test_out"
test_leak "redir input" "cat < Makefile"
test_leak "redir append" "echo world >> /tmp/test_out"
test_leak "heredoc simple" "cat << EOF
hello
world
EOF"
test_leak "redir seule" "> /tmp/empty_file"
test_leak "multiple redir" "cat < Makefile > /tmp/out"
test_leak "redir + pipe" "cat < Makefile | grep CC"

echo ""
echo "=== TESTS QUOTES ==="
test_leak "single quotes" "echo 'hello world'"
test_leak "double quotes" "echo \"hello world\""
test_leak "quotes mixtes" "echo 'hello' \"world\""
test_leak "quotes avec variable" "echo \"USER is \$USER\""
test_leak "quotes vides" "echo '' \"\""
test_leak "quotes imbriquées" "echo \"l'apostrophe\""

echo ""
echo "=== TESTS VARIABLES ==="
test_leak "expansion simple" "echo \$USER"
test_leak "expansion multiple" "echo \$USER \$HOME \$PATH"
test_leak "expansion inexistante" "echo \$NONEXISTENT"
test_leak "exit status" "false; echo \$?"

echo ""
echo "=== TESTS AND/OR ==="
test_leak "AND success" "true && echo yes"
test_leak "AND failure" "false && echo no"
test_leak "OR success" "false || echo yes"
test_leak "OR failure" "true || echo no"
test_leak "AND chain" "true && true && echo yes"
test_leak "OR chain" "false || false || echo yes"
test_leak "AND + OR" "true && false || echo mixed"

echo ""
echo "=== TESTS PARENTHESES/SUBSHELLS ==="
test_leak "subshell simple" "(echo hello)"
test_leak "subshell avec cd" "(cd /tmp; pwd); pwd"
test_leak "AND dans subshell" "(true && echo yes)"
test_leak "OR dans subshell" "(false || echo yes)"
test_leak "pipe avec subshell" "(echo test) | cat"
test_leak "subshell imbriqué" "((echo nested))"
test_leak "multiple subshells" "(echo a); (echo b); (echo c)"
test_leak "subshell complexe" "(echo a && echo b) || echo c"
test_leak "subshell + redir" "(echo test) > /tmp/sub_out"

echo ""
echo "=== TESTS COMBINAISONS COMPLEXES ==="
test_leak "pipe + redir" "cat < Makefile | grep CC > /tmp/result"
test_leak "subshell + pipe + redir" "(echo test | cat) > /tmp/complex"
test_leak "AND + pipe" "true && echo yes | cat"
test_leak "OR + redir" "false || echo fallback > /tmp/or_out"
test_leak "tout ensemble" "(cat < Makefile | grep CC) && echo done || echo failed"

echo ""
echo "=== TESTS EDGE CASES ==="
test_leak "commande vide" ""
test_leak "espaces multiples" "echo    hello    world"
test_leak "tabs" "echo	hello	world"
test_leak "pipe sans commande droite" "echo hello |"
test_leak "redir sans fichier" "echo hello >"
test_leak "builtin export vide" "export"
test_leak "builtin env vide" "env"
test_leak "cd sans argument" "cd"

echo ""
echo "=== TESTS LONGS (STRESS) ==="
test_leak "50 pipes" "echo a | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
test_leak "10 AND" "true && true && true && true && true && true && true && true && true && true"
test_leak "commande longue" "echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

echo ""
echo "========================================="
echo "  TESTS TERMINÉS"
echo "========================================="
echo ""
echo "Nettoyage des fichiers temporaires..."
rm -f /tmp/test_out /tmp/empty_file /tmp/out /tmp/sub_out /tmp/result /tmp/complex /tmp/or_out 2>/dev/null

echo "Pour voir le détail complet d'un test spécifique, lance:"
echo "echo 'COMMANDE' | valgrind --leak-check=full --suppressions=ignore.supp ./minishell"
