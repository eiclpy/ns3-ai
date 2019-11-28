#pragma once
#include "ns3/ns3-ai-rl.h"
#include "ff-mac-common.h"

namespace ns3 {
#define MAX_RBG_NUM 32
struct CqiPredictEnv
{
  uint8_t wbCqi;
  uint8_t rbgNum;
  uint8_t nLayers;
  uint8_t sbCqi[MAX_RBG_NUM][2];
};
struct CqiPredictAct
{
  uint8_t new_wbCqi;
  uint8_t new_sbCqi[MAX_RBG_NUM][2];
};
class CQIRL : public Ns3AIRL<CqiPredictEnv, CqiPredictAct>
{
public:
  CQIRL (void) = delete;
  CQIRL (uint16_t id);
  void SetWbCQI (uint8_t cqi);
  uint8_t GetWbCQI (void);
  void SetSbCQI (SbMeasResult_s cqi, uint32_t nLayers);
  void GetSbCQI (SbMeasResult_s &cqi);
};

} // namespace ns3
