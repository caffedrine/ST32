//
// Created by curiosul on 1/4/19.
//
// Fixing some known g++ compiler problems
//
// Sources: http://pastebin.com/7VKUuTJa


#ifndef _EXTENSIONS_H
#define _EXTENSIONS_H

#include <new>
#include <malloc.h>

/*
 * Pure virtual functions do increase the size of the binary.
 */
extern "C" void __cxa_pure_virtual()
{
	while(true)
	{
		;
	}
}

/*
 * Operators 'new' and 'delete' also increase the size of the binary
 */
void* operator new(std::size_t size) {
	return malloc(size);
}

void* operator new[](std::size_t size) {
	return malloc(size);
}

void operator delete(void* ptr) {
	free(ptr);
}

void operator delete[](void* ptr) {
	free(ptr);
}

/* Optionally you can override the 'nothrow' versions as well.
   This is useful if you want to catch failed allocs with your
   own debug code, or keep track of heap usage for example,
   rather than just eliminate exceptions.
 */

void* operator new(std::size_t size, const std::nothrow_t&) {
	return malloc(size);
}

void* operator new[](std::size_t size, const std::nothrow_t&) {
	return malloc(size);
}

void operator delete(void* ptr, const std::nothrow_t&) {
	free(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) {
	free(ptr);
}


#endif //_EXTENSIONS_H
