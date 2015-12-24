#ifndef _EINK_H
#define _EINK_H

#include <hal.h>

#define EINK_CLOCKDELAY 4
#ifndef EINK_CLOCKDELAY
#       define EINK_CLOCKDELAY 0
#endif

/** Delay between signal changes, to give time for IO pins to change state. */
static inline void clockdelay(void)
{
#if EINK_CLOCKDELAY & 1
    asm("nop");
#endif
#if EINK_CLOCKDELAY & 2
    asm("nop");
    asm("nop");
#endif
#if EINK_CLOCKDELAY & 4
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
#endif
#if EINK_CLOCKDELAY & 8
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
#endif
}

static inline void setpower_vdd(bool on) {
		palWritePad(GPIOB, GPIOB_EINK_VDD, on);
		palWritePad(GPIOC, GPIOC_SMPS_ON, !on);
		palWritePad(GPIOC, GPIOC_POS_ON, !on);
}

/* Delay for display waveforms. Should be an accurate microsecond delay. */
static void eink_delay(int us)
{
    //chThdSleepMicroseconds(us);
				// int a;
				// for(a = 0; a < us;a++)
				// 	clockdelay();
				chSysPolledDelayX(US2ST(us));
}


/* Turn the E-ink panel negative supplies (-15V, -20V) on or off. */
static inline void setpower_vneg(bool on) {
		palWritePad(GPIOC, GPIOC_NEG_EN, on);
}

/* Turn the E-ink panel positive supplies (-15V, -20V) on or off. */
static inline void setpower_vpos(bool on) {
		palWritePad(GPIOC, GPIOC_POS_EN, on);
}

/* Set the state of the LE (source driver Latch Enable) pin. */
static inline void setpin_le(bool on) {
    palWritePad(GPIOC, GPIOC_EINK_LE, on);
}

/* Set the state of the OE (source driver Output Enable) pin. */
static inline void setpin_oe(bool on) {
    palWritePad(GPIOC, GPIOC_EINK_OE, on);
}

/* Set the state of the CL (source driver Clock) pin. */
static inline void setpin_cl(bool on) {
    palWritePad(GPIOC, GPIOC_EINK_CL, on);
}

/* Set the state of the SPH (source driver Start Pulse Horizontal) pin. */
static inline void setpin_sph(bool on) {
    palWritePad(GPIOC, GPIOC_EINK_SPH, on);
}

/* Set the state of the D0-D7 (source driver Data) pins. */
static inline void setpins_data(uint8_t value) {
    palWriteGroup(GPIOB, 0x00FF, 0, value);
}

/* Set the state of the CKV (gate driver Clock Vertical) pin. */
static inline void setpin_ckv(bool on) {
    palWritePad(GPIOC, GPIOC_EINK_CKV, on);
}

/* Set the state of the GMODE (gate driver Gate Mode) pin. */
static inline void setpin_gmode(bool on) {
    palWritePad(GPIOC, GPIOC_EINK_GMODE, on);
}

/* Set the state of the SPV (gate driver Start Pulse Vertical) pin. */
static inline void setpin_spv(bool on) {
    palWritePad(GPIOC, GPIOC_EINK_SPV, on);
}



#endif
