#include "cqi-rl-env.h"

namespace ns3 {
CQIRL::CQIRL (uint16_t id) : Ns3AIRL<CqiPredictEnv, CqiPredictAct> (id)
{
  SetCond (2, 0);
}

void
CQIRL::SetWbCQI (uint8_t cqi)
{
  auto env = EnvSetterCond ();
  env->wbCqi = cqi;
  SetCompleted ();
}
uint8_t
CQIRL::GetWbCQI (void)
{
  auto act = ActionGetterCond ();
  uint8_t ret = act->new_wbCqi;
  GetCompleted ();
  return ret;
}

void
CQIRL::SetSbCQI (SbMeasResult_s cqi, uint32_t nLayers)
{
  auto env = EnvSetterCond ();
  uint32_t rbgNum = cqi.m_higherLayerSelected.size ();
  env->rbgNum = rbgNum;
  env->nLayers = nLayers;
  for (uint32_t i = 0; i < rbgNum; ++i)
    {
      for (uint32_t j = 0; j < nLayers; ++j)
        {
          env->sbCqi[i][j] = cqi.m_higherLayerSelected.at (i).m_sbCqi.at (j);
        }
    }
  SetCompleted ();
}
void
CQIRL::GetSbCQI (SbMeasResult_s &cqi)
{
  auto env = EnvGetterCond ();
  auto act = ActionGetterCond ();
  uint32_t rbgNum = env->rbgNum;
  uint32_t nLayers = env->nLayers;

  for (uint32_t i = 0; i < rbgNum; ++i)
    {
      for (uint32_t j = 0; j < nLayers; ++j)
        {
          cqi.m_higherLayerSelected.at (i).m_sbCqi.at (j) = act->new_sbCqi[i][j];
        }
    }
  GetCompleted ();
}
} // namespace ns3
