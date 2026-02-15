#ifndef SPI_STRUCT_H_
#define SPI_STRUCT_H_

/*************************************************************\
| --- YAENAMI v3 SPI Stream Structure Overview ---            |
| [Block 1: Global 1] (Stream [ 0: 2]) - 3 bytes              |
| [Block 2: Channel]  (Stream [ 3:58]) - 7 bytes * 8 channels |
| [Block 3: Global 2] (Stream [59:60]) - 2 bytes              |
\*************************************************************/

namespace yaenami_v3_spi {

// ==========================================================
// SPI Configuration Structs
// ==========================================================
namespace cfg {

// --- Block 1: Global Configuration1 -------------
struct Pll_Serializer {
  const uint8_t EXT_CLK		 = 0;	     // [0].[7:7]
  const uint8_t SDIF_ADC_CLK_POL = 1;	     // [0].[6:6]
  const uint8_t NC		 = 1;	     // [0].[5:5]
  uint8_t       DO_TP_EN	 = 0;	     // [0].[4:4]
  const uint8_t REF_DIV_CONT	 = 0b00;     // [0].[3:2]
  const uint8_t OSC_R		 = 0;	     // [0].[1:1]
  const uint8_t CLK_OUT_POL	 = 0;	     // [0].[0:0]
  const uint8_t IBAMP		 = 0b10;     // [1].[7:6]
  const uint8_t IBCP		 = 0b10;     // [1].[5:4]
  const uint8_t OSC_CONT	 = 0;	     // [1].[3:0]
  const uint8_t OSC_EN		 = 1;	     // [2].[7:7]
  const uint8_t DIV_CONT	 = 0;	     // [2].[6:5]
  const uint8_t N_CONT		 = 0b0'1000; // [2].[4:0]

  Pll_Serializer() = default;
};

// --- Block 2: Channel Configuration -------------
struct Channel {
  uint8_t        ADC_R    = 0;		    // [0].[7:7]
  const uint8_t  NC0      = 0;		    // [0].[6:6]
  uint8_t        S2D_GAIN = 0b10;	    // [0].[5:4]
  uint8_t        TP_EN    = 0;		    // [0].[3:3]
  uint8_t        A_MON    = 0;		    // [0].[2:2]
  uint16_t       VB_SIPM  = 0b10'0000'0000; // [0].[1:0], [1].[7:0]
  uint16_t       VTH_COMP = 0b10'0000'1000; // [2].[7:0], [3].[7:6]
  const uint8_t  NC1      = 0;		    // [3].[5:5]
  uint8_t        MIN_ENB  = 1;		    // [3].[4:4]
  const uint8_t  NC2      = 0;		    // [3].[3:3]
  uint8_t        DO_POL   = 0;		    // [3].[2:2]
  uint8_t        COMP_POL = 0;		    // [3].[1:1]
  uint8_t        MIN_CAP  = 0b0000;	    // [3].[0:0], [4].[7:5]
  uint8_t        MIN_DLY  = 0b111;	    // [4].[4:2]
  uint8_t        R_SHP2   = 0b000;	    // [4].[1:0], [5].[7:7]
  uint8_t        C_SHP    = 0b111;	    // [5].[6:4]
  uint8_t        R_SHP1   = 0b111;	    // [5].[3:1]
  uint8_t        C_VGA1   = 0b000;	    // [5].[0:0], [6].[7:6]
  const uint8_t  NC3      = 0b000;	    // [6].[5:3]
  uint8_t        C_VGA2	  = 0b111;	    // [6].[2:0]

  Channel() = default;
};

// --- Block 3: Global Configuration2 -------------
struct Adc_Vcm_Dac
{
  uint8_t        PRBS_EN   = 1;		     // STR[0].[7:7]
  uint8_t        CAL_EN    = 0;		     // STR[0].[6:6]
  uint8_t        CAL_R     = 0;		     // STR[0].[5:5]
  const uint8_t  SAM_WD    = 0b01;	     // STR[0].[4:3]
  uint8_t        PRBS_MODE = 1;		     // STR[0].[2:2]
  const uint16_t VCM_DAC   = 0b10'0000'0000; // STR[0].[1:0], STR[1].[7:0]

  Adc_Vcm_Dac() = default;
};
} // namespace cfg


// ==========================================================
// Bit Mask Definition
// ==========================================================
namespace mask {

// --- Block 1 ------------------------------------
const uint8_t EXT_CLK	       = 0b1;
const uint8_t SDIF_ADC_CLK_POL = 0b1;
const uint8_t NC	       = 0b1;
const uint8_t DO_TP_EN	       = 0b1;
const uint8_t REF_DIV_CONT     = 0b11;
const uint8_t OSC_R	       = 0b1;
const uint8_t CLK_OUT_POL      = 0b1;
const uint8_t IBAMP	       = 0b11;
const uint8_t IBCP	       = 0b11;
const uint8_t OSC_CONT	       = 0b1111;
const uint8_t OSC_EN	       = 0b1;
const uint8_t DIV_CONT	       = 0b11;
const uint8_t N_CONT	       = 0b1'1111;

// --- Block 2 ------------------------------------
const uint8_t  ADC_R	       = 0b1;
const uint8_t  NC0	       = 0b1;
const uint8_t  S2D_GAIN	       = 0b11;
const uint8_t  TP_EN	       = 0b1;
const uint8_t  A_MON	       = 0b1;
const uint16_t VB_SIPM_UPPER   = 0b11'0000'0000;
const uint16_t VB_SIPM_LOWER   = 0b00'1111'1111;
const uint16_t VTH_COMP_UPPER  = 0b11'1111'1100;
const uint16_t VTH_COMP_LOWER  = 0b00'0000'0011;
const uint8_t  NC1	       = 0b1;
const uint8_t  MIN_ENB	       = 0b1;
const uint8_t  NC2	       = 0b1;
const uint8_t  DO_POL	       = 0b1;
const uint8_t  COMP_POL	       = 0b1;
const uint8_t  MIN_CAP_UPPER   = 0b1000;
const uint8_t  MIN_CAP_LOWER   = 0b0111;
const uint8_t  MIN_DLY	       = 0b111;
const uint8_t  R_SHP2_UPPER    = 0b110;
const uint8_t  R_SHP2_LOWER    = 0b001;
const uint8_t  C_SHP	       = 0b111;
const uint8_t  R_SHP1	       = 0b111;
const uint8_t  C_VGA1_UPPER    = 0b100;
const uint8_t  C_VGA1_LOWER    = 0b011;
const uint8_t  NC3	       = 0b111;
const uint8_t  C_VGA2	       = 0b111;

// --- Block 3 ------------------------------------
const uint8_t  PRBS_EN	       = 0b1;
const uint8_t  CAL_EN	       = 0b1;
const uint8_t  CAL_R	       = 0b1;
const uint8_t  SAM_WD	       = 0b11;
const uint8_t  PRBS_MODE       = 0b1;
const uint16_t VCM_DAC_UPPER   = 0b11'0000'0000;
const uint16_t VCM_DAC_LOWER   = 0b00'1111'1111;
} // namespace mask


// ==========================================================
// Bit Shift Definition
// ==========================================================
namespace shift {

// --- Block 1 ------------------------------------
const uint8_t EXT_CLK	       = 7;
const uint8_t SDIF_ADC_CLK_POL = 6;
const uint8_t NC	       = 5;
const uint8_t DO_TP_EN	       = 4;
const uint8_t REF_DIV_CONT     = 2;
const uint8_t OSC_R	       = 1;
const uint8_t CLK_OUT_POL      = 0;

const uint8_t IBAMP	       = 6;
const uint8_t IBCP	       = 4;
const uint8_t OSC_CONT	       = 0;

const uint8_t OSC_EN	       = 7;
const uint8_t DIV_CONT	       = 5;
const uint8_t N_CONT	       = 0;

// --- Block 2 ------------------------------------
const uint8_t ADC_R	       = 7;
const uint8_t NC0	       = 6;
const uint8_t S2D_GAIN	       = 4;
const uint8_t TP_EN	       = 3;
const uint8_t A_MON	       = 2;
const uint8_t VB_SIPM_UPPER    = 8; // to right

const uint8_t VB_SIPM_LOWER    = 0;

const uint8_t VTH_COMP_UPPER   = 2; // to right

const uint8_t VTH_COMP_LOWER   = 6;
const uint8_t NC1	       = 5;
const uint8_t MIN_ENB	       = 4;
const uint8_t NC2	       = 3;
const uint8_t DO_POL	       = 2;
const uint8_t COMP_POL	       = 1;
const uint8_t MIN_CAP_UPPER    = 3; // to right

const uint8_t MIN_CAP_LOWER    = 5;
const uint8_t MIN_DLY	       = 2;
const uint8_t R_SHP2_UPPER     = 1; // to right

const uint8_t R_SHP2_LOWER     = 7;
const uint8_t C_SHP	       = 4;
const uint8_t R_SHP1	       = 1;
const uint8_t C_VGA1_UPPER     = 2; // to right

const uint8_t C_VGA1_LOWER     = 5;
const uint8_t NC3	       = 3;
const uint8_t C_VGA2	       = 0;

// --- Block 3 ------------------------------------
const uint8_t PRBS_EN	       = 7;
const uint8_t CAL_EN	       = 6;
const uint8_t CAL_R	       = 5;
const uint8_t SAM_WD	       = 3;
const uint8_t PRBS_MODE	       = 2;
const uint8_t VCM_DAC_UPPER    = 8; // to right

const uint8_t VCM_DAC_LOWER    = 0;
} // napmespace shift

} // namespace yaenami_v3_spi

#endif
