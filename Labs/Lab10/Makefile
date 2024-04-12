# Makefile feito por Julio Nunes Avelar
# Use e redistribua a vontade
# Para utilizalo em seus Labs de mc202 substitua o PROJ_NAME pelo nome do arquivo principal do projeto


# Nome do projeto
PROJ_NAME=cozinha
 
# arquivos .c
C_SOURCE=$(wildcard ./*.c)
 
# arquivos .h
H_SOURCE=$(wildcard ./*.h)

TEST_IN=$(wildcard ./testes/*.in)
TEST_OUT=$(TEST_IN:.in=.out)
TEST_RES=$(wildcard ./testes/*.res)

OBJ_DIR=objects

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(C_SOURCE)))
 
# Compilador e linker
CC=gcc
 
# Flags de compilação
CC_FLAGS= -std=c99  \
		 -c         \
         -Wvla      \
         -Wall      \
         -Werror    \
         -lm        \
		 -g
 
# Comando usado na target clean
RM = rm -rf
 
#
# Compilação e linkagem
#
all: objFolder $(PROJ_NAME) ## Compila o projeto e realiza a likagem
 
$(PROJ_NAME): $(OBJ)
	@ echo 'Buildando binario usando GCC: $@'
	$(CC) $^ -o $@
	@ echo 'Binario buildado com sucesso: $@'
	@ echo ' '
 
./objects/%.o: %.c %.h
	@ echo 'Alvo de Building usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
./objects/$(PROJ_NAME).o: $(PROJ_NAME).c $(H_SOURCE)
	@ echo 'Alvo de Building usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
objFolder:
	@ echo 'Criando diretorio para os objetos'
	@ mkdir -p $(OBJ_DIR)
 
clean: ## Apaga todos os arquivos de compilação .o e binarios, além das saidas geradas pelos testes
	@rm -rf ./testes/*.out
	@ echo 'Removendo arquivos de Objeto e binarios'
	@ $(RM) ./$(OBJ_DIR)/*.o $(PROJ_NAME) *~
	@ echo 'Removendo diretorio de objetos'
	@ $(RM) $(OBJ_DIR)
	@ echo 'Clean executado com sucesso'

# Comando padrão do make: executa os testes
test: objFolder $(PROJ_NAME) $(TEST_RES) ## Realiza a testagem do programa em todos os casos de teste e no valgring
	@echo "\nTodos os testes foram executados com sucesso!"
	@rm -rf ./testes/*.out
	@echo "Executando Valgrind..."
	valgrind -v --leak-check=full --show-leak-kinds=all \
	--error-exitcode=1 ./$(PROJ_NAME) < ./testes/teste2.in
	@echo "Valgrind executado com sucesso!"

# Regra genérica para gerar arquivos .out a partir de arquivos .in
./testes/%.out: ./testes/%.in $(PROJ_NAME)
	@echo "Executando teste para $<..."
	@./$(PROJ_NAME) < $< > $@

./testes/%.res: ./testes/%.out
	@echo "Comparando resultados..."
	@diff -q $< $@ > /dev/null || \
    (echo "Test $< falho" && exit 1)
	@echo "Teste concluído."

help: ## Printa os comandos disponiveis
	@printf "\uso : make <commands> \n\nos seguintes comandos estão disponiveis : \n\n"
	@grep -F -h "##" $(MAKEFILE_LIST) | grep -F -v grep -F | sed -e 's/\\$$//' | sed -e 's/##//'
	@printf "\n"


.PHONY: all clean test help