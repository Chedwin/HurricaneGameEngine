//*******************************//
//
// Name:			Macro.h
// Description:		Macro defines all the types and keys in Hurricane
//					Most of them are std macros
//					Include this header to access any external dependencies provided by the system
//					A general goal of this header file to avoid some dependencies being multiply loaded into the compiler
//
// Author:			Edwin Chen
// Created:			Apr 05, 2016
// Last updated:	Sep 22, 2016
//
//*******************************//
#pragma once

#ifndef _MACRO_H
#define _MACRO_H

////// WINDOWS STUFF /////
#ifndef WINDOWS
#define WINDOWS
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif

////// SDL STUFF /////
#ifndef SDL
#define SDL
#include <SDL.h> // Avoid the stupid LNK2019 _ShowError linker error....
#undef main
#endif


/////// Include files ///////
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

#include <cstddef>

#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>

#include <memory>
#include <algorithm>

#include "PrimitiveTypes.h"

//////// Macros /////////

// iostream
#define COUT std::cout
#define CIN  std::cin
#define ENDL std::endl
#define CERR std::cerr
#define STOI std::stoi // string to int

// pair
#define PAIR(A, B) std::pair<A, B>

// ofstream
#define OFSTREAM std::ofstream
// ifstream
#define IFSTREAM std::ifstream

// getline
#define GETLINE std::getline

// string
#define STRING std::string
// ios
#define IOS std::ios


// stdio.h
#define PRINTF std::printf
#define GETCHAR std::getchar



// list
#define LIST(T) std::list<T>
// vector
#define VECTOR(X) std::vector<X>
// stack
#define STACK(P) std::stack<P>
// queue
#define QUEUE(L) std::queue<L>
// map
#define MAP(K, V) std::map<K, V>



// memory - smart pointers
#define UNIQUE_PTR(A)		std::unique_ptr<A>
#define SHARED_PTR(B)		std::shared_ptr<B>
#define DEFAULT_DELETE(C)	std::default_delete<C>
#define WEAK_PTR(D)			std::weak_ptr<D>




/////////////////////////////////////////////////////////////////////////
#endif