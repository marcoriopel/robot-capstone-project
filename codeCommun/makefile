# Makefile Global pour compiler notre projet


####### variables #######
SRC_dir = tests/sources
BUILD_dir = tests/build
PROJECTNAME = test
LIB_inc = ./Librairie/sources
LIB_dir = ./Librairie
LIB_name = anane 

CC = avr-gcc


#Nom des cibles par defaut
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

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
	rm -f $(BUILD_dir)/*.o *.out $(HEXTRG)
	
cleanLib: makefile
	cd $(LIB_dir); make clean



# installer l'executable sur le robot
install: $(HEXROMTRG)				
	avrdude -c usbasp   \
	-p atmega324pa -P -e -U flash:w:$(HEXROMTRG)

%.hex: %.out
	avr-objcopy -j .text -j .data \
		-O ihex $< $@