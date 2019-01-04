//
// Created by curiosul on 1/4/19.
//
// Fixing some known g++ compiler problems
//
// Sources: http://pastebin.com/7VKUuTJa

/*
 * Known issues when ported to C++11:
 * 	o if a class is declared static the size of the code is increasing heavily (the same for pure virtual function bug solved below)
 *  o constructor of objects declared globally is not triggered. better to declare pointers then create all instances altogether
 *  o std::vector::push/emplace_back is also increasing the size of the binary file
 */

#ifndef _EXTENSIONS_H
#define _EXTENSIONS_H

#include <new>
#include <malloc.h>

/*
 * Pure virtual functions do increase the size of the binary.
 */
extern "C" void __cxa_pure_virtual()
{
	while( true )
	{ ;
	}
}

/*
 * Operators 'new' and 'delete' also increase the size of the binary
 */
void *operator new(std::size_t size)
{
	return malloc(size);
}

void *operator new[](std::size_t size)
{
	return malloc(size);
}

void operator delete(void *ptr)
{
	free(ptr);
}

void operator delete[](void *ptr)
{
	free(ptr);
}

/* Optionally you can override the 'nothrow' versions as well.
   This is useful if you want to catch failed allocs with your
   own debug code, or keep track of heap usage for example,
   rather than just eliminate exceptions.
 */

void *operator new(std::size_t size, const std::nothrow_t &)
{
	return malloc(size);
}

void *operator new[](std::size_t size, const std::nothrow_t &)
{
	return malloc(size);
}

void operator delete(void *ptr, const std::nothrow_t &)
{
	free(ptr);
}

void operator delete[](void *ptr, const std::nothrow_t &)
{
	free(ptr);
}

/*
 * Global variables are not initialized
 * Full discussion: https://stackoverflow.com/questions/6343348/global-constructor-call-not-in-init-array-section/15056330
 */
//extern "C"
//{
//extern void (**__init_array_start)();
//extern void (**__init_array_end)();
//
//inline void static_init()
//{
//	for( void (**p)() = __init_array_start; p < __init_array_end; ++p )
//		(*p)();
//}
//}


#endif //_EXTENSIONS_H
