#!/bin/bash

# Couleurs
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

SHELL="./minishell"
PASSED=0
FAILED=0

echo "========================================="
echo "  TESTS PARENTHÈSES + RÉGRESSION"
echo "========================================="
echo ""

# Fonction pour tester une commande
test_command() {
    local test_name="$1"
    local command="$2"
    local expected_behavior="$3"  # "success" ou "failure" ou exit code
    
    echo -n "Test: $test_name ... "
    
    # Exécuter la commande
    echo "$command" | $SHELL > /tmp/minishell_output.txt 2>&1
    exit_code=$?
    
    if [ "$expected_behavior" = "success" ]; then
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✓ PASS${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAIL${NC} (expected success, got exit=$exit_code)"
            ((FAILED++))
        fi
    elif [ "$expected_behavior" = "failure" ]; then
        if [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}✓ PASS${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAIL${NC} (expected failure, got success)"
            ((FAILED++))
        fi
    else
        # Test exit code spécifique
        if [ $exit_code -eq $expected_behavior ]; then
            echo -e "${GREEN}✓ PASS${NC} (exit=$exit_code)"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAIL${NC} (expected=$expected_behavior, got=$exit_code)"
            ((FAILED++))
        fi
    fi
}

echo -e "${BLUE}=== TESTS DE RÉGRESSION (Ancien code) ===${NC}"
echo ""

echo "--- Tests: Commandes Simples ---"
test_command "echo simple" "echo hello" "success"
test_command "ls commande" "ls > /dev/null" "success"
test_command "pwd commande" "pwd > /dev/null" "success"

echo ""
echo "--- Tests: Redirections ---"
test_command "redirection output" "echo test > /tmp/test_redir.txt" "success"
test_command "redirection input" "cat < /tmp/test_redir.txt" "success"
test_command "redirection append" "echo test2 >> /tmp/test_redir.txt" "success"
test_command "redirections multiples" "echo hello > /tmp/f1 > /tmp/f2" "success"

echo ""
echo "--- Tests: Pipes ---"
test_command "pipe simple" "echo test | cat" "success"
test_command "pipe double" "echo test | cat | cat" "success"
test_command "pipe avec grep" "echo hello | grep hello" "success"

echo ""
echo "--- Tests: AND/OR ---"
test_command "AND success" "true && echo yes" "success"
test_command "AND failure" "false && echo no" "failure"
test_command "OR success" "false || echo yes" "success"
test_command "OR failure" "true || echo no" "success"

echo ""
echo "--- Tests: Quotes ---"
test_command "single quotes" "echo 'hello world'" "success"
test_command "double quotes" 'echo "hello world"' "success"
test_command "quotes avec variable" 'echo "test $USER"' "success"

echo ""
echo -e "${BLUE}=== TESTS PARENTHÈSES (Nouveau code) ===${NC}"
echo ""

echo "--- Tests: Parenthèses Simples ---"
test_command "parenthèses vides interdites" "( )" "failure"
test_command "subshell simple" "(echo hello)" "success"
test_command "subshell avec commande" "(pwd)" "success"
test_command "subshell avec echo" "(echo test)" "success"

echo ""
echo "--- Tests: Isolation du Subshell ---"
# Note: Ces tests sont approximatifs car on ne peut pas vérifier l'état interne
test_command "subshell cd isolé" "(cd /tmp)" "success"
test_command "multiple commandes dans subshell" "(echo a; echo b)" "success"
test_command "commandes séparées avec ;" "(echo 1; echo 2; echo 3)" "success"

echo ""
echo "--- Tests: Priorité des Opérateurs ---"
test_command "parenthèses avant AND" "(echo a) && echo b" "success"
test_command "parenthèses avant OR" "(echo a) || echo b" "success"
test_command "AND dans parenthèses" "(true && echo yes)" "success"
test_command "OR dans parenthèses" "(false || echo yes)" "success"

echo ""
echo "--- Tests: Combinaisons Complexes ---"
test_command "subshell puis AND" "(echo start) && echo end" "success"
test_command "subshell puis OR" "(false) || echo fallback" "success"
test_command "AND puis subshell" "true && (echo yes)" "success"
test_command "nested logic" "(true && echo a) || echo b" "success"

echo ""
echo "--- Tests: Parenthèses avec Pipes ---"
test_command "subshell pipe à gauche" "(echo test) | cat" "success"
test_command "pipe dans subshell" "(echo a | cat)" "success"
test_command "subshell pipe subshell" "(echo test) | (cat)" "success"

echo ""
echo "--- Tests: Parenthèses avec Redirections ---"
test_command "subshell avec output" "(echo test) > /tmp/subshell_out.txt" "success"
test_command "redirection dans subshell" "(echo test > /tmp/inside.txt)" "success"

echo ""
echo "--- Tests: Erreurs de Syntaxe ---"
test_command "parenthèse non fermée" "(echo test" "failure"
test_command "parenthèse non ouverte" "echo test)" "failure"
test_command "parenthèses déséquilibrées" "((echo test)" "failure"
test_command "parenthèse vide" "()" "failure"

echo ""
echo "--- Tests: Cas Limites ---"
test_command "parenthèses imbriquées niveau 1" "((echo nested))" "success"
test_command "multiple subshells" "(echo a) && (echo b)" "success"
test_command "subshell complexe" "(echo start && echo middle || echo end)" "success"

echo ""
echo "========================================="
echo "  RÉSULTATS"
echo "========================================="
echo -e "${GREEN}PASSED: $PASSED${NC}"
echo -e "${RED}FAILED: $FAILED${NC}"
echo ""

# Cleanup
rm -f /tmp/test_redir.txt /tmp/f1 /tmp/f2 /tmp/subshell_out.txt /tmp/inside.txt /tmp/minishell_output.txt

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 Tous les tests sont passés !${NC}"
    exit 0
else
    echo -e "${RED}❌ Certains tests ont échoué.${NC}"
    exit 1
fi
