/*****************************************************************************
 * Soubor:   c++.cpp
 * Datum:    
 * Autor:    Jan Porhincak, xporhi00@fit.vutbr.cz
 * Projekt:  
 * Verzia:
 * Komentar: 
 * Poznamka: 
 *****************************************************************************/

#include <iostream>
#include <string>

#include "log.hpp"
#include "core.hpp"


int main(/*int argc, char* argv[]*/)
{
	Core core;
	core.loadAssets("../assets/opica3.blend");
	core.renderLoop();
	return 0;
}
