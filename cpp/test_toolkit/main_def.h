// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#ifndef MAIN_FUNC
#ifdef EPI_TEST_TOOLKIT
	#define EPI_MERGE_(a,b)  a##b
	#define EPI_LABEL_(a) EPI_MERGE_(_main_, a)
	#define MAIN_FUNC EPI_LABEL_(__COUNTER__)
#else
	#define MAIN_FUNC main
#endif
#endif
