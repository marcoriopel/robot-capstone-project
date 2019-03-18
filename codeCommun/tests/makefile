# Makefile Global pour compiler notre projet


####### variables #######
#repertoire contenant le code source
SRC_dir = sources
#repertoire contenant les fichiers binaires
BUILD_dir = build
#nom du projet
PROJECTNAME = test
#repertoire contenant les fichiers de la lib a inclure
LIB_inc = ../Librairie/sources
#repertoire contenant la librairie a inclure
LIB_dir = ../Librairie
#nom de la librairie
LIB_name = anane 
#nom de la librairie
TEST_SRC = test_moteur

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
SRC = $(SRC_dir)/$(TEST_SRC).cpp
OBJ = $(subst $(SRC_dir),$(BUILD_dir),$(SRC:.cpp=.o))
LIBS = -L $(LIB_dir) -l $(LIB_name)
INC = -I $(LIB_inc)


####### Commandes du Makefile ####### 

# Compiler le projet
all: $(TRG)

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



# Nettoyer les dossiers
clean: 
	rm -f $(BUILD_dir)/*.o *.out $(HEXTRG) $(BUILD_dir)/*.d $(TRG).map $(TRG).out.map $(TRG).hex

# installer l'executable sur le robot
install: $(HEXROMTRG)				
	avrdude -c usbasp   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

%.hex: %.out
	avr-objcopy -j .text -j .data \
		-O ihex $< $@