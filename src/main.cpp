#include <iostream>
#include <thread>

#include "Server.h"
#include "ConfigReader.h"
#include "ConsoleReader.h"

#include "Game.h"
#include "TestGame.h"

int main(int args, char ** argv){
	std::string configFile;
	if (args == 1){
		configFile = "default_config.conf";
	}else{
		configFile = argv[1];
	}

	auto config = config::readConfig ( configFile );

	auto *comm = new CommunicationManager();

	Game *game = new TestGame(config);
	game->setCommunicationManager(comm);

	auto server = Server(3200);
	server.setCommunicationManager(comm);

	auto consoleReader = ConsoleReader();

	std::thread(&Server::run, &server).detach();
	std::thread(&ConsoleReader::run, &consoleReader).detach();
		
	game->start();
	

	delete game;
	delete comm;

	return 0;
}
