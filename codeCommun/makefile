# Makefile Global pour compiler notre projet


####### variables #######
SRC_dir = tests/sources
BUILD_dir = tests/build
TRG = executable.out
LIB_inc = ./Librairie/sources
LIB_dir = ./Librairie
LIB_name = anane 

CC = avr-gcc


####### flags #######
CFLAGS = -I $(LIB_inc)


####### Cible (Target) #######
SRC = $(wildcard $(SRC_dir)/*.cpp)
OBJ = $(subst $(SRC_dir),$(BUILD_dir),$(SRC:.cpp=.o))



####### Commandes du Makefile ####### 

# Compiler le projet
all: compileLib $(TRG)

# Compiler la librairie au besoin
compileLib: makefile
	cd $(LIB_dir); make

$(TRG): $(OBJ)
	$(CC) -o $@ $(OBJ) -L $(LIB_dir) -l $(LIB_name)

$(BUILD_dir)/%.o: $(SRC_dir)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS) 

# Afficher les variables
vars:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"
	@echo "TRG = $(TRG)"

# Nettoyer les dossiers
clean: cleanLib
	rm $(BUILD_dir)/*.o *.out
	
cleanLib: makefile
	cd $(LIB_dir); make clean

# Nettoyer les dossiers
install: ihex				
	avrdude -c usbasp   \
	-p atmega324pa -P -e -U flash:w:ihex