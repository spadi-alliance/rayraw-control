#ifndef SPI_CONFIG_LOADER_H_
#define SPI_CONFIG_LOADER_H_

#include <cstdint>
#include "rayraw_const.hh"
#include "SPI_struct.hh"

namespace spi_cfg = yaenami_v3_spi::cfg;

class SPIConfigLoader
{
public :
  SPIConfigLoader();

  // void read_EXT_CLK();
  // void read_SDIF_ADC_CLK_POL();
  // void read_SDIF_Rn();
  // void read_ENB_CRC();
  // void read_OSC_R();
  // void read_CLK_OUT_POL();
  // void read_TP_MASK();
  // void read_AMON();
  // void read_MPPC_BIAS();
  // void read_VTH_COMP();
  // void read_RF_B_SHP();
  // void read_C_B_SHP();
  // void read_RIN_B_SHP();
  // void read_CIN_B_VGA();
  // void read_CF_B_VGA();
  // void read_SPI_Values();
  // void make_RegisterValues();

  void read_DO_TP_EN();
  void read_TP_EN();
  void read_A_MON();
  void read_VB_SIPM();
  void read_VTH_COMP();
  void read_MIN_ENB();
  void read_DO_POL();
  void read_COMP_POL();
  // void read_MIN_CAP();
  void read_MIN_DLY();
  void read_R_SHP2();
  void read_C_SHP();
  void read_R_SHP1();
  void read_C_VGA1();
  void read_C_VGA2();
  void make_RegisterValues();

  static SPIConfigLoader& get_instance();

private :
  // SPI_PLL_SDIF m_SPI_PLL_SDIF[NumOfYaenami];
  // SPI_CH       m_SPI_CH[NumOfYaenami][NumOfCh];
  // SPI_ADC_VCM_DAC m_SPI_ADC_VCM_DAC[NumOfYaenami];
  spi_cfg::Pll_Serializer m_spi_pll_ser[NumOfYaenami]{};
  spi_cfg::Channel        m_spi_ch[NumOfYaenami][NumOfCh]{};
  spi_cfg::Adc_Vcm_Dac    m_spi_adc_vcm_dac[NumOfYaenami]{};

  uint8_t DO_TP_EN[NumOfYaenami];

  uint8_t  ADC_R[NumOfYaenami][NumOfCh];
  uint8_t  TP_EN[NumOfYaenami][NumOfCh];
  uint8_t  A_MON[NumOfYaenami][NumOfCh];
  uint16_t VB_SIPM[NumOfYaenami][NumOfCh];
  uint16_t VTH_COMP[NumOfYaenami][NumOfCh];
  uint8_t  MIN_ENB[NumOfYaenami][NumOfCh];
  uint8_t  DO_POL[NumOfYaenami][NumOfCh];
  uint8_t  COMP_POL[NumOfYaenami][NumOfCh];
  uint8_t  MIN_CAP[NumOfYaenami][NumOfCh];
  uint8_t  MIN_DLY[NumOfYaenami][NumOfCh];
  uint8_t  R_SHP2[NumOfYaenami][NumOfCh];
  uint8_t  C_SHP[NumOfYaenami][NumOfCh];
  uint8_t  R_SHP1[NumOfYaenami][NumOfCh];
  uint8_t  C_VGA1[NumOfYaenami][NumOfCh];
  uint8_t  C_VGA2[NumOfYaenami][NumOfCh];

  uint8_t  PRBS_EN[NumOfYaenami];
  uint8_t  CAL_EN[NumOfYaenami];
  uint8_t  CAL_R[NumOfYaenami];
  uint8_t  PRBS_MODE[NumOfYaenami];

  // --- V1 -----------------------------
  // int EXT_CLK[4];
  // int SDIF_ADC_CLK_POL[4];
  // int SDIF_Rn[4];
  // int ENB_CRC[4];
  // int OSC_R[4];
  // int CLK_OUT_POL[4];
  // int TP_MASK[4][8];
  // int AMON[4][8];
  // int MPPC_BIAS[4][8];
  // int VTH_COMP[4][8];
  // int RF_B_SHP[4][8];
  // int C_B_SHP[4][8];
  // int RIN_B_SHP[4][8];
  // int CIN_B_VGA[4][8];
  // int CF_B_VGA[4][8];

  void initialize_SPI_Values();
};

// __________________________________________________________
inline SPIConfigLoader&
SPIConfigLoader::get_instance()
{
  static SPIConfigLoader inst;
  return inst;
}


#endif
