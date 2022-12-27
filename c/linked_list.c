#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


// "struct digit" is used to implement arbitrarily large non-negative
// integers. Each digit of the number is represented using a node.

typedef struct digit {
	int num;
	struct digit *next;
} digit;


// print list of digits
void print_number(digit *dt);
// Q1. implement print_number()

// read number from console and return a list of digits
digit *read_number(void);
// Q2. implement read_number()

// free list of digits
void free_number(digit *dt);
// Q3. implement free_number()
// As a bonus, run it under valgrind.
// What's the behaviour that you observe under valgrind
// if program is statically linked, e.g, with musl-libc?


// reverse the list of digits. create a new list of digits.
digit *reverse_number(digit *dt);
// Q4. implement reverse_number();


// sort the digits using insertion sort. returns a copy of sorted digits.
digit *sort_digits(digit *dt);
// Q5. implement sort_digits()

// Helper functions, used for implementing Q2.
// append node to the end of list. returns new tail.
digit *append(digit *tail, digit *node);
digit *create_digit(int num);


// Helper function used for implementing Q4.
// insert at the start of the list. returns new head.
digit *insert_at_head(digit *hd, digit *node);

// Helper function used for implementing Q5.
digit *head(digit *dt);
digit *insert_in_sorted_order(digit *sorted, digit *node);


int main(void)
{
	digit *number = NULL;
	digit *reversed = NULL;
	digit *sorted = NULL;

	number = read_number();
	print_number(number);

	reversed = reverse_number(number);
	print_number(reversed);

	sorted = sort_digits(number);
	print_number(sorted);

	free_number(sorted);
	free_number(reversed);
	free_number(number);

	return EXIT_SUCCESS;
}

// Implementation. Please don't scroll past beyond main().

digit *head(digit *dt)
{
	digit *node = NULL;

	if (dt != NULL) {
		node = create_digit(dt->num);
	}

	return node;
}

digit *insert_in_sorted_order(digit *sorted, digit *node)
{
	digit *prev = NULL;
	digit *curr = NULL;

	if (sorted == NULL) {
		return node;
	}

	curr = sorted;
	prev = NULL;

	while ((curr != NULL) && (curr->num < node->num)) {

		prev = curr;
		curr = curr->next;
	}

	if (prev == NULL) {

		node->next = sorted;
		sorted = node;
	}
	else {
		prev->next = node;
		node->next = curr;
	}

	return sorted;
}


digit *sort_digits(digit *dt)
{
	digit *sorted = NULL;

	while (dt != NULL) {

		sorted = insert_in_sorted_order(sorted, head(dt));
		dt = dt->next;
	}

	return sorted;
}


digit *insert_at_head(digit *hd, digit *node)
{
	node->next = hd;
	return node;
}

digit *reverse_number(digit *dt)
{
	digit *hd = NULL;
	digit *node = NULL;

	while (dt != NULL) {

		node = create_digit(dt->num);
		hd = insert_at_head(hd, node);
		dt = dt->next;
	}

	return hd;
}



void free_number(digit *dt)
{
	digit *next = NULL;

	while (dt != NULL) {

		next = dt->next;
		free(dt);
		dt = next;
	}

	return;
}


digit *create_digit(int num)
{
	digit *d = (digit *)malloc(sizeof(digit));
	if (d == NULL) {
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	d->num = num;
	d->next = NULL;

	return d;
}


digit *append(digit *tail, digit *node)
{
	tail->next = node;
	return node;
}

digit *read_number(void)
{
	char c = '\0';
	int n = 0;
	digit *hd = NULL;
	digit *tl = NULL;
	digit *d = NULL;

	while (true) {

		if (scanf("%c", &c) == EOF) {
			break;
		}

		if (!isdigit(c)) {
			break;
		}

		n = (int)(c - '0');
		d = create_digit(n);

		if (hd == NULL) {
			hd = d;
			tl = d;
		}
		else {
			tl = append(tl,  d);
		}
	}

	return hd;
}


void print_number(digit *dt)
{
	bool print_newline = (dt != NULL);

	while (dt != NULL) {
		printf("%d", dt->num);
		dt = dt->next;
	}

	if (print_newline) {
		puts("");
	}

	return;
}

