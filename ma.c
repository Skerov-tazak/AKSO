#include "ma.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

uint64_t* undefined;
uint64_t disconnected;

struct moore{

	void (*transition_function_t)(uint64_t *next_state, uint64_t const *input,
                                      uint64_t const *state, size_t n, size_t s);
	
	void (*output_function_t)(uint64_t *output, uint64_t const *state,
                                  size_t m, size_t s);

	size_t in;
	size_t num;
	size_t out;
	
	
	uint64_t*** prev_machine;
	uint64_t* inputs;
	uint64_t* state;
	uint64_t* output;
	uint64_t** next_machine;
};

moore_t * ma_create_full(size_t n, size_t m, size_t s, transition_function_t t,
		output_function_t y, uint64_t const *q){

	if(n == 0 || m == 0 || q == NULL || t == NULL || y == NULL)
	{
		errno = EINVAL;
		return NULL;
	}
	
	moore_t* new_moore;
	new_moore = (moore_t*)malloc(sizeof(moore_t));
	if(new_moore == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	new_moore->output_function_t = y;
	new_moore->transition_function_t = t;
	new_moore->in = n;
	new_moore->num = s;
	new_moore->out = m;

	new_moore->prev_machine = (uint64_t***)calloc(new_moore->in, sizeof(uint64_t*));
	new_moore->next_machine = (uint64_t**)calloc(new_moore->in, sizeof(uint64_t*));
	new_moore->inputs = (uint64_t*)calloc(new_moore->in, sizeof(uint64_t));
	new_moore->state = (uint64_t*)calloc((new_moore->num), sizeof(uint64_t));
	new_moore->output = (uint64_t*)calloc((new_moore->out), sizeof(uint64_t));
	if(new_moore->prev_machine == NULL || new_moore->next_machine == NULL || new_moore->state == NULL || new_moore->inputs == NULL || new_moore->output == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	for(int i = 0; i < new_moore->in; i++)
	{	
		new_moore->prev_machine[i] = &undefined;
		new_moore->next_machine[i] = &disconnected;
	}
	memcpy(new_moore->state, q, s * sizeof(uint64_t));

	return new_moore;
}

void identity(uint64_t* output, uint64_t const *state, size_t s, size_t m)
{
	if( s != m )
	{
		errno = EINVAL;
		return;
	}

	memcpy(output, state, sizeof(uint64_t) * m);
}

moore_t* ma_create_simple(size_t n, size_t s, transition_function_t t){
	
	uint64_t* zero_state = (uint64_t*)malloc(sizeof(uint64_t) * s);
	return ma_create_full(n, s, s, t, identity, zero_state);
}

void ma_delete(moore_t *a)
{

	
}

int ma_connect(moore_t *a_in, size_t in, moore_t *a_out, size_t out, size_t num)
{
		
	// ADD SAFEGUARDS
		
	for(int i = 0; i < num; i++)
	{
		*(a_in->inputs + in + i) = *(a_out->output + out + i);
		*(a_in->prev_machine + in + i) = (a_out->next_machine + out + i);
		*(a_out->next_machine + out + i) = (a_in->inputs + in + i);
	}
	
}

int ma_disconnect(moore_t *a_in, size_t in, size_t num)
{
	// ADD SAFEGUARDS

	for(int i = 0; i < num; i++)
	{
		(a_in->prev_machine + i + in)->next_machine

	}
	
	
}

int ma_set_input(moore_t *a, uint64_t const *input)
{
	// ADD SAFEGUARDS

	for(int i = 0; i < a->in; i++)
	{
		if(*(a->prev_machine + i) == &undefined)
		{
			*(a->inputs + i) = *(input + i);		
		}
	}
}

int ma_set_state(moore_t *a, uint64_t const *state)
{
	// ADD SAFEGUARDS
	
	memcpy(a->state, state, a->num);
}

uint64_t const * ma_get_output(moore_t const *a)
{
	// ADD SAFEGUARDS
	
	return a->output;

}
	

int ma_step(moore_t *at[], size_t num)
{
	// ADD SAFEGUARDS

	for(int i = 0; i < num; i++)
	{
		(*at[i]->output_function_t)(at[i]->output, at[i]->state, at[i]->out, at[i]->num);
		(*(at[i]->transition_function_t))(at[i]->state, at[i]->inputs, at[i]->state, at[i]->in, at[i]->num);	
	}

}


