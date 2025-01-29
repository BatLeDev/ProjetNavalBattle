# Makefile du projet "Bataille navale" A PLACER dans le répertoire /ws du projet VSCode

# Chaque classe du projet doit être testée séparément.
# Il y aura donc un lanceur (main) par classe à tester.

# Ce makefile doit permettre de faire :
#	- la compilation du lanceur associé à chaque classe à tester
#	- la compilation du projet final (c-à-d main.cpp)

# Déclaration de quelques variables utiles au makefile
GPP = g++ -Wall
SRC = ./src
BIN = ./bin

# La cible "deleteAll" est exécutée en tapant la commande "make deleteAll"
deleteAll :
	@# Précéder chaque commande d'une TABULATION
	@echo suppression du contenu du répertoire ./bin
	rm -f $(BIN)/*.o $(BIN)/*.bin

# Test de la classe CBateau
# Compilation du lanceur testCBateau, pour cela (l'ordre de compilation est important en C++) :
#	- supprimer le contenu du répertoire "./bin" et
#	- d'abord compiler CBateau
#	- ensuite compiler testCBateau

# La cible "testCBateau" est exécutée en la déclarant correctement sous VSCode
testCBateau : deleteAll compilCBateau compilTestCBateau

# La cible "compilCBateau" est exécutée en la déclarant correctement sous VSCode
compilCBateau :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CBateau
	$(GPP) $(SRC)/CBateau.cpp -o $(BIN)/CBateau.o -c

# La cible "compilTestCBateau" est exécutée en la déclarant correctement sous VSCode
compilTestCBateau :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation testCBateau
	$(GPP) $(SRC)/testCBateau.cpp $(BIN)/CBateau.o -o $(BIN)/testCBateau.bin

# Test de la classe CArmada
# Compilation du lanceur testCArmada, pour cela (l'ordre de compilation est important en C++) :
#	- supprimer le contenu du répertoire "./bin" et
# - d'abord compiler la classe CBateau
#	- puis compiler CArmada
#	- ensuite compiler testCArmada

# La cible "testCArmada" est exécutée en la déclarant correctement sous VSCode
testCArmada : deleteAll compilCBateau compilCArmada compilTestCArmada

# La cible "compilCArmada" est exécutée en la déclarant correctement sous VSCode
compilCArmada :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CArmada
	$(GPP) $(SRC)/CArmada.cpp -o $(BIN)/CArmada.o -c

# La cible "compilTestCArmada" est exécutée en la déclarant correctement sous VSCode
compilTestCArmada :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation testCArmada
	$(GPP) $(SRC)/testCArmada.cpp $(BIN)/CBateau.o $(BIN)/CArmada.o -o $(BIN)/testCArmada.bin

# Test de la classe CGui
# Compilation du lanceur testCGui, pour cela (l'ordre de compilation est important en C++) :
#	- supprimer le contenu du répertoire "./bin"
# - compiler la classe CBateau
# - ensuite compiler la classe CArmada
# - puis compiler la classe CCoups
#	- puis compiler CGui
#	- et enfin compiler testCGui

# La cible "testCGui" est exécutée en la déclarant correctement sous VSCode
testCGui : deleteAll compilCBateau compilCArmada compilCCoups compilCGui compilTestCGui

# La cible "compilCGui" est exécutée en la déclarant correctement sous VSCode
compilCGui :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CGui
	$(GPP) $(SRC)/CGui.cpp -o $(BIN)/CGui.o -c

# La cible "compilTestCGui" est exécutée en la déclarant correctement sous VSCode
compilTestCGui :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation testCGui
	$(GPP) $(SRC)/testCGui.cpp $(BIN)/CBateau.o $(BIN)/CArmada.o $(BIN)/CCoups.o $(BIN)/CGui.o -o $(BIN)/testCGui.bin

# ---------------------- Compil des autres classes

# La cible "compilCCoups" est exécutée en la déclarant correctement sous VSCode
compilCCoups :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CCoups
	$(GPP) $(SRC)/CCoups.cpp -o $(BIN)/CCoups.o -c

# La cible "compilCSocket" est exécutée en la déclarant correctement sous VSCode
compilCSocket :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CSocket
	$(GPP) $(SRC)/CSocket.cpp -o $(BIN)/CSocket.o -c

# La cible "compilCClientSocket" est exécutée en la déclarant correctement sous VSCode
compilCClientSocket :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CClientSocket
	$(GPP) $(SRC)/CClientSocket.cpp -o $(BIN)/CClientSocket.o -c

# La cible "compilCServerSocket" est exécutée en la déclarant correctement sous VSCode
compilCServerSocket :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CServerSocket
	$(GPP) $(SRC)/CServerSocket.cpp -o $(BIN)/CServerSocket.o -c

# La cible "compilCJoueur" est exécutée en la déclarant correctement sous VSCode
compilCJoueur :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CJoueur
	$(GPP) $(SRC)/CJoueur.cpp -o $(BIN)/CJoueur.o -c

# La cible "compilCJoueurCli" est exécutée en la déclarant correctement sous VSCode
compilCJoueurCli :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CJoueurCli
	$(GPP) $(SRC)/CJoueurCli.cpp -o $(BIN)/CJoueurCli.o -c

# La cible "compilCJoueurServ" est exécutée en la déclarant correctement sous VSCode
compilCJoueurServ :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CJoueurServ
	$(GPP) $(SRC)/CJoueurServ.cpp -o $(BIN)/CJoueurServ.o -c

# ICI, la cible de compilation finale pour obtenir main.bin
# A executer A LA FIN du projet en s'assurant que toutes les classes du projet compilent et s'exécutent sans erreurs !
# La cible "lanceurFinal"
lanceurFinal : deleteAll compilCBateau compilCArmada compilCCoups compilCGui compilCSocket compilCClientSocket compilCServerSocket compilCJoueur compilCJoueurCli compilCJoueurServ
	@echo Compilation lanceurFinal
	$(GPP) $(SRC)/main.cpp $(BIN)/CBateau.o $(BIN)/CArmada.o $(BIN)/CCoups.o $(BIN)/CGui.o $(BIN)/CSocket.o $(BIN)/CClientSocket.o $(BIN)/CServerSocket.o $(BIN)/CJoueur.o $(BIN)/CJoueurCli.o $(BIN)/CJoueurServ.o -o $(BIN)/main.bin
