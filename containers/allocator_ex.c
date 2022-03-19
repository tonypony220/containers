/** Header structure for linear buffer. */
typedef struct _LinearBuffer {
	uint8_t  *mem;      /*!< Pointer to buffer memory. */
	uint32_t totalSize; /*!< Total size in bytes. */
	uint32_t offset;    /*!< Offset. */
} LinearBuffer;

/* non-aligned allocation from linear buffer. */
void* linearBufferAlloc(LinearBuffer* buf, uint32_t size) {

	if(!buf || !size)
		return NULL;
	
	uint32_t newOffset = buf->offset + size;
	if(newOffset <= buf->totalSize) {
		void * ptr = buf->mem + buf->offset;
		buf->offset = newOffset;
		return ptr;
	}
	return NULL; /* out of memory */
}


/* STUCK ALLOCATOR */
typedef uint32_t StackHandle;

void* stackBufferAlloc(StackBuffer* buf, uint32_t size, StackHandle* handle) {

	if(!buf || !size)
		return NULL;

	const uint32_t currOffset = buf->offset;
	if(currOffset + size <= buf->totalSize) {
		uint8_t * ptr = buf->mem + currOffset;
		buf->offset += size;
		if(handle)
			*handle = currOffset; /* set the handle to old offset */
		return (void*)ptr;
	}
	return NULL;
}

void stackBufferSet(StackBuffer* buf, StackHandle handle) {
	buf->offset = handle;
	return;
}

/* PULL STACK */
//* allocate a chunk from the pool. */
void* poolAlloc(Pool * buf) {

	if(!buf)
		return NULL;

	if(!buf->head)
		return NULL; /* out of memory */

	uint8_t * currPtr = buf->head;
	buf->head = (*((uint8_t**)(buf->head)));
	return currPtr;
}


/* return a chunk to the pool. */
void poolFree(Pool* buf, void* ptr) {


	if(!buf || !ptr)
		return;

	*((uint8_t**)ptr) = buf->head;
	buf->head = (uint8_t*)ptr;
	return;
}


/* initialise the pool header structure, and set all chunks in the pool as empty. */
void poolInit(Pool* buf, uint8_t* mem, uint32_t size, uint32_t chunkSize) {

	if(!buf || !mem || !size || !chunkSize)
		return;

	const uint32_t chunkCount = (size / chunkSize) - 1;
	for(uint32_t chunkIndex=0; chunkIndex<chunkCount; ++chunkIndex) {
		uint8_t* currChunk = mem + (chunkIndex * chunkSize);
		*((uint8_t**)currChunk) = currChunk + chunkSize;
	}

	*((uint8_t**)&mem[chunkCount * chunkSize]) = NULL; /* terminating NULL */
	buf->mem = buf->head = mem;
		return;
} 







