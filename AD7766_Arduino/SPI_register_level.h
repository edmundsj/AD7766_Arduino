/*
 * Author: Jordan Edmunds (jordan.e@berkeley.edu)
 * Authorized for distribution and use under CC-BY
 * 
 * This is designed to be a blazingly fast SPI transfer library,
 * which makes more assumptions than the core arduino library is
 * able to. For now, it communicates with only one device (because
 * that's all I need).
 * 
 */

// POS: bit position (0 through 31)
// MASK: bitmask (32-bit)

#define NOP __asm__ __volatile__ ("nop\n\t");
#define NOP4 NOP NOP NOP NOP
#define NOP16 NOP4 NOP4 NOP4 NOP4
#define NOP64 NOP16 NOP16 NOP16 NOP16

inline void SPISetMaster() {
  SPI0 -> SPI_MR |= SPI_MR_MSTR;
}

inline void SPIEnable() {
  SPI0 -> SPI_CR |= SPI_CR_SPIEN;
}

inline void SPIDisable() {
  SPI0 -> SPI_CR |= SPI_CR_SPIDIS;
}

inline void SPISetLastTransfer() {
  SPI0 -> SPI_CR |= SPI_CR_LASTXFER;
}

inline void SPIEnableReadInterrupt() {
  SPI0 -> SPI_IER |= SPI_IER_RDRF;
}

inline void SPIEnableTransmitInterrupt() {
  SPI0 -> SPI_IER |= SPI_IER_TDRE;
}

inline void SPIDisableReadInterrupt() {
  SPI0 -> SPI_IER &= ~SPI_IER_RDRF;
}

inline void SPIDisableTransmitInterrupt() {
  SPI0 -> SPI_IER &= ~SPI_IER_TDRE;
}

inline void SPIEnableOverrunInterrupt() {
  SPI0 -> SPI_IER |= SPI_IER_OVRES;
}

inline void SPIDisableOverrunInterrupt() {
  SPI0 -> SPI_IER &= ~SPI_IER_OVRES;
}

inline void SPISetChipSelectActiveAfterTransfer() {
  SPI0 -> SPI_CSR[0] |= SPI_CSR_CSAAT;
}

inline void SPISetClockParity0() {
  SPI0 -> SPI_CSR[0] &= ~SPI_CSR_CPOL;
}

inline void SPISetClockPhase0() {
  SPI0 -> SPI_CSR[0] &= ~SPI_CSR_NCPHA;
}

inline void SPISetClockDivider(uint32_t divisionFactor) {
  SPI0 -> SPI_CSR[0] = (SPI0 -> SPI_CSR[0] & ~SPI_CSR_SCBR_Msk) | (divisionFactor << SPI_CSR_SCBR_Pos);
}

// "Initiates a "read" by writing nonsense data to the register.
inline void SPIInitiateRead() {
  SPI0 -> SPI_TDR = 0;
}

inline void SPIBegin() {
  SPISetClockDivider(8);
  SPISetClockPhase0();
  SPISetClockParity0();
  SPISetMaster();
  
  SPIEnable();
}
