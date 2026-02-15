#include "SPIConfigLoader.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <string>

#define DEBUG 1

static const std::string class_name = "SPIConfigLoader";

//----------------------------------------------------
SPIConfigLoader::SPIConfigLoader()
{
  read_DO_TP_EN();
  read_TP_EN();
  read_A_MON();
  read_VB_SIPM();
  read_VTH_COMP();
  read_MIN_ENB();
  read_DO_POL();
  read_COMP_POL();
  // read_MIN_CAP();
  read_MIN_DLY();
  read_R_SHP2();
  read_C_SHP();
  read_R_SHP1();
  read_C_VGA1();
  read_C_VGA2();

  initialize_SPI_Values();
  make_RegisterValues();

  // --- V1 -----------------------------
  // read_EXT_CLK();
  // read_SDIF_ADC_CLK_POL();
  // read_SDIF_Rn();
  // read_ENB_CRC();
  // read_OSC_R();
  // read_CLK_OUT_POL();
  // read_TP_MASK();
  // read_AMON();
  // read_MPPC_BIAS();
  // read_VTH_COMP();
  // read_RF_B_SHP();
  // read_C_B_SHP();
  // read_RIN_B_SHP();
  // read_CIN_B_VGA();
  // read_CF_B_VGA();

  // initialize_SPI_Values();
  // make_RegisterValues();
}

// __________________________________________________________
void SPIConfigLoader::read_DO_TP_EN()
{
  int i, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_DO_TP_EN.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_DO_TP_EN.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &i, &value);

    if (value == 0 || value == 1) {
    } else{
      std::cerr << "#E: The Value of 'setup_DO_TP_EN.cfg' must be 0 or 1" << std::endl;
      exit(1);
    }


    if (i < NumOfYaenami) {
      DO_TP_EN[i] = value;
    } else {
      std::cerr << "#E: Wrong setup for the number of YAENAMI in 'setup_DO_TP_EN.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_TP_EN()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_TP_EN.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_TP_EN.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    if (value == 0 || value == 1) {
    } else {
    std::cerr << "#E: Wrong setup for the value in 'setup_TP_EN.cfg'" << std::endl;
      exit(1);
    }

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      TP_EN[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_TP_EN.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_A_MON()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_A_MON.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_A_MON.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: Wrong setup for the value in 'setup_A_MON.cfg'" << std::endl;
      exit(1);
    }

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      A_MON[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_A_MON.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_VB_SIPM()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_VB_SIPM.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_VB_SIPM.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      VB_SIPM[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_VB_SIPM.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_VTH_COMP()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_VTH_COMP.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_VTH_COMP.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      VTH_COMP[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_VTH_COMP.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_MIN_ENB()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_MIN_ENB.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_MIN_ENB.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    if (value == 0 || value == 1) {
    } else{
      std::cerr << "#E: The Value of 'setup_MIN_ENB.cfg' must be 0 or 1" << std::endl;
      exit(1);
    }

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      MIN_ENB[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_MIN_ENB.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_DO_POL()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_DO_POL.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_DO_POL.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    if (value == 0 || value == 1) {
    } else{
      std::cerr << "#E: The Value of 'setup_DO_POL.cfg' must be 0 or 1" << std::endl;
      exit(1);
    }

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      DO_POL[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_DO_POL.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_COMP_POL()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_COMP_POL.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_COMP_POL.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    if (value == 0 || value == 1) {
    } else{
      std::cerr << "#E: The Value of 'setup_COMP_POL.cfg' must be 0 or 1" << std::endl;
      exit(1);
    }

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      COMP_POL[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_COMP_POL.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// // __________________________________________________________
// void SPIConfigLoader::read_MIN_CAP()
// {
//   int channel, value;
//   char buf[100];
//   FILE *fp = fopen("./setup/setup_MIN_CAP.cfg", "r");

//   if (!fp) {
//     std::cerr << "#E: Cannot open the file 'setup_MIN_CAP.cfg'" << std::endl;
//     exit(1);
//   }

//   while (1) {
//     if (fgets(buf, sizeof(buf), fp) == NULL) break;

//     if (buf[0] == '#' || buf[0] == '\n') continue;

//     sscanf(buf, "%d : %d", &channel, &value);

//     if (value < 0 || 15 < value) {
//       std::cerr << "#E: Wrong setup for the value in 'setup_MIN_CAP.cfg'" << std::endl;
//       exit(1);
//     }

//     int i  = channel / 8;
//     int ch = 7 - (channel % 8);

//     if (i < NumOfYaenami && ch < NumOfCh) {
//       MIN_CAP[i][ch] = value;
//     } else {
//       std::cerr << "#E: Wrong setup for number of channel in 'setup_MIN_ENB.cfg'" << std::endl;
//       exit(1);
//     }
//   }
//   fclose(fp);
// }

// __________________________________________________________
void SPIConfigLoader::read_MIN_DLY()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_MIN_DLY.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_MIN_DLY.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &value);

    if (value < 0 || 7 < value) {
      std::cerr << "#E: Wrong setup for the value in 'setup_MIN_DLY.cfg'" << std::endl;
      exit(1);
    }

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      MIN_DLY[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for number of channel in 'setup_MIN_DLY.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_R_SHP2()
{
  int channel, NumOfR, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_R_SHP2.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_R_SHP2.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &NumOfR);

    if (NumOfR < 1 || 4 < NumOfR) {
      std::cerr << "#E: Wrong setup for the number of registors in 'setup_R_SHP2.cfg'" << std::endl;
      exit(1);
    }

    if (NumOfR == 1) value = 4;
    if (NumOfR == 2) value = 2;
    if (NumOfR == 3) value = 1;
    if (NumOfR == 4) value = 0;

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      R_SHP2[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for the number of channel in 'setup_R_SHP2.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_C_SHP()
{
  int channel, NumOfC, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_C_SHP.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_C_SHP.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &NumOfC);

    if (NumOfC < 1 || 8 < NumOfC) {
      std::cerr << "#E: Wrong setup for the number of capacitors in 'setup_C_SHP.cfg'" << std::endl;
      exit(1);
    }

    value = NumOfC - 1;

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      C_SHP[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for the number of channel in 'setup_C_SHP.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_R_SHP1()
{
  int channel, NumOfR, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_R_SHP1.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_R_SHP1.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &NumOfR);

    if (NumOfR < 1 || 4 < NumOfR) {
      std::cerr << "#E: Wrong setup for the number of registors in 'setup_R_SHP1.cfg'" << std::endl;
      exit(1);
    }

    if (NumOfR == 1) value = 4;
    if (NumOfR == 2) value = 2;
    if (NumOfR == 3) value = 1;
    if (NumOfR == 4) value = 0;

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      R_SHP1[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for the number of channel in 'setup_R_SHP1.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_C_VGA1()
{
  int channel, NumOfC, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_C_VGA1.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_C_VGA1.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &NumOfC);

    if (NumOfC < 1 || 4 < NumOfC) {
      std::cerr << "#E: Wrong setup for the number of capasitors in 'setup_C_VGA1.cfg'" << std::endl;
      exit(1);
    }

    value = NumOfC - 1;

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      C_VGA1[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for the number of channel in 'setup_C_VGA1.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::read_C_VGA2()
{
  int channel, NumOfC, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_C_VGA2.cfg", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_C_VGA2.cfg'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;

    if (buf[0] == '#' || buf[0] == '\n') continue;

    sscanf(buf, "%d : %d", &channel, &NumOfC);

    if (NumOfC < 1 || 8 < NumOfC) {
      std::cerr << "#E: Wrong setup for the number of capasitors in 'setup_C_VGA2.cfg'" << std::endl;
      exit(1);
    }

    value = NumOfC - 1;

    int i  = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      C_VGA2[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for the number of channel in 'setup_C_VGA2.cfg'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// __________________________________________________________
void SPIConfigLoader::initialize_SPI_Values()
{
  // --- Global Configuration from user -----------
  for (int i = 0; i < NumOfYaenami; ++i) {
    m_spi_pll_ser[i].DO_TP_EN = DO_TP_EN[i];
  }

  // --- Channel Configuration from user ----------
  for (int i = 0; i < NumOfYaenami; ++i) {
    for (int ch = 0; ch < NumOfCh; ++ch) {
      m_spi_ch[i][ch].TP_EN    = TP_EN[i][ch];
      m_spi_ch[i][ch].A_MON    = A_MON[i][ch];
      m_spi_ch[i][ch].VB_SIPM  = VB_SIPM[i][ch];
      m_spi_ch[i][ch].VTH_COMP = VTH_COMP[i][ch];
      m_spi_ch[i][ch].MIN_ENB  = MIN_ENB[i][ch];
      m_spi_ch[i][ch].DO_POL   = DO_POL[i][ch];
      m_spi_ch[i][ch].COMP_POL = COMP_POL[i][ch];
      m_spi_ch[i][ch].MIN_CAP  = MIN_CAP[i][ch];
      m_spi_ch[i][ch].MIN_DLY  = MIN_DLY[i][ch];
      m_spi_ch[i][ch].R_SHP2   = R_SHP2[i][ch];
      m_spi_ch[i][ch].C_SHP    = C_SHP[i][ch];
      m_spi_ch[i][ch].R_SHP1   = R_SHP1[i][ch];
      m_spi_ch[i][ch].C_VGA1   = C_VGA1[i][ch];
      m_spi_ch[i][ch].C_VGA2   = C_VGA2[i][ch];
    }
  }
}

// __________________________________________________________
void SPIConfigLoader::make_RegisterValues()
{
  namespace shift = yaenami_v3_spi::shift;
  namespace mask  = yaenami_v3_spi::mask;

  uint8_t buf;
  std::ostringstream oss_init_0, oss_init_1, oss_init_2, oss_init_3;
  std::ostringstream oss_normal;

  static int i_stream = 0;

  for (int i = 0; i < NumOfYaenami; ++i) {
    if (DEBUG) {
      std::cout << "======= SPI Stream for YAENAMI #" << i << " =======" << std::endl;
    }

    // -------------------------------------------- //
    // [Initialize Sequence of YAENAMI]             //
    // - 0 : ADC_R = 0, CAL_EN = 1                  //
    // - 1 : ADC_R = 0, CAL_EN = 0                  //
    // - 2 : ADC_R = 1, CAL_EN = 0                  //
    // - 3 : ADC_R = 0, CAL_EN = 0                  //
    //                                              //
    // ! Note that ADC_R is valid only for ch0 !    //
    // (Refer to the RAYRAW user guide for details) //
    // -------------------------------------------- //

    oss_init_0.str("");
    oss_init_1.str("");
    oss_init_2.str("");
    oss_init_3.str("");
    oss_normal.str("");

    oss_init_0 << "./RegisterValue/initialize/YAENAMI_" << i << "_initialize-0.txt";
    oss_init_1 << "./RegisterValue/initialize/YAENAMI_" << i << "_initialize-1.txt";
    oss_init_2 << "./RegisterValue/initialize/YAENAMI_" << i << "_initialize-2.txt";
    oss_init_3 << "./RegisterValue/initialize/YAENAMI_" << i << "_initialize-3.txt";
    oss_normal << "./RegisterValue/YAENAMI_" << i << ".txt";

    FILE *fp_init_0 = fopen(oss_init_0.str().c_str(), "w");
    FILE *fp_init_1 = fopen(oss_init_1.str().c_str(), "w");
    FILE *fp_init_2 = fopen(oss_init_2.str().c_str(), "w");
    FILE *fp_init_3 = fopen(oss_init_3.str().c_str(), "w");
    FILE *fp_normal = fopen(oss_normal.str().c_str(), "w");

    if (!fp_init_0) {
      std::cerr << "#E: Cannot open the file '" << oss_init_0.str().c_str() << "'" << std::endl;
      exit(1);
    }
    if (!fp_init_1) {
      std::cerr << "#E: Cannot open the file '" << oss_init_1.str().c_str() << "'" << std::endl;
      exit(1);
    }
    if (!fp_init_2) {
      std::cerr << "#E: Cannot open the file '" << oss_init_2.str().c_str() << "'" << std::endl;
      exit(1);
    }
    if (!fp_init_3) {
      std::cerr << "#E: Cannot open the file '" << oss_init_3.str().c_str() << "'" << std::endl;
      exit(1);
    }
    if (!fp_normal) {
      std::cerr << "#E: Cannot open the file '" << oss_normal.str().c_str() << "'" << std::endl;
      exit(1);
    }

    if (DEBUG) {
      std::cout << "----- Global  Block 1 -----" << std::endl;
    }
    // --- PLL, Serializer Block -------------------------
    // SPI Stream[0]
    buf = 0x00;

    buf |= (m_spi_pll_ser[i].EXT_CLK          & mask::EXT_CLK)          << shift::EXT_CLK;
    buf |= (m_spi_pll_ser[i].SDIF_ADC_CLK_POL & mask::SDIF_ADC_CLK_POL) << shift::SDIF_ADC_CLK_POL;
    buf |= (m_spi_pll_ser[i].NC               & mask::NC)               << shift::NC;
    buf |= (m_spi_pll_ser[i].DO_TP_EN         & mask::DO_TP_EN)         << shift::DO_TP_EN;
    buf |= (m_spi_pll_ser[i].REF_DIV_CONT     & mask::REF_DIV_CONT)     << shift::REF_DIV_CONT;
    buf |= (m_spi_pll_ser[i].OSC_R	      & mask::OSC_R)            << shift::OSC_R;
    buf |= (m_spi_pll_ser[i].CLK_OUT_POL      & mask::CLK_OUT_POL)      << shift::CLK_OUT_POL;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);

    if (DEBUG) {
      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf)
		<< std::dec
		<< std::endl;

      ++i_stream;
    }

    // SPI Stream[1]
    buf = 0x00;

    buf |= (m_spi_pll_ser[i].IBAMP    & mask::IBAMP)    << shift::IBAMP;
    buf |= (m_spi_pll_ser[i].IBCP     & mask::IBCP)     << shift::IBCP;
    buf |= (m_spi_pll_ser[i].OSC_CONT & mask::OSC_CONT) << shift::OSC_CONT;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);

    if (DEBUG) {
      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf)
		<< std::dec
		<< std::endl;

      ++i_stream;
    }

    // SPI Stream[2]
    buf = 0x00;

    buf |= (m_spi_pll_ser[i].OSC_EN   & mask::OSC_EN)   << shift::OSC_EN;
    buf |= (m_spi_pll_ser[i].DIV_CONT & mask::DIV_CONT) << shift::DIV_CONT;
    buf |= (m_spi_pll_ser[i].N_CONT   & mask::N_CONT)   << shift::N_CONT;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);

    if (DEBUG) {
      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf)
		<< std::dec
		<< std::endl;

      ++i_stream;
    }


    if (DEBUG) {
      std::cout << "----- Channel  Block -----" << std::endl;
    }
    // --- Channel Block ---------------------------------
    for (int ch = 0; ch < NumOfCh; ++ch) {
      // SPI Stream[3 + ch*7]
      buf = 0x00;

      if (ch == 0) {
	buf |= (m_spi_ch[i][ch].ADC_R    & mask::ADC_R)         << shift::ADC_R;
	buf |= (m_spi_ch[i][ch].NC0      & mask::NC0)           << shift::NC0;
      } else {
	buf |= 0b0 << shift::ADC_R;
	buf |= 0b1 << shift::NC0;
      }
      buf |= (m_spi_ch[i][ch].S2D_GAIN & mask::S2D_GAIN)      << shift::S2D_GAIN;
      buf |= (m_spi_ch[i][ch].TP_EN    & mask::TP_EN)         << shift::TP_EN;
      buf |= (m_spi_ch[i][ch].A_MON    & mask::A_MON)         << shift::A_MON;
      buf |= (m_spi_ch[i][ch].VB_SIPM  & mask::VB_SIPM_UPPER) >> shift::VB_SIPM_UPPER;

      if (ch == 0) {
	fprintf(fp_init_0, "0x%02x\n", buf &= ~0x80); // ADC Reset must be 0
	fprintf(fp_init_1, "0x%02x\n", buf &= ~0x80); // ADC Reset must be 0
	fprintf(fp_init_2, "0x%02x\n", buf |=  0x80); // Assert ADC Reset
	fprintf(fp_init_3, "0x%02x\n", buf &= ~0x80); // De-assert ADC Reset
	fprintf(fp_normal, "0x%02x\n", buf &= ~0x80); // Normal mode, ADC Reset must be 0
      } else {
	// ADC Reset Register is valid only for ch0
	fprintf(fp_init_0, "0x%02x\n", buf);
	fprintf(fp_init_1, "0x%02x\n", buf);
	fprintf(fp_init_2, "0x%02x\n", buf);
	fprintf(fp_init_3, "0x%02x\n", buf);
	fprintf(fp_normal, "0x%02x\n", buf);
      }

      if (DEBUG) {
	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf &= ~0x80)
		  << std::dec;
	std::cout << " (init_0: ADC Reset = 0)" << std::endl;


	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf &= ~0x80)
		  << std::dec;
	std::cout << " (init_1: ADC Reset = 0)" << std::endl;

	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf |= 0x80)
		  << std::dec;
	std::cout << " (init_2: ADC Reset = 1)" << std::endl;

	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf &= ~0x80)
		  << std::dec;
	std::cout << " (init_3: ADC Reset = 0)" << std::endl;

	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf &= ~0x80)
		  << std::dec;
	std::cout << " (normal: ADC Reset = 0)" << std::endl;

	++i_stream;
      }

      // SPI Stream[4 + ch*7]
      buf = 0x00;

      buf |= (m_spi_ch[i][ch].VB_SIPM & mask::VB_SIPM_LOWER) << shift::VB_SIPM_LOWER;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      if (DEBUG) {
	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf)
		  << std::dec
		  << std::endl;

	++i_stream;
      }

      // SPI Stream[5 + ch*7]
      buf = 0x00;

      buf |= (m_spi_ch[i][ch].VTH_COMP & mask::VTH_COMP_UPPER) >> shift::VTH_COMP_UPPER;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      if (DEBUG) {
	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf)
		  << std::dec
		  << std::endl;

	++i_stream;
      }

      // SPI Stream[6 + ch*7]
      buf = 0x00;

      buf |= (m_spi_ch[i][ch].VTH_COMP & mask::VTH_COMP_LOWER) << shift::VTH_COMP_LOWER;
      buf |= (m_spi_ch[i][ch].NC1      & mask::NC1)            << shift::NC1;
      buf |= (m_spi_ch[i][ch].MIN_ENB  & mask::MIN_ENB)        << shift::MIN_ENB;
      buf |= (m_spi_ch[i][ch].NC2      & mask::NC2)            << shift::NC2;
      buf |= (m_spi_ch[i][ch].DO_POL   & mask::DO_POL)         << shift::DO_POL;
      buf |= (m_spi_ch[i][ch].COMP_POL & mask::COMP_POL)       << shift::COMP_POL;
      buf |= (m_spi_ch[i][ch].MIN_CAP  & mask::MIN_CAP_UPPER)  >> shift::MIN_CAP_UPPER;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      if (DEBUG) {
	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf)
		  << std::dec
		  << std::endl;

	++i_stream;
      }

      // SPI Stream[7 + ch*7]
      buf = 0x00;

      buf |= (m_spi_ch[i][ch].MIN_CAP & mask::MIN_CAP_LOWER) << shift::MIN_CAP_LOWER;
      buf |= (m_spi_ch[i][ch].MIN_DLY & mask::MIN_DLY)       << shift::MIN_DLY;
      buf |= (m_spi_ch[i][ch].R_SHP2  & mask::R_SHP2_UPPER)  >> shift::R_SHP2_UPPER;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      if (DEBUG) {
	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf)
		  << std::dec
		  << std::endl;

	++i_stream;
      }

      // SPI Stream[8 + ch*7]
      buf = 0x00;

      buf |= (m_spi_ch[i][ch].R_SHP2 & mask::R_SHP2_LOWER) << shift::R_SHP2_LOWER;
      buf |= (m_spi_ch[i][ch].C_SHP  & mask::C_SHP)        << shift::C_SHP;
      buf |= (m_spi_ch[i][ch].R_SHP1 & mask::R_SHP1)       << shift::R_SHP1;
      buf |= (m_spi_ch[i][ch].C_VGA1 & mask::C_VGA1_UPPER) >> shift::C_VGA1_UPPER;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      if (DEBUG) {
	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf)
		  << std::dec
		  << std::endl;

	++i_stream;
      }

      // SPI Stream[9 + ch*7]
      buf = 0x00;

      buf |= (m_spi_ch[i][ch].C_VGA1 & mask::C_VGA1_LOWER) << shift::C_VGA1_LOWER;
      buf |= (m_spi_ch[i][ch].NC3    & mask::NC3)          << shift::NC3;
      buf |= (m_spi_ch[i][ch].C_VGA2 & mask::C_VGA2)       << shift::C_VGA2;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      if (DEBUG) {
	std::cout << "Stream[" << i_stream << "] ";
	std::cout << "0x"
		  << std::hex
		  << std::setw(2)
		  << std::setfill('0')
		  << static_cast<int>(buf)
		  << std::dec
		  << std::endl;

	++i_stream;
      }
    } // for channel


    if (DEBUG) {
      std::cout << "----- Global  Block 2 -----" << std::endl;
    }
    // --- ADC, VCM DAC Block ----------------------------
    // SPI Stream[59]
    buf = 0x00;

    buf |= (m_spi_adc_vcm_dac[i].PRBS_EN   & mask::PRBS_EN)       << shift::PRBS_EN;
    buf |= (m_spi_adc_vcm_dac[i].CAL_EN    & mask::CAL_EN)        << shift::CAL_EN;
    buf |= (m_spi_adc_vcm_dac[i].CAL_R     & mask::CAL_R)         << shift::CAL_R;
    buf |= (m_spi_adc_vcm_dac[i].SAM_WD    & mask::SAM_WD)        << shift::SAM_WD;
    buf |= (m_spi_adc_vcm_dac[i].PRBS_MODE & mask::PRBS_MODE)     << shift::PRBS_MODE;
    buf |= (m_spi_adc_vcm_dac[i].VCM_DAC   & mask::VCM_DAC_UPPER) >> shift::VCM_DAC_UPPER;

    fprintf(fp_init_0, "0x%02x\n", buf |=  0x40); // Assert ADC Calibration
    fprintf(fp_init_1, "0x%02x\n", buf &= ~0x40); // De-asser ADC Calibration
    fprintf(fp_init_2, "0x%02x\n", buf &= ~0x40); // ADC Calibration must be 0
    fprintf(fp_init_3, "0x%02x\n", buf &= ~0x40); // ADC Calibration must be 0
    fprintf(fp_normal, "0x%02x\n", buf &= ~0x40); // Normal mode, ADC Calibration must be 0


    if (DEBUG) {
      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf |= 0x40)
		<< std::dec;
      std::cout << "(init_0: CAL_EN = 1)"<< std::endl;

      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf &= ~0x40)
		<< std::dec;
      std::cout << "(init_1: CAL_EN = 0)"<< std::endl;

      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf &= ~0x40)
		<< std::dec;
      std::cout << "(init_2: CAL_EN = 0)"<< std::endl;

      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf &= ~0x40)
		<< std::dec;
      std::cout << "(init_3: CAL_EN = 0)"<< std::endl;

      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf &= ~0x40)
		<< std::dec;
      std::cout << "(normal: CAL_EN = 0)"<< std::endl;

      ++i_stream;
    }

    // SPI Stream[60]
    buf = 0x00;

    buf |= (m_spi_adc_vcm_dac[i].VCM_DAC & mask::VCM_DAC_LOWER) << shift::VCM_DAC_LOWER;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);

    if (DEBUG) {
      std::cout << "Stream[" << i_stream << "] ";
      std::cout << "0x"
		<< std::hex
		<< std::setw(2)
		<< std::setfill('0')
		<< static_cast<int>(buf)
		<< std::dec
		<< std::endl;

      ++i_stream;
    }

    fclose(fp_init_0);
    fclose(fp_init_1);
    fclose(fp_init_2);
    fclose(fp_init_3);
    fclose(fp_normal);
  }
}
