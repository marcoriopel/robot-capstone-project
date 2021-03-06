# Makefile Global pour compiler notre projet


####### variables #######
#repertoire contenant le code source
SRC_dir = Projet/sources
#repertoire contenant les fichiers binaires
BUILD_dir = Projet/build
#repertoire contenant le makefile de test
TEST_dir = tests
#nom du projet
PROJECTNAME = test
#repertoire contenant les fichiers de la lib a inclure
LIB_inc = ./Librairie/sources
#repertoire contenant la librairie a inclure
LIB_dir = ./Librairie
#nom de la librairie
LIB_name = anane 
#repertoire contenant le makefile du test
TEST_dir = tests

#Nom du compilateur
CC = avr-g++
# Nom du microcontroleur cible
MCU=atmega324pa
# Niveau d'optimization
OPTLEVEL=s

#Nom des cibles par defaut
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

####### flags #######
# Flags pour le compilateur en C
CFLAGS = -I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall 

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions     

# Flags du Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)  


####### Cible (Target) #######
SRC = $(wildcard $(SRC_dir)/*.cpp)
OBJ = $(subst $(SRC_dir),$(BUILD_dir),$(SRC:.cpp=.o))
LIBS = -L $(LIB_dir) -l $(LIB_name)
INC = -I $(LIB_inc)


####### Commandes du Makefile ####### 

# Compiler le projet
all: compileLib $(TRG)

# Compiler la librairie au besoin
compileLib: makefile
	cd $(LIB_dir); make

$(TRG): $(OBJ)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJ) \
	-lm $(LIBS)

$(BUILD_dir)/%.o: $(SRC_dir)/%.cpp
	$(CC) -o $@ $(CFLAGS) $(CXXFLAGS) -c $<



# Afficher les variables
vars:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"
	@echo "TRG = $(TRG)"
	@echo "LIBS = $(LIBS)"
	@echo "INC = $(INC)"


# Installer le test sur le robot
test: compileLib makefile
	cd $(TEST_dir); make install


# Nettoyer les dossiers
clean: cleanLib cleanTest
	rm -f $(BUILD_dir)/*.o *.out $(HEXTRG) *.d $(TRG).map $(TRG).out.map $(TRG).hex
	
cleanLib: makefile
	cd $(LIB_dir); make clean

cleanTest: makefile
	cd $(TEST_dir); make clean



# installer l'executable sur le robot
install: compileLib $(HEXROMTRG)				
	avrdude -c usbasp   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

%.hex: %.out
	avr-objcopy -j .text -j .data \
		-O ihex $< $@