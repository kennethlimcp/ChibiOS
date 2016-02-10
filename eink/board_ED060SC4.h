/*
 * Copyright 2013 Petteri Aimonen <jpa@gfx.mail.kapsi.fi>
 * This file is released to the public domain.
 *
 */

/* Board interface definitions for ED060SC4 PrimeView E-ink panel.
 *
 * You should implement the following functions to define the interface to
 * the panel on your board.
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

/* Set up IO pins for the panel connection. */
static inline void init_board(GDisplay *g) {

}

/* Delay for display waveforms. Should be an accurate microsecond delay. */
static void eink_delay(int us)
{
	chSysPolledDelayX(US2ST(us));
}

/* Turn the E-ink panel Vdd supply (+3.3V) on or off. */
static inline void setpower_vdd(GDisplay *g, bool_t on) {
	palWritePad(GPIOB, GPIOB_EINK_VDD, on);
	palWritePad(GPIOC, GPIOC_SMPS_ON, !on);
	palWritePad(GPIOC, GPIOC_POS_ON, !on);
}

/* Turn the E-ink panel negative supplies (-15V, -20V) on or off. */
static inline void setpower_vneg(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_NEG_EN, on);
}

/* Turn the E-ink panel positive supplies (-15V, -20V) on or off. */
static inline void setpower_vpos(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_POS_EN, on);
}

/* Set the state of the LE (source driver Latch Enable) pin. */
static inline void setpin_le(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_EINK_LE, on);
}

/* Set the state of the OE (source driver Output Enable) pin. */
static inline void setpin_oe(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_EINK_OE, on);
}

/* Set the state of the CL (source driver Clock) pin. */
static inline void setpin_cl(GDisplay *g, bool_t on) {
	 palWritePad(GPIOC, GPIOC_EINK_CL, on);
}

/* Set the state of the SPH (source driver Start Pulse Horizontal) pin. */
static inline void setpin_sph(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_EINK_SPH, on);
}

/* Set the state of the D0-D7 (source driver Data) pins. */
static inline void setpins_data(GDisplay *g, uint8_t value) {
	palWriteGroup(GPIOA, 0xFF, GPIOA_EINK_D0, value);
}

/* Set the state of the CKV (gate driver Clock Vertical) pin. */
static inline void setpin_ckv(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_EINK_CKV, on);
}

/* Set the state of the GMODE (gate driver Gate Mode) pin. */
static inline void setpin_gmode(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_EINK_GMODE, on);
}

/* Set the state of the SPV (gate driver Start Pulse Vertical) pin. */
static inline void setpin_spv(GDisplay *g, bool_t on) {
	palWritePad(GPIOC, GPIOC_EINK_SPV, on);
}

#endif // _GDISP_LLD_BOARD_H //
