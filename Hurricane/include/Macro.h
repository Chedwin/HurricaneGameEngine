#ifndef MACRO_H
#define MACRO_H

#include "PCH.h"

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


// functional
#define FUNCTION(U) std::function<U>

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

#define BIT(x) (1 << x)

#endif MACRO_H