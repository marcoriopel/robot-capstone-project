# Makefile Global pour compiler notre librairie


####### variables #######
SRC_dir = sources
BUILD_dir = build
TRG = libanane.a

# Nom du compilateur
CC = avr-g++
# Nom de l'archiveur
AR = avr-ar
# Nom du microcontroleur cible
MCU=atmega324pa
# Niveau d'optimization
OPTLEVEL=s


####### flags #######
# Flags pour le compilateur en C
CFLAGS = -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall 

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions 

# Flags pour la creation de la librairie
LIBFLAGS = -csr



####### Cible (Target) #######
SRC = $(wildcard $(SRC_dir)/*.cpp)
OBJ = $(subst $(SRC_dir),$(BUILD_dir),$(SRC:.cpp=.o))



####### Commandes du Makefile ####### 

# Compiler le projet
all: $(TRG)

$(TRG): $(OBJ)
	$(AR) $(LIBFLAGS) -o $@ $(OBJ)

$(BUILD_dir)/%.o: $(SRC_dir)/%.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@ 

# Afficher les variables
vars:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"
	@echo "TRG = $(TRG)"

# Nettoyer les dossiers
clean: 
	rm -f $(BUILD_dir)/*.o $(TRG)