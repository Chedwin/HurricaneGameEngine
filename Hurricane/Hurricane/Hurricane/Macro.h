//*******************************//
//
// Name:			Macro.h
// Description:		Macro defines all the types and keys in Hurricane
//					Most of them are std macros
//					Include this header to access any external dependencies provided by the system
//					A general goal of this header file to avoid some dependencies being repeadily loaded into the compiler
//
// Author:			Edwin Chen
// Created:			Apr 05, 2016
// Last updated:	Nov 18, 2016
//
//*******************************//

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



/////// Include files ///////
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

#include <sstream>
#include <cstddef>

#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>

#include <memory>
#include <algorithm>

#include <cassert>
#include <iterator>

#include <time.h>

#include <typeinfo>

#include "PrimitiveTypes.h"

//////// Macros /////////

// iostream
#define COUT std::cout
#define CIN  std::cin
#define ENDL std::endl
#define CERR std::cerr

#define STOI std::stoi // string to int
#define STOF std::stof // string to float

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
// to_string conversion
#define TO_STRING(A) std::to_string(A)

// ios
#define IOS std::ios


// stdio.h
#define PRINTF std::printf
#define GETCHAR std::getchar

// sstream
#define STRINGSTREAM std::stringstream 

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
// unordered map
#define UNORDERED_MAP(N, M) std::unordered_map<N, M>


// memory - smart pointers
#define UNIQUE_PTR(A)		std::unique_ptr<A>
#define SHARED_PTR(B)		std::shared_ptr<B>
#define DEFAULT_DELETE(C)	std::default_delete<C>
#define WEAK_PTR(D)			std::weak_ptr<D>




/////////////////////////////////////////////////////////////////////////
#endif