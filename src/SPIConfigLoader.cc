#include "SPIConfigLoader.hh"

#include<cstdio>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>

static const std::string class_name = "SPIConfigLoader";

//___________________________________________________________
SPIConfigLoader::SPIConfigLoader()
{
  read_EXT_CLK();
  read_SDIF_ADC_CLK_POL();
  read_SDIF_Rn();
  read_ENB_CRC();
  read_OSC_R();
  read_CLK_OUT_POL();
  read_TP_MASK();
  read_AMON();
  read_MPPC_BIAS();
  read_VTH_COMP();
  read_RF_B_SHP();
  read_C_B_SHP();
  read_RIN_B_SHP();
  read_CIN_B_VGA();
  read_CF_B_VGA();

  initialize_SPI_Values();
  make_RegisterValues();
}

//___________________________________________________________
void SPIConfigLoader::read_EXT_CLK()
{
  int i, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_EXT_CLK.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_EXT_CLK.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &i, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: The value of 'setup_EXT_CLK.txt' must be 0 or 1'" << std::endl;
      exit(1);
    }

    if (i < NumOfYaenami) {
      EXT_CLK[i] = value;
    } else {
      std::cerr << "#E: Wrong setup for Number of YAENAMI in 'setup_EXT_CLK.txt''" << std::endl;
      fprintf(stderr, "Error : \n");
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_SDIF_ADC_CLK_POL()
{
  int i, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_SDIF_ADC_CLK_POL.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_SDIF_ADC_CLK_POL.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &i, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: The value of SDIF_ADC_CLK_POL must be 0 or 1" << std::endl;
      exit(1);
    }

    if (i < NumOfYaenami) {
      SDIF_ADC_CLK_POL[i] = value;
    } else {
      std::cerr << "#E: Wrong setup for Number of YAENAMI in 'setup_SIDF_ADC_CLK_POL.txt'" << std::endl;
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_SDIF_Rn()
{
  int i, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_SDIF_Rn.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_SDIF_Rn.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &i, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: The value of 'setup_SDIF_Rn.txt' must be 0 or 1" << std::endl;
      exit(1);
    }

    if (i < NumOfYaenami) {
      SDIF_Rn[i] = value;
    } else {
      std::cerr << "#E: Wrong setup for Number of YAENAMI in 'setup_SDIF_Rn.txt'" << std::endl;
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_ENB_CRC()
{
  int i, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_ENB_CRC.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_ENB_CRC.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &i, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: The value of 'setup_ENB_CRC.txt' must be 0 or 1" << std::endl;
      exit(1);
    }

    if (i < NumOfYaenami) {
      ENB_CRC[i] = value;
    } else {
      std::cerr << "#E: Wrong setup for Number of YAENAMI in 'setup_ENB_CRC.txt'" << std::endl;
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_OSC_R()
{

  int i, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_OSC_R.txt", "r");

  if (!fp) {
    std::cerr << "#E: cannot open the file 'setup_OSC_R.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &i, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: The value of 'setup_OSC_R.txt' must be 0 or 1" << std::endl;
      exit(1);
    }

    if (i < NumOfYaenami) {
      OSC_R[i] = value;
    } else {
      std::cerr << "#E: wrong setup for Number of YAENAMI in 'setup_OSC_R.txt'" << std::endl;
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_CLK_OUT_POL()
{
  int i, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_CLK_OUT_POL.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_CLK_OUT_POL.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &i, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: The value of 'setup_CLK_OUT_POL.txt' must be 0 or 1" << std::endl;
      exit(1);
    }

    if (i < NumOfYaenami) {
      CLK_OUT_POL[i] = value;
    } else {
      std::cerr << "#E: Wrong setup for Number of YAENAMI in 'setup_CLK_OUT_POL.txt'" << std::endl;
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_TP_MASK()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_TP_MASK.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_TP_MASK.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &value);

    if (value == 0 || value == 1) {
    } else {
      std::cerr << "#E: Wrong setup for value in 'setup_TP_MASK.txt'" << std::endl;
      exit(1);
    }

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      TP_MASK[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_TP_MASK.txt'" << std::endl;
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_AMON()
{
  int channel, value;
  char buf[100];
  int count = 0;
  int en_count[4] = {};
  FILE *fp = fopen("./setup/setup_AMON.txt", "r");
  if (!fp) {
    std::cerr << "#E: cannot open the file 'setup_AMON.txt'" << std::endl;
    exit(1);
  }


  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &value);

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      AMON[i][ch] = value;

      if (value == 0) {
      } else if (value == 1) {
	en_count[i] += 1;
      } else {
	std::cerr << "#E: Invalid value in 'setup_AMON.txt'" << std::endl;
	exit(1);
      }

    } else {
      std::cerr << "#E: Wrong setup for ch" <<  i*8 + ch << "in 'setup_AMON.txt'" << std::endl;
      exit(1);
    }
  }

  for (int j = 0; j < NumOfYaenami; ++j) {
    if (en_count[j] == 0 || en_count[j] == 1) {
      continue;
    } else {
      std::cerr << "#E: Cannnot monitor multiple channels: YAENAMI[" << j + 1 << "]" << std::endl;
      exit(1);
    }
  }
}

//___________________________________________________________
void SPIConfigLoader::read_MPPC_BIAS()
{
  int channel, value;
  char buf[100];
  FILE *fp = fopen("./setup/setup_MPPC_BIAS.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_MPPC_BIAS.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &value);

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      MPPC_BIAS[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_MPPC_BIAS.txt'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

//___________________________________________________________
void SPIConfigLoader::read_VTH_COMP()
{
  int channel, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_VTH_COMP.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_VTH_COMP.txt'" << std::endl;
    exit(1);
  }

  while (1) {

    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &value);

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      VTH_COMP[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_VTH_COMP.txt'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

//___________________________________________________________
void SPIConfigLoader::read_RF_B_SHP()
{
  int channel, NumOfR, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_RF_B_SHP.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_RF_B_SHP.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &NumOfR);

    if (NumOfR < 1 || 4 < NumOfR) {
      std::cerr << "#E: Wrong setup for Number of R in 'setup_RF_B_SHP.txt'" << std::endl;
      exit(1);
    }

    if (NumOfR == 1)
      value = 4;

    if (NumOfR == 2)
      value = 2;

    if (NumOfR == 3)
      value = 1;

    if (NumOfR == 4)
      value = 0;

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      RF_B_SHP[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_RF_B_SHP.txt'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

//___________________________________________________________
void SPIConfigLoader::read_C_B_SHP()
{
  int channel, NumOfC, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_C_B_SHP.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_C_B_SHP.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &NumOfC);

    if (0 < NumOfC && NumOfC < 9) {
      value = NumOfC - 1;
    } else {
      std::cerr << "#E: Wrong setup for Number of C in 'setup_C_B_SHP.txt'" << std::endl;
      exit(1);
    }


    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      C_B_SHP[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_C_B_SHP.txt'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

//___________________________________________________________
void SPIConfigLoader::read_RIN_B_SHP()
{
  int channel, NumOfR, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_RIN_B_SHP.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_RIN_B_SHP.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &NumOfR);

    if (NumOfR < 1 || 4 < NumOfR) {
      std::cerr << "#E: Wrong setup for Number of R in 'setup_RIN_B_SHP.txt'" << std::endl;
      exit(1);
    }

    if (NumOfR == 1) {
      value = 4;
    } else if (NumOfR == 2) {
      value = 2;
    } else if (NumOfR == 3) {
      value = 1;
    } else if (NumOfR == 4) {
      value = 0;
    }

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      RIN_B_SHP[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_RIN_B_SHP.txt'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

//___________________________________________________________
void SPIConfigLoader::read_CIN_B_VGA()
{
  int channel, NumOfC, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_CIN_B_VGA.txt", "r");

  if (!fp) {
    std::cerr << "#E: Cannot open the file 'setup_CIN_B_VGA.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &NumOfC);

    if (NumOfC < 1 || 4 < NumOfC) {
      std::cerr << "#E: Wrong setup for Number of C in 'setup_CIN_B_VGA.txt'" << std::endl;
      exit(1);
    }

    if (NumOfC == 1) {
      value = 0;
    } else if(NumOfC == 2) {
      value = 1;
    } else if(NumOfC == 3) {
      value = 3;
    } else if(NumOfC == 4) {
      value = 7;
    }

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      CIN_B_VGA[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_CIN_B_VGA.txt'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

//___________________________________________________________
void SPIConfigLoader::read_CF_B_VGA()
{
  int channel, NumOfC, value;
  char buf[100];

  FILE *fp = fopen("./setup/setup_CF_B_VGA.txt", "r");

  if (!fp) {
    std::cerr << "#E: cannot open the file 'setup_CF_B_VGA.txt'" << std::endl;
    exit(1);
  }

  while (1) {
    if (fgets(buf, sizeof(buf), fp) == NULL)
      break;

    if (buf[0] == '#' || buf[0] == '\n')
      continue;

    sscanf(buf, "%d : %d", &channel, &NumOfC);

    if (0 < NumOfC && NumOfC < 9) {
      value = NumOfC - 1;
    } else {
      std::cerr << "#E: Wrong setup for Number of C in 'setup_CF_B_VGA.txt'" << std::endl;
      exit(1);
    }

    int i = channel / 8;
    int ch = 7 - (channel % 8);

    if (i < NumOfYaenami && ch < NumOfCh) {
      CF_B_VGA[i][ch] = value;
    } else {
      std::cerr << "#E: Wrong setup for channel in 'setup_CF_B_VGA.txt'" << std::endl;
      exit(1);
    }
  }
  fclose(fp);
}

// Above here, fprintf->std::cerr was done, but indent, space was not adjusted. 2026.04.01 18:30
// From here, you must edit initialize sequence

// File4 and normal txt was not adjusted. 2026.04.02 22:30

//___________________________________________________________
void SPIConfigLoader::initialize_SPI_Values()
{
  for (int i = 0; i < NumOfYaenami; ++i) {
    m_SPI_PLL_SDIF[i].EXT_CLK          = EXT_CLK[i];
    m_SPI_PLL_SDIF[i].SDIF_ADC_CLK_POL = SDIF_ADC_CLK_POL[i];
    m_SPI_PLL_SDIF[i].SDIF_Rn          = SDIF_Rn[i];
    m_SPI_PLL_SDIF[i].ENB_CRC          = ENB_CRC[i];
    m_SPI_PLL_SDIF[i].REF_DIV_CONT     = 0b00;
    m_SPI_PLL_SDIF[i].OSC_R            = OSC_R[i];
    m_SPI_PLL_SDIF[i].CLK_OUT_POL      = CLK_OUT_POL[i];
    m_SPI_PLL_SDIF[i].IBAMP            = 0b10;
    m_SPI_PLL_SDIF[i].IBCP             = 0b10;
    m_SPI_PLL_SDIF[i].OSC_CONT         = 0b0000;
    m_SPI_PLL_SDIF[i].OSC_EN           = 0b1;
    m_SPI_PLL_SDIF[i].DIV_CONT         = 0b00;
    m_SPI_PLL_SDIF[i].N_CONT           = 0b01000;
  }

  for (int i = 0; i < NumOfYaenami; ++i) {
    for (int ch = 0; ch < NumOfCh; ++ch) {
      m_SPI_CH[i][ch].ADC_R         = 0b0;
      m_SPI_CH[i][ch].ASD_CLK_EN    = 0b0;
      m_SPI_CH[i][ch].GC_BUF        = 0b01;
      m_SPI_CH[i][ch].TP_MASK       = TP_MASK[i][ch];
      m_SPI_CH[i][ch].AMON          = AMON[i][ch];
      m_SPI_CH[i][ch].MPPC_BIAS     = MPPC_BIAS[i][ch];
      m_SPI_CH[i][ch].VTH_COMP      =  VTH_COMP[i][ch];
      m_SPI_CH[i][ch].MON_SEL       = 0b01;
      m_SPI_CH[i][ch].MIN_PULSE_SEL = 0b0;
      m_SPI_CH[i][ch].DO_POL        = 0b0;
      m_SPI_CH[i][ch].COMP_POL      = 0b0;
      m_SPI_CH[i][ch].DELAY_F       = 0b0100;
      m_SPI_CH[i][ch].DELAY_C       = 0b100;
      m_SPI_CH[i][ch].RF_B_SHP      = RF_B_SHP[i][ch];
      m_SPI_CH[i][ch].C_B_SHP       = C_B_SHP[i][ch];
      m_SPI_CH[i][ch].RIN_B_SHP     = RIN_B_SHP[i][ch];
      m_SPI_CH[i][ch].CIN_B_VGA     = CIN_B_VGA[i][ch];
      m_SPI_CH[i][ch].R_B_VGA       = 0b000;
      m_SPI_CH[i][ch].CF_B_VGA      = CF_B_VGA[i][ch];
      m_SPI_CH[i][ch].ASD_R         = 0b00;
    }
  }

  for (int i = 0; i < NumOfYaenami; ++i) {
    m_SPI_ADC_VCM_DAC[i].NC1       = 0b0;
    m_SPI_ADC_VCM_DAC[i].CAL_EN    = 0b0;
    m_SPI_ADC_VCM_DAC[i].CAL_REG_R = 0b0;
    m_SPI_ADC_VCM_DAC[i].SAM_WD    = 0b01;
    m_SPI_ADC_VCM_DAC[i].NC2       = 0b0;
    m_SPI_ADC_VCM_DAC[i].VCM_DAC   = 0b1000000000;
  }
}

//___________________________________________________________
void SPIConfigLoader::make_RegisterValues()
{
  uint8_t buf;
  std::ostringstream oss_init_0, oss_init_1, oss_init_2, oss_init_3;
  std::ostringstream oss_normal;

  for (int i = 0; i < NumOfYaenami; ++i) {

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

    // PLL, SDIF block
    // from EXT_CLK to CLK_OUT_POL
    buf = 0x00;

    buf |= (m_SPI_PLL_SDIF[i].EXT_CLK          & EXT_CLK_mask)          << EXT_CLK_shift;
    buf |= (m_SPI_PLL_SDIF[i].SDIF_ADC_CLK_POL & SDIF_ADC_CLK_POL_mask) << SDIF_ADC_CLK_POL_shift;
    buf |= (m_SPI_PLL_SDIF[i].SDIF_Rn          & SDIF_Rn_mask)          << SDIF_Rn_shift;
    buf |= (m_SPI_PLL_SDIF[i].ENB_CRC          & ENB_CRC_mask)          << ENB_CRC_shift;
    buf |= (m_SPI_PLL_SDIF[i].REF_DIV_CONT     & REF_DIV_CONT_mask)     << REF_DIV_CONT_shift;
    buf |= (m_SPI_PLL_SDIF[i].OSC_R            & OSC_R_mask)            << OSC_R_shift;
    buf |= (m_SPI_PLL_SDIF[i].CLK_OUT_POL      & CLK_OUT_POL_mask)      << CLK_OUT_POL_shift;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);

    // from IBAMP to IBCP
    buf = 0x00;

    buf |= (m_SPI_PLL_SDIF[i].IBAMP    & IBAMP_mask)    << IBAMP_shift;
    buf |= (m_SPI_PLL_SDIF[i].IBCP     & IBCP_mask)     << IBCP_shift;
    buf |= (m_SPI_PLL_SDIF[i].OSC_CONT & OSC_CONT_mask) << OSC_CONT_shift;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);

    // from OSC_EN to N_CONT
    buf = 0x00;

    buf |= (m_SPI_PLL_SDIF[i].OSC_EN   & OSC_EN_mask)   << OSC_EN_shift;
    buf |= (m_SPI_PLL_SDIF[i].DIV_CONT & DIV_CONT_mask) << DIV_CONT_shift;
    buf |= (m_SPI_PLL_SDIF[i].N_CONT   & N_CONT_mask)   << N_CONT_shift;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);


    // ch block
    for (int ch = 0; ch < NumOfCh; ++ch) {
      // from ADC_R to upper 2bits of MPPC_BIAS
      buf = 0x00;

      buf |= (m_SPI_CH[i][ch].ADC_R      & ADC_R_mask)      << ADC_R_shift;
      buf |= (m_SPI_CH[i][ch].ASD_CLK_EN & ASD_CLK_EN_mask) << ASD_CLK_EN_shift;
      buf |= (m_SPI_CH[i][ch].GC_BUF     & GC_BUF_mask)     << GC_BUF_shift;
      buf |= (m_SPI_CH[i][ch].TP_MASK    & TP_MASK_mask)    << TP_MASK_shift;
      buf |= (m_SPI_CH[i][ch].AMON       & AMON_mask)       << AMON_shift;
      buf |= (m_SPI_CH[i][ch].MPPC_BIAS  & MPPC_BIAS1_mask) >> MPPC_BIAS1_shift;

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

      // lower 8bits of MPPC_BIAS
      buf = 0x00;

      buf |= (m_SPI_CH[i][ch].MPPC_BIAS & MPPC_BIAS2_mask) << MPPC_BIAS2_shift;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      // upper 8bits of VTH_COMP
      buf = 0x00;

      buf |= (m_SPI_CH[i][ch].VTH_COMP & VTH_COMP1_mask) >> VTH_COMP1_shift;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      // from lower 2bits of VTH_COMP to upper 1bit of DELAY_F
      buf = 0x00;

      buf |= (m_SPI_CH[i][ch].VTH_COMP      & VTH_COMP2_mask)     << VTH_COMP2_shift;
      buf |= (m_SPI_CH[i][ch].MON_SEL       & MON_SEL_mask)       << MON_SEL_shift;
      buf |= (m_SPI_CH[i][ch].MIN_PULSE_SEL & MIN_PULSE_SEL_mask) << MIN_PULSE_SEL_shift;
      buf |= (m_SPI_CH[i][ch].DO_POL        & DO_POL_mask)        << DO_POL_shift;
      buf |= (m_SPI_CH[i][ch].COMP_POL      & COMP_POL_mask)      << COMP_POL_shift;
      buf |= (m_SPI_CH[i][ch].DELAY_F       & DELAY_F1_mask) >> DELAY_F1_shift;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      // from lower 3bits of DELAY_F to upper 2bits of RF_B_SHP
      buf = 0x00;

      buf |= (m_SPI_CH[i][ch].DELAY_F  & DELAY_F2_mask) << DELAY_F2_shift;
      buf |= (m_SPI_CH[i][ch].DELAY_C  & DELAY_C_mask)  << DELAY_C_shift;
      buf |= (m_SPI_CH[i][ch].RF_B_SHP & RF_B_SHP1_mask) >> RF_B_SHP1_shift;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      // from the lowest bit of RF_B_SHP to MSB of CIN_B_VGA
      buf = 0x00;

      buf |= (m_SPI_CH[i][ch].RF_B_SHP  & RF_B_SHP2_mask) << RF_B_SHP2_shift;
      buf |= (m_SPI_CH[i][ch].C_B_SHP   & C_B_SHP_mask)   << C_B_SHP_shift;
      buf |= (m_SPI_CH[i][ch].RIN_B_SHP & RIN_B_SHP_mask) << RIN_B_SHP_shift;
      buf |= (m_SPI_CH[i][ch].CIN_B_VGA & CIN_B_VGA1_mask) >> CIN_B_VGA1_shift;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);

      // from lower 2bits of CIB_B_VGA to CF_B_VGA
      buf = 0x00;

      buf |= (m_SPI_CH[i][ch].CIN_B_VGA & CIN_B_VGA2_mask) << CIN_B_VGA2_shift;
      buf |= (m_SPI_CH[i][ch].R_B_VGA   & R_B_VGA_mask)    << R_B_VGA_shift;
      buf |= (m_SPI_CH[i][ch].CF_B_VGA  & CF_B_VGA_mask)   << CF_B_VGA_shift;

      fprintf(fp_init_0, "0x%02x\n", buf);
      fprintf(fp_init_1, "0x%02x\n", buf);
      fprintf(fp_init_2, "0x%02x\n", buf);
      fprintf(fp_init_3, "0x%02x\n", buf);
      fprintf(fp_normal, "0x%02x\n", buf);
    }

    // ADC, VCM_DAC block
    // from NC1 to upper 2bits of VCM_DAC
    buf = 0x00;

    buf |= (m_SPI_ADC_VCM_DAC[i].NC1       & NC1_mask)       << NC1_shift;
    buf |= (m_SPI_ADC_VCM_DAC[i].CAL_EN    & CAL_EN_mask)    << CAL_EN_shift;
    buf |= (m_SPI_ADC_VCM_DAC[i].CAL_REG_R & CAL_REG_R_mask) << CAL_REG_R_shift;
    buf |= (m_SPI_ADC_VCM_DAC[i].SAM_WD    & SAM_WD_mask)    << SAM_WD_shift;
    buf |= (m_SPI_ADC_VCM_DAC[i].NC2       & NC2_mask)       << NC2_shift;
    buf |= (m_SPI_ADC_VCM_DAC[i].VCM_DAC   & VCM_DAC1_mask) >> VCM_DAC1_shift;

    fprintf(fp_init_0, "0x%02x\n", buf |=  0x40); // Assert ADC Calibration
    fprintf(fp_init_1, "0x%02x\n", buf &= ~0x40); // De-asser ADC Calibration
    fprintf(fp_init_2, "0x%02x\n", buf &= ~0x40); // ADC Calibration must be 0
    fprintf(fp_init_3, "0x%02x\n", buf &= ~0x40); // ADC Calibration must be 0
    fprintf(fp_normal, "0x%02x\n", buf &= ~0x40); // Normal mode, ADC Calibration must be 0

    //lower 8bits of VCM_DAC
    buf = 0x00;

    buf |= (m_SPI_ADC_VCM_DAC[i].VCM_DAC & VCM_DAC2_mask) << VCM_DAC2_shift;

    fprintf(fp_init_0, "0x%02x\n", buf);
    fprintf(fp_init_1, "0x%02x\n", buf);
    fprintf(fp_init_2, "0x%02x\n", buf);
    fprintf(fp_init_3, "0x%02x\n", buf);
    fprintf(fp_normal, "0x%02x\n", buf);

    fclose(fp_init_0);
    fclose(fp_init_1);
    fclose(fp_init_2);
    fclose(fp_init_3);
    fclose(fp_normal);
  }
}
