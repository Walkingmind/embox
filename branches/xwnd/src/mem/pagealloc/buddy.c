/**
 * @file
 * @brief multipage allocator buddy algorithm
 * @details Use `page allocator' when we need allocate or free only one page,
 * else see `multipage allocator' or `malloc'.
 *
 * @date 01.07.10
 * @author Fedor Burdun
 */

/**
 * `taddr' is index in binary tree
 * left child of node with index `addr' is addr*2
 * right child -/-/- is addr*2+1
 * addr of root is 1
 *
 * BITS:
 *  1 - left subtree partially released
 *  2 - right subtree partially released
 *  4 - node is released or released all of chlidren
 *  8 - node isn't in heap
 */

/* MY code MARKS
 * TFMBR - this function must be rewriting
 * TFwR  - this function was rewriting
 * TFW   - this function work (while don't see any bugs)
 */

#include <errno.h>
#include <lib/list.h>
#include <mem/page.h>
#include <embox/unit.h>

EMBOX_UNIT_INIT(page_alloc_init);


extern char *_heap_start;
extern char *_heap_end;
# define HEAP_START_PTR 	_heap_start
# define HEAP_END_PTR		_heap_end

#define PAGE_QUANTITY \
	( (((size_t) HEAP_END_PTR - (size_t) HEAP_START_PTR) ) / PAGE_SIZE() )

#define SET_BIT1(ind,bit) set_bits( ind , get_bits(ind) | (bit) )
#define SET_BIT0(ind,bit) set_bits( ind , get_bits(ind) & (255^(bit)) )
#define HAS_BIT(ind,bit) ( get_bits(ind) & (bit) )

#if 1
# define ANY_OPTIMIZATION
#endif


typedef struct block_info {
	struct list_head *next, *prev;
	size_t size;
	bool free;
} block_info_t;

typedef size_t taddr; /* addres in tree */
static char* heap_start; /* real heap_start */
static size_t sizeofpool; /* real size of heap */
//static int hasinit = 0;
static size_t maxblocksize; /* size of real max block (may be not root) */
static size_t rootblocksize; /* size of root block */

/**
 * bit pack
 * no real bit pack. only array mapping
 * addr - 1 because root is 1
 */
static inline void set_bits(taddr addr, char bit) {
	(HEAP_START_PTR)[addr - 1] = bit;
}

static inline char get_bits(taddr addr) {
	return (HEAP_START_PTR)[addr - 1];
}

/**
 * initialization of tree
 * Mark block if it isn't in heap.
 *
 * return 1 if subtree isn't in heap
 * return 0 if node with subtree is in heap
 */
static int dfs_init(taddr addr, char * ptr, size_t size) {
	int marked = 0;

	if ((ptr + (size * PAGE_SIZE())) <= HEAP_END_PTR) {
		/* block is in heap */
		set_bits(addr, 0);
	} else {
		/* block isn't in heap */
		set_bits(addr, 8);
		marked = 1;
	}

	/* if it's no leaf */
	if (size > 1) {
		/* initialize left subtree */
		if (dfs_init(2 * addr, ptr, size / 2)) {
			SET_BIT1( addr , 1 );
			marked = 1;
		}
		/* initialize right subtree */
		if (dfs_init(2 * addr + 1, ptr + PAGE_SIZE() * size / 2, size / 2)) {
			SET_BIT1( addr , 2 );
			marked = 1;
		}
	}
	return marked;
}

/**
 * initialization of allocator
 */
static int page_alloc_init(void) {
	int sizeoftree;
	int qpt;

	int page_quantity = PAGE_QUANTITY;
	/* calculate maxblocksize */
	for (rootblocksize = 1; rootblocksize < page_quantity; rootblocksize *= 2)
		;
	sizeoftree = 2 * rootblocksize; /* one byte for one page (no bit pack) */

	/* (sizeoftree - 1) / 0x1000 + 1 // quantity of pages for tree */
	qpt = ((sizeoftree - 1) / PAGE_SIZE() + 1);

	heap_start = (HEAP_START_PTR) + PAGE_SIZE() * qpt;
	sizeofpool = PAGE_QUANTITY - qpt;

	maxblocksize = rootblocksize == sizeofpool ? rootblocksize : rootblocksize
			/ 2;

	dfs_init(1, heap_start, rootblocksize);
	return 0;
}

/**
 * convert place in tree to pointer
 */
static void * taddr_to_ptr(taddr addr) {

	for (; addr < rootblocksize; addr *= 2)
		;
	return heap_start + (addr - rootblocksize) * PAGE_SIZE();
}

/**
 * check block for alloc
 */
static inline int is_avail(taddr addr) {
	return !get_bits(addr);
}

/**
 * check block in heap or not
 */
static inline int in_heap(taddr addr, size_t length) {
	return (((unsigned long) taddr_to_ptr(addr) + (unsigned long) length
			* PAGE_SIZE()) <= (unsigned long) HEAP_END_PTR);
}

/**
 * find first available proper block for reserve.
 * return 0 if same block don't exist.
 */
static taddr dfs_find(taddr lroot, size_t cursize, size_t size) {
	/* must check above that size != 0 */
	taddr child_return;
	/* enough codition ( it's reserved or no proper )
	 (if lroot not belongs main tree, than cursize == 0) */
	if (cursize < size || HAS_BIT( lroot , 4 ))
		return 0;
	/* find in left subtree */
	if ((child_return = dfs_find(lroot * 2, cursize / 2, size)))
		return child_return;
	/* find in right subtree */
	if ((child_return = dfs_find(lroot * 2 + 1, cursize / 2, size)))
		return child_return;
	/* may be it is current block*/
	if (is_avail(lroot) && in_heap(lroot, cursize))
		return lroot;
	/* no exist proper block */
	return 0;
}

/**
 * allocator
 */
void * page_alloc(size_t size) {
	taddr block, parent, taddr_fr;

	/* initialization of allocator */
#if 0
	if (!hasinit) {
		multipage_init();
		hasinit = 1;
	}
#endif

	/* find proper block */
	if (!(block = dfs_find( /* root of tree */1, rootblocksize, size)))
		return NULL; /* no exist proper block */

	set_bits(block, 4);
	taddr_fr = block;
	for (; block > 1; block = parent) {
		parent = block >> 1;
		SET_BIT1( parent , block & 1 ? 2 : 1 );
		/* mark from left or right child for node */
#ifdef ANY_OPTIMIZATION
		/* if children was released then parent released */
		if (HAS_BIT(block, 4) && HAS_BIT(block^1, 4)) {
			SET_BIT1(parent , 4);
		}
#endif
	}
	return taddr_to_ptr(taddr_fr);
}

/**		TFMBR
 * free block, that was allocated
 */
void page_free(void * ptr, size_t size) {
	taddr parent, before, addr;
	// TODO addr and addr, wtf? -- sikmir, Eldar
	addr = ((size_t) ptr - (size_t) heap_start) / PAGE_SIZE();
	addr = rootblocksize + ((size_t) ptr - (size_t) heap_start)
			/ PAGE_SIZE();
	/* in OLD version was different and WORK!!! */
	for (before = 0; (addr > 0) && (!get_bits(addr)) && !(before & 1); addr
			= (before = addr) >> 1)
		;
	/* addr was allocated */
	if (get_bits(addr) == 4) { /* else if don't equal 0 algorithm has ERROR!!! */
#ifdef ANY_OPTIMIZATION
		/* now exist alow block */
		for (parent = addr; parent >= 1; parent >>= 1) {
			SET_BIT0(parent, 4);
		}
#else
		set_bits(addr, 0);
#endif
		/* it code wrong! */
		for (; addr > 1;) {
			/* expected that bits[addr] == 0 */
			parent = addr >> 1;
			SET_BIT0(parent,addr & 1 ? 2 : 1); /* unmark from left or right child for node */
			/* if unmarked left or right node then unmark parent (needed mark) */
			/* if (!(get_bits(parent) | get_bits(parent^1))) { */
			if (!get_bits(parent)) {
				addr = parent;
			} else {
				break;
			}
			addr = parent;
		}
	}
}


#if 0
/**
 * convert place in tree to block size
 */
static int get_block_size(taddr addr) {
	int i;
	for (i = 1; i <= addr; i *= 2)
		;
	return rootblocksize / (i / 2);
}

/**
 * find all free and busy blocks
 */
static void dfs_stat(taddr addr, struct list_head* list) {
	if (!get_bits(addr)) {
		block_info_t* tmp_info = (block_info_t*) malloc(sizeof(block_info_t));
		tmp_info->size = get_block_size(addr);
		tmp_info->free = true;
		list_add((struct list_head*) tmp_info, list);
		return;
	}

	if (HAS_BIT(addr, 4) && !HAS_BIT(addr, 1) && !HAS_BIT(addr, 2)) {
		block_info_t* tmp_info = (block_info_t*) malloc(sizeof(block_info_t));
		tmp_info->size = get_block_size(addr);
		tmp_info->free = false;
		list_add((struct list_head*) tmp_info, list);
		return;
	}

	if (addr < rootblocksize) {
		dfs_stat(addr * 2, list);
		dfs_stat(addr * 2 + 1, list);
	}
}

/**
 * return list of free and busy blocks in heap
 */
void mpget_blocks_info(struct list_head* list) {
	if (!hasinit) {
		multipage_init();
		hasinit = 1;
	}

	dfs_stat(1, list);
}
#endif
