#ifndef _VFP2CMACROS_H__
#define _VFP2CMACROS_H__

// defines for easier access to VFP parameters (1 based)
// by value
#define p1 (parm->p[0].val)
#define p2 (parm->p[1].val)
#define p3 (parm->p[2].val)
#define p4 (parm->p[3].val)
#define p5 (parm->p[4].val)
#define p6 (parm->p[5].val)
#define p7 (parm->p[6].val)
#define p8 (parm->p[7].val)
#define p9 (parm->p[8].val)
#define p10 (parm->p[9].val)
#define p11 (parm->p[10].val)
#define p12 (parm->p[11].val)
#define p13 (parm->p[12].val)
#define p14 (parm->p[13].val)
#define p15 (parm->p[14].val)
#define p16 (parm->p[15].val)
#define p17 (parm->p[16].val)
#define p18 (parm->p[17].val)
#define p19 (parm->p[18].val)
#define p20 (parm->p[19].val)
#define p21 (parm->p[20].val)
#define p22 (parm->p[21].val)
#define p23 (parm->p[22].val)
#define p24 (parm->p[23].val)
#define p25 (parm->p[24].val)
#define p26 (parm->p[25].val)

// by reference
#define r1 (parm->p[0].loc)
#define r2 (parm->p[1].loc)
#define r3 (parm->p[2].loc)
#define r4 (parm->p[3].loc)
#define r5 (parm->p[4].loc)
#define r6 (parm->p[5].loc)
#define r7 (parm->p[6].loc)
#define r8 (parm->p[7].loc)
#define r9 (parm->p[8].loc)
#define r10 (parm->p[9].loc)
#define r11 (parm->p[10].loc)
#define r12 (parm->p[11].loc)
#define r13 (parm->p[12].loc)
#define r14 (parm->p[13].loc)
#define r15 (parm->p[14].loc)
#define r16 (parm->p[15].loc)
#define r17 (parm->p[16].loc)
#define r18 (parm->p[17].loc)
#define r19 (parm->p[18].loc)
#define r20 (parm->p[19].loc)
#define r21 (parm->p[20].loc)
#define r22 (parm->p[21].loc)
#define r23 (parm->p[22].loc)
#define r24 (parm->p[23].loc)
#define r25 (parm->p[24].loc)
#define r26 (parm->p[25].loc)

// count of parameters passed
#define PCount() (parm->pCount)

#endif // _VFP2CMACROS_H__