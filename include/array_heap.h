/*
 * Copyright © 2012  Fabio Falzoi, Juri Lelli, Giuseppe Lipari
 *
 * This file is part of PRAcTISE.
 *
 * PRAcTISE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRAcTISE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with PRAcTISE.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Max-deadline CPU queue implementation
 * using a max-heap built with a static array.
 * array_heap.h
 */
#include <pthread.h>
#include <linux/types.h>
#include "common_ops.h"

#define IDX_INVALID	-1
#define MAX_CPU		-1

typedef struct array_item {
	__u64 dl;
	int cpu;
} item;

typedef struct heap_struct {
	pthread_spinlock_t lock;
	int size;
	int *cpu_to_idx;
	item *elements;
	int (*cmp_dl)(__u64 a, __u64 b);
} array_heap_t;

void array_heap_init(void *s, int nproc, int (*cmp_dl)(__u64 a, __u64 b));

void print_array_heap(void *s, int nproc);

void max_heapify(array_heap_t *h, int idx);

int heap_set(void *s, int cpu, __u64 dl, int is_valid);

int heap_maximum(void *s);

int heap_extract_max(array_heap_t *h, int cpu);

int array_heap_check(void *s, int nproc);

void array_heap_save(void *s, int nproc, FILE *f);
