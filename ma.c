#include "ma.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

uint64_t sink;
struct moore{

	void (*transition_function_t)(uint64_t *next_state, uint64_t const *input,
                                      uint64_t const *state, size_t n, size_t s);
	
	void (*output_function_t)(uint64_t *output, uint64_t const *state,
                                  size_t m, size_t s);

	size_t in;
	size_t num;
	size_t out;
	
	
	uint64_t** connected_inputs;
	uint64_t* inputs;
	uint64_t* state;
	uint64_t* output;
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

	new_moore->connected_inputs = (uint64_t**)calloc(new_moore->in, sizeof(uint64_t*));
	new_moore->inputs = (uint64_t*)calloc(new_moore->in, sizeof(uint64_t));
	new_moore->state = (uint64_t*)calloc((new_moore->num), sizeof(uint64_t));
	new_moore->output = (uint64_t*)calloc((new_moore->out), sizeof(uint64_t));
	if(new_moore->connected_inputs == NULL || new_moore->state == NULL || new_moore->inputs == NULL || new_moore->output == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}

	for(int i = 0; i < new_moore->in; i++)
		new_moore->connected_inputs[i] = &sink;

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

moore_t * ma_create_simple(size_t n, size_t m, transition_function_t t){
	
	if(n == 0 || m == 0 || t == NULL)
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
	
	new_moore->in = n;
	new_moore->out = new_moore->num = m;
	new_moore->transition_function_t = t;
	new_moore->output_function_t = identity;
	
	new_moore->connected_inputs = (uint64_t**)calloc(new_moore->in, sizeof(uint64_t*));
	new_moore->inputs = (uint64_t*)calloc(new_moore->in, sizeof(uint64_t));
	new_moore->state = (uint64_t*)calloc((new_moore-> num), sizeof(uint64_t));
	new_moore->output = (uint64_t*)calloc((new_moore->out), sizeof(uint64_t));
	if(new_moore-> connected_inputs == NULL || new_moore->inputs == NULL || new_moore->output == NULL || new_moore->state == NULL)
	{
		errno = ENOMEM;
		return NULL;
	
	for(int i = 0; i < new_moore->in; i++)
		new_moore->connected_inputs[i] = &sink;}
	
	return new_moore;	
}

void ma_delete(moore_t *a){
	
}

int ma_connect(moore_t *a_in, size_t in, moore_t *a_out, size_t out, size_t num)
{
	
	

}

int ma_disconnect(moore_t *a_in, size_t in, size_t num)
{

}

int ma_set_input(moore_t *a, uint64_t const *input)
{

}

int ma_set_state(moore_t *a, uint64_t const *state)
{

}

uint64_t const * ma_get_output(moore_t const *a)
{

}
	

int ma_step(moore_t *at[], size_t num)
{

}


