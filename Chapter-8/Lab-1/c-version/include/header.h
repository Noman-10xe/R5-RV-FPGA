
// Seven - Segments Display Registers (memory map)
#define En_REG    0x80001038
#define DIGITS_REG   0x8000103C

// PTC Registers
#define RPTC_CNTR 0x80001200
#define RPTC_HRC  0x80001204
#define RPTC_LRC  0x80001208
#define RPTC_CTRL 0x8000120C

// Macros to read/write Registers
#define READ_Reg(dir) (*(volatile unsigned *)dir)
#define WRITE_Reg(dir, value) { (*(volatile unsigned *)dir) = (value); }

