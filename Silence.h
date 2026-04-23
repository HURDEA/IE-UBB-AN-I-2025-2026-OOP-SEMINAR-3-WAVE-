#ifndef IE_UBB_AN_I_2025_2026_OOP_SEMINAR_3_WAVE__SILENCE_H
#define IE_UBB_AN_I_2025_2026_OOP_SEMINAR_3_WAVE__SILENCE_H
#include "Wave.h"


class Silence : public AcousticWave {
    void computeSamples(float duration) override;
};



#endif //IE_UBB_AN_I_2025_2026_OOP_SEMINAR_3_WAVE__SILENCE_H
