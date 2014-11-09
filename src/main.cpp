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

#include "log.h"
#include "core.h"


int main(/*int argc, char* argv[]*/)
{
	Core_t core;
	core.loadAssets("../assets/test.blend");
	core.renderLoop();
	return 0;
}
