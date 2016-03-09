/*

cl /W3 /Zi     ring_test.cpp && ring_test
cl /W3 /Zi /Ox ring_test.cpp && ring_test

*/
#include <stdio.h>
#include <stdlib.h>
#include "ring.h"

#ifdef assert
#undef assert
#endif

// The second BREAKME version is useful when debugging
//#define BREAKME (void)0
#ifndef BREAKME
#	ifdef _MSC_VER
#		define BREAKME __debugbreak()
#	else
#		define BREAKME __builtin_trap()
#	endif
#endif

#define assert(exp) (void) ((exp) || (printf("Error: %s:%d:\n %s\n", __FILE__, __LINE__, #exp), BREAKME, exit(1), 0))

int main(int argc, char** argv)
{
	{
		ring::Buf<int> b;
		int buf[100];
		for (int chunk = 1; chunk <= 5; chunk++)
		{
			for (int loops = 0; loops < 20; loops++)
			{
				assert(b.Size() == 0);
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < chunk; j++)
						buf[j] = i;
					assert(b.Write(buf, chunk));
					assert(b.Size() == chunk * (i + 1));
				}
				for (int i = 0; i < 30; i++)
				{
					assert(b.Read(buf, chunk) == chunk);
					for (int j = 0; j < chunk; j++)
						assert(buf[j] == i);
				}
				assert(b.Size() == 0);
				int v;
				assert(!b.Read(v));
			}
		}
	}
	return 0;
}