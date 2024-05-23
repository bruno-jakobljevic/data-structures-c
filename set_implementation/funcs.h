#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* generiraj(int n);
void shuffle(int* niz, int n);

int compare(const void* a, const void* b);
int* presjek(int* skupA, int* skupB, int n);
int* presjek_jedan_sortiran(int* skupA, int* skupB, int n);
int* presjek_oba_sortirana(int* skupA, int* skupB, int n);