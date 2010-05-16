/**
 * @file
 *
 * @date 27.11.09
 * @author Nikolay Korotky
 */
#ifndef BITOPS_H_
#define BITOPS_H_

#define set_bit(rg, bit)  do { OVK_REGORIN(rg, (1UL << (bit))); } while(0)
#define clear_bit(rg, bit) do { OVK_REGANDIN(rg, ~(1UL << (bit))); } while(0)
#define get_bit(rg, bit)   ( ((rg) >> (bit)) & 1 )

#endif /* BITOPS_H_ */
